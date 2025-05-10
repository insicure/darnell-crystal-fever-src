#include "bento/App.hpp"
#include "MenuSelector.hpp"
#include "scene/testing/FileLoading.hpp"
#include "scene/testing/SillyImgTester.hpp"
#include "scene/testing/MovieclipTest.hpp"
#include "scene/testing/AnimationBasic.hpp"
#include "scene/demo/CreatingTiles.hpp"
#include "scene/demo/CollisionPlayer.hpp"
#include "scene/demo/Jumping.hpp"
#include "scene/darnell/MainMenu.hpp"
#include "utils.hpp"
#include <cstring>
#include <nds/arm9/console.h>
#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/input.h>
#include <nds/system.h>

using namespace ppx;

extern App app;

#define ITEMS_PER_PAGE 8

static SceneDesc SceneList[] = {
  SceneDesc{"AnimationBasic", "Animation testing"},
  SceneDesc{"SillyImgTester", "SillyImage testing area"},
  SceneDesc{"3. Jumping", "testing y-velocity"},
  SceneDesc{"2. CollisionPlayer", "8-way movement with gridmap collision"},
  SceneDesc{"1. CreatingTiles", "generate 2d gridmap"},
  SceneDesc{"MovieclipTest", "drawing animated texture"},
  SceneDesc{"FileLoading", "test file loading using nitrofs"},
  SceneDesc{"MainMenu", "Darnell main menu"},
};

MenuSelector::MenuSelector()
{
  videoSetMode(MODE_0_2D);
  videoSetModeSub(MODE_0_2D);

  vramSetPrimaryBanks(
    VRAM_A_LCD,
    VRAM_B_LCD,
    VRAM_C_SUB_BG_0x06200000,
    VRAM_D_MAIN_BG_0x06000000);
}

MenuSelector::~MenuSelector()
{
  
}

void MenuSelector::Preload()
{
  lcdMainOnTop();

  consoleInit(&console_main, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 1, true, true);
  consoleInit(&console_sub, 0, BgType_Text4bpp, BgSize_T_256x256, 17, 3, false, true);
  consoleSelect(&console_sub);

  counter_selected.max = ARRAYSIZE(SceneList);
  counter_page.max = (ARRAYSIZE(SceneList)-1) / ITEMS_PER_PAGE;
}

void MenuSelector::Update()
{
/// --- LOGIC --- 

  // page navigation
  {
    if (keysDown() & KEY_LEFT)
    {
      counter_selected.value = 0;
      counter_page.Prev();
    }

    if (keysDown() & KEY_RIGHT)
    {
      counter_selected.value = 0;
      counter_page.Next();
    }
  }

  // select navigation
  {
    if (keysDown() & KEY_UP) counter_selected.Prev();
    if (keysDown() & KEY_DOWN) counter_selected.Next();
  }

  // value clamp
  {
    if (counter_page.value == counter_page.max)
      counter_selected.max = (ARRAYSIZE(SceneList) - (counter_page.max)*ITEMS_PER_PAGE) - 1;
    else
      counter_selected.max = ITEMS_PER_PAGE - 1;
  }

  if (keysDown() & (KEY_A | KEY_B | KEY_X | KEY_Y))
    return selectMenu();

/// --- RENDER ---

  {
    consoleClear();
    consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
    
    consoleSetCursor(nullptr, 0, 2);
    printf("  UP/DOWN - select demo\n");
    printf("  LEFT/RIGHT - change page\n");
    printf("  A/B/X/Y - select\n");
    printf("  START+SELECT - exit\n");
    printf("  START - restart\n\n\n");

    for (int i=0; i<ITEMS_PER_PAGE; i++)
    {
      uint32_t index = counter_page.value*ITEMS_PER_PAGE + i;
      if (index > ARRAYSIZE(SceneList)-1) break;

      if (i == counter_selected.value) {
        consoleSetColor(nullptr, ConsoleColor::CONSOLE_LIGHT_GREEN);
        printf(" * %s\n", SceneList[index].name.c_str());

        consoleSelect(&console_main);
        consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
        consoleClear();
        printf("%s \n", SceneList[index].desc.c_str());
        consoleSelect(&console_sub);
      }
      else {
        consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
        printf("   %s\n", SceneList[index].name.c_str());
      }
    }

    consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
    printf("\n\n\n Page %i of %i\n", counter_page.value, counter_page.max);
  }
}

void MenuSelector::selectMenu()
{
  uint32_t index = counter_page.value*ITEMS_PER_PAGE + counter_selected.value;
  std::string name = SceneList[index].name;

  if (name == "FileLoading")
    app.SetScene(new FileLoading());

  if (name == "MainMenu")
    app.SetScene(new MainMenu());

  if (name == "MovieclipTest")
    app.SetScene(new MovieclipTest());

  if (name == "1. CreatingTiles")
    app.SetScene(new CreatingTiles());

  if (name == "2. CollisionPlayer")
    app.SetScene(new CollisionPlayer());

  if (name == "3. Jumping")
    app.SetScene(new Jumping());

  if (name == "AnimationBasic")
    app.SetScene(new AnimationBasic());

  if (name == "SillyImgTester")
    app.SetScene(new SillyImgTester());
}
