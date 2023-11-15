#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool check(Point2D point, int maxX, int maxY)
{
  if(point.x < maxX)
    return false;
  if(point.x > 0)
    return false;
  if(point.y < maxY)
    return false;
  if(point.y > 0)
    return false;
  else return true;
}
std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p)
{
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  if(check(p.Up(),sideOver2, sideOver2))
    visitables.push_back(p.Up());
  if(check(p.Down(),sideOver2, sideOver2))
    visitables.push_back(p.Down());
  if(check(p.Right(),sideOver2, sideOver2))
    visitables.push_back(p.Right());
  if(check(p.Left(),sideOver2, sideOver2))
    visitables.push_back(p.Left());

  return visitables;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}
bool RecursiveBacktrackerExample::Step(World* w) {
  auto rngStart = randomStartPoint(w);
  if(rngStart == Point2D{INT_MAX, INT_MAX} && stack.empty())
  {
    return false;
  }
  if(stack.empty())
  {
    stack.push_back(rngStart);
    return true;
  }
  while(!stack.empty())
  {
    Point2D current = stack.back();
    visited[current.y][current.x] = true;
    int options = getVisitables(w, current).size();
    if(options == 1)
    {
      Point2D pt = getVisitables(w, current).at(0);
      if(pt.Up() == current && pt.Up().y < INT_MAX)
        w->GetNode(current).SetSouth(false);
      if(pt.Down() == current && pt.Down().y > -INT_MAX)
        w->GetNode(current).SetNorth(false);
      if(pt.Left() == current && pt.Left().x > -INT_MAX)
        w->GetNode(current).SetEast(false);
      if(pt.Right() == current && pt.Right().x < INT_MAX)
        w->GetNode(current).SetWest(false);
    }
    else if(options != 0)
    {
      auto neighs = getVisitables(w, current);
      int numV = neighs.size();

      int decision = Random::Range(0, numV);

      Point2D pts = getVisitables(w, current).at(decision);
      if(pts.Up() == current)
        w->GetNode(current).SetSouth(false);
      if(pts.Down() == current)
        w->GetNode(current).SetNorth(false);
      if(pts.Left() == current)
        w->GetNode(current).SetEast(false);
      if(pts.Right() == current)
        w->GetNode(current).SetWest(false);
    }
    else if(options == 0)
    {
      RecursiveBacktrackerExample();
    }
  }

  return true;
}
