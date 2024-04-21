#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

const static char *DEFAULT_VERTEX_SHADER = R"VERTEX(#version 330 core

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
)VERTEX";

const static char *DEFAULT_FRAGMENT_SHADER = R"FRAGMENT(#version 330 core

in vec3 vertex_colour;
in vec2 tex_coord;

out vec4 frag_colour;

uniform sampler2D tex;

void main() {
	frag_colour = texture(tex, tex_coord);
}
)FRAGMENT";

#endif /* DEFAULT_SHADER_H */
