#version 330 core

in vec3 vertex_colour;
in vec2 tex_coord;

out vec4 frag_colour;

uniform sampler2D tex;

void main() {
	frag_colour = texture(tex, tex_coord)*vec4(vertex_colour, 1.0f);
}
