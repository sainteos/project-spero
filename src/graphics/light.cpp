#include <algorithm>
#include "light.h"
#include "transform.h"

namespace Graphics {

  Light::Light(const Type& type) :
    type(type), color(1.0), intensity(0.0), linear_attenuation(0.0), quadratic_attenuation(0.0),
    quantized_bands(0), cone_angle(0.0), cone_direction(0.0) {

  }

  Light::~Light() {

  }

  void Light::onStart() {

  }

  bool Light::onUpdate(const double delta) {
    return true;
  }

  void Light::onDestroy() {

  }

  void Light::setColor(const glm::vec3 color) noexcept {
    this->color = color;
  }

  glm::vec3 Light::getColor() const noexcept {
    return color;
  }

  void Light::setIntensity(const float intensity) noexcept {
    this->intensity = intensity;
  }

  float Light::getIntensity() const noexcept {
    return intensity;
  }

  void Light::setLinearAttenuation(const float linear) noexcept {
    this->linear_attenuation = linear;
  }

  float Light::getLinearAttenuation() const noexcept {
    return linear_attenuation;
  }

  void Light::setQuadraticAttenuation(const float quadratic) noexcept {
    this->quadratic_attenuation = quadratic;
  }

  float Light::getQuadraticAttenuation() const noexcept {
    return quadratic_attenuation;
  }

  bool Light::castsQuantizedBands() const noexcept {
    return quantized_bands > 0;
  }

  void Light::setNumberOfQuantizedBands(const int bands) noexcept {
    this->quantized_bands = bands;
  }

  int Light::getNumberOfQuantizedBands() const noexcept {
    return quantized_bands;
  }

  void Light::setConeAngle(const float angle) noexcept {
    this->cone_angle = angle;
  }

  float Light::getConeAngle() const noexcept {
    return cone_angle;
  }

  void Light::setConeDirection(const glm::vec3 direction) noexcept {
    this->cone_direction = direction;
  }

  glm::vec3 Light::getConeDirection() const noexcept {
    return cone_direction;
  }

  Light::Type Light::getType() const noexcept {
    return this->type;
  }

  float Light::influenceOnComponent(const Component& component) const {
    float diffuse_coefficient = std::max(0.0f, glm::dot(glm::vec3(0.0, 0.0, 1.0), glm::vec3(glm::vec2(getTransform()->getAbsoluteTranslation()) - glm::vec2(component.getTransform()->getAbsoluteTranslation()), getTransform()->getAbsoluteTranslation().z)));
    if(diffuse_coefficient < 0.001)
      diffuse_coefficient = 0.0;
    return diffuse_coefficient;
  }

  unsigned long long Light::getValueForSorting() const noexcept {
    return getId();
  }

  std::string Light::className() const noexcept {
    return "Graphics::Light";
  }

  void Light::log(el::base::type::ostream_t& os) const {
    os<<"{Light("<<typeToString(type)<<")} "<<"Color: "<<glm::to_string(color)<<" Intensity: "<<intensity<<" LinearAttenuation: "<<linear_attenuation
      <<" Quadratic Attenuation: "<<quadratic_attenuation<<" Quantized Bands: "<<quantized_bands<<" ConeAngle: "<<cone_angle
      <<" Cone Direction: "<<glm::to_string(cone_direction)<<" Position: "<<glm::to_string(getTransform()->getAbsoluteTranslation());
  }
}
