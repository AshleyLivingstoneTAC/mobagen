//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for (int x = 0; x < world.SideSize(); x++) {
    for (int y = 0; y < world.SideSize(); y++) {
      Point2D* pt = new Point2D(x, y);
      if (CountNeighbors(world, *pt) <= 1 && world.Get(*pt)) {
        world.SetCurrent(*pt, false);
      }
      if (CountNeighbors(world, *pt) >= 4 && world.Get(*pt)) {
        world.SetCurrent(*pt, false);
      }
      if (CountNeighbors(world, *pt) == 3 && !world.Get(*pt)) {
        world.SetCurrent(*pt, true);
      }
    }
  }
}


  int HexagonGameOfLife::CountNeighbors(World & world, Point2D point)
{
    int n = 0;
    if (world.Get(point.UP)) n++;
    if (world.Get(point.DOWN)) n++;
    if (world.Get(point.LEFT)) n++;
    if (world.Get(point.RIGHT)) n++;
    return n;
  }
