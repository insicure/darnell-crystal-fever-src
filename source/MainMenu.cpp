#include <PA9.h>
#include "all_gfx.h"
#include "fdz.h"
#include "debug.h"
#include <maxmod9.h>

void HelpScreen(void);
void SelectScreen(void);
void SettingsScreen(void);
int MainMenu(void){
    PA_ResetAll();
    PA_SetBrightness(1,-31);
    PA_SetBrightness(0,-31);

    PA_InitText(0,0);
    PA_InitText(1,0);
    PA_OutputText(0,0,0,"SDINIT0FAILED.");
    PA_ClearTextBg(0);
    PA_OutputText(0,10,12,"Press Start.");
    PA_OutputText(1,10,11,"  Darnell:\nCrystal Fever");
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    FAT_LoadBackground(0,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    
    PA_CFadeInSys();
    while(1) {
        if(Pad.Held.Start && Pad.Held.L && Pad.Held.R){
            PA_ResetAll();
            debugMenu();
            return 0;
        }
        if(Pad.Newpress.Start||Stylus.Newpress){
            PA_CFadeOutSys();
            PA_ClearTextBg(0);
            SelectScreen();
            return 0;
        }
        PA_WaitForVBL();
    }
    return 0;
}
void SelectScreen(void){
    PA_ResetSpriteSys();
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    FAT_LoadBackground(0,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    PA_LoadSprite16cPal(0,0,FatLoad("nitro:/data/graphics/titlebuttom/bPal.bin"));
    PA_LoadSprite16cPal(0,1,FatLoad("nitro:/data/graphics/titlebuttom/sound_Pal.bin"));
    //PA_LoadSprite16cPal(0,0,(void*)NewGameButton_Pal);
    PA_CreateSprite(0,0,FatLoad("nitro:/data/graphics/titlebuttom/NewGameButton_Sprite.bin"),OBJ_SIZE_64X32,0,0,90,32);
    PA_CreateSprite(0,1,FatLoad("nitro:/data/graphics/titlebuttom/settings_Sprite.bin"),OBJ_SIZE_64X32,0,0,90,96);
    PA_InitText(1,0);
    PA_OutputText(1,10,11,"  Darnell:\nCrystal Fever");
    PA_CFadeInSys();
    while(1){
        if(Pad.Held.Start && Pad.Held.L && Pad.Held.R){
            PA_ResetAll();
            debugMenu();
            return;
        }
        if(PA_SpriteTouched(0)) {
            PA_StartSpriteAnim(0,0,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            fdz1Func();
            return;
        }
        else if(PA_SpriteTouched(1)){
            PA_StartSpriteAnim(0,1,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            SettingsScreen();
            return;
        }
        PA_WaitForVBL();
    }
    return;
}
void SettingsScreen(void){
    FAT_LoadBackground(0,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_InitText(0,0);
    PA_InitText(1,0);

    PA_OutputSimpleText(0,10,3,"Game Settings");
    PA_CreateSprite(0,0,FatLoad("nitro:/data/graphics/titlebuttom/help_Sprite.bin"),OBJ_SIZE_64X32,0,0,64,48);
    PA_CreateSprite(0,1,FatLoad("nitro:/data/graphics/titlebuttom/main_Sprite.bin"),OBJ_SIZE_64X32,0,0,64,112);
    
    PA_OutputText(1,10,11,"  Game Settings");
    PA_CFadeInSys();
    while(1){
        if(PA_SpriteTouched(0)) {
            PA_StartSpriteAnim(0,0,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            HelpScreen();
            return;
        }
        else if(PA_SpriteTouched(1)){
            PA_StartSpriteAnim(0,1,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            SelectScreen();
            return;
        }
        PA_WaitForVBL();
    }

}
void HelpScreen(void){
    FAT_LoadBackground(0,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen2");
    FAT_LoadBackground(1,3,256, 192,PA_BgNormal,"nitro:/data/graphics/TitleScreen");
    PA_InitText(0,0);
    PA_InitText(1,0);
    PA_OutputSimpleText(0,12,3,"Game Help");
    PA_OutputSimpleText(0,6,5,"Darnell Crystal Fever\nVer:IDV190723\nMade with B90sR");
    //PA_CreateSprite(0,0,(void*)settings_Sprite,OBJ_SIZE_64X32,0,0,90,64);
    PA_CreateSprite(0,0,FatLoad("nitro:/data/graphics/titlebuttom/settings_Sprite.bin"),OBJ_SIZE_64X32,0,0,90,64);
    PA_CreateSprite(0,1,FatLoad("nitro:/data/graphics/titlebuttom/main_Sprite.bin"),OBJ_SIZE_64X32,0,0,90,112);
    
    PA_OutputText(1,10,11,"  Game Help");
    PA_CFadeInSys();
    while(1){
        if(PA_SpriteTouched(0)) {
            PA_StartSpriteAnim(0,0,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            SettingsScreen();
            return;
        }
        else if(PA_SpriteTouched(1)){
            PA_StartSpriteAnim(0,1,1,1,0);
            PA_CFadeOutSys();
            PA_ResetAll();
            SelectScreen();
            return;
        }
        PA_WaitForVBL();
    }
    return;
}