#include <easylogging++.h>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "exceptions/invalid_vertex_array_exception.h"
#include "exceptions/renderable_not_initialized_exception.h"
#include "exceptions/invalid_shader_object_exception.h"
#include "renderable.h"
#include "graphics/set_uniform_event.h"

namespace Graphics {
  Renderable::Renderable(const unsigned int vertex_array_object, const VertexData& vertex_data) : shader(nullptr), vertex_data(vertex_data), light_reactive(false), ambient_light(1.0), ambient_intensity(1.0) {
    if(!glIsVertexArray(vertex_array_object)) {
      throw Exceptions::InvalidVertexArrayException(vertex_array_object);
    }
    this->vertex_array_object = vertex_array_object;
  }


  std::shared_ptr<Renderable> Renderable::create(const VertexData& vertex_data) {
    return std::make_shared<Renderable>(vertex_data.generateVertexArrayObject(), vertex_data);
  }

  Renderable::Renderable(Renderable&& renderable) : vertex_data(renderable.vertex_data) {
    vertex_array_object = std::move(renderable.vertex_array_object);
    shader = renderable.shader;
    light_reactive = std::move(renderable.light_reactive);
    textures = renderable.textures;
  }

  Renderable& Renderable::operator=(Renderable&& renderable) {
    vertex_array_object = std::move(renderable.vertex_array_object);
    shader = renderable.shader;
    vertex_data = renderable.vertex_data;
    light_reactive = std::move(renderable.light_reactive);
    textures = renderable.textures;

    return *this;
  }

  Renderable::~Renderable() {
    onDestroy();
  }

  void Renderable::setShader(const std::shared_ptr<Shader> shader_object) noexcept {
    this->shader = shader_object;
  }

  std::shared_ptr<Shader> Renderable::getShader() const noexcept {
    return shader;
  }

  void Renderable::addTexture(const unsigned int unit, const std::string uniform_name, std::shared_ptr<BaseTexture> texture_object) noexcept {
    textures[unit] = texture_object;
    Uniform texture_uniform;
    //convert unit to int, samplers expect glUniform1i
    texture_uniform.setData(uniform_name, (int)unit);
    uniforms.insert(texture_uniform);
  }

  void Renderable::removeTexture(const unsigned int unit) {
    textures.erase(unit);
  }

  std::map<unsigned int, std::shared_ptr<BaseTexture>> Renderable::getTextures() const noexcept {
    return textures;
  }

  void Renderable::setLightReactive(const bool reactive) noexcept {
    light_reactive = reactive;
  }

  bool Renderable::isLightReactive() const noexcept {
    return light_reactive;
  }

  void Renderable::setAmbientLight(const glm::vec3 color) noexcept {
    ambient_light = color;
  }

  glm::vec3 Renderable::getAmbientLight() const noexcept {
    return ambient_light;
  }

  void Renderable::setAmbientIntensity(const float intensity) noexcept {
    ambient_intensity = intensity;
  }

  float Renderable::getAmbientIntensity() const noexcept {
    return ambient_intensity;
  }

  void Renderable::addInfluencingLight(std::shared_ptr<Light> light) noexcept {
    influencing_lights.push_back(light);
  }

  void Renderable::clearInfluencingLights() {
    influencing_lights.clear();
  }

  float Renderable::highestZ() const noexcept {
    return vertex_data.highestZ();
  }

  unsigned int Renderable::getVertexArrayBinding() const noexcept {
    return vertex_array_object;
  }

  VertexData Renderable::getVertexData() const noexcept {
    return vertex_data;
  }

  void Renderable::setUniforms() {
    for(auto i : uniforms) {
      if(i.isDirty()) {
        getShader()->setUniform(i);
        i.clean();
      }
    }
  }

  void Renderable::setUniform(const Uniform& uniform) noexcept {
    auto find_iter = uniforms.find(uniform);

    if(find_iter != uniforms.end()) {
      if(*find_iter != uniform) {
        uniforms.erase(find_iter);
        uniforms.insert(uniform);
      }
    }
    else {
      uniforms.insert(uniform);
    }
  }

  void Renderable::onDestroy() {
    //not this one's job to destroy shader
    shader = nullptr;
    textures.clear();
  }

  void Renderable::onStart() {
    if(light_reactive) {
      Uniform ambient_uniform;
      ambient_uniform.setData<glm::vec3>("ambient_color", ambient_light);

      Uniform ambient_intensity_uniform;
      ambient_intensity_uniform.setData<float>("ambient_intensity", ambient_intensity);

      setUniform(ambient_uniform);
      setUniform(ambient_intensity_uniform);
    }
  }

  bool Renderable::onUpdate(const double delta) {
    if(isActive()) {
      if(!glIsVertexArray(vertex_array_object)) {
        throw Exceptions::InvalidVertexArrayException(vertex_array_object);
      }

      Uniform transform_uniform;
      transform_uniform.setData<glm::mat4>("transform", getTransform()->getAbsoluteTransformationMatrix());
      setUniform(transform_uniform);


      glBindVertexArray(vertex_array_object);

      if(shader != nullptr) {
        setUniforms();
        // if(light_reactive) {
        //   shader->setUniform("num_lights", (int)influencing_lights.size());
        //   int index = 0;
        //   std::stringstream light_str;
        //   for(auto& light : influencing_lights) {
        //     light_str << "lights[" << index << "].";
        //     shader->setUniform(light_str.str() + "position", light->getTransform()->getAbsoluteTranslation());
        //     shader->setUniform(light_str.str() + "color", light->getColor());
        //     shader->setUniform(light_str.str() + "intensity", light->getIntensity());
        //     shader->setUniform(light_str.str() + "linear_attenuation", light->getLinearAttenuation());
        //     if(light->castsQuantizedBands()) {
        //       shader->setUniform(light_str.str() + "number_quantized_bands", light->getNumberOfQuantizedBands());
        //     }
        //     if(light->getType() == Light::Type::POINT) {
        //       shader->setUniform(light_str.str() + "cone_angle", 0.0f);
        //     }
        //     else if(light->getType() == Light::Type::SPOT) {
        //       shader->setUniform(light_str.str() + "cone_angle", light->getConeAngle());
        //       shader->setUniform(light_str.str() + "cone_direction", light->getConeDirection());
        //     }
        //     light_str.str(std::string());
        //     index++;
        //   }
        // }

        shader->useProgram();

        for(auto& texture : textures) {
          texture.second->bind(texture.first);
        }
      }
      else {
        LOG(WARNING)<<"Trying to render renderable with nullptr shader";
      }

      if(vertex_data.getIndexCount() > 0) {
        glDrawElements(GL_TRIANGLES, vertex_data.getIndexCount(), GL_UNSIGNED_INT, 0);
      }
      else {
        glDrawArrays(GL_TRIANGLES, 0, vertex_data.getVertexCount());
      }
    }
    return true;
  }


  void Renderable::handleQueuedEvent(std::shared_ptr<Events::Event> event) {
    switch(event->getEventType()) {
      case Events::EventType::SET_SHADER:
        break;
      case Events::EventType::ADD_TEXTURE:
        break;
      case Events::EventType::REMOVE_TEXTURE:
        break;
      case Events::EventType::SET_UNIFORM: {
        auto casted_event = std::static_pointer_cast<Graphics::SetUniformEvent>(event);

        setUniform(casted_event->getUniform());
        break;
      }
      default:
        Component::handleQueuedEvent(event);
        break;
    }
  }

  void Renderable::onNotifyNow(std::shared_ptr<Events::Event> event) {
    handleQueuedEvent(event);
  }

  unsigned long long Renderable::getValueForSorting() const noexcept {

    return (unsigned long long)getTransform()->getAbsoluteTranslation().z;
  }

  std::string Renderable::className() const noexcept {
    return "Graphics::Renderable";
  }

  std::string Renderable::to_string() const noexcept {
    std::stringstream str;
    str << Component::to_string()<<" vao: "<<vertex_array_object<<" Highest Z: "<<highestZ();

    for(auto u : uniforms) {
      str<<" "<<u.to_string();
    }
    return str.str();
  }

  void Renderable::log(el::base::type::ostream_t& os) const {
    os<<to_string();
  }
}
