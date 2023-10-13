#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> getVisitableNeighbors(World* w, Point2D current)
{
    std::vector<Point2D> eligible;
   if(w->isValidPosition(w->E(current)))
     eligible.push_back(w->E(current));
   if(w->isValidPosition(w->NE(current)))
     eligible.push_back(w->NE(current));
   if(w->isValidPosition(w->SE(current)))
     eligible.push_back(w->SE(current));
   if(w->isValidPosition(w->NW(current)))
     eligible.push_back(w->NW(current));
   if(w->isValidPosition(w->SW(current)))
     eligible.push_back(w->SW(current));
   if(w->isValidPosition(w->W(current)))
     eligible.push_back(w->W(current));

   return eligible;
}
std::vector<Point2D> Agent::generatePath(World* w){
  unordered_map<Point2D, Point2D> cameFrom; // to build the flowfield and build the path
  queue<Point2D> frontier; // to store next ones to visit
  unordered_set<Point2D> frontierSet; // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited; // use .at() to get data, if the element dont exist [] will give you wrong results
  std::vector<Point2D> finalPath;
  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE; // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()){
    Point2D current = frontier.front();
    frontierSet.erase(current);
    visited.emplace(current, true);
    for(auto iter: getVisitableNeighbors(w, current))
    {
      frontier.push(iter);
      frontierSet.insert(iter);
      if(w->catWinsOnSpace(iter))
      {
        borderExit = iter;
        break;
      }
    }
  }
if(borderExit != Point2D::INFINITE)
  {
    finalPath.push_back(cameFrom.)
  }
}
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
}
