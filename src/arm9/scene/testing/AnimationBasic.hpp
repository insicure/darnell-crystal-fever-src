#include "bento/Scene.hpp"
#include "bento/TextureAtlas.hpp"
#include "nds/arm9/console.h"

class AnimationBasic : public ppx::Scene
{
public:
  PrintConsole console;
  ppx::TextureAtlas atlas;
  
  AnimationBasic();
  ~AnimationBasic() override;
  void Preload() override;
  void Update() override;
};