#include "ppx/App.hpp"
#include "filesystem.h"
#include "libadx.h"
#include "nds/arm9/sassert.h"
#include "scene/MenuSelector.hpp"
#include <nds/arm9/console.h>
#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/input.h>
#include <nds/interrupts.h>

using namespace ppx;
bool disableGlobal = false;

int main()
{
  consoleDemoInit();
  consoleDebugInit(DebugDevice_NOCASH);

  {
    bool res = nitroFSInit(nullptr);
    sassert(res, "failed to initialize nitrofs");
    // TODO: handle nitrofs error 
  }

  {
    bool res = adx_init();
    sassert(res, "failed to initialize ADX library");
    // TODO: handle adx error 
  }

  App &app = App::Get();
  app.SetScene(new MenuSelector());

  while (true) {
    scanKeys();
    
    if (!disableGlobal)
    {
      if (keysHeld() == (KEY_START | KEY_SELECT))
        app.SetScene(new MenuSelector());
      
      // if (keysHeld() == (KEY_START | KEY_L | KEY_R)) 
      //   app.SetScene(new DebugMenu());
      
      if (keysHeld() == (KEY_START | KEY_SELECT | KEY_DOWN)) break;
    }

    app.AppUpdate();
    swiWaitForVBlank();
  }
  return 0;
}