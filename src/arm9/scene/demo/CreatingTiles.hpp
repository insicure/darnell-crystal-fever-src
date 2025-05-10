#include "bento/Scene.hpp"
#include "bento/Camera.hpp"
#include "bento/TextureAtlas.hpp"
#include "nds/arm9/console.h"
#include <cstdint>

using namespace ppx;

class CreatingTiles : public Scene {
public:
  PrintConsole console;
  TextureAtlas atlas;
  Camera cam;

  uint8_t *map;

  CreatingTiles();
  ~CreatingTiles() override;
  void Preload() override;
  void Update() override;
};