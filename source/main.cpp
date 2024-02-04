#include <PA9.h>
#include "MainMenu.h"
#include "debug.h"
#include "all_gfx.h"
#include "common.h"
#include <unistd.h>

int main(){
    PA_Init();
    PA_InitText(1,0);
	PA_VBLFunctionInit(AS_SoundVBL);
	AS_Init(AS_MODE_MP3 | AS_NO_DELAY | AS_MODE_16CH);
	AS_SetDefaultSettings(AS_PCM_8BIT, 8000, AS_NO_DELAY);
    if(!nitroFSInit()){
        PA_OutputSimpleText(1,0,0,"NitroFS error.");
        while(1)PA_WaitForVBL();
    }
    chdir("nitro:/");
    PA_SetBrightness(1,0);
    PA_SetBrightness(0,0);
    MainMenu();

    return 0;
}