#include <easylogging++.h>
#include <fstream>
#include <OpenGL/gl3.h>
#include "texture_manager.h"
#include "exceptions/invalid_texture_name_exception.h"

namespace Graphics {

  TextureManager::TextureManager() {
    
  }

  TextureManager::~TextureManager() {

  }

  const bool TextureManager::loadTexture(const std::string& path, const std::string& texture_uniform_name) {
    std::string tex_name = getNameFromPath(path);
    auto texture = std::make_shared<BaseTexture>(texture_uniform_name, GL_TEXTURE_2D, 0);

    if(texture->load(path)) {
      textures_to_names[tex_name] = texture;
      return true;
    }
    else {
      return false;
    }
  }

  const std::shared_ptr<BaseTexture> TextureManager::operator[](const std::string& name) const {
    return getTexture(name);
  }

  const std::shared_ptr<BaseTexture> TextureManager::getTexture(const std::string& name) const {
    if(textures_to_names.count(name) == 0) {
      throw Exceptions::InvalidTextureNameException(name);
    } 
    return textures_to_names.at(name);
  }

  const bool TextureManager::textureExists(const std::string& name) const noexcept {
    if(textures_to_names.count(name) > 0)
      return true;
    else
      return false;
  }

  const std::string TextureManager::getNameFromPath(const std::string& path) noexcept {
    std:: string name;
    //plus one to remove the slash :)
    auto start = path.find_last_of("/") + 1;
    auto end = path.find_last_of(".");
    name = path.substr(start, end - start);
    return name;
  }
}