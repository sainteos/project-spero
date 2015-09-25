#include "text.h"

namespace Graphics {
  
  Text::Text() : text("text"), font(nullptr), color(1.0), horizontal_alignment(HorizontalAlignment::LEFT), vertical_alignment(VerticalAlignment::CENTER) {

  }

  void Text::setFont(const std::shared_ptr<Font> font) {
    this->font = font;
  }

  void Text::setText(const std::string& text) {
    this->text = text;
    horizontal_alignment_transform = Transform();

    if(horizontal_alignment == HorizontalAlignment::CENTER) {
      for(auto character : this->text) {
        horizontal_alignment_transform.translate(-glm::vec2((float)(font->getCharacter(character).advance >> 6) / (font->getSize() * 2.0), 0.0));
      }
    }
    else if(horizontal_alignment == HorizontalAlignment::RIGHT) {
      for(auto character : this->text) {
        horizontal_alignment_transform.translate(-glm::vec2((float)(font->getCharacter(character).advance >> 6) / (float)font->getSize(), 0.0));
      }
    }
  }

  void Text::setColor(const glm::vec4& color) {
    this->color = color;
  }

  void Text::addCharacterVertexData(const char character, const VertexData& vertex_data, const unsigned int vertex_array_object) {
    character_vertex_data[character] = TextData { vertex_data, vertex_array_object };
  }

  void Text::setHorizontalAlignment(const HorizontalAlignment& alignment) {
    this->horizontal_alignment = alignment;
    horizontal_alignment_transform = Transform();

    if(horizontal_alignment == HorizontalAlignment::CENTER) {
      for(auto character : this->text) {
        horizontal_alignment_transform.translate(-glm::vec2((float)(font->getCharacter(character).advance >> 6) / (font->getSize() * 2.0), 0.0));
      }
    }
    else if(horizontal_alignment == HorizontalAlignment::RIGHT) {
      for(auto character : this->text) {
        horizontal_alignment_transform.translate(-glm::vec2((float)(font->getCharacter(character).advance >> 6) / (float)font->getSize(), 0.0));
      }
    }
  }

  void Text::setVerticalAlignment(const VerticalAlignment& alignment) {
    this->vertical_alignment = alignment;
    vertical_alignment_transform = Transform();
    if(vertical_alignment == VerticalAlignment::TOP) {
      vertical_alignment_transform.translate(glm::vec2(0.0, -1.0));
    }
    else if(vertical_alignment == VerticalAlignment::CENTER) {
      vertical_alignment_transform.translate(glm::vec2(0.0, -0.5));
    }
  }

  void Text::onDestroy() {

  }

  void Text::onStart() {

  }

  const bool Text::onUpdate(const double delta) {
    return true;
  }

  const bool Text::onRender() {
    if(isActive()) {
      if(getShader() != nullptr) {
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

        Transform character_transform = *transform;

        getShader()->useProgram();
        getShader()->setUniform<glm::vec4>("color", color);

        for(auto character : text) {
          getShader()->setUniform<glm::mat4>("transform", vertical_alignment_transform.getAbsoluteTransformationMatrix() * horizontal_alignment_transform.getAbsoluteTransformationMatrix() * character_transform.getAbsoluteTransformationMatrix());
          getShader()->setUniform<int>("text_texture", 0);

          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, font->getCharacter(character).texture_handle);

          glBindVertexArray(character_vertex_data[character].vertex_array_object);

          if(character_vertex_data[character].vertex_data.getIndexCount() > 0) {
            glDrawElements(GL_TRIANGLES, character_vertex_data[character].vertex_data.getIndexCount(), GL_UNSIGNED_INT, 0);
          }
          else {
            glDrawArrays(GL_TRIANGLES, 0, character_vertex_data[character].vertex_data.getVertexCount());
          }
          character_transform.translate(glm::vec2((float)(font->getCharacter(character).advance >> 6) / 64.0, 0.0));
        }
      }
      else {
        LOG(WARNING)<<"Trying to render renderable with nullptr shader";
      }
      return true;
    }
    else {
      return false;
    }
  }
}