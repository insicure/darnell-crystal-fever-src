#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "objects.h"
#include "ccz.h"

static ACrystal Crystals[35];
static APlayer Player;
static ACannon Cannon[10];
static u8 crystal_counter = 0;
static int timerms = 0;
static int timer = 0;
static void CreateCrystals(){
    Crystals[0].Create(1,1,256,256);
Crystals[1].Create(2,1,256,272);
Crystals[2].Create(3,1,256,240);
Crystals[3].Create(4,1,240,256);
Crystals[4].Create(5,1,240,272);
Crystals[5].Create(6,1,240,240);
Crystals[6].Create(7,1,224,256);
Crystals[7].Create(8,1,224,272);
Crystals[8].Create(9,1,224,240);
Crystals[9].Create(10,1,432,288);
Crystals[10].Create(11,1,448,288);
Crystals[11].Create(12,1,432,272);
Crystals[12].Create(13,1,448,272);
Crystals[13].Create(14,1,432,304);
Crystals[14].Create(15,1,448,304);
Crystals[15].Create(16,1,608,352);
Crystals[16].Create(17,1,624,352);
Crystals[17].Create(18,1,640,352);
Crystals[18].Create(19,1,608,336);
Crystals[19].Create(20,1,624,336);
Crystals[20].Create(21,1,640,336);
Crystals[21].Create(22,1,576,208);
Crystals[22].Create(23,1,592,208);
Crystals[23].Create(24,1,576,192);
Crystals[24].Create(25,1,592,192);
Crystals[25].Create(26,1,992,256);
Crystals[26].Create(27,1,1008,256);
Crystals[27].Create(28,1,1104,352);
Crystals[28].Create(29,1,1120,352);
Crystals[29].Create(30,1,1136,352);
Crystals[30].Create(31,1,1104,336);
Crystals[31].Create(32,1,1120,336);
Crystals[32].Create(33,1,1136,336);
Crystals[33].Create(34,1,1088,224);
Crystals[34].Create(35,1,1104,224);
}
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 324;
    Player.g = 0;
    Player.UpdateBg();
    Player.Update();
    timer = 0;
    timerms =0;
    for(u8 i = 0; i <= 31; i ++) {
        Crystals[i].ReActivate();
        if(i <= 7) Cannon[i].ReActivate();
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
    if(timer < 17){
        PA_OutputText(1,0,4,"Perfect S rank!!!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystalscore >= 3500){
        PA_OutputText(1,0,4,"Perfect S rank!!!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }    
    else if(crystalscore <= 3500){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(2);
        PA_CFadeOutSys();
        return 0;
    }
    else if(crystalscore <= 2000){
        PA_OutputText(1,0,4,"B rank.");
        PA_Sleep(2);
        return 0;
    }
    else if(crystalscore <= 1000){
        PA_OutputText(1,0,4,"C rank :(");
        PA_Sleep(2);
        return 0;
    }
    else{
        PA_OutputText(1,0,4,"no.");
        PA_Sleep(2);
        return 0;
    }
    return 0;
}
u8 ccz1Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,5,12,"Colorful Caverns Act 1");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/cc/act1/bg3");
    FAT_LoadBackground(1,2,2256, 400,PA_BgLarge,"nitro:/data/graphics/levels/bgs/cc/act1/cc1bg");
    FAT_LoadBackground(0,2,2256, 400,PA_BgLarge,"nitro:/data/graphics/levels/bgs/cc/act1/cc1bgc");    

    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    FAT_LoadBackground(1,1,512, 256,PA_BgNormal,"nitro:/data/graphics/levels/bgs/cc/act1/ccbg1");    

    PA_HideBg(0,2);
    PA_InitText(0,0);
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    PA_LoadSprite16cPal(1,2,(void*)cannon3index_Pal);
    Player.Create(0,34,324,1,3,2,4,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_SetSpritePrio(1,0,2);
	//mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    PA_EnableSpecialFx(1, SFX_ALPHA, SFX_BG1 |SFX_BD, SFX_BG0 | SFX_BG1 | SFX_BG2 | SFX_BG3 | SFX_OBJ | SFX_BD);
    PA_SetSFXAlpha(1,4,15);
    CreateCrystals();
    Cannon[0].CreateCustomGFX(36,(void*)cannon3index_Sprite,2,256,272,0,2);
    Cannon[1].CreateCustomGFX(37,(void*)cannon3index_Sprite,2,288,352,0,2);
    Cannon[2].CreateCustomGFX(38,(void*)cannon3index_Sprite,2,672,368,0,2);
    Cannon[3].CreateCustomGFX(39,(void*)cannon3index_Sprite,2,672,240,0,2);
    Cannon[4].CreateCustomGFX(40,(void*)cannon3index_Sprite,2,592,224,0,2);
    Cannon[5].CreateCustomGFX(41,(void*)cannon3index_Sprite,2,864,256,0,2);
    Cannon[6].CreateCustomGFX(42,(void*)cannon3index_Sprite,2,1232,256,0,2);
    Cannon[7].CreateCustomGFX(43,(void*)cannon3index_Sprite,2,1408,256,0,2);
    for(int i = 36; i <= 45; i++) {
        PA_SetSpriteRotEnable(1,i,1);
    }
    u16 angle = 0;
    AS_MP3StreamPlay("nitro:/data/music/cc.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        Player.Move();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgx < 0) player_bgx =0;
        else if(player_bgx > 2000) player_bgx = 2000;
        if(player_bgy > 208) player_bgy = 208;
        else if(player_bgy < 0) player_bgy = 0;
        Player.Update();
        angle ++;
        PA_SetRotsetNoZoom(1,1,angle);
        if(Player.y > 400) death();
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX/2,0);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX/2,0);
        for(u8 i = 0; i <= 34; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++; 
            if(i <= 7 && Cannon[i].vblRot(Player.x,Player.y,true,1)) death();
        }
        if(Player.x > 2094 && Player.y > 326){
            PA_CFadeOutSys();
            PA_ClearTextBg(0);
            AS_MP3Stop();
            rank();
            ccz2Func();
            return 0;
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