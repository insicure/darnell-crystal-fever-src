#include <PA9.h>
#include "all_gfx.h"
#include "player.h"
#include "objects.h"
#include "fdz.h"
#include "bwz.h"

static ACrystal Crystals[28];
static APlayer Player;
static ACannon Cannon[3];
u8 crystal_counter_fdzb;
int timerb = 0;
int timermsb =0;
static int death(){
    PA_CFadeOutSys();
    crystal_counter_fdzb = 0;
    Player.x = 30;
    Player.y = 900;
    Player.g = 0;
    timerb = 0;
    Player.UpdateBg();
    Player.Update();
    for(u8 i = 0; i <= 28; i ++) {
        Crystals[i].ReActivate();
        if(i <= 2) Cannon[i].ReActivate();
    }
    PA_CFadeInSys();
    return 0;
}
static int rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystal_counter_fdzb,timerb);
    PA_CFadeInSys();
    if(timerb < 18){
        PA_OutputSimpleText(1,0,4,"Perfect S rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystal_counter_fdzb > 24){
        PA_OutputSimpleText(1,0,4,"Perfect S rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
    }
    else if(crystal_counter_fdzb > 18){
        PA_OutputSimpleText(1,0,4,"A rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
    }
    else{
        PA_OutputSimpleText(1,0,4,"B rank.");
        PA_Sleep(3);
        PA_CFadeOutSys();
    }
    return 0;
}
u8 fdz3Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Fever Dream Act 3");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(0,2,1488,1040,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza3/fdaz3c");
    FAT_LoadBackground(1,2,1488,1040,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza3/fdaz3");
    FAT_LoadBackground(1,1,1488,1040,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza3/fdaz3bg");
    FAT_LoadBackground(1,3,256, 1040,PA_BgLarge,"nitro:/data/graphics/levels/bgs/fdza3/fdaz3bg3");

    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,30,900,1,3,4,2,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_SetSpritePrio(1,0,3);
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    PA_LoadSprite16cPal(1,2,(void*)cannon_Pal);

	//mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    Crystals[0].Create(1,1,48,704);
Crystals[1].Create(2,1,64,704);
Crystals[2].Create(3,1,80,704);
Crystals[3].Create(4,1,96,704);
Crystals[4].Create(5,1,48,688);
Crystals[5].Create(6,1,64,688);
Crystals[6].Create(7,1,80,688);
Crystals[7].Create(8,1,96,688);
Crystals[8].Create(9,1,48,672);
Crystals[9].Create(10,1,64,672);
Crystals[10].Create(11,1,80,672);
Crystals[11].Create(12,1,96,672);
Crystals[12].Create(13,1,48,656);
Crystals[13].Create(14,1,64,656);
Crystals[14].Create(15,1,80,656);
Crystals[15].Create(16,1,96,656);
Crystals[16].Create(17,1,352,848);
Crystals[17].Create(18,1,352,832);
Crystals[18].Create(19,1,352,816);
Crystals[19].Create(20,1,352,800);
Crystals[20].Create(21,1,560,832);
Crystals[21].Create(22,1,544,832);
Crystals[22].Create(23,1,528,832);
Crystals[23].Create(24,1,560,816);
Crystals[24].Create(25,1,544,816);
Crystals[25].Create(26,1,528,816);
Crystals[26].Create(27,1,1408,512);
Crystals[27].Create(28,1,1408,496);
Crystals[28].Create(29,1,1408,480);
Cannon[0].Create(30,2,208,720,0,2);
Cannon[1].Create(31,2,496,752,0,2);
Cannon[2].Create(32,2,752,880,0,2);

    AS_MP3StreamPlay("nitro:/data/music/fv.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        if(Player.Move()) death();
        if(Player.Gravity()) death();
        Player.UpdateBg();

        if(player_bgx < 0) player_bgx =0;
        else if(player_bgx > 1232) player_bgx = 1232;
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 848) player_bgy = 848;
        else if(player_bgy < 172 && (Player.y > 182)) player_bgy = 172;
        if(Player.y < 0) Player.y = 0;
        
        if(Player.x < 900 && Player.y < 133) {
            PA_CFadeOutSys();
            AS_MP3Stop();
            rank();
            bwz1Func();
            return 0;
        }
        if(Player.x > 1356 && Player.y > 950) Player.g = -25;
        Player.Update();
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 28; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter_fdzb ++;
            if(i<=2&&Cannon[i].vbl(Player.x,Player.y,true))death();
        }
        timermsb ++;
        if(timermsb >= 60){
            timerb ++;
            timermsb = 0;
        }
        if(Pad.Newpress.Start) {
            PA_WaitForVBL();
            PA_WaitFor(Pad.Newpress.Start);
        }
        PA_ClearTextBg(0);
        PA_OutputText(0,10,10,"Crystals: %d\n\n\nTimer:%d",crystal_counter_fdzb,timerb);
        PA_WaitForVBL();
    }
    return 0;
}