#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "bwz.h"
#include "sbz.h"
static APlayer Player;
static ACannon Cannon[5];
static u8 crystal_counter;
static int timer = 0;
static int timerms =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 14;
    Player.y = 628;
    Player.g = 0;
    timer = 0;
    Player.UpdateBg();
    Player.Update();
    PA_CFadeInSys();
    return 0;
}
u8 bdwz2Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Lost World Act 2");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
//
//    FAT_LoadBackground(1,1,1920, 704,PA_BgLarge,"data/graphics/levels/bgs/bdw/dw");
//    FAT_LoadBackground(0,2,1920, 704,PA_BgLarge,"data/graphics/levels/bgs/bdw/dwc");
//    FAT_LoadBackground(1,2,1920,256,PA_BgLarge,"data/graphics/levels/bgs/bdw/lava");
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bdw/bgr");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");

    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bdw/bgr");
    FAT_LoadBackground(1,2,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/act2/act2");
    FAT_LoadBackground(1,1,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/act2/act2bg1");
    FAT_LoadBackground(0,2,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bdw/act2/act2c");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");

    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,14,628,1,3,5,2,4);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_SetSpritePrio(1,0,2);
    //mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    AS_MP3StreamPlay("nitro:/data/music/bdw.mp3");
    AS_SetMP3Loop(true);
    PA_LoadSprite16cPal(1,1,(void*)rev01_Pal);
    Cannon[0].CreateCustomGFX(1,(void*)rev01_Sprite,1,912,352,0,2);
    Cannon[1].CreateCustomGFX(2,(void*)rev01_Sprite,1,994,208,0,2);
    Cannon[2].CreateCustomGFX(3,(void*)rev01_Sprite,1,994,208,0,2);
    Cannon[3].CreateCustomGFX(4,(void*)rev01_Sprite,1,1456,592,0,2);
    Cannon[4].CreateCustomGFX(5,(void*)rev01_Sprite,1,1728,576,0,2);
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
        if(Player.x > 1854){
            PA_CFadeOutSys();
            sbz1Func();
            return 0;
        }
        bg_y --;
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 4; i ++) {
            if(Cannon[i].vblRot(Player.x,Player.y,true,1)) death();
        }
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