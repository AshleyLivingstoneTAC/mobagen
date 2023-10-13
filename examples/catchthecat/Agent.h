#ifndef AGENT_H
#define AGENT_H
#include <vector>
#include "math/Point2D.h"
class World;

class Agent {
public:
  explicit Agent() = default;
  ;
  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* world, Point2D current);
};

#endif  // AGENT_H
