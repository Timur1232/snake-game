#pragma once

constexpr int SCREEN_WIDTH = 504;   // pixels
constexpr int SCREEN_HEIGHT = 504;  // pixels

constexpr int TILE_SIDE_SIZE = 36;  // pixels

static_assert(!(SCREEN_HEIGHT % TILE_SIDE_SIZE || SCREEN_WIDTH % TILE_SIDE_SIZE), "Aliquant of the screen size");

constexpr int TILES_WIDTH = SCREEN_WIDTH / TILE_SIDE_SIZE;
constexpr int TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIDE_SIZE;
constexpr int TILES_AMOUNT = TILES_WIDTH * TILES_HEIGHT;
