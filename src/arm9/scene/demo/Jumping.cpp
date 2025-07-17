#include "nds/system.h"
#include "ppx/Camera.hpp"
#include "ppx/Drawing.hpp"
#include "ppx/Math.hpp"
#include "ppx/Memory.hpp"
#include "ppx/TextureAtlas.hpp"
#include "nds/arm9/input.h"
#include "nds/input.h"
#include "Jumping.hpp"
#include <cstdint>
#include <cstdlib>
#include <ctime>

static inline int MAP_WIDTH = 120;
static inline int MAP_HEIGHT = 12;
static inline int TILEW = 20;
static inline int TILEH = 20;

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

void Jumping::BuildMap()
{
  if (map) ppx_free(map);
  map = ppx_calloc<uint8_t>(MAP_WIDTH*MAP_HEIGHT);

  for (int i=0; i<MAP_WIDTH*MAP_HEIGHT; i++)
    map[i] = ((rand() % 10) < 8) ? 0 : 1;

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      map[y * MAP_WIDTH + x] = 0;
    }
  }

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

  Vec2 default_position(2, 1);

  player.position = {
    default_position.x*TILEW + TILEW/2,
    default_position.y*TILEH + TILEH/2
  };

  player.map_data = map;
  player.map_size = {MAP_WIDTH, MAP_HEIGHT};
  player.map_tile_size = {TILEW, TILEH};
}

void Jumping::Preload()
{
  atlas = Load_TextureAtlas("nitro:/atlas/prototype.txt");

  // prepare map data
  {
    BuildMap();
    player_texture = (*atlas)["player"];
  }

 cam.Set(
   {SCREEN_WIDTH/2, SCREEN_HEIGHT*0.6f},
   {0, 0},
   0, 1);

  consoleClear();
  printf("Arrow Keys - Move player\n");
  printf("A/B - Jump\n");
  printf("Start - Reset\n");

  setBrightness(3, 0);

  // player.position = {SCREEN_WIDTH/2, SCREEN_HEIGHT-50};
  player.hitbox = {
    -player_texture->width*0.5f,
    -player_texture->height*0.4f,
    player_texture->width*0.9f,
    player_texture->height*0.8f
  };
}

Jumping::~Jumping()
{
  Unload_TextureAtlas(atlas);
  ppx_free(map);
}

void Jumping::Move(Vec2 direction)
{
  f32 length = Math::sqrt(direction.x*direction.x + direction.y*direction.y);
  Vec2 delta((direction.x/length)*PLAYER_SPEED, (direction.y/length)*std::abs(player_yvelocity.toFloat()));

  Vec2 newpos(player_position.x + delta.x, player_position.y+delta.y);

  // horizontal check
  {
    Rect collision(
      newpos.x - player_texture->width/2 + 1,
      player_position.y - player_texture->height/2 + 1,
      player_texture->width - 2, player_texture->height - 2
    );

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

  // // input
  // {
  //   // if      (keysHeld() & KEY_LEFT && keysHeld() & KEY_UP) Move({-1, -1});
  //   // else if (keysHeld() & KEY_LEFT && keysHeld() & KEY_DOWN) Move({-1, 1});
  //   // else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_UP) Move({1, -1});
  //   // else if (keysHeld() & KEY_RIGHT && keysHeld() & KEY_DOWN) Move({1, 1});
    
  //   if      (keysHeld() & KEY_RIGHT && keysHeld() & KEY_LEFT) Move({0, 0});
  //   else if (keysHeld() & KEY_UP && keysHeld() & KEY_DOWN) Move({0, 0});
    
  //   else if (keysHeld() & KEY_LEFT) Move({-1, 0});
  //   else if (keysHeld() & KEY_RIGHT) Move({1, 0});
  //   else if (keysHeld() & KEY_UP) Move({0, -1});
  //   else if (keysHeld() & KEY_DOWN) Move({0, 1});

  //   if (keysDown() & KEY_A || keysDown() & KEY_B)
  //   {
  //     player_jump = -PLAYER_JUMP;
  //     player_yvelocity = player_jump;
  //   }

  //   if (keysDown() & KEY_START)
  //   {
  //     // prepare map data
  //     {
  //       BuildMap(map);
  //       player_texture = (*atlas)["player"];

  //       Vec2 position(1, 1);
  //       player_position = Vec2(
  //         position.x*TILEW + TILEW/2,
  //         position.y*TILEH + TILEH/2);

  //       // prevent player spawn blocked
  //       map[position.y.toInt()*MAP_WIDTH + position.x.toInt()] = 0;
  //     }
  //   }
  // }

  // // y velocity logic
  // {
  //   if (player_yvelocity > 0)
  //     player_yvelocity += PLAYER_GRAVITY * 1.4f;
  //   else if (player_yvelocity <= 0)
  //     player_yvelocity += PLAYER_GRAVITY;
    
  //   // player_yvelocity += player_jump;
  //   if (player_jump < 0) player_jump += PLAYER_GRAVITY;
  //   else player_jump = 0;
    
  //   if (player_yvelocity > 0) Move({0, 1});
  //   else Move({0, -1});
  // }

  // cam.target = player_position;
  
  // // render
  // {
  //   BeginDrawing();
  //   // BeginCamera(cam);
  //   ClearBackground(Color::White());
    
  //   int camoffsetx = ((cam.target.x - cam.offset.x) / TILEW).toInt();
  //   int camoffsety = ((cam.target.y - cam.offset.y) / TILEH).toInt();

  //   printf("\033[%d;%dHposX: %i posY: %i\033[K", 5, 1, player_position.x.toInt()/TILEW, player_position.y.toInt()/TILEH);
  //   printf("\033[%d;%dHcamX: %i camY: %i\033[K", 7, 1, cam.target.x.toInt(), cam.target.y.toInt());
    
  //   for (int y=0; y<(SCREEN_HEIGHT/TILEH)+2; y++)
  //   {
  //     for (int x=0; x<(SCREEN_WIDTH/TILEW)+2; x++)
  //     {
  //       int currx = camoffsetx + x;
  //       int curry = camoffsety + y;
        
  //       if (currx < 0 || currx > (MAP_WIDTH-1) || curry < 0 || curry > (MAP_HEIGHT-1)) continue;
        
  //       TextureMap *tex = (*atlas)[(map[curry * MAP_WIDTH + currx] == 0) ? "box2" : "box1"];
  //       if (tex) tex->Draw({currx*TILEW, curry*TILEH});
  //     }
  //   }

  //   // SetColor(Red);
  //   // DrawRect(player_collision);

  //   SetColor(Color::White());
  //   player_texture->Draw(player_position, {1, 1}, {player_texture->width/2, player_texture->height/2});

  //   // EndCamera();
  //   EndDrawing();
  // }

  if (keysDown() & KEY_START)
  {
    BuildMap();
    cam.target = {};
  }

  printf("\033[%d;%dHposition: %.1f , %.1f\033[K", 4, 1, player.position.x.toFloat(), player.position.y.toFloat());
  printf("\033[%d;%dHvelocity: %.1f , %.1f\033[K", 5, 1, player.velocity.x.toFloat(), player.velocity.y.toFloat());
  
  printf("\033[%d;%dHonGround: %i\033[K", 7, 1, player.onGround);
  printf("\033[%d;%dHcurrentlyJumping: %i\033[K", 8, 1, player.currentlyJumping);
  printf("\033[%d;%dHcanJumpAgain: %i\033[K", 9, 1, player.canJumpAgain);
  printf("\033[%d;%dHgravMultiplier: %.2f\033[K", 10, 1, player.gravMultiplier.toFloat());

  printf("\033[%d;%dHcoyoteTimeCounter: %.2f\033[K", 12, 1, player.coyoteTimeCounter.toFloat());
  printf("\033[%d;%dHjumpBufferCounter: %.2f\033[K", 13, 1, player.jumpBufferCounter.toFloat());

  player.Update(
    (keysHeld() & KEY_LEFT),
    (keysHeld() & KEY_RIGHT),
    ((keysDown() & KEY_B) || (keysDown() & KEY_A)),
    ((keysUp() & KEY_B) || (keysUp() & KEY_A)),
    1.0f / 60.0f
  );

  cam.target = {
    cam.target.x + (player.position.x - cam.target.x) * 0.2f,
    cam.target.y + (player.position.y - cam.target.y) * 0.1f
  };

  // camera clamp
  {
    // X axis
    if (cam.target.x - cam.offset.x < 0) {
      cam.target.x = cam.offset.x;
    }
    else if (cam.target.x + cam.offset.x > (MAP_WIDTH+1) * TILEW) {
      cam.target.x = (MAP_WIDTH+1) * TILEW - cam.offset.x;
    }
  
    // Y axis
    if (cam.target.y - cam.offset.y < 0) {
      cam.target.y = cam.offset.y;
    }
    else if (cam.target.y + cam.offset.y > (MAP_HEIGHT+2) * TILEH) {
      cam.target.y = (MAP_HEIGHT+2) * TILEH - cam.offset.y;
    }
  }

  BeginDrawing();
  BeginCamera(cam);
  ClearBackground(Color::White());

  {
    int camoffsetx = ((cam.target.x - cam.offset.x) / TILEW).toInt();
    int camoffsety = ((cam.target.y - cam.offset.y) / TILEH).toInt();

    for (int y=0; y<(SCREEN_HEIGHT/TILEH)+2; y++)
    {
      for (int x=0; x<(SCREEN_WIDTH/TILEW)+2; x++)
      {
        int currx = camoffsetx + x;
        int curry = camoffsety + y;
        
        if (currx < 0 || currx > (MAP_WIDTH-1) || curry < 0 || curry > (MAP_HEIGHT-1)) continue;
        
        TextureMap *tex = (*atlas)[(map[curry * MAP_WIDTH + currx] == 0) ? "box2" : "box1"];
        if (tex) tex->Draw({currx*TILEW, curry*TILEH});
      }
    }
  }

  player_texture->Draw({player.position.x, player.position.y}, {1, 1}, {player_texture->width/2, player_texture->height/2});
  SetColor(Color::Red());
  DrawRectLines({
    player.position.x+player.hitbox.x,
    player.position.y+player.hitbox.y,
    player.hitbox.width, player.hitbox.height
  });

  EndCamera();
  EndDrawing();
}