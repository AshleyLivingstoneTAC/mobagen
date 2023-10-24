#include "JohnConway.h"
#include <iostream>
// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  for (int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {
      Point2D pt = Point2D(x, y);
      auto count = CountNeighbors(world, pt) ;
      auto isAlive = world.Get(pt);
      if (count <= 1 && isAlive) {
        world.SetNext(pt, false);
      }
      if (count >= 4 && isAlive) {
        world.SetNext(pt, false);
      }
      if (count == 3 && !isAlive) {
        world.SetNext(pt, true);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int n = 0;
  if (world.Get(point.Up())) n++;
  if (world.Get(point.Up() + point.Left())) n++;
  if (world.Get(point.Up() + point.Right())) n++;
  if (world.Get(point.Down())) n++;
  if (world.Get(point.Down() + point.Left())) n++;
  if (world.Get(point.Down() + point.Right())) n++;
  if (world.Get(point.Left())) n++;
  if (world.Get(point.Right())) n++;
  return n;
}
