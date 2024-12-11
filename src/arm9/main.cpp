#include "filesystem.h"
#include "core.hpp"
#include "scene/MenuSelector.hpp"
#include <nds/arm9/console.h>
#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/input.h>
#include <nds/interrupts.h>

using namespace nb;
App app;

int main()
{
  consoleDemoInit();
  consoleDebugInit(DebugDevice_NOCASH);

  nitroFSInit(nullptr);

  app.SetScene(new MenuSelector());

  while (true) {
    scanKeys();

    if (keysUp() & KEY_START) app.SetScene(new MenuSelector());
    if (keysHeld() == (KEY_START | KEY_SELECT)) break;

    app.AppUpdate();
    swiWaitForVBlank();
  }
  return 0;
}