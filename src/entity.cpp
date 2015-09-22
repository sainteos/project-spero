#include <easylogging++.h>
#include <typeinfo>
#include "entity.h"

Entity::Entity() {
  transform = std::make_shared<Transform>();
}

void Entity::addComponent(std::shared_ptr<Component> component) {
  transform->addChild(component->getTransform());
  components.push_back(component);
  components.unique();
}

void Entity::removeComponent(std::shared_ptr<Component> component) {
  transform->removeChild(component->getTransform());
  components.remove(component);
}

std::shared_ptr<Transform> Entity::getTransform() const noexcept {
  return transform;
}

void Entity::onStart() {
}

void Entity::onUpdate(const float delta) {
}

void Entity::onStop() {
}

void Entity::onDestroy() {
}
