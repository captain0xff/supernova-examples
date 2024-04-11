#version 330 core

in vec3 vertex_colour;
in vec2 tex_coord;

out vec4 frag_colour;

uniform sampler2D tex;

void main() {
	vec4 colour = texture(tex, tex_coord);
	float avg = (colour.r + colour.g + colour.b)/3.0f;
	frag_colour = vec4(avg, avg, avg, colour.a);
}
