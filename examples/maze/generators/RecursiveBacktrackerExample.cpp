#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool check(Point2D point, Point2D min, Point2D max)
{
  if(point.x < min.x)
    return false;
  if(point.x > max.x)
    return false;
  if(point.y < min.y)
    return false;
  if(point.y > max.y)
    return false;

  return true;
}
std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p)
{
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  if(check(p.Up(), Point2D(-sideOver2, -sideOver2), Point2D(sideOver2, sideOver2)))
    visitables.push_back(p.Up());
  if(check(p.Down(),Point2D(-sideOver2, -sideOver2), Point2D(sideOver2, sideOver2)))
    visitables.push_back(p.Down());
  if(check(p.Right(),Point2D(-sideOver2, -sideOver2), Point2D(sideOver2, sideOver2)))
    visitables.push_back(p.Right());
  if(check(p.Left(),Point2D(-sideOver2, -sideOver2), Point2D(sideOver2, sideOver2)))
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
  auto sideOver2 = w->GetSize()/2;
  auto rngStart = randomStartPoint(w);
  if (rngStart == Point2D{INT_MAX, INT_MAX} && stack.empty()) {
    return false;
  }
  if (stack.empty()) {
    stack.push_back(rngStart);
    return true;
  }

  Point2D current = stack.back();

  w->SetNodeColor(current, CURRENT);
  visited[current.y][current.x] = true;
  auto v = getVisitables(w, current);
  std::vector<Point2D> options;
  for(auto iter : v)
  {
    if(!visited[iter.y][iter.x])
      options.push_back(iter);
  }
  if (!options.empty()) {
    int numV = options.size();

    int decision = Random::Range(0, numV - 1);

    Point2D pt = options.at(decision);
    auto delta = pt - current;

    // right
    if(delta == Point2D(1,0) && pt.x<=sideOver2){
      w->SetNodeColor(pt, CURRENT);
      w->SetEast(current, false);
      stack.push_back(pt);
      visited[pt.y][pt.x] = true;
    }
    // left
    if(delta == Point2D(-1,0) && pt.x>=-sideOver2){
      w->SetNodeColor(pt, CURRENT);
      w->SetWest(current, false);
      stack.push_back(pt);
      visited[pt.y][pt.x] = true;
    }
    // up
    if(delta == Point2D(0,1) && pt.y<=sideOver2){
      w->SetNodeColor(pt, CURRENT);
      w->SetSouth(current,false);
      stack.push_back(pt);
      visited[pt.y][pt.x] = true;
    }
    // down
    if(delta == Point2D(0,-1) && pt.y>=-sideOver2){
      w->SetNodeColor(pt, CURRENT);
      w->SetNorth(current, false);
      stack.push_back(pt);
      visited[pt.y][pt.x] = true;
    }

    w->SetNodeColor(current, NXT);
    return true;
  }
  else if (options.empty()) {
    w->SetNodeColor(current, POPBACK);
    stack.pop_back();
    return true;
  }
}