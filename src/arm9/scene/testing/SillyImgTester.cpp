#include "SillyImgTester.hpp"
#include "bento/Drawing.hpp"
#include "bento/Texture.hpp"
#include "nds/arm9/input.h"
#include "nds/arm9/video.h"
#include "nds/arm9/videoGL.h"
#include "nds/input.h"
#include <array>
#include <cstdio>

static const std::array<const char*, 4> tex_name {
  "rgb16", "indexed4", "indexed16", "indexed256"
};

void SillyImgTester::LoadTexture()
{
  char path[128];
  snprintf(path, sizeof(path), "nitro:/sillyimage-tester/miku_%s.sillyimg", tex_name[selector.value]);
  printf("%s\n", tex_name[selector.value]);
  tex1.Unload();
  tex1.Load(path);
}

SillyImgTester::SillyImgTester()
{
  videoSetMode(MODE_0_3D);
  videoSetModeSub(MODE_0_2D);

  vramSetPrimaryBanks(
    VRAM_A_TEXTURE,
    VRAM_B_TEXTURE,
    VRAM_C_SUB_BG_0x06200000,
    VRAM_D_TEXTURE);

  vramSetBankF(VRAM_F_TEX_PALETTE);
  vramSetBankG(VRAM_G_TEX_PALETTE);

  lcdMainOnBottom();
  InitDrawing();

  consoleInit(&console, 1, BgType_Text4bpp, BgSize_T_256x256, 22, 3, false, true);
  consoleSelect(&console);

  setBrightness(3, -16);
}

SillyImgTester::~SillyImgTester()
{
  tex1.Unload();
}

void SillyImgTester::Preload()
{
  selector.max = tex_name.size() - 1;
  LoadTexture();

  setBrightness(3, 0);
}

void SillyImgTester::Update()
{
  if (keysUp() & KEY_RIGHT)
  {
    selector.Next();
    LoadTexture();
  }

  if (keysUp() & KEY_LEFT)
  {
    selector.Prev();
    LoadTexture();
  }

  if (keysHeld() & KEY_L)
  {
    LoadTexture();
  }

  BeginDrawing();
  ClearBackground(Color::Gray());
  tex1.Draw({32,0});
  EndDrawing();
}
