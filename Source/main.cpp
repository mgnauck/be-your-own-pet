#include "Intro.h"
#include "minifmod/minifmod.h"
#include "GLContext.h"
#include "EffectPlayer.h"

// 20110501/supah: replaced this for non-console windowed version :) 
//int main(int argc, char* argv[]) {
int PASCAL WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int show) { 

	Window			window(RESX, RESY, BPP, TITLE, FULLSCREEN);
	GLContext		glc(window);
	EffectPlayer	effectPlayer;

	glc.setDefaultParameters();

	FSOUND_File_SetCallbacks(memopen, memclose, memread, memseek, memtell);
	FMUSIC_MODULE* mod = FMUSIC_LoadSong("", 0);
	FMUSIC_PlaySong(mod);

	float startTime = (float) FMUSIC_GetTime(mod); // timeGetTime();
	while(window.active() && effectPlayer.isRunning()) {

		//float time	= (float)timeGetTime() - startTime;
		float time = FMUSIC_GetTime(mod) - startTime;

		effectPlayer.run(time);

		glc.flush();
	}

	FMUSIC_StopSong(mod);

	return 0;
}


		/*

  	float timeFPS = startTime;
	int lastPattern = -1; 
	float lastPatternTimeMS = 0.f;
	float lastPatternTimeSwitchMS = 0.f;


		// temp
		int order = FMUSIC_GetOrder(mod);
		if(lastPattern != order)
		{
			lastPattern = order;
			lastPatternTimeMS = time - lastPatternTimeSwitchMS;
			lastPatternTimeSwitchMS = time;

			//timedump
			FILE *tmp = fopen("c:/timedump.txt", "at");
			fprintf(tmp, "pattern 0x%02x :: %4.2f\t fps :: %4.2f\t ms :: %4.2f\t ms/pattern\n", 
					order, window.getFPS(), time, lastPatternTimeMS);
			fclose(tmp);
		}

		if(time - timeFPS >= 250.f)
		{
			char buf[256];
			sprintf(buf, "%4.2f fps :: %4.2f ms :: %4.2f ms/pattern", 
					window.getFPS(), time, lastPatternTimeMS);
			SetWindowText(window.hwnd(), buf);
			timeFPS -= time; //timeGetTime();
		}*/
