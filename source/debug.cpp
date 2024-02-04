#include <PA9.h>
#include "fdz.h"
#include "debug.h"
#include "bwz.h"
#include "ccz.h"
#include "all_gfx.h"
#include "imz.h"
#include "sbz.h"
#include "credits.h"

void debugMenu(){
    u8 select = 0;
    PA_ResetAll();
    PA_InitText(1,0);
    PA_InitText(0,0);
    PA_OutputSimpleText(1,0,0,"YOU UNLOCKED THE CHEAT CODE NOOO\n\nB90sR debugmenu\nB90sR ver 1\n\nGame Data:\nGameVer: 202308221117\nGameCN:DCF\n");
    while(1){
        select += Pad.Newpress.Down - Pad.Newpress.Up;
        select += (Pad.Newpress.Right - Pad.Newpress.Left) * 5;
        PA_ClearTextBg(0);
        PA_OutputSimpleText(0,0,select,">");
        PA_OutputSimpleText(0,1,0,"fdz1\nfdz2\nfdz3\nbwz1\nbwz2\nccz1\nccz2\nccz3\nhpz1\nbwpt\ndwa1\ndwa2\nsbza1\nsbza2\nFINAL ZONE.\nfinal boss\nfnc\nCREDITS");
        
        if(Pad.Newpress.A){
            switch(select){
                case 0:
                fdz1Func();
                return;
                break;
                case 1:
                fdz2Func();
                return;
                break;
                case 2:
                fdz3Func();
                return;
                break;
                case 3:
                bwz1Func();
                return;
                break;
                case 4:
                bwz2Func();
                return;
                case 5:
                ccz1Func();
                return;
                break;
                case 6:
                ccz2Func();
                return;
                break;
                case 7:
                imz1Func();
                return;
                break;
                case 8:
                imz2Func();
                return;
                break;
                case 9:
                imStoryFunc();
                return;
                break;
                case 10:
                bdwz1Func();
                return;
                break;
                case 11:
                bdwz2Func();
                return;
                break;
                case 12:
                sbz1Func();
                return;
                case 13:
                sbz2Func();
                return;
                case 14:
                sbz3Func();
                return;
                break;
                case 15:
                sbzBossFunc(false);
                return;
                break;
                case 16:
                sbzBossFunc(true);
                return;
                break;
                case 17:
                STAFF_CREDITS();
                return;
                break;
            }
        }
        PA_WaitForVBL();
    }
}