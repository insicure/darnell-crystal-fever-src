#include "bento/FileData.hpp"
#include "bento/Scene.hpp"
#include "nds/arm9/console.h"

using namespace ppx;

class FileLoading : public Scene {
public:
  PrintConsole console;
  FileData file;

  FileLoading();
  ~FileLoading() override;
  void Preload() override;
  void Update() override;
};