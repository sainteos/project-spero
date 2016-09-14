#include <easylogging++.h>
#include "area.h"

namespace Graphics {
  namespace UI {

    Area::Area(VertexData vertex_data, std::shared_ptr<Skin> skin) : Element(vertex_data, skin) {
      setShader(skin->shader.lock());
      addTexture(0, "skin0", skin->texture.lock());
    }

    std::shared_ptr<Area> Area::create(std::shared_ptr<Skin> skin, glm::vec4 color, float screen_width, float screen_height, float x_pos, float y_pos, float width, float height) {
      auto vertex_data = VertexData();
      vertex_data.addVec(VertexData::DATA_TYPE::GEOMETRY, generateRect(screen_width, screen_height, x_pos, y_pos, width, height));
      vertex_data.addVec(VertexData::DATA_TYPE::TEX_COORDS, basisTexCoords());

      auto area = std::make_shared<Area>(vertex_data, skin);
      area->setColor(color);
      area->setAnchorPoint(glm::vec2(x_pos, y_pos));
      area->setWidth(width);
      area->setHeight(height);

      return area;
    }

    void Area::onDestroy() {
      Element::onDestroy();
    }

    void Area::onStart() {
      Element::onStart();
    }

    const bool Area::onUpdate(const double delta) {
      return Element::onUpdate(delta);
    }
    
    void Area::handleQueuedEvent(std::shared_ptr<Events::Event> event) {
      Element::handleQueuedEvent(event);
    }

    void Area::onNotifyNow(std::shared_ptr<Events::Event> event) {
      handleQueuedEvent(event);
    }

    const unsigned long long Area::getValueForSorting() const noexcept {
      return -24;
    }

    void Area::onLeftClick() {
    }

    void Area::onRightClick() {
    }

    void Area::onCursorEnter() {
    }

    void Area::onCursorLeave() {
    }

    void Area::onKeyDown(const int key) {
    }

    void Area::onKeyUp(const int key) {
    }

    void Area::onScroll(const glm::dvec2 position_change) {
    }

    void Area::log(el::base::type::ostream_t& os) const {
      Element::log(os);
    }
  }
}