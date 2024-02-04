#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "objects.h"
#include "ccz.h"
#include "imz.h"

static ACrystal Crystals[34];
static APlayer Player;
static ACannon Cannon[8];
static ACierra Cierra[9];
static u8 crystal_counter = 0;
static int timerms = 0;
static int timer = 0;
static void CreateCrystals(){
    Crystals[0].Create(1,1,320,160);
Crystals[1].Create(2,1,336,160);
Crystals[2].Create(3,1,352,160);
Crystals[3].Create(4,1,320,144);
Crystals[4].Create(5,1,336,144);
Crystals[5].Create(6,1,352,144);
Crystals[6].Create(7,1,448,160);
Crystals[7].Create(8,1,464,160);
Crystals[8].Create(9,1,480,160);
Crystals[9].Create(10,1,448,144);
Crystals[10].Create(11,1,464,144);
Crystals[11].Create(12,1,480,144);
Crystals[12].Create(13,1,576,160);
Crystals[13].Create(14,1,592,160);
Crystals[14].Create(15,1,608,160);
Crystals[15].Create(16,1,624,160);
Crystals[16].Create(17,1,576,144);
Crystals[17].Create(18,1,592,144);
Crystals[18].Create(19,1,608,144);
Crystals[19].Create(20,1,624,144);
Crystals[20].Create(21,1,1378,208);
Crystals[21].Create(22,1,1394,208);
Crystals[22].Create(23,1,1456,271);
Crystals[23].Create(24,1,1472,271);
Crystals[24].Create(25,1,1664,288);
Crystals[25].Create(26,1,1680,288);
Crystals[26].Create(27,1,1664,272);
Crystals[27].Create(28,1,1680,272);
Crystals[28].Create(29,1,1760,288);
Crystals[29].Create(30,1,1760,288);
Crystals[30].Create(31,1,1760,272);
Crystals[31].Create(32,1,1760,272);
Crystals[32].Create(33,1,1632,64);
Crystals[33].Create(34,1,1728,48);


}
static int death(){
    PA_CFadeOutSys();
    crystal_counter = 0;
    Player.x = 30;
    Player.y = 260;
    Player.g = 0;
    Player.UpdateBg();
    Player.Update();
    timer = 0;
    timerms =0;
    for(u8 i = 0; i <= 33; i ++) Crystals[i].ReActivate();
    for(u8 i = 0; i <= 7; i ++) Cannon[i].ReActivate();
    PA_CFadeInSys();
    return 0;
}
static int rank(){
    PA_ResetAll();
    PA_InitText(1,0);
    int crystalscore = crystal_counter * 100;
    PA_OutputText(1,0,0,"Results:\nCrystals:%d\nTime in stage:%d",crystalscore,timer);
    PA_CFadeInSys();
    if(timer < 20){
        PA_OutputText(1,0,4,"geez you are too fast, S RANK.");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }
    if(crystalscore >= 4300){
        PA_OutputText(1,0,4,"Perfect S rank!!!");
        PA_Sleep(3);
        PA_CFadeOutSys();
        return 0;
    }    
    else if(crystalscore > 3000){
        PA_OutputText(1,0,4,"A rank!");
        PA_Sleep(2);
        PA_CFadeOutSys();
        return 0;
    }
    else if(crystalscore > 2000){
        PA_OutputText(1,0,4,"B rank.");
        PA_Sleep(2);
        return 0;
    }
    else if(crystalscore > 1000){
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
u8 ccz2Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,5,12,"Colorful Caverns Act 2");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256,192,PA_BgNormal,"nitro:/data/graphics/levels/bgs/cc/act1/bg3");
    FAT_LoadBackground(1,2,2640,336,PA_BgLarge,"nitro:/data/graphics/levels/bgs/cc/act1/cc2bg");
    FAT_LoadBackground(0,2,2640,336,PA_BgLarge,"nitro:/data/graphics/levels/bgs/cc/act1/cc2bgc");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    FAT_LoadBackground(1,1,512, 256,PA_BgNormal,"nitro:/data/graphics/levels/bgs/cc/act1/ccbg1");    
    PA_HideBg(0,2);
    PA_InitText(0,0);
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    PA_LoadSprite16cPal(1,2,(void*)cannon3index_Pal);
    Player.Create(0,30,260,1,4,2,3,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_SetSpritePrio(1,0,2);
	//mmLoadEffect(SFX_CRYS);
	//mmLoadEffect(SFX_JUMP);
    PA_EnableSpecialFx(1, SFX_ALPHA, SFX_BG1 |SFX_BD, SFX_BG0 | SFX_BG1 | SFX_BG2 | SFX_BG3 | SFX_OBJ | SFX_BD);
    PA_SetSFXAlpha(1,4,10);
    PA_LoadSprite16cPal(1,3,(void*)cierra_Pal);
    CreateCrystals();
    Cannon[0].CreateCustomGFX(35,(void*)cannon3index_Sprite,2,143,224,0,2);
    Cannon[1].CreateCustomGFX(36,(void*)cannon3index_Sprite,2,224,192,0,2);
    Cannon[2].CreateCustomGFX(37,(void*)cannon3index_Sprite,2,352,176,0,2);
    Cannon[3].CreateCustomGFX(38,(void*)cannon3index_Sprite,2,480,176,0,2);
    Cannon[4].CreateCustomGFX(39,(void*)cannon3index_Sprite,2,800,240,0,2);
    Cannon[5].CreateCustomGFX(40,(void*)cannon3index_Sprite,2,912,224,0,2);
    Cannon[6].CreateCustomGFX(41,(void*)cannon3index_Sprite,2,1584,288,0,2);
    Cannon[7].CreateCustomGFX(42,(void*)cannon3index_Sprite,2,1888,288,0,2);
    Cierra[0].Create(43,3,1609,224,320);
    Cierra[1].Create(44,3,1704,240,320);
    Cierra[2].Create(45,3,1801,240,320);
    Cierra[3].Create(46 ,3,1912,240,320);
    Cierra[4].Create(47,3,800,220,304);
    Cierra[5].Create(48,3,912,224,304);
    Cierra[6].Create(49,3,2297,76,209);
    Cierra[7].Create(50,3,2187,76,209);
    Cierra[8].Create(51,3,2078,76,209);
    for(u8 i = 35; i <= 51; i++) {
        if(i >= 43) PA_SetSpriteRotEnable(1,i,1);
        else PA_SetSpriteRotEnable(1,i,2);
    }
    u16 angle1 = 0;
    u16 angle2 = 0;
    AS_MP3StreamPlay("nitro:/data/music/cc.mp3");
    AS_SetMP3Loop(true);
    PA_CFadeInSys();
    while(1){
        Player.Move();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgx < 0) player_bgx =0;
        else if(player_bgx >2384) player_bgx = 2384;
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 144) player_bgy = 144;
        Player.Update();
        if(Player.y > 305) death();
        angle1 += 5;
        angle2 += 5;
        PA_SetRotsetNoZoom(1,1,angle2);
        PA_SetRotsetNoZoom(1,2,angle1);
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX/2,0);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        PA_EasyBgScrollXY(1,1,PA_BgInfo[0][2].ScrollX/2,0);
        for(u8 i = 0; i <= 33; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++; 
            if((i <= 6 && Cannon[i].vblRot(Player.x,Player.y,true,1))) death();
            if(i <= 8 && Cierra[i].vbl(Player.x,Player.y)) death();
        }
        if(Player.y > 336) death();
        if(Player.x > 2410) {
            PA_DisableSpecialFx(1);
            rank();
            imz1Func();
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
        PA_OutputText(0,10,10,"Crystals: %d\n\n\nTimer:%d  ",crystal_counter,timer);
        PA_WaitForVBL();
    }
    return 0;
}