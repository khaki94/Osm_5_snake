//
// main.c
//

#include "main.h"
#include "stdio.h"


#ifdef RPiLAB_WIN
char credits[51]="        RPiLAB                DEMO                ";
#endif
long TimerIsrPeriod = 1;            //czas podany w milisekundach

#define MaxObj 10000
int dx[MaxObj];
int dy[MaxObj];
int s[MaxObj];
int x[MaxObj];
int y[MaxObj];
int xt[MaxObj];
int yt[MaxObj];

unsigned long* SCREEN;
unsigned long SCREENBUF[640 * 480];
int mode = 0;
int stage = 0;
int frame_count = 0;
int Jxt = 0, Jyt = 0, Jx = 0, Jy = 0, Jz = 0, JRz = 0;

// moje zmienne
Player player(SCREENBUF);
Map map(SCREENBUF);

bool frame = true;
int counter;

Player::Direction GetKey()
{
	if(getKey() == 96 )
		return Player::UP;
	if(getKey() == 92 )
		return Player::LEFT;
	if(getKey() == 0 )
		return Player::DOWN;
	if(getKey() == 94 )
		return Player::RIGHT;
	return Player::NONE;
}

int main(void) {


	if (SystemInit())		return EXIT_HALT;
	DataPrepare();
	while (1) {
		if (UpdateIO())	return 0;
		PrintDiagnosticInfo();
		Synchronize();
		ClearScreen();

		if( frame )
		{
			// mapa
			map.UpdateMap();
			map.UpdateSprite();
			// player
		}

		map.DrawMap();
		player.Draw();

	}
}

volatile long presc = 0;

void TimerIsr() {
	presc++;
	if ((presc / 250) % 2)
		RegisterSet(GPSET1, 1 << (35 - 32));
	else
		RegisterSet(GPCLR1, 1 << (35 - 32));
	if ((presc / 500) % 2)
		RegisterSet(GPSET1, 1 << (47 - 32));
	else
		RegisterSet(GPCLR1, 1 << (47 - 32));
	if( counter++ < (250 - player.GetSpeed()*25) )
	{
		frame = true;
		counter = 0;
	}
}

void DrawObjects() {
	unsigned long* GRAPH = SCREENBUF;
	Jx = (Jx * 93 + 7 * JoYAct.AxisX) / 100;
	Jy = (Jy * 93 + 7 * JoYAct.AxisY) / 100;
	Jz = (Jz * 93 + 7 * ((JoYAct.ButtonStates & BUTTON_2 ? -128 : 0) + (JoYAct.ButtonStates & BUTTON_4 ? 127 : 0))) / 100;
	JRz = (JRz * 93 + 7 * ((JoYAct.ButtonStates & BUTTON_1 ? -128 : 0) + (JoYAct.ButtonStates & BUTTON_3 ? 127 : 0))) / 100;

	for (int c = 0; c < MaxObj; c++) {
		int srt = abs(dy[c]) + abs(dx[c]);
		for (int g = 0; g < srt / 10 + 1; g++) {
			int ddf = 20;
			ddf += -(JRz) / (srt + 1);
			if (ddf < 8)
				ddf = 8;
			y[c] += (ddf * dy[c]) / 30 + (Jyt - Jy) * srt / 20;
			x[c] += (ddf * dx[c]) / 30 + (Jxt - Jx) * srt / 20;
			y[c] -= ((xt[c] - x[c]) * Jz) / 200;
			x[c] += ((yt[c] - y[c]) * Jz) / 200;
			xt[c] = x[c];
			yt[c] = y[c];
			if (x[c] < 0 || y[c] < 0 || x[c] > 639 * 16 - s[c] || y[c] > 479 * 16 - s[c]) {
				do {
					s[c] = randr(0x1f) + 1;
					xt[c] = x[c] = randr(519 * 16 - s[c]) + 60 * 16;
					yt[c] = y[c] = randr(379 * 16 - s[c]) + 50 * 16;
					int spd = randr(15) + 7;
					dx[c] = (x[c] - 320 * 16 - 16 * Jx - (Jx - Jxt) / 2) * spd;
					dy[c] = (y[c] - 240 * 16 - 16 * Jy - (Jy - Jyt) / 2) * spd;

					while (abs(dx[c]) > (-JRz / 5 + 40) || abs(dy[c]) > (-JRz / 5 + 35)) {
						dx[c] /= 3;
						dy[c] /= 3;
					}
				} while ((abs(dy[c]) + abs(dx[c])) <= 8);
			}
			int size = s[c];

			int col = (y[c] * 255 / (480 << 4)) + 0xf0000 * size + (0x100 * ((x[c] * 255 / (640 << 4))));

			for (int b = y[c] >> 4; b < (y[c] + size) >> 4; b++)
				for (int a = x[c] >> 4; a < (x[c] + size) >> 4; a++)
					SetPixel(GRAPH, a, b, col);
		}
	}
	Jxt = Jx;
	Jyt = Jy;

}
void ClearScreen() {
	unsigned long bckgcol = 0;
	if (JoYAct.ButtonStates & BUTTON_L1)
		bckgcol = 0x3f0000;
	if (JoYAct.ButtonStates & BUTTON_L2)
		bckgcol = 0x3f00;
	if (JoYAct.ButtonStates & BUTTON_R1)
		bckgcol = 0x3f;
	if (JoYAct.ButtonStates & BUTTON_R2)
		bckgcol = 0x3f3f3f;
	int stage_max = getKey() - KEY_1 + 1;

	if (stage_max < 2)
		stage_max = 2;
	if (stage_max > 9)
		stage_max = 9;

	if (JoYAct.ButtonStates & BUTTON_SELECT)
		stage_max = 24;
	unsigned long* GRAPH = SCREENBUF;
	stage++;
	for (int a = stage % stage_max; a < (640 * 480); a += stage_max) {
		SCREEN[a] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1) | bckgcol;
	}
}
void PrintDiagnosticInfo() {
	frame_count++;
#ifdef RPiLAB_RPi
	TString strbuf;
	String(&strbuf);
	StringFormat(&strbuf, "%d: %d, %d, %d, %x\r\n", frame_count, getKey(), Jx, Jy, JoYAct.ButtonStates);
	if ((frame_count % 20) == 0)
		StringUart(StringGet(&strbuf));
	_String(&strbuf);
#endif

#ifdef RPiLAB_WIN
	char strbuf[1000];
	sprintf(strbuf,"%i: %i, %i, %i, %x\r\n",frame_count,getKey(), Jx, Jy,JoYAct.ButtonStates);
	if((frame_count%20)==0) StringUart(strbuf);
#endif
}
void DataPrepare() {
	for (unsigned char a = 0; a < sizeof(struct JoY); a++)
		((char*) &JoYAct)[a] = 0;

	for (int a = 0; a < MaxObj; a++) {
		do {
			s[a] = randr(0x1f) + 1;
			xt[a] = x[a] = randr(519 * 16 - s[a]) + 60 * 16;
			yt[a] = y[a] = randr(379 * 16 - s[a]) + 50 * 16;
			int spd = randr(15) + 7;
			dx[a] = (x[a] - 320 * 16) * spd;
			dy[a] = (y[a] - 240 * 16) * spd;

			while (abs(dx[a]) > (40) || abs(dy[a]) > (35)) {
				dx[a] /= 3;
				dy[a] /= 3;
			}
		} while ((abs(dy[a]) + abs(dx[a])) <= 2);
	}
}
#ifdef RPiLAB_RPi

void TimerHandler(unsigned hTimer, void *pParam, void *pContext) {
	TimerIsr();
	StartKernelTimer(TimerIsrPeriod, TimerHandler, (void *) 0, (void *) 0);
}
unsigned long timeElapse = 0;
void Synchronize() {
	while (*((volatile unsigned long*) ARM_SYSTIMER_CLO) - timeElapse < 20 * CLOCKHZ / 1000)
		;
	timeElapse = *((volatile unsigned long*) ARM_SYSTIMER_CLO);
}

int SystemInit() {

	RegisterAccess(GPFSEL4, ~(7 << 21), 1 << 21); // Wartoœci ustawiaj¹ce tryby dzia³ania portow IO nale¿y ustalac z duza rozwaga !!!
	RegisterAccess(GPFSEL3, ~(7 << 15), 1 << 15); // Wartoœci ustawiaj¹ce tryby dzia³ania portow IO nale¿y ustalac z duza rozwaga !!!

	if (!USPiEnvInitialize())
		return -1;
	ScreenDeviceClearDisplay(USPiEnvGetScreen());
	if (!USPiInitialize()) {
		LogWrite("USPi Error", LOG_ERROR, "Cannot initialize USPi");
		USPiEnvClose();
		return -1;
	}

	StartKernelTimer(TimerIsrPeriod, TimerHandler, (void *) 0, (void *) 0);

	USPiKeyboardRegisterKeyStatusHandlerRaw(KeyboardHandlerA);
	USPiGamePadRegisterStatusHandler(GamePadStatusHandlerA);
	uart_init();
	TScreenDevice* screen = USPiEnvGetScreen();
	SCREEN = (unsigned long*) screen->m_pBuffer;
	timeElapse = *((volatile unsigned long*) ARM_SYSTIMER_CLO);
	return 0;
}

int UpdateIO() {
	USPiGamePadGetStatus(0);
	return 0;
}

#endif

#ifdef RPiLAB_WIN

int SystemInit()
{
	RegisterAccess(GPFSEL4,~(7<<21),1<<21);
	RegisterAccess(GPFSEL3,~(7<<15),1<<15);
	return 0;
}
int UpdateIO()
{
	GamePadGetStatus();
	KeyboardGetStatus();
	return SimulatorUpdate();
}
#endif

