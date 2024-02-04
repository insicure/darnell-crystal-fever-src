#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "fdz.h"
#include "bwz.h"

static ACrystal Crystals[36];
static APlayer Player;
static ACannon Cannon[5];
static u8 crystal_counter;
static int timer = 0;
static int timerms =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 17;
    Player.g = 0;
    timer = 0;
    Player.UpdateBg();
    Player.Update();
    for(u8 i = 0; i <= 36; i ++) {
        Crystals[i].ReActivate();
        if(i <= 4) Cannon[i].ReActivate();
    }
    PA_CFadeInSys();
    return 0;
}
static int rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystal_counter,timer);
    PA_CFadeInSys();
    if(timer < 18){
        PA_OutputText(1,0,4,"geez you are too fast, S RANK.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    else if(timer >= 18){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    return 0;
}
u8 fdz2Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Fever Dream Act 2");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,2,1600,1600,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza2/fdza2");
    FAT_LoadBackground(0,2,1600,1600,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza2/fdza2c");
    FAT_LoadBackground(1,3,256,256,PA_BgNormal,"nitro:/data/graphics/levels/bgs/fdza1/fdz1bg_beta");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,30,17,1,3,4,2,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    PA_LoadSprite16cPal(1,2,(void*)cannon_Pal);
    Crystals[0].Create(1,1,176,768);
Crystals[1].Create(2,1,192,768);
Crystals[2].Create(3,1,208,768);
Crystals[3].Create(4,1,224,768);
Crystals[4].Create(5,1,176,752);
Crystals[5].Create(6,1,192,752);
Crystals[6].Create(7,1,208,752);
Crystals[7].Create(8,1,224,752);
Crystals[8].Create(9,1,176,736);
Crystals[9].Create(10,1,192,736);
Crystals[10].Create(11,1,208,736);
Crystals[11].Create(12,1,224,736);
Crystals[12].Create(13,1,804,1344);
Crystals[13].Create(14,1,820,1344);
Crystals[14].Create(15,1,836,1344);
Crystals[15].Create(16,1,804,1328);
Crystals[16].Create(17,1,820,1328);
Crystals[17].Create(18,1,836,1328);
Crystals[18].Create(19,1,1214,832);
Crystals[19].Create(20,1,1214,848);
Crystals[20].Create(21,1,1214,864);
Crystals[21].Create(22,1,1214,880);
Crystals[22].Create(23,1,1214,896);
Crystals[23].Create(24,1,1214,912);
Crystals[24].Create(25,1,880,926);
Crystals[25].Create(26,1,880,910);
Crystals[26].Create(27,1,880,894);
Crystals[27].Create(28,1,880,878);
Crystals[28].Create(29,1,896,926);
Crystals[29].Create(30,1,896,910);
Crystals[30].Create(31,1,896,894);
Crystals[31].Create(32,1,896,878);
Crystals[32].Create(33,1,1214,928);
Crystals[33].Create(34,1,1214,944);
Crystals[34].Create(35,1,1214,960);
Crystals[35].Create(36,1,1214,976);
Crystals[36].Create(37,1,1214,992);
Cannon[0].Create(38,2,734,1232,0,2);
Cannon[1].Create(39,2,192,1232,0,2);
Cannon[2].Create(40,2,192,768,0,2);
Cannon[3].Create(41,2,1024,912,0,2);
Cannon[4].Create(42,2,1136,784,0,2);

    AS_MP3StreamPlay("nitro:/data/music/fv.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();
        Player.UpdateBg();

        if(player_bgx < 0) player_bgx =0;
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 1480) player_bgy = 1480;
        if(Player.y < 0) Player.y = 0;

        if(Player.x > 1334){
            PA_CFadeOutSys();
            rank();
            fdz3Func();
            return 0;
        }
        Player.Update();
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 36; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++;
            if(i <= 4) if(Cannon[i].vbl(Player.x,Player.y,true)) death();
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
        PA_OutputText(0,10,10,"Crystals: %d\n\n\nTimer:%d",crystal_counter,timer);
        PA_WaitForVBL();
    }
    return 0;
}