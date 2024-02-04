#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "objects.h"
#include "imz.h"
#include "sbz.h"
#include "b90s/utils.h"

static APlayer Player;
static u8 crystal_counter = 0;
static int timerms = 0;
static int timer = 0;

static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 420;
    Player.g = 0;
    Player.UpdateBg();
    Player.Update();
    timer = 0;
    timerms =0;
    PA_CFadeInSys();
    return 0;
}

void sbz3Cutscene(){
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
    PA_SetRotset(1,1,0,194,192);
    PA_SetRotset(1,0,0,194,192);
    PA_CFadeInSys();
    B90SR_PW_OutputBoxText(0,0,0,2,"???: Hey slaves, is prototype MD-2201 ready? I gotta go kill some random kid.");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,2,"???: The kid dresses up gray and has some orange in it with a brown hair and black eyes, the only one that wasn't controlled by the master emerald, I gotta go.");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    PA_SetRotset(1,1,0,-194,192);
    B90SR_PW_OutputBoxText(0,0,0,2,"???: Wait there is no way you little rat already got here, what are you gonna do, fight me?");
    PA_Sleep(2);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,2,"Darnell: Too easy, give me something harder Hashimoto-san!");    PA_Sleep(3);
    PA_Sleep(2);
    PA_ClearTextBg(0);
    B90SR_PW_OutputBoxText(0,0,0,2,"???: My name is Josue, not Hashimoto-San, I do not care why you are here but since you are I gotta kill you.");
    PA_Sleep(2);
    PA_CFadeOutSys();
}
u8 sbz3Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    PA_OutputSimpleText(1,10,12,"FINAL ZONE.");
   PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
//    FAT_LoadBackground(1,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp2");
//    FAT_LoadBackground(0,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp2c");
    PA_LoadBackground(1,2,&tilemap3);
    PA_LoadBackground(0,2,&tilemap3c);
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,30,420,1,4,3,2,4);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_SetSpritePrio(1,0,2);
    AS_MP3StreamPlay("nitro:/data/music/sbz.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgx < 0) player_bgx = 0;
        else if(player_bgx > 864) player_bgx = 864;

        if(player_bgy < 0)player_bgy = 0;
        else if(player_bgy > 288) player_bgy = 288;
        Player.Update();
        if(Player.x < 0) Player.x = 0;
        if(Player.x > 792) {
            PA_CFadeOutSys();
            PA_ResetAll();
            sbz3Cutscene();
            sbzBossFunc(false);
            return 0;
        }
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        timerms ++;
        if(timerms >= 60){
            timer ++;
            timerms = 0;
        }
        if(Pad.Newpress.Start) {
            PA_WaitForVBL();
            PA_WaitFor(Pad.Newpress.Start);
        }
        PA_ClearTextBg(0);
        PA_OutputText(0,10,10,"Crystals: %d\n\n\nTimer:%d ",crystal_counter,timer);
        PA_WaitForVBL();
    }
    return 0;
}