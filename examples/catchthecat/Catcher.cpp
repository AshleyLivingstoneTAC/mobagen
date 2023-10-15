#include "Catcher.h"
#include "World.h"

#include <vector>
#include <queue>
#include <unordered_map>

Point2D Catcher::Move(World* world)
{
  std::queue<Point2D> frontier;
  std::unordered_map<Point2D, Point2D> came_from;
  auto pos = world->getCat();
  frontier.push(pos);
  came_from[pos] = pos;

  while(!frontier.empty())
  {
    Point2D current = frontier.front();
    frontier.pop();
    for(Point2D next : world->neighbors(pos))
    {
      if(came_from.find(next) == came_from.end() && world->catCanMoveToPosition(next))
      {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
return frontier.back();
}
