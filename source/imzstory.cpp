#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "b90s/utils.h"
#include "bwz.h"

u8 imStoryFunc(){
    PA_ResetAll();
    PA_SetBrightness(1,0);
    PA_SetBrightness(0,0);
    PA_InitText(0,0);
    B90SR_PW_OutputBoxText(0,0,0,3,"Hey you.");
    PA_Sleep(1);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,3,"While you were stuck in Colorful Caverns.");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,3,"The evil has taken over everyone's minds.");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    PA_SetTextCol(0,31,0,0);
    B90SR_PW_OutputBoxText(0,0,0,7,"Do not let him laugh at you.");
    PA_Sleep(2);
    PA_ResetAll();
    bdwz1Func();
    return 0;
}