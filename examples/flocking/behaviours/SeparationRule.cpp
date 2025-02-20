#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
     float const desiredDistance = desiredMinimalDistance;
    std::vector<Boid*>  spaceViolators;
     // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
     if (!neighborhood.empty()) {
         Vector2f const position = boid->transform.position;
         int countCloseFlockmates = 0;
         for(auto *iter : neighborhood)
         {
           Vector2f diffVector = position - iter->getPosition();
           float distance = diffVector.getMagnitude();
           if(distance < desiredDistance)
           {
             countCloseFlockmates++;
             Vector2f hat = diffVector.normalized();
             Vector2f force = hat / distance;
             separatingForce += force;
             separatingForce /= countCloseFlockmates;
           }
         }
         // todo: find and apply force only on the closest mates

     }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
          valueHasChanged = true;
  }

  return valueHasChanged;
}
