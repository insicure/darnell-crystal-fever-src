#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "objects.h"
static ACrystal Crystals[43];
static APlayer Player;
static ACannon Cannon[7];
static u8 crystal_counter = 0;
static int timerms = 0;
static int timer = 0;

static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 434;
    Player.g = 0;
    Player.UpdateBg();
    Player.Update();
    timer = 0;
    timerms =0;
    for(u8 i = 0; i <= 42; i ++) {
        Crystals[i].ReActivate();
        if(i <= 6) Cannon[i].ReActivate();
    }
    PA_CFadeInSys();
    return 0;
}
static int rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystal_counter,timer);
    PA_CFadeInSys();
    if(timer < 20){
        PA_OutputText(1,0,4,"Perfect S rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystal_counter >= 43){
        PA_OutputText(1,0,4,"Perfect S rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }    
    else if(crystal_counter > 30){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(2);
        PA_CFadeOutSys();
        return 0;
    }
    else if(crystal_counter > 20){
        PA_OutputText(1,0,4,"B rank.");
        PA_Sleep(2);
        return 0;
    }
    else if(crystal_counter > 10){
        PA_OutputText(1,0,4,"C rank :(");
        PA_Sleep(2);
        return 0;
    }
    else{
        PA_OutputText(1,0,4,"what.");
        PA_Sleep(2);
        return 0;
    }
    return 0;
}
u8 fdz1Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Fever Dream Act 1");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,2,1472,640,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza1/fvdz1");
    FAT_LoadBackground(1,3,256,256,PA_BgNormal,"nitro:/data/graphics/levels/bgs/fdza1/fdz1bg_beta");
    FAT_LoadBackground(0,2,1472,640,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza1/fdz1cbg");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,30,434,1,2,3,4,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    Crystals[0].Create(1,1,80,228);
    Crystals[1].Create(2,1,96,228);
    Crystals[2].Create(3,1,112,228);
    Crystals[3].Create(4,1,80,244);
    Crystals[4].Create(5,1,96,244);
    Crystals[5].Create(6,1,112,244);
    Crystals[6].Create(7,1,80,260);
    Crystals[7].Create(8,1,96,260);
    Crystals[8].Create(9,1,112,260);
    Crystals[9].Create(10,1,546,444);
    Crystals[10].Create(11,1,562,444);
    Crystals[11].Create(12,1,546,428);
    Crystals[12].Create(13,1,562,428);
    Crystals[13].Create(14,1,400,404);
    Crystals[14].Create(15,1,416,404);
    Crystals[15].Create(16,1,432,404);
    Crystals[16].Create(17,1,400,388);
    Crystals[17].Create(18,1,416,388);
    Crystals[18].Create(19,1,432,388);
    Crystals[19].Create(20,1,208,253);
    Crystals[20].Create(21,1,224,253);
    Crystals[21].Create(22,1,240,253);
    Crystals[22].Create(23,1,272,64);
    Crystals[23].Create(24,1,256,64);
    Crystals[24].Create(25,1,240,64);
    Crystals[25].Create(26,1,272,48);
    Crystals[26].Create(27,1,256,48);
    Crystals[27].Create(28,1,240,48);
    Crystals[28].Create(29,1,624,304);
    Crystals[29].Create(30,1,640,304);
    Crystals[30].Create(31,1,624,320);
    Crystals[31].Create(32,1,640,320);
    Crystals[32].Create(33,1,624,336);
    Crystals[33].Create(34,1,640,336);
    Crystals[34].Create(35,1,864,352);
    Crystals[35].Create(36,1,848,352);
    Crystals[36].Create(37,1,832,352);
    Crystals[37].Create(38,1,864,336);
    Crystals[38].Create(39,1,848,336);
    Crystals[39].Create(40,1,832,336);
    Crystals[40].Create(41,1,864,320);
    Crystals[41].Create(42,1,848,320);
    Crystals[42].Create(43,1,832,320);
    PA_LoadSprite16cPal(1,2,(void*)cannon_Pal);
    Cannon[0].Create(44,2,272,592,0,2);
    Cannon[1].Create(45,2,413,304,0,2);
    Cannon[2].Create(46,2,688,160,0,2);
    Cannon[3].Create(47,2,176,304,0,2);
    Cannon[4].Create(48,2,944,176,0,2);
    Cannon[5].Create(49,2,1152,448,0,2);
    Cannon[6].Create(50,2,1280,160,0,2);

    AS_MP3StreamPlay("nitro:/data/music/fv.mp3");
    AS_SetMP3Loop(true);    
    PA_CFadeInSys();
    while(1){
        Player.Move();
        if(Player.Gravity()) death();
        Player.UpdateBg();

        if(Player.x < 1312 && Player.y > 600) death();
        else if(Player.x > 1312 && Player.y > 600) {
            PA_CFadeOutSys();
            PA_ClearTextBg(0);
            rank();
            fdz2Func();
            return 0;
        }
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 440) player_bgy = 440;
        
        if(player_bgx < 0) player_bgx = 0;
        else if(player_bgx >1216) player_bgx = 1216;

        if(Player.y < 0) Player.y = 0;
        Player.Update();
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 42; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++;
            if(i <= 6) if(Cannon[i].vbl(Player.x,Player.y,true)) death();
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