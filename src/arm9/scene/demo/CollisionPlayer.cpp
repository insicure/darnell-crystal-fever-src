#include "ppx/Drawing.hpp"
#include "ppx/Math.hpp"
#include "ppx/Memory.hpp"
#include "ppx/TextureAtlas.hpp"
#include "nds/arm9/input.h"
#include "nds/input.h"
#include "CollisionPlayer.hpp"
#include <cstdint>
#include <cstdlib>
#include <ctime>

CollisionPlayer::CollisionPlayer()
{
  videoSetMode(MODE_0_3D);
  videoSetModeSub(MODE_0_2D);

  vramSetPrimaryBanks(
    VRAM_A_TEXTURE,
    VRAM_B_TEXTURE,
    VRAM_C_SUB_BG_0x06200000,
    VRAM_D_MAIN_BG_0x06000000);

  vramSetBankF(VRAM_F_TEX_PALETTE);

  lcdMainOnBottom();
  InitDrawing();

  consoleInit(&console, 1, BgType_Text4bpp, BgSize_T_256x256, 22, 3, false, true);
  consoleSelect(&console);

  setBrightness(3, -16);
  srand(time(nullptr));
}

CollisionPlayer::~CollisionPlayer()
{
  Unload_TextureAtlas(atlas);
  ppx_free(map);
}

void CollisionPlayer::Preload()
{
  atlas = Load_TextureAtlas("nitro:/atlas/prototype.txt");

  // prepare map data
  {
    map = ppx_malloc<uint8_t>(MAP_WIDTH*MAP_HEIGHT);

    for (int i=0; i<MAP_WIDTH*MAP_HEIGHT; i++)
      map[i] = ((rand() % 10) < 8) ? 0 : 1;

    for (int i=0; i<MAP_WIDTH; i++)
    {
      map[i] = 1;
      map[i + (MAP_HEIGHT-1)*MAP_WIDTH] = 1;
    }

    for (int i=0; i<MAP_HEIGHT; i++)
    {
      map[i*MAP_WIDTH] = 1;
      map[i*MAP_WIDTH + (MAP_WIDTH-1)] = 1;
    }

  }

  // prepare player
  {
    player = (*atlas)["player"];

    Vec2 position(1, 1);
    player_position = Vec2(
      position.x*TILEW + TILEW/2,
      position.y*TILEH + TILEH/2);

    // prevent player spawn blocked
    map[position.y.toInt()*MAP_WIDTH + position.x.toInt()] = 0;
  }

  cam.Set(
    Vec2(MAP_WIDTH/2*TILEW + TILEW, MAP_HEIGHT/2*TILEH + TILEH),
    Vec2(MAP_WIDTH/2*TILEW, MAP_HEIGHT/2*TILEH),
    0, 1);

  consoleClear();
  // printf("Arrow Keys - Move camera\n");
  // printf("L/R - Rotate camera\n");
  // printf("X/Y - Zoom camera\n");
  // printf("Start - Reset camera\n");

  setBrightness(3, 0);
}

bool CollisionPlayer::isWalkable(int tileX, int tileY)
{
  if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT)
    return false; // Out of bounds
  
  return map[tileY * MAP_WIDTH + tileX] == 0;
}

void CollisionPlayer::Move(Vec2 direction)
{
  f32 length = Math::sqrt(direction.x*direction.x + direction.y*direction.y);
  Vec2 delta((direction.x/length)*PLAYER_SPEED, (direction.y/length)*PLAYER_SPEED);

  Vec2 newpos(player_position.x + delta.x, player_position.y+delta.y);

  // horizontal check
  {
    Rect collision(
      newpos.x - player->width/2 + 1,
      player_position.y - player->height/2 + 1,
      player->width - 2,
      player->height - 2);
    
    if (direction.x < 0)
    {
      bool left_top = isWalkable((collision.Left() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool left_bot = isWalkable((collision.Left() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!left_top || !left_bot)
        newpos.x = ((collision.Left() / TILEW).toInt()+1) * TILEW + player->width/2;
    }
    else if (direction.x > 0)
    {
      bool right_top = isWalkable((collision.Right() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool right_bot = isWalkable((collision.Right() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!right_top || !right_bot)
        newpos.x = ((collision.Right() / TILEW).toInt()) * TILEW - player->width/2;
    }
  }

  // vertical check
  {
    Rect collision(
      player_position.x - player->width/2 + 1,
      newpos.y - player->height/2 + 1,
      player->width - 2,
      player->height - 2);

    if (direction.y < 0)
    {
      bool top_left = isWalkable((collision.Left() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool top_right = isWalkable((collision.Right() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      if (!top_left || !top_right)
        newpos.y = ((collision.Top() / TILEH).toInt()+1) * TILEH + player->height/2;
    }
    else if (direction.y > 0)
    {
      bool bot_left = isWalkable((collision.Left() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      bool bot_right = isWalkable((collision.Right() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!bot_left || !bot_right)
        newpos.y = ((collision.Bottom() / TILEH).toInt()) * TILEH - player->height/2;
    }
  }


  player_position = newpos;
}

void CollisionPlayer::Update()
{
  // input
  {
    if      (keysHeld() & KEY_LEFT && keysHeld() & KEY_UP) Move({-1, -1});
    else if (keysHeld() & KEY_LEFT && keysHeld() & KEY_DOWN) Move({-1, 1});
    else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_UP) Move({1, -1});
    else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_DOWN) Move({1, 1});
    else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_LEFT) Move({0, 0});
    else if (keysHeld() & KEY_UP && keysHeld() & KEY_DOWN) Move({0, 0});
    else if (keysHeld() & KEY_LEFT) Move({-1, 0});
    else if (keysHeld() & KEY_RIGHT) Move({1, 0});
    else if (keysHeld() & KEY_UP) Move({0, -1});
    else if (keysHeld() & KEY_DOWN) Move({0, 1});
  }

  // logic
  {
    

    // collision check

    // top left
  }

  // render
  {
    BeginDrawing();
    ClearBackground(Color::White());

    for (int y=0; y<MAP_HEIGHT; y++)
    {
      for (int x=0; x<MAP_WIDTH; x++)
      {
        TextureMap *tex = (*atlas)[(map[y * MAP_WIDTH + x] == 0) ? "box2" : "box1"];
        if (tex) tex->Draw({x*TILEW, y*TILEH});
      }
    }

    // SetColor(Red);
    // DrawRect(player_collision);

    SetColor(Color::White());
    player->Draw(player_position, {1, 1}, {player->width/2, player->height/2});

    EndDrawing();
  }
}
