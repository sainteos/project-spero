#include "component.h"

void Component::setTransform(std::shared_ptr<Transform> transform) {
  this->transform = transform;
}

std::shared_ptr<Transform> Component::getTransform() const noexcept {
  return transform;
}