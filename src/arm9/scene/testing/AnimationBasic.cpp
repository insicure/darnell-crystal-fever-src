#include "AnimationBasic.hpp"
#include "bento/CircularCounter.hpp"
#include "bento/Drawing.hpp"
#include "bento/Texture.hpp"
#include "bento/Tracelog.hpp"
#include "nds/arm9/background.h"
#include "nds/arm9/input.h"
#include "nds/arm9/video.h"
#include <cstdio>
#include <vector>

using namespace ppx;

AnimationBasic::AnimationBasic()
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
}

AnimationBasic::~AnimationBasic()
{
  atlas.Unload();
}

static std::vector<Texture*> anim = std::vector<Texture*>();

void AnimationBasic::Preload()
{
  atlas.Unload();
  anim.clear();
  anim.reserve(10);
  setBrightness(3, 0);
}


void AnimationBasic::Update()
{
  if (keysUp() & KEY_L)
  {
    atlas.Load("nitro:/atlas/cat.txt");
    anim.push_back(atlas["run1"]);
    anim.push_back(atlas["run2"]);
    anim.push_back(atlas["run3"]);
    anim.push_back(atlas["run4"]);
    anim.push_back(atlas["run5"]);
    anim.push_back(atlas["run6"]);
    anim.push_back(atlas["run7"]);
    anim.push_back(atlas["run8"]);
    anim.push_back(atlas["run9"]);
    anim.push_back(atlas["run10"]);

    TraceLog("pressed!");
  }

  if (keysUp() & KEY_R)
  {
    atlas.Unload();
    anim.clear();
    anim.reserve(10);
    return;
  }

  
  BeginDrawing();
  ClearBackground(Color::Gray());

  if (atlas.isValid())
  {
    static int frame = 0;
    static CircularCounter framecounter(anim.size()-1);

    Texture *tex = anim[framecounter.value];

    frame++;
    if (frame % 4 == 0) framecounter.Next();

    if (tex)
    {
      tex->Draw({0, 0}, 0);
    }
  }
  EndDrawing();
}

