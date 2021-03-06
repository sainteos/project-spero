#version 330 core
precision highp float;

struct Light
{
  vec3 position;
  vec3 color;
  float intensity;
  float linear_attenuation;
  float quadratic_attenuation;
  float cone_angle;
  vec3 cone_direction;
  float quantization_bandwidth;
  int number_quantized_bands;
};

const int MAX_LIGHTS = 8;

in vec2 uv;
flat in uint unit;
in vec3 surface_pos;

layout(location = 0)out vec4 fragColor;

uniform sampler2D tileset0;
uniform sampler2D tileset1;
uniform sampler2D tileset2;
uniform sampler2D tileset3;
uniform sampler2D tileset4;
uniform sampler2D tileset5;
uniform sampler2D tileset6;
uniform sampler2D tileset7;
uniform sampler2D tileset8;
uniform sampler2D tileset9;
uniform sampler2D tileset10;
uniform sampler2D tileset11;

uniform int num_lights;
uniform Light lights[MAX_LIGHTS];

uniform vec3 ambient_color;    //ambient RGB
uniform float ambient_intensity;

vec4 selectTexel(uint unit) {
  if(unit == 0u)
    return texture(tileset0, uv);
  if(unit == 1u)
    return texture(tileset1, uv);
  if(unit == 2u)
    return texture(tileset2, uv);
  if(unit == 3u)
    return texture(tileset3, uv);
  if(unit == 4u)
    return texture(tileset4, uv);
  if(unit == 5u)
    return texture(tileset5, uv);
  if(unit == 6u)
    return texture(tileset6, uv);
  if(unit == 7u)
    return texture(tileset7, uv);
  if(unit == 8u)
    return texture(tileset8, uv);
  if(unit == 9u)
    return texture(tileset9, uv);
  if(unit == 10u)
    return texture(tileset10, uv);
  if(unit == 11u)
    return texture(tileset11, uv);
}

vec3 applyLight(Light light, vec3 surface_color, vec3 normal, vec3 surface_pos) {
  vec3 surface_to_light = normalize(vec3(light.position.xy - surface_pos.xy, light.position.z));
  float distance_to_light = length(vec3(light.position.xy - surface_pos.xy, light.position.z));

  float attenuation = 1.0 / ( 1.0 + (light.linear_attenuation * distance_to_light) + (light.quadratic_attenuation * distance_to_light * distance_to_light));

  //cone restrictions (affects attenuation)
  float light_to_surface_angle = degrees(acos(dot(-surface_to_light, normalize(light.cone_direction))));
  if(light_to_surface_angle > light.cone_angle){
    attenuation = 0.0;
  }

  //diffuse
  float diffuse_coefficient = max(0.0, dot(normal, surface_to_light));
  //Should we quantize?
  if(light.number_quantized_bands > 0 && diffuse_coefficient > 0.0) {
    diffuse_coefficient = floor(diffuse_coefficient * float(light.number_quantized_bands + 1.0)) / float(light.number_quantized_bands + 1.0);
  }

  vec3 diffuse = diffuse_coefficient * light.color * light.intensity;

  
  vec3 intensity = attenuation * diffuse;
  //linear color (color before gamma correction)
  return clamp(intensity * surface_color.rgb, vec3(0.0), vec3(1.0));
}

void main()
{
  vec4 texel = selectTexel(unit);
  if(texel.a < 0.1)
    discard;

  vec3 normal = vec3(0.0, 0.0, 1.0);

  vec3 final_color = vec3(0.0, 0.0, 0.0);

  //ambient
  vec3 ambient = ambient_color.rgb * ambient_intensity * texel.rgb;


  for(int i = 0; i < num_lights; i++) {
    final_color += applyLight(lights[i], texel.rgb, normal, surface_pos);
  }

  fragColor = vec4(clamp(final_color + ambient, vec3(0.0), vec3(1.0)), texel.a);
}