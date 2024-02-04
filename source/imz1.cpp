#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "player.h"
#include "imz.h"
#include "objects.h"
static ACrystal Crystals[60];
static APlayer Player;
static ACannon Cannon[9];
static ACierra Cierra[3];
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
    for(u8 i = 0; i <= 59; i ++) {
        Crystals[i].ReActivate();
        if(i <= 8) Cannon[i].ReActivate();
    }
    PA_CFadeInSys();
    return 0;
}
u8 imz1Func(){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);
    PA_InitText(1,0);
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_OutputSimpleText(1,7,12,"Colorful Caverns Act 3");
    PA_CFadeInSys();
    PA_Sleep(1);
    PA_CFadeOutSys();
    PA_ResetAll();
    FAT_LoadBackground(1,3,256, 256,PA_BgNormal,"data/graphics/levels/bgs/lp/lpbg");
    FAT_LoadBackground(1,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp1");
    FAT_LoadBackground(0,2,1344, 480,PA_BgLarge,"data/graphics/levels/bgs/lp/lp1c");
    FAT_LoadBackground(0,1,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    
    PA_HideBg(0,2);
    PA_InitText(0,0);
    Player.Create(0,30,420,1,2,4,3,5);
    Player.cbg = 2;
    Player.screenc = 0;
    Player.UpdateBg();
    Player.Update();
    PA_LoadSprite16cPal(1,1,(void*)crystal_Pal);
    AS_MP3StreamPlay("nitro:/data/music/fv.mp3");
    AS_SetMP3Loop(true);
    Crystals[0].Create(1,1,144,368);
Crystals[1].Create(2,1,160,368);
Crystals[2].Create(3,1,144,384);
Crystals[3].Create(4,1,160,384);
Crystals[4].Create(5,1,256,368);
Crystals[5].Create(6,1,272,368);
Crystals[6].Create(7,1,272,384);
Crystals[7].Create(8,1,256,384);
Crystals[8].Create(9,1,352,416);
Crystals[9].Create(10,1,368,416);
Crystals[10].Create(11,1,384,416);
Crystals[11].Create(12,1,384,224);
Crystals[12].Create(13,1,400,224);
Crystals[13].Create(14,1,416,224);
Crystals[14].Create(15,1,432,224);
Crystals[15].Create(16,1,320,208);
Crystals[16].Create(17,1,336,208);
Crystals[17].Create(18,1,352,208);
Crystals[18].Create(19,1,320,192);
Crystals[19].Create(20,1,336,192);
Crystals[20].Create(21,1,352,192);
Crystals[21].Create(22,1,304,256);
Crystals[22].Create(23,1,288,256);
Crystals[23].Create(24,1,272,256);
Crystals[24].Create(25,1,304,112);
Crystals[25].Create(26,1,320,112);
Crystals[26].Create(27,1,368,98);
Crystals[27].Create(28,1,384,98);
Crystals[28].Create(29,1,464,48);
Crystals[29].Create(30,1,480,48);
Crystals[30].Create(31,1,464,64);
Crystals[31].Create(32,1,480,64);
Crystals[32].Create(33,1,544,112);
Crystals[33].Create(34,1,560,112);
Crystals[34].Create(35,1,572,112);
Crystals[35].Create(36,1,640,144);
Crystals[36].Create(37,1,656,144);
Crystals[37].Create(38,1,672,144);
Crystals[38].Create(39,1,688,112);
Crystals[39].Create(40,1,704,112);
Crystals[40].Create(41,1,688,128);
Crystals[41].Create(42,1,704,128);
Crystals[42].Create(43,1,704,320);
Crystals[43].Create(44,1,720,320);
Crystals[44].Create(45,1,736,320);
Crystals[45].Create(46,1,544,320);
Crystals[46].Create(47,1,560,320);
Crystals[47].Create(48,1,576,320);
Crystals[48].Create(49,1,800,432);
Crystals[49].Create(50,1,816,432);
Crystals[50].Create(51,1,864,416);
Crystals[51].Create(52,1,880,416);
Crystals[52].Create(53,1,896,416);
Crystals[53].Create(54,1,912,336);
Crystals[54].Create(55,1,928,336);
Crystals[55].Create(56,1,944,336);
Crystals[56].Create(57,1,960,80);
Crystals[57].Create(58,1,976,80);
Crystals[58].Create(59,1,1216,336);
Crystals[59].Create(60,1,1232,336);
PA_LoadSprite16cPal(1,2,(void*)lpca_Pal);
Cannon[0].CreateCustomGFX(61,(void*)lpca_Sprite,2,118,432,0,2);
Cannon[1].CreateCustomGFX(62,(void*)lpca_Sprite,2,384,432,0,2);
Cannon[2].CreateCustomGFX(63,(void*)lpca_Sprite,2,385,304,0,2);
Cannon[3].CreateCustomGFX(64,(void*)lpca_Sprite,2,336,224,0,2);
Cannon[4].CreateCustomGFX(65,(void*)lpca_Sprite,2,556,128,0,2);
Cannon[5].CreateCustomGFX(66,(void*)lpca_Sprite,2,663,160,0,2);
Cannon[6].CreateCustomGFX(67,(void*)lpca_Sprite,2,880,432,0,2);
Cannon[7].CreateCustomGFX(68,(void*)lpca_Sprite,2,832,160,0,2);
Cannon[8].CreateCustomGFX(69,(void*)lpca_Sprite,2,927,112,0,2);

PA_LoadSprite16cPal(1,3,(void*)cierrab_Pal);
Cierra[0].CreateB(70,3,997,112,209);
Cierra[1].CreateB(71,3,1091,112,209);
Cierra[2].CreateCustomXb(72,3,993,354,1184,354);
    for(u8 i = 70; i <= 72; i++) {
        PA_SetSpriteRotEnable(1,i,1);
    }
    AS_MP3StreamPlay("nitro:/data/music/cc.mp3");
    u16 angle = 0;
    PA_CFadeInSys();
    while(1){
        Player.Move();
        if(Player.Gravity()) death();
        Player.UpdateBg();
        if(player_bgx < 0) player_bgx = 0;
        else if(player_bgx > 1088) player_bgx = 1088;
        if(player_bgy < 0) player_bgy = 0;
        else if(player_bgy > 288) player_bgy = 288;
        Player.Update();

        if(Player.y > 450) death();
        if(Player.x > 1276) {
            imz2Func();
            return 0;
        }
        PA_EasyBgScrollXY(1,3,PA_BgInfo[0][2].ScrollX/2,PA_BgInfo[0][2].ScrollY/2);
        PA_EasyBgScrollXY(1,2,PA_BgInfo[0][2].ScrollX,PA_BgInfo[0][2].ScrollY);
        for(u8 i = 0; i <= 59; i ++) {
            if(Crystals[i].vbl(Player.x,Player.y)) crystal_counter ++;
            if(i<=8&&Cannon[i].vbl(Player.x,Player.y,true))death();
            if((i==0||i==1)&&Cierra[i].vbl(Player.x,Player.y)) death();
            else if(i==2&&Cierra[2].vblMX(Player.x,Player.y)) death();
        }
        angle ++;
        PA_SetRotsetNoZoom(1,1,angle);
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