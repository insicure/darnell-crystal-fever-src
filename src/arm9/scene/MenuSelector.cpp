#include "MenuSelector.hpp"
#include "FileLoading.hpp"
#include <cstring>
#include <nds/arm9/console.h>
#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/input.h>
#include <nds/system.h>

using namespace nb;

extern App app;

#define ITEMS_PER_PAGE 8
#define ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

static const char* SceneList[] = {
  "FileLoading"
};

MenuSelector::MenuSelector()
{
  videoSetMode(MODE_0_3D);
  lcdMainOnTop();
  consoleDemoInit();

  counter_selected.max = ARRAYSIZE(SceneList);
  counter_page.max = ARRAYSIZE(SceneList) / ITEMS_PER_PAGE;
}

MenuSelector::~MenuSelector()
{

}

void MenuSelector::Preload()
{

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
        printf(" * %s\n", SceneList[index]);
      }
      else {
        consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
        printf("   %s\n", SceneList[index]);
      }
    }

    consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
    printf("\n\n\n Page %i of %i\n", counter_page.value, counter_page.max);
  }
}

void MenuSelector::selectMenu()
{
  uint32_t index = counter_page.value*ITEMS_PER_PAGE + counter_selected.value;
  const char* name = SceneList[index];

  if (strcmp(name, "FileLoading") == 0)
    app.SetScene(new FileLoading());
}
