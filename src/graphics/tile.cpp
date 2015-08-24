#include "graphics/tile.h"
#include "graphics/tile_attribute_trait.h"

namespace Graphics {
  Tile::Tile(const unsigned int vertex_array_object, const VertexData& data) : Renderable(vertex_array_object, data, new TileAttributeTrait()), size_pixels(0) {

  }

  Tile::~Tile() {

  }

  void Tile::destroy() {
    Renderable::destroy();
  }

  const bool Tile::onUpdate(const double delta) {
    return true;

  }

  void Tile::setSizeInPixels(const unsigned int size) {
    size_pixels = size;
  }

  const unsigned int Tile::sizeInPixels() const noexcept {
    return size_pixels;
  }

  void Tile::setTexture(std::shared_ptr<BaseTexture> texture_object) noexcept {
    Renderable::addTexture(texture_object);
  }

  std::shared_ptr<BaseTexture> Tile::getTexture() const noexcept {
    return Renderable::getTextures().back();
  }
}