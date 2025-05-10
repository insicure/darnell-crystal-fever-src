#include "bento/Scene.hpp"
#include "bento/TextureAtlas.hpp"
#include "bento/Camera.hpp"
#include "bento/Texture.hpp"
#include "bento/Vec2.hpp"
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
  TextureAtlas atlas;
  Camera cam;

  Vec2 player_position;
  Texture *player;

  uint8_t *map;

  const f32 PLAYER_SPEED = 2.6f;

  CollisionPlayer();
  ~CollisionPlayer() override;
  void Preload() override;
  void Update() override;

  void Move(Vec2 direction);
  bool isWalkable(int tileX, int tileY);
};