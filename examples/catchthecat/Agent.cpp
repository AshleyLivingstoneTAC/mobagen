#include "Agent.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "World.h"

std::vector<Point2D> Agent::generatePath(World* w)
{
  // from cat to border
  //
  std::unordered_map<int, std::unordered_map<int, Point2D>> cameFrom;
std::unordered_set<Point2D> frontierSet;
std::queue<Point2D> frontierQ;
auto catPos = w->getCat();


frontierQ.push(catPos);
frontierSet.insert(catPos);

while(true)
{
  auto current = frontierQ.front();
  frontierQ.pop();
  frontierSet.erase(current);
}

}
