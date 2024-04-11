#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolour;
layout (location = 2) in vec2 atexcoord;

out vec3 vertex_colour;
out vec2 tex_coord;

void main() {
	gl_Position = vec4(apos, 1.0f);
	vertex_colour = acolour;
	tex_coord = atexcoord;
}
