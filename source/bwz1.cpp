#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "bwz.h"
static ACrystal Crystals[41];
static APlayer Player;
static ACannon Cannon[4];
static u8 crystal_counter;
static int timer = 0;
static int timerms =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 0;
    Player.y = 704;
    Player.g = 0;
    timer = 0;
    Player.UpdateBg();
    Player.Update();
    for(u8 i = 0; i <= 41; i ++) {
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
    if(timer < 20 || crystal_counter >= 39){
        PA_OutputText(1,0,4,"Perfect S rank!!!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystal_counter >= 29){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    else if(crystal_counter < 29){
        PA_OutputText(1,0,4,"B rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    return 0;
}
u8 bwz1Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Blocky Woods Act 1");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/bw/bgscr");
    FAT_LoadBackground(1,2,1600,800,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bw/act1/bg");
    FAT_LoadBackground(0,2,1600,800,PA_BgLarge,"nitro:/data/graphics/levels/bgs/bw/act1/cmapc");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");

    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,0,704,1,2,4,3,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    Crystals[0].Create(1,1,48,576);
Crystals[1].Create(2,1,64,576);
Crystals[2].Create(3,1,80,576);
Crystals[3].Create(4,1,16,320);
Crystals[4].Create(5,1,16,336);
Crystals[5].Create(6,1,16,352);
Crystals[6].Create(7,1,16,368);
Crystals[7].Create(8,1,112,448);
Crystals[8].Create(9,1,112,432);
Crystals[9].Create(10,1,112,416);
Crystals[10].Create(11,1,112,400);
Crystals[11].Create(12,1,176,336);
Crystals[12].Create(13,1,192,336);
Crystals[13].Create(14,1,176,320);
Crystals[14].Create(15,1,192,320);
Crystals[15].Create(16,1,176,304);
Crystals[16].Create(17,1,192,304);
Crystals[17].Create(18,1,272,464);
Crystals[18].Create(19,1,272,448);
Crystals[19].Create(20,1,272,432);
Crystals[20].Create(21,1,272,416);
Crystals[21].Create(22,1,272,400);
Crystals[22].Create(23,1,272,384);
Crystals[23].Create(24,1,432,336);
Crystals[24].Create(25,1,432,352);
Crystals[25].Create(26,1,432,368);
Crystals[26].Create(27,1,432,384);
Crystals[27].Create(28,1,432,400);
Crystals[28].Create(29,1,432,416);
Crystals[29].Create(30,1,432,432);
Crystals[30].Create(31,1,432,448);
Crystals[31].Create(32,1,432,464);
Crystals[32].Create(33,1,432,480);
Crystals[33].Create(34,1,496,688);
Crystals[34].Create(35,1,512,688);
Crystals[35].Create(36,1,576,640);
Crystals[36].Create(37,1,588,640);
Crystals[37].Create(38,1,604,640);
Crystals[38].Create(39,1,864,176);
Crystals[39].Create(40,1,848,176);
Crystals[40].Create(41,1,864,160);
Crystals[41].Create(42,1,848,160);
PA_LoadSpritePal(1,2,(void*)xed_Pal);
Cannon[0].CreateGFX2(43,2,176,624,0,2);
Cannon[1].CreateGFX2(44,2,64,448,0,2);
Cannon[2].CreateGFX2(45,2,336,336,0,2);
Cannon[3].CreateGFX2(46,2,784,368,0,2);

    //mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    AS_MP3StreamPlay("nitro:/data/music/bw.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 608) player_bgy = 608;
        if(player_bgx < 0) player_bgx = 0;
        else if(player_bgx >1216) player_bgx = 1216;

        if(Player.y > 800) death();
        if(Player.x > 1366){
            PA_CFadeOutSys();
            rank();
            bwz2Func();
            return 0;
        }
        Player.Update();
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 41; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++;
            if(i <=3) if(Cannon[i].vbl(Player.x,Player.y,true)) death();
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