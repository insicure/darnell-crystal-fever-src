#include "ppx/Drawing.hpp"
#include "MainMenu.hpp"
#include "ppx/FileData.hpp"
#include "ppx/SillyImage.hpp"
#include "nds/arm9/background.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/sassert.h"
#include "nds/arm9/video.h"
#include "nds/input.h"
#include "nds/system.h"
#include "nds/touch.h"
#include "palib_fallback.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sys/_intsup.h>

MainMenu::MainMenu()
{
  videoSetMode(MODE_3_3D);
  videoSetModeSub(MODE_3_2D);

  vramSetPrimaryBanks(
    VRAM_A_TEXTURE,
    VRAM_B_LCD,
    VRAM_C_SUB_BG_0x06200000,
    VRAM_D_MAIN_BG_0x06000000);
  
  vramSetBankF(VRAM_F_TEX_PALETTE);

  lcdMainOnBottom();
  InitDrawing();

  bgMain = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 1, 0);
  bgSub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 1, 0);

  consoleInit(&consoleMain, 1, BgType_Text4bpp, BgSize_T_256x256, 7, 0, true, true);
  consoleInit(&consoleSub, 1, BgType_Text4bpp, BgSize_T_256x256, 7, 0, false, true);

  // turn off screen while preload data to avoid flickering effect
  setBrightness(3, -16);
}

MainMenu::~MainMenu()
{
  Unload_SillyImage(TitleScreen);
  Unload_SillyImage(TitleScreen2);
}

void MainMenu::Preload()
{
  TitleScreen = Load_SillyImage("nitro:/background/TitleScreen.sillyimg");
  sassert(TitleScreen, "failed to load TitleScreen!");

  TitleScreen2 = Load_SillyImage("nitro:/background/TitleScreen2.sillyimg");
  sassert(TitleScreen2, "failed to load TitleScreen2!");

  dmaCopy(TitleScreen2->data, bgGetGfxPtr(bgMain), TitleScreen2->width*TitleScreen2->height);
  // dmaCopy(TitleScreen2.map->data, bgGetMapPtr(bgMain), TitleScreen2.map->length);
  dmaCopy(TitleScreen2->palette_data, BG_PALETTE, sizeof(uint16_t)*TitleScreen2->palette_count);

  dmaCopy(TitleScreen->data, bgGetGfxPtr(bgSub), TitleScreen2->width*TitleScreen2->height);
  // dmaCopy(TitleScreen2.map->data, bgGetMapPtr(bgSub), TitleScreen2.map->length);
  dmaCopy(TitleScreen2->palette_data, BG_PALETTE_SUB, sizeof(uint16_t)*TitleScreen2->palette_count);

  consoleSelect(&consoleSub);
  printf("\033[11;12H\033[KDarnell:");
  printf("\033[12;10H\033[KCrystal Fever");

  fade.Set(3, -16, 0);

  // clear 3d engine first time
  BeginDrawing();
  ClearBackground(Color::Blank());
  EndDrawing();
}

void MainMenu::Update()
{
  switch (state)
  {
    case IDLE:
    {
      frameCounter = (frameCounter+1) % 50;
      bool enableInput = fade.Step();

      consoleSelect(&consoleMain);
      if (frameCounter < 30) printf("\033[12;10H\033[KPress Start.");
      else printf("\033[12;10H\033[K");

      if (enableInput && (keysDown() & (KEY_START | KEY_TOUCH)))
      {
        fade.StepForce(3, 0, -16);
        consoleClear();
        fade.Set(3, -16, 0);

        dmaCopy(TitleScreen2->data, bgGetGfxPtr(bgMain), TitleScreen2->width*TitleScreen2->height*sizeof(uint16_t));
        // dmaCopy(TitleScreen2.map->data, bgGetMapPtr(bgMain), TitleScreen2.map->length);
        // dmaCopy(TitleScreen2->palette_data, BG_PALETTE, sizeof(uint16_t)*TitleScreen2->palette_count);

        state = SELECTSCREEN;
      }
      break;
    }

    case SELECTSCREEN:
    {
      // bool enableInput = fade.Step();
      touchPosition touch;
      touchRead(&touch);

      // const Rect guiRect[] {
      //   {90, 32, gui_play_0.width, gui_play_0.height},
      //   {90, 96, gui_settings_0.width, gui_settings_0.height}
      // };

      // if (enableInput)
      // {
        // if ((keysUp() & KEY_TOUCH) && Check_PointRect({touch.px, touch.py}, guiRect[0]))
        //   fdz1()

      //   if ((GetTouch(RELEASE, touch)) && Check_PointRect({touch.px, touch.py}, guiRect[1]))
      //   {
      //     fade.StepForce(3, 0, -16);
      //     fade.Set(3, -16, 0);

      //     dmaCopy(TitleScreen2.tex, bgGetGfxPtr(bgMain), TitleScreen2.tex_length);
      //     dmaCopy(TitleScreen2.map, bgGetMapPtr(bgMain), TitleScreen2.map_length);
      //     dmaCopy(TitleScreen2.pal, BG_PALETTE, sizeof(uint16_t)*16);

      //     dmaCopy(TitleScreen.tex, bgGetGfxPtr(bgSub), TitleScreen.tex_length);
      //     dmaCopy(TitleScreen.map, bgGetMapPtr(bgSub), TitleScreen.map_length);
      //     dmaCopy(TitleScreen.pal, BG_PALETTE, sizeof(uint16_t)*16);

      //     BeginDrawing();
      //     ClearBackground(Blank);
      //     EndDrawing();

      //     state = SETTINGS;
      //     break;
      //   }
      // }

      // const SpriteMap &play = ((keysHeld() & KEY_TOUCH) && Check_PointRect({touch.px, touch.py}, guiRect[0]))
      //   ? gui_play_1 : gui_play_0;

      // const SpriteMap &settings = ((keysHeld() & KEY_TOUCH) && Check_PointRect({touch.px, touch.py}, guiRect[1]))
      //   ? gui_settings_1 : gui_settings_0;

      // BeginDrawing();
      // ClearBackground(Blank);
      // DrawSprite(gui_tex, play, {guiRect[0].x, guiRect[0].y}, 0, 1);
      // DrawSprite(gui_tex, settings, {guiRect[1].x, guiRect[1].y}, 0, 1);
      // EndDrawing();

      break;
    }

    case SETTINGS:
    {
      fade.StepForce(3, -16, 0);
      while(true) {}
      // state = IDLE;
      break;
    }

    case END:
    {
      fade.StepForce(3, 0, -16);

      state = IDLE;
      break;
    }
    
  }
}
