#include "core.hpp"

using namespace nb;

class FileLoading : public Scene {
public:
  FileLoading();
  ~FileLoading();
  void Preload() override;
  void Update() override;
};