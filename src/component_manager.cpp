#include "component_manager.h"
#include "exceptions/no_camera_attached_exception.h"
#include "graphics/camera.h"
#include <easylogging++.h>
#include <typeinfo>
#include <algorithm>
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/utility/utility.hpp>


void ComponentManager::addComponent(std::shared_ptr<Component> component) {
  components.insert(std::pair<unsigned long long, std::shared_ptr<Component>>(component->getValueForSorting(), component));
}

void ComponentManager::addComponent(std::shared_ptr<Graphics::Camera> component) {
  components.insert(std::pair<unsigned long long, std::shared_ptr<Component>>(component->getValueForSorting(), component));
  camera = component;
}

void ComponentManager::addComponents(std::vector<std::shared_ptr<Component>> components) {
  for(auto c : components) {
    this->components.insert(std::pair<unsigned long long, std::shared_ptr<Component>>(c->getValueForSorting(), c));
  }
}

void ComponentManager::addComponents(std::list<std::shared_ptr<Component>> components) {
  for(auto c : components) {
    this->components.insert(std::pair<unsigned long long, std::shared_ptr<Component>>(c->getValueForSorting(), c));
  }
}

void ComponentManager::removeComponent(std::shared_ptr<Component> component) {
  auto component_ptr_matcher = [](std::shared_ptr<Component> com, std::pair<unsigned long long, std::shared_ptr<Component>> com_pair) {
          return com == com_pair.second;
    };
  auto component_iter = std::find_if(components.begin(), components.end(), std::bind(component_ptr_matcher, component, std::placeholders::_1));
  if(component_iter != components.end())
    components.erase(component_iter);
}

void ComponentManager::removeComponents(std::vector<std::shared_ptr<Component>> components) {
  for(auto component : components)
    removeComponent(component);
}

unsigned int ComponentManager::count() const noexcept {
  return components.size();
}

void ComponentManager::onStart() {
  if(camera.lock() == nullptr)
    throw Exceptions::NoCameraAttachedException();
  for(auto component : components) {
    component.second->onStart();
  }
}

void ComponentManager::onUpdate(const float delta) {
  if(camera.lock() == nullptr)
    throw Exceptions::NoCameraAttachedException();
  for(auto component : components) {
    component.second->processEventQueue();
    //if(camera.lock()->isComponentWithin(*component)) {
      //if(component.second->isActive())
        component.second->onUpdate(delta);
    //}
  }
}

void ComponentManager::destroy() {
  for(auto component : components) {
    component.second->onDestroy();
    component.second.reset();
  }
  components.clear();
}
