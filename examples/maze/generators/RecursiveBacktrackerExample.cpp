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
  Point2D rngPt = Point2D(Random::Range(-sideOver2, sideOver2), Random::Range(-sideOver2, sideOver2));
  if (!visited[rngPt.y][rngPt.x]) return {rngPt.x, rngPt.y};
  else return {INT_MAX, INT_MAX};
}
bool RecursiveBacktrackerExample::Step(World* w) {
  auto rngStart = randomStartPoint(w);
  if (rngStart == Point2D{INT_MAX, INT_MAX} && stack.empty()) {
    return false;
  }
  if (stack.empty()) {
    stack.push_back(rngStart);
    return true;
  }

  Point2D current = stack.back();
  w->SetNodeColor(current, Color32(255, 0, 0, 255));
  visited[current.y][current.x] = true;
  auto options = getVisitables(w, current);
  if (options.size() == 1) {
    Point2D pt = options.at(0);
    if (pt.Up() == current && pt.Up().y < INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetSouth(true);
      stack.push_back(current.Down());
    }
    if (pt.Down() == current && pt.Down().y > -INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetNorth(false);
      stack.push_back(current.Up());
    }
    if (pt.Left() == current && pt.Left().x > -INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetEast(false);
      stack.push_back(current.Right());
    }
    if (pt.Right() == current && pt.Right().x < INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetWest(false);
      stack.push_back(current.Left());
    }
    return true;
  } else if (options.size() != 0) {
    auto neighs = getVisitables(w, current);
    int numV = neighs.size();

    int decision = Random::Range(0, numV - 1);

    Point2D pt = getVisitables(w, current).at(decision);
    if (pt.Up() == current && pt.Up().y < INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetSouth(false);
      stack.push_back(current.Down());
    }
    if (pt.Down() == current && pt.Down().y > -INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetNorth(false);
      stack.push_back(current.Up());
    }
    if (pt.Left() == current && pt.Left().x > -INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetEast(false);
      stack.push_back(current.Right());
    }
    if (pt.Right() == current && pt.Right().x < INT_MAX) {
      w->SetNodeColor(current, NXT);
      w->GetNode(current).SetWest(false);
      stack.push_back(current.Left());
    }
    return true;
  }
  else if (options.size() == 0) {
    w->SetNodeColor(current, POPBACK);
    stack.pop_back();
    return true;
  }
}
