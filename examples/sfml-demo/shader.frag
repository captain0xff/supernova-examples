void main() {
	vec2 uv = gl_FragCoord.xy/vec2(200, 200);
	gl_FragColor = vec4(sqrt(uv.x), sqrt(uv.y), 0.0, 1.0); 
}
