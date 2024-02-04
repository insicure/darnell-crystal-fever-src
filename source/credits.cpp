#include <PA9.h>
#include "b90s/utils.h"
#include "MainMenu.h"
#include "all_gfx.h"

u8 STAFF_CREDITS(){
    PA_ResetAll();
    PA_InitText(0,0);
    PA_InitText(1,0);
    PA_OutputSimpleText(0,1,10,"Darnell: Crystal Fever Credits.");
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,8,10,"Main Programmer: \n\n  AerGlass.");
    PA_LoadBackground(1,3,&programmingdesign);
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_DeleteBg(1,3);
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,8,10,"Level Designer: \n\n  AerGlass.");
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,8,10,"Music Composer: \n\n  DesCube");
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,8,10,"Art Design: \n\nAerGlass\nGretel Morris\nClydeCheese");
    PA_LoadBackground(1,3,&artdesigncreditsbg);
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_DeleteBg(1,3);
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,8,10,"Director: \n\nAerGlass\nGretel Morris");
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_OutputSimpleText(0,8,10,"Special Thanks: \n\nJosue Tam\nGretel Morris\nQuilt\nlifehackerhansol\nRocketRobz\ndevkitPro\nPAlib");
    PA_CFadeInSys();
    PA_Sleep(2);
    PA_CFadeOutSys();
    PA_ClearTextBg(0);
    PA_OutputSimpleText(0,10,10,"The End.");
    PA_OutputSimpleText(0,0,12,"Thank you so much for playing \nour game.");
    PA_SetTextCol(1,5,5,5);
    PA_OutputSimpleText(1,0,0,"Press Start\nL+R+START");
    PA_CFadeInSys();
    PA_WaitFor(Pad.Newpress.A);
    PA_CFadeOutSys();
     MainMenu();
    return 0;
}
