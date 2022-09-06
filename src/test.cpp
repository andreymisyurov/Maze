#include "cave.h"
#include "unistd.h"

auto main() -> int {
  // for (int i = 1; i < 15; ++i) {
  Cave temp(10, 5, 4);
  temp.generateField();
  int count;
  while (!count) {
    temp.killFrame();
    temp.writeNeighbours();
    temp.printField();
    cout << endl;
    count = temp.checkEquals();
    temp.lifeYear();
    // sleep(1);
  }

  // }

  return 0;
}
