#include "ppx/Scene.hpp"
#include "ppx/TextureAtlas.hpp"
#include "ppx/Camera.hpp"
#include "ppx/Texture.hpp"
#include "ppx/Vec2.hpp"
#include "nds/arm9/console.h"
#include <cstdint>

using namespace ppx;

#define MAP_WIDTH 12
#define MAP_HEIGHT 10
#define TILEW 20
#define TILEH 20

class CollisionPlayer : public Scene {
public:
  PrintConsole console;
  TextureAtlas *atlas = nullptr;
  Camera cam;

  Vec2 player_position;
  TextureMap *player;

  uint8_t *map;

  const f32 PLAYER_SPEED = 2.6f;

  CollisionPlayer();
  ~CollisionPlayer() override;
  void Preload() override;
  void Update() override;

  void Move(Vec2 direction);
  bool isWalkable(int tileX, int tileY);
};