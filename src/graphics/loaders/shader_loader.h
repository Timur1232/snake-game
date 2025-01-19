#pragma once

#include <string>

namespace SnakeGame
{

[[nodiscard]]
uint32_t load_shader(const char* vertexShader, const char* fragmentShader);

} // SnakeGame