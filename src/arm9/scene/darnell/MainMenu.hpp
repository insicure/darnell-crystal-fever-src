#include "bento/FileData.hpp"
#include "bento/Scene.hpp"
#include "bento/Texture.hpp"
#include "nds/arm9/console.h"
#include "palib_fallback.hpp"

using namespace ppx;

enum SceneState {
  IDLE, SELECTSCREEN, SETTINGS, END
};

struct Background {
  FileData tex;
  FileData map;
  FileData pal;

  inline void Unload()
  {
    tex.Unload();
    map.Unload();
    pal.Unload();
  }
};

class MainMenu : public Scene {
public:
  PrintConsole consoleMain;
  PrintConsole consoleSub;

  int bgMain;
  int bgSub;
  int frameCounter = 0;
  
  BrightnessFade fade;

  SceneState state = SceneState::IDLE;

  Background TitleScreen;
  Background TitleScreen2;
  Texture gui_tex;

  MainMenu();
  ~MainMenu() override;
  void Preload() override;
  void Update() override;
};