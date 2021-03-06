#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <vector>
#include "../physics/collision_data.h"
#include "../transform.h"
#include "../component.h"
#include "../entity.h"

namespace Game {
  /**
   * @brief      A container holding a base transform, a vector of components, and a vector of entities.
   */
  class [[scriptable]] Scene {
    private:
      std::shared_ptr<Transform> transform;
      std::vector <std::shared_ptr<Component>> components;
      std::vector<std::shared_ptr<Entity>> entities;
      std::string name;
      std::shared_ptr<Physics::CollisionData> collision_data;

    public:
      Scene() = delete;
      /**
       * @brief      Scene constructor
       *
       * @param[in]  scene_name  The name of the scene.
       */
      [[scriptable]] Scene(const std::string scene_name);
      /**
       * @brief      Sets the transform.
       *
       * @param[in]  transform  The transform
       */
      [[scriptable]] void setTransform(std::shared_ptr<Transform> transform) noexcept;
      /**
       * @brief      Gets the transform.
       *
       * @return     The transform.
       */
      [[scriptable]] std::shared_ptr<Transform> getTransform() const noexcept;
      /**
       * @brief      Adds a component.
       *
       * @param[in]  component  The component
       */
      [[scriptable]] void addComponent(std::shared_ptr<Component> component);
      /**
       * @brief      Adds a collision data component
       *
       * @param[in]  collision_data  The collision data
       */
      [[scriptable]] void addComponent(std::shared_ptr<Physics::CollisionData> collision_data);
      /**
       * @brief      Adds components.
       *
       * @param[in]  components  The components
       */
      [[scriptable]] void addComponents(std::vector<std::shared_ptr<Component>> components);
      /**
       * @brief      Gets all components
       *
       * @return     A vector of components
       */
      [[scriptable]] std::vector<std::shared_ptr<Component>> getComponents() const noexcept;

      /**
       * @brief      Gets the collision data.
       *
       * @return     The collision data.
       */
      [[scriptable]] std::shared_ptr<Physics::CollisionData> getCollisionData() const noexcept;
      /**
       * @brief      Adds an entity.
       *
       * @param[in]  entity  The entity
       */
      [[scriptable]] void addEntity(std::shared_ptr<Entity> entity) noexcept;
      /**
       * @brief      Adds entities.
       *
       * @param[in]  entities  The entities
       */
      [[scriptable]] void addEntities(std::vector<std::shared_ptr<Entity>> entities) noexcept;
      /**
       * @brief      Gets all entities
       *
       * @return     A vector of entities
       */
      [[scriptable]] std::vector<std::shared_ptr<Entity>> getEntities() const noexcept;
      /**
       * @brief      Sets the name.
       *
       * @param[in]  name  The name
       */
      [[scriptable]] void setName(const std::string name) noexcept;
      /**
       * @brief      Gets the name.
       *
       * @return     The name.
       */
      [[scriptable]] std::string getName() const noexcept;

      /**
       * @brief      Returns a string representation of the object, mostly for use in chaiscript.
       *
       * @return     String representation of the object.
       */
      [[scriptable]] std::string to_string() const noexcept;
  };
}
#endif
