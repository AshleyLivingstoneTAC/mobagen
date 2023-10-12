#include "Catcher.h"
#include "World.h"
#include <vector>
#include <queue>
#include <unordered_map>

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    std::queue<Point2D> frontier;
    std::unordered_map<Point2D, Point2D> came_from;
    std::vector<Point2D> path;
    std::vector<Point2D> goal;

    for(int x = 0; x < side * 2; x++)
    {
      for(int y = 0; y < side * 2; y++)
      {
        Point2D pt = Point2D(x,y);
        if(world->catWinsOnSpace(pt))
        {
          goal.push_back(pt);
        }
      }
    }

   Point2D current = frontier.front();

   while (current != world->getCat())
    {
      path.push_back(current);
      current = came_from[current];
    }

    path.push_back(world->getCat());
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;

  }
}
