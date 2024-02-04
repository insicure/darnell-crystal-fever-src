#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "objects.h"
#include "imz.h"
#include "sbz.h"
#include "b90s/utils.h"
#include "credits.h"
static APlayer Player;
static int timerms = 0;

static void death(){
    PA_CFadeOutSys();
    sbzBossFunc(false);
}
static void sbzBossCutscene(){
    PA_ResetAll();
    PA_InitText(0,0);
    PA_LoadBackground(1,3,&finalcutscene);
    PA_LoadSprite16cPal(1,1,(void*)josue_Pal);
    PA_LoadSpritePal(1,0,(void*)dar_Pal);
    PA_CreateSprite(1,1,(void*)josue_Sprite,OBJ_SIZE_16X32,0,1,200,106);
    PA_CreateSprite(1,0,(void*)dar_Sprite,OBJ_SIZE_16X32,1,0,30,106);
    PA_SetSpriteRotEnable(1,1,1);
    PA_SetSpriteDblsize(1,1,1);
    PA_SetSpriteRotEnable(1,0,0);
    PA_SetSpriteDblsize(1,0,1);
    PA_SetRotset(1,1,0,-194,192);
    PA_SetRotset(1,0,0,194,192);
    PA_CFadeInSys();
    B90SR_PW_OutputBoxText(0,0,0,1,"Josue: I got a button to destroy the base.");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,6,"Darnell: Great! See you in hell!");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    PA_DeleteSprite(1,0);
    B90SR_PW_OutputBoxText(0,0,0,1,"Josue: Where did he go?.");
    PA_CFadeOutSys();
    PA_ResetAll();
    PA_InitText(0,0);
    AS_MP3Stop();
    B90SR_PW_OutputBoxText(0,0,0,6,"One base explosion later...");
    PA_Sleep(3);
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bw/bgscr");
    PA_LoadBackground(1,2,&actcutscene);
    PA_CFadeInSys();
    u8 angle = 0;
    PA_CreateSprite(1,0,(void*)dar_Sprite,OBJ_SIZE_16X32,1,0,30,-32);
    PA_SetSpriteRotEnable(1,0,0);
    PA_SetSpriteDblsize(1,0,1);
    PA_SetRotset(1,0,0,194,192);
    PA_SetSpritePrio(1,0,3);
    for(int y = -32; y < 192; y ++){
        angle ++;
        PA_SetSpriteXY(1,0,30,y);
        PA_SetRotset(1,0,angle,194,192);
        PA_WaitForVBL();
    }
    PA_SetSpriteXY(1,0,30,107);
    PA_SetRotset(1,0,0,194,192);
    PA_Sleep(2);
    PA_CFadeOutSys();
    STAFF_CREDITS();
}

u8 sbzBossFunc(bool gocutscene){
    if(gocutscene == true) {
        sbzBossCutscene();
        return 0;
    }
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_ResetAll();
//    FAT_LoadBackground(1,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp2");
//    FAT_LoadBackground(0,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp2c");
    PA_LoadBackground(1,2,&finalcutscene);
    PA_LoadBackground(0,2,&finalcutscenec);
    
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,32,64,1,4,3,2,4);
    PA_SetSpritePrio(1,0,2);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    AS_MP3StreamPlay("nitro:/data/music/sbb.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    u8 bglasers = 0;
    while(1){
        Player.Move();
        Player.Gravity();
        Player.UpdateBg();
        player_bgx = 0;
        player_bgy = 0;
        Player.Update();
        timerms ++;
        if(timerms == 60){
            bglasers ++;
            PA_DeleteBg(1,1);
            switch(bglasers){
                case 1:
                PA_LoadBackground(1,1,&lasersbg1);
                break;
                case 2:
                PA_LoadBackground(1,1,&lasersbg2);
                break;
                case 3:
                PA_LoadBackground(1,1,&lasersbg3);
                break;
                case 4:
                PA_LoadBackground(1,1,&lasersbg4);
                break;
                case 5:
                sbzBossCutscene();
                return 0;
                break;
            }
        }
        else if(timerms == 120){
            PA_SetBgPalNCol(1,1,0,1,PA_RGB(31,0,0));
        }
        else if(timerms > 140) {
            PA_DeleteBg(1,1);
            timerms = 0;
        }
        else if(timerms > 130 && bglasers == 4) PA_DeleteBg(1,1);
        if(timerms>120&&
        (((Player.x < 138||Player.x > 200 )&&bglasers==1)||
        ((Player.x < 56||Player.x > 118 )&&bglasers==2)||
        ((Player.x < 102||Player.x > 154 )&&bglasers==3)||
        ((Player.y > 122&&timerms <140)&&bglasers==4))){
            death();
            return 0;
        }
        if(Pad.Newpress.Start) {
            PA_WaitForVBL();
            PA_WaitFor(Pad.Newpress.Start);
        }
        PA_ClearTextBg(0);
        PA_WaitForVBL();
    }
    return 0;
}