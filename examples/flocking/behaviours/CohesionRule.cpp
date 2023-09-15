#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centreMass;
  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  for(auto *iter : neighborhood)
  {
    centreMass += iter->getPosition();
  }
  // find center of mass
  centreMass /= neighborhood.size();
  cohesionForce = centreMass - boid->getPosition();
  return cohesionForce;
}