#include "nds/arm9/input.h"
#include "nds/input.h"
#include "nds/system.h"
#include "ppx/Scene.hpp"
#include "ppx/TextureAtlas.hpp"
#include "ppx/Camera.hpp"
#include "nds/arm9/console.h"
#include "ppx/Vec2.hpp"
#include "scene/demo/CharacterController.h"
#include <cstdint>

using namespace ppx;

class Jumping : public Scene {
public:

  PrintConsole console;
  TextureAtlas *atlas = nullptr;
  Camera cam;

  Vec2 player_position;
  f32 player_yvelocity;
  f32 player_jump;
  TextureMap *player_texture = nullptr;

  uint8_t *map = nullptr;

  CharacterController player;

  const f32 PLAYER_SPEED = 2.6f;
  const f32 PLAYER_GRAVITY = 0.4f;
  const f32 PLAYER_JUMP = 5.0f;

  Jumping();
  ~Jumping() override;
  void Preload() override;
  void Update() override;

  void BuildMap();
  void Move(Vec2 direction);
  bool isWalkable(int tileX, int tileY);
};