#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "bwz.h"
static APlayer Player;
static ACannon Cannon[4];
static u8 crystal_counter;
static int timer = 0;
static int timerms =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 2;
    Player.y = 660;
    Player.g = 0;
    timer = 0;
    Player.UpdateBg();
    Player.Update();
    for(u8 i = 0; i <= 3; i ++) {
        Cannon[i].ReActivate(); 
    }
    PA_CFadeInSys();
    return 0;
}
static void rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystal_counter,timer);
    if(timer < 20) PA_OutputSimpleText(1,0,0,"S Rank WOW");
    else PA_OutputSimpleText(1,0,0,"B Rank.");
    PA_Sleep(3);
    return;
}
u8 bdwz1Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    AS_MP3Stop();
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Lost World Act 1");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bdw/bgr");
    FAT_LoadBackground(1,1,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/dw");
    FAT_LoadBackground(0,2,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/dwc");
    FAT_LoadBackground(1,2,1920,256,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/lava");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");

    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,2,660,1,3,5,2,4);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();

    //mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    PA_DisableSpecialFx(1);

    AS_MP3StreamPlay("nitro:/data/music/bdw.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    u8 bg_y = 0;
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgx < 0) player_bgx =0;
        else if(player_bgx > 1664) player_bgx = 1664;

        if(player_bgy <0) player_bgy = 0;
        else if(player_bgy > 512) player_bgy = 512;
        Player.Update();
        if(Player.y > 675) death();
        if(Player.x > 1890) {
            rank();
            bdwz2Func();
            return 0;
        }
        bg_y --;
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,bg_y);
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
        PA_OutputText(0,10,10,"Crystals: %d\n\n\nTimer:%d  ",crystal_counter,timer);
        PA_WaitForVBL();
    }
    return 0;
}