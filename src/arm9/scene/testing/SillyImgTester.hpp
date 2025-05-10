#include "bento/CircularCounter.hpp"
#include "bento/Scene.hpp"
#include "bento/Texture.hpp"
#include "nds/arm9/console.h"

using namespace ppx;

class SillyImgTester : public Scene {
public:
  PrintConsole console;
  CircularCounter selector;
  Texture tex1;
  Texture tex2;

  SillyImgTester();
  ~SillyImgTester() override;
  void Preload() override;
  void Update() override;

  void LoadTexture();
};