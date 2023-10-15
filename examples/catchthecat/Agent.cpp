#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::getVisitableNeighbors(World* world, Point2D current)
{
    std::vector<Point2D> eligible;
   if(world->isValidPosition(world->E(current))) {
     eligible.push_back(world->E(current));
   }
   if(world->isValidPosition(world->NE(current))) {
     eligible.push_back(world->NE(current));
   }
   if(world->isValidPosition(world->SE(current))) {
     eligible.push_back(world->SE(current));
   }
   if(world->isValidPosition(world->NW(current))) {
     eligible.push_back(world->NW(current));
   }
   if(world->isValidPosition(world->SW(current))) {
     eligible.push_back(world->SW(current));
   }
   if(world->isValidPosition(world->W(current))) {
     eligible.push_back(world->W(current));
   }

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
  Point2D* borderExit = new Point2D(Random::Range(0, w->getWorldSideSize()), Random::Range(0, w->getWorldSideSize())); // if at the end of the loop we dont find a border, we have to return random points
  bool found = false;
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
        borderExit = &iter;
        found = true;
        break;
      }
    }
    if(found == true)
    {

        finalPath.push_back(frontier.back());
        frontier.pop();
    }
    else
    {
        return finalPath;
    }
    return finalPath;
  }

}

// if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

