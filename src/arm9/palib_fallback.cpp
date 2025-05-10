#include "palib_fallback.hpp"
#include "nds/arm9/video.h"
#include "nds/interrupts.h"

extern bool disableGlobal;

void BrightnessFade::Set(int screen, int from, int to)
{
  this->screen = screen;
  this->from = from;
  this->to = to;
  this->value = from;
}

bool BrightnessFade::Step()
{
  if (from == to || value == to) return true;

  if (from < to) setBrightness(screen, value++);
  else setBrightness(screen, value--);
  
  return false;
}

void BrightnessFade::StepForce(int screen, int from, int to)
{
  if (from < to)
  {
    for(int i=from; i<to; i++)
    {
      setBrightness(screen, i);
      swiWaitForVBlank();
    }
  }
  else
  {
    for(int i=from; i>=to; i--)
    {
      setBrightness(screen, i);
      swiWaitForVBlank();
    }
  }

  this->screen = screen;
  this->from = from;
  this->to = to;
  this->value = to;
}
