#include "bento/Camera.hpp"
#include "bento/Color.hpp"
#include "bento/Drawing.hpp"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/video.h"
#include "nds/input.h"
#include "nds/system.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "CreatingTiles.hpp"

#define MAP_WIDTH 10
#define MAP_HEIGHT 8
#define TILEW 20
#define TILEH 20

CreatingTiles::CreatingTiles()
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

CreatingTiles::~CreatingTiles()
{
  atlas.Unload();
}

void CreatingTiles::Preload()
{
  atlas.Load("nitro:/atlas/prototype.txt");

  map = (uint8_t*)malloc(MAP_WIDTH*MAP_HEIGHT * sizeof(uint8_t));
  
  for (int i=0; i<MAP_WIDTH*MAP_HEIGHT; i++)
    map[i] = rand() % 2;

  cam.Set(
    Vec2(MAP_WIDTH/2*TILEW + TILEW, MAP_HEIGHT/2*TILEH + TILEH),
    Vec2(MAP_WIDTH/2*TILEW, MAP_HEIGHT/2*TILEH),
    0, 1);

  consoleClear();
  printf("Arrow Keys - Move camera\n");
  printf("L/R - Rotate camera\n");
  printf("X/Y - Zoom camera\n");
  printf("Start - Reset camera\n");

  setBrightness(3, 0);
}

void CreatingTiles::Update()
{
  BeginDrawing();
  ClearBackground(Color::White());
  BeginCamera(cam);

  for (int y=0; y<MAP_HEIGHT; y++)
  {
    for (int x=0; x<MAP_WIDTH; x++)
    {
      Texture *tex = atlas[(map[y * MAP_WIDTH + x] == 0) ? "box2" : "box1"];
      if (tex) tex->Draw(Vec2(x*TILEW, y*TILEH), TRANS_NONE);
    }
  }

  EndCamera();
  EndDrawing();

  if (keysHeld() & KEY_LEFT) cam.offset.x += 1;
  if (keysHeld() & KEY_RIGHT) cam.offset.x -= 1;
  if (keysHeld() & KEY_UP) cam.offset.y += 1;
  if (keysHeld() & KEY_DOWN) cam.offset.y -= 1;

  if (keysHeld() & KEY_L) cam.rotation -= 1;
  if (keysHeld() & KEY_R) cam.rotation += 1;

  if (keysHeld() & KEY_X) cam.zoom -= 0.01f;
  if (keysHeld() & KEY_Y) cam.zoom += 0.01f;

  if (keysDown() & KEY_START) cam.Set(
    Vec2(MAP_WIDTH/2*TILEW + TILEW, MAP_HEIGHT/2*TILEH + TILEH),
    Vec2(MAP_WIDTH/2*TILEW, MAP_HEIGHT/2*TILEH),
    0, 1);

  if (cam.zoom < 0.1f) cam.zoom = 0.1f;
}
