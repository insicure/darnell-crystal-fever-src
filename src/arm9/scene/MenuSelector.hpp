#include "core.hpp"
#include "struct.hpp"

using namespace nb;

class MenuSelector : public Scene {
public:
  CircularCounter counter_selected;
  CircularCounter counter_page;

  MenuSelector();
  ~MenuSelector();
  void Preload() override;
  void Update() override;
  void selectMenu();
};