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
    std::vector<Point2D> goal = world->



    //path.push_back(world->getCat());
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;

  }
}
