#include "ppx/FileData.hpp"
#include "ppx/Memory.hpp"
#include "ppx/Scene.hpp"
#include "ppx/SillyImage.hpp"
#include "ppx/Texture.hpp"
#include "nds/arm9/console.h"
#include "palib_fallback.hpp"

using namespace ppx;

enum SceneState {
  IDLE, SELECTSCREEN, SETTINGS, END
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

  SillyImage *TitleScreen = nullptr;
  SillyImage *TitleScreen2 = nullptr;

  MainMenu();
  ~MainMenu() override;
  void Preload() override;
  void Update() override;
};