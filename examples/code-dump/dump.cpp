void draw_grid(Renderer &renderer, const Colour colour, const int rows, const int columns, const int tile_size) {
	double width  = rows*tile_size, height = columns*tile_size;

	renderer.set_colour(colour);

	for (int i = 0; i <= rows; i++) {
		renderer.draw_line_raw({0, double(i*tile_size)}, {width, double(i*tile_size)});
	}

	for (int i = 0; i <= columns; i++) {
		renderer.draw_line_raw({double(i*tile_size), 0}, {double(i*tile_size), height});
	}
}
