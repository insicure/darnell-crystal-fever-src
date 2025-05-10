#pragma once

class BrightnessFade
{
public:
  int screen;
  int from;
  int to;
  int value;

  constexpr BrightnessFade() : screen(3), from(0), to(0), value(0) { }
  constexpr BrightnessFade(int screen, int from, int to)
    : screen(screen), from(from), to(to), value(from) { }

  void Set(int screen, int from, int to);
  bool Step();
  void StepForce(int screen, int from, int to);
};