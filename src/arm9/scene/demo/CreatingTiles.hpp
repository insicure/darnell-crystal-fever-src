#include "ppx/Scene.hpp"
#include "ppx/Camera.hpp"
#include "ppx/TextureAtlas.hpp"
#include "nds/arm9/console.h"
#include <cstdint>

using namespace ppx;

class CreatingTiles : public Scene {
public:
  PrintConsole console;
  TextureAtlas *atlas = nullptr;
  Camera cam;

  uint8_t *map = nullptr;

  CreatingTiles();
  ~CreatingTiles() override;
  void Preload() override;
  void Update() override;
};