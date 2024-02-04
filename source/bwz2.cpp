#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "bwz.h"
#include "ccz.h"
static ACrystal Crystals[53];
static APlayer Player;
static u8 crystal_counter;
static ACannon Cannon[4];
static int timer = 0;
static int timerms =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 603;
    Player.g = 0;
    timer = 0;
    Player.UpdateBg();
    Player.Update();
    for(u8 i = 0; i <= 52; i ++) {
        Crystals[i].ReActivate();
        if(i <= 3) Cannon[i].ReActivate(); 
    }
    PA_CFadeInSys();
    return 0;
}
static int rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    int crystalscore = crystal_counter * 100;
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystalscore,timer);
    PA_CFadeInSys();
    if(timer < 30 || crystal_counter >= 39){
        PA_OutputText(1,0,4,"Perfect S rank!!!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystal_counter >= 28){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    else if(crystal_counter < 28){
        PA_OutputText(1,0,4,"B rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    return 0;
}
u8 bwz2Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Blocky Woods Act 2");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bw/bgscr");
    FAT_LoadBackground(1,1,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bw/act2/act2");

    FAT_LoadBackground(1,2,1920, 256,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bw/act2/water");
    FAT_LoadBackground(0,2,1920, 704,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bw/act2/act2c");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");

    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,36,603,1,3,5,2,4);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
PA_LoadSpritePal(1,2,(void*)xed_Pal);
Crystals[0].Create(1,1,224,624);
Crystals[1].Create(2,1,240,624);
Crystals[2].Create(3,1,256,624);
Crystals[3].Create(4,1,496,640);
Crystals[4].Create(5,1,512,640);
Crystals[5].Create(6,1,528,640);
Crystals[6].Create(7,1,496,624);
Crystals[7].Create(8,1,512,624);
Crystals[8].Create(9,1,528,624);
Crystals[9].Create(10,1,992,656);
Crystals[10].Create(11,1,1008,656);
Crystals[11].Create(12,1,992,640);
Crystals[12].Create(13,1,1008,640);
Crystals[13].Create(14,1,1136,400);
Crystals[14].Create(15,1,1152,400);
Crystals[15].Create(16,1,1136,384);
Crystals[16].Create(17,1,1152,384);
Crystals[17].Create(18,1,1136,364);
Crystals[18].Create(19,1,1152,364);
Crystals[19].Create(20,1,1344,624);
Crystals[20].Create(21,1,1360,624);
Crystals[21].Create(22,1,1376,624);
Crystals[22].Create(23,1,1360,528);
Crystals[23].Create(24,1,1376,528);
Crystals[24].Create(25,1,1392,528);
Crystals[25].Create(26,1,1360,416);
Crystals[26].Create(27,1,1376,416);
Crystals[27].Create(28,1,1392,416);
Crystals[28].Create(29,1,1599,80);
Crystals[29].Create(30,1,1599,96);
Crystals[30].Create(31,1,1599,112);
Crystals[31].Create(32,1,1696,160);
Crystals[32].Create(33,1,1680,160);
Crystals[33].Create(34,1,1759,112);
Crystals[34].Create(35,1,1775,112);
Crystals[35].Create(36,1,448,496);
Crystals[36].Create(37,1,464,496);
Crystals[37].Create(38,1,480,496);
Crystals[38].Create(39,1,448,480);
Crystals[39].Create(40,1,464,480);
Crystals[40].Create(41,1,480,480);
Crystals[41].Create(42,1,544,464);
Crystals[42].Create(43,1,560,464);
Crystals[43].Create(44,1,816,496);
Crystals[44].Create(45,1,800,496);
Crystals[45].Create(46,1,880,432);
Crystals[46].Create(47,1,864,432);
Crystals[47].Create(48,1,880,416);
Crystals[48].Create(49,1,864,416);
Crystals[49].Create(50,1,896,304);
Crystals[50].Create(51,1,916,304);
Crystals[51].Create(52,1,1024,208);
Crystals[52].Create(53,1,1040,208);

Cannon[0].CreateGFX2(54,2,368,640,0,2);
Cannon[1].CreateGFX2(55,2,1456,592,0,2);
Cannon[2].CreateGFX2(56,2,1328,496,0,2);
Cannon[3].CreateGFX2(57,2,1392,304,0,2);
    AS_MP3StreamPlay("nitro:/data/music/bw.mp3");
    AS_SetMP3Loop(true);
	//mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    PA_CFadeInSys();
    u8 animtimer = 0;
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();                   
        Player.UpdateBg();
        if(player_bgy > 512) player_bgy = 512;
        else if(player_bgy < 0) player_bgy = 0;
        if(player_bgx < 0) player_bgx = 0;
        else if(player_bgx > 1664) player_bgx = 1664;
        if(Player.y > 675) death();

        if(Player.x > 1838) {
            PA_CFadeOutSys();
            AS_MP3Stop();
            rank();
            ccz1Func();
            return 0;
        }
        Player.Update();
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,-animtimer);
        for(u8 i = 0; i <= 52; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++; 
            if(i <= 3 && Cannon[i].vbl(Player.x,Player.y,true)) death();
        }
        animtimer ++;   
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