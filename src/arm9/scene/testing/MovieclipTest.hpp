#pragma once

#include "bento/Scene.hpp"
#include "bento/TextureAtlas.hpp"
#include "nds/arm9/console.h"

using namespace ppx;

class MovieclipTest : public Scene
{
public:
  PrintConsole console;
  TextureAtlas atlas;

  MovieclipTest();
  ~MovieclipTest() override;
  void Preload() override;
  void Update() override;
};