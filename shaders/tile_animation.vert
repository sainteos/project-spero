#version 330 core
precision highp float;

layout(location = 0)in vec3 vert;
layout(location = 1)in vec2 tex;

out vec2 uv;

uniform mat4 transform;
uniform mat4 projection_matrix;
uniform ivec2 tile_coord;
uniform vec2 tile_coord_multiplier;

void main()
{
  gl_Position = (projection_matrix * transform) * vec4(vert, 1.0);
  
  uv = tex * tile_coord_multiplier + vec2(tile_coord) * tile_coord_multiplier;
}