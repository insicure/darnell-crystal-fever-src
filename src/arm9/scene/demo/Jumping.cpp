#include "bento/Drawing.hpp"
#include "bento/Math.hpp"
#include "nds/arm9/input.h"
#include "nds/input.h"
#include "Jumping.hpp"
#include <cstdlib>
#include <ctime>

Jumping::Jumping()
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

void Jumping::Preload()
{
  atlas.Load("nitro:/atlas/prototype.txt");

  // prepare map data
  {
    map = (uint8_t*)calloc(sizeof(uint8_t), MAP_WIDTH*MAP_HEIGHT);

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
    player_texture = atlas["player"];

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
  printf("Arrow Keys - Move player\n");
  printf("A/B - Jump\n");
  printf("Start - Reset\n");

  setBrightness(3, 0);
}

Jumping::~Jumping()
{
  atlas.Unload();
  free(map);
}

void Jumping::Move(Vec2 direction)
{
  f32 length = math::sqrt(direction.x*direction.x + direction.y*direction.y);
  Vec2 delta((direction.x/length)*PLAYER_SPEED, (direction.y/length)*std::abs(player_yvelocity.toFloat()));

  Vec2 newpos(player_position.x + delta.x, player_position.y+delta.y);

  // horizontal check
  {
    Rect collision(
      newpos.x - player_texture->width/2 + 1,
      player_position.y - player_texture->height/2 + 1,
      player_texture->width - 2,
      player_texture->height - 2);

    if (direction.x < 0)
    {
      bool left_top = isWalkable((collision.Left() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool left_bot = isWalkable((collision.Left() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!left_top || !left_bot)
        newpos.x = ((collision.Left() / TILEW).toInt()+1) * TILEW + player_texture->width/2;
    }
    else if (direction.x > 0)
    {
      bool right_top = isWalkable((collision.Right() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool right_bot = isWalkable((collision.Right() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!right_top || !right_bot)
        newpos.x = ((collision.Right() / TILEW).toInt()) * TILEW - player_texture->width/2;
    }
  }

  // vertical check
  {
    Rect collision(
      player_position.x - player_texture->width/2 + 1,
      newpos.y - player_texture->height/2 + 1,
      player_texture->width - 2,
      player_texture->height - 2);

    if (direction.y < 0)
    {
      bool top_left = isWalkable((collision.Left() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      bool top_right = isWalkable((collision.Right() / TILEW).toInt(), (collision.Top() / TILEH).toInt());
      if (!top_left || !top_right)
      {
        newpos.y = ((collision.Top() / TILEH).toInt()+1) * TILEH + player_texture->height/2;
        player_yvelocity = 0;
        player_jump = 0;
      }
    }
    else if (direction.y > 0)
    {
      bool bot_left = isWalkable((collision.Left() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      bool bot_right = isWalkable((collision.Right() / TILEW).toInt(), (collision.Bottom() / TILEH).toInt());
      if (!bot_left || !bot_right)
      {
        newpos.y = ((collision.Bottom() / TILEH).toInt()) * TILEH - player_texture->height/2;
        player_yvelocity = 0;
        player_jump = 0;
      }
    }
  }


  player_position = newpos;
}

bool Jumping::isWalkable(int tileX, int tileY)
{
  if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT)
    return false; // Out of bounds

  return map[tileY * MAP_WIDTH + tileX] == 0;
}

void Jumping::Update()
{
  // input
  {
    // if      (keysHeld() & KEY_LEFT && keysHeld() & KEY_UP) Move({-1, -1});
    // else if (keysHeld() & KEY_LEFT && keysHeld() & KEY_DOWN) Move({-1, 1});
    // else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_UP) Move({1, -1});
    // else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_DOWN) Move({1, 1});
    
    if      (keysHeld() & KEY_RIGHT && keysHeld() & KEY_LEFT) Move({0, 0});
    else if (keysHeld() & KEY_UP && keysHeld() & KEY_DOWN) Move({0, 0});
    
    else if (keysHeld() & KEY_LEFT) Move({-1, 0});
    else if (keysHeld() & KEY_RIGHT) Move({1, 0});
    else if (keysHeld() & KEY_UP) Move({0, -1});
    else if (keysHeld() & KEY_DOWN) Move({0, 1});

    if (keysDown() & KEY_A || keysDown() & KEY_B)
    {
      player_jump = -PLAYER_JUMP;
      player_yvelocity = player_jump;
    }

    if (keysDown() & KEY_START)
    {
      // prepare map data
      {
        map = (uint8_t*)calloc(sizeof(uint8_t), MAP_WIDTH*MAP_HEIGHT);

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
        player_texture = atlas["player"];

        Vec2 position(1, 1);
        player_position = Vec2(
          position.x*TILEW + TILEW/2,
          position.y*TILEH + TILEH/2);

        // prevent player spawn blocked
        map[position.y.toInt()*MAP_WIDTH + position.x.toInt()] = 0;
      }
    }
  }

  // y velocity logic
  {
    if (player_yvelocity > 0)
      player_yvelocity += PLAYER_GRAVITY * 1.4f;
    else if (player_yvelocity <= 0)
      player_yvelocity += PLAYER_GRAVITY;
    
    // player_yvelocity += player_jump;
    if (player_jump < 0) player_jump += PLAYER_GRAVITY;
    else player_jump = 0;
    
    if (player_yvelocity > 0) Move({0, 1});
    else Move({0, -1});
  }

  // render
  {
    BeginDrawing();
    ClearBackground(Color::White());

    for (int y=0; y<MAP_HEIGHT; y++)
    {
      for (int x=0; x<MAP_WIDTH; x++)
      {
        const TextureMap *tex = atlas[(map[y * MAP_WIDTH + x] == 0) ? "box2" : "box1"];
        if (tex) tex->Draw(Vec2(x*TILEW, y*TILEH), 0);
      }
    }

    // SetColor(Red);
    // DrawRect(player_collision);

    SetColor(Color::White());
    player_texture->Draw(player_position, 0, 0, Vec2(1, 1), Vec2(player_texture->width/2, player_texture->height/2));

    EndDrawing();
  }
}