#include "Shader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>

#include "loaders/shader_loader.h"

namespace SnakeGame
{

Shader::~Shader()
{
}

void Shader::loadShader(const char* vertexShader, const char* fragmentShader)
{
	deleteShader();
	m_Id = load_shader(vertexShader, fragmentShader);
	if (!m_Id)
	{
		std::string err("SHADER::LOAD: Failed to load shader\n");
		err += vertexShader;
		err += ' ';
		err += fragmentShader;
		std::cerr << err << std::endl;
		throw std::runtime_error(err);
	}
}

void Shader::deleteShader()
{
	if (m_Id)
	{
		glDeleteProgram(m_Id);
		m_Id = 0;
	}
}

bool Shader::loaded()
{
	return m_Id;
}

void Shader::use()
{
	glUseProgram(m_Id);
}

void Shader::setUniform(const char* name, float data)
{
	glUniform1f(glGetUniformLocation(m_Id, name), data);
}

void Shader::setUniform(const char* name, const glm::vec2& data)
{
	glUniform2f(glGetUniformLocation(m_Id, name), data.x, data.y);
}

void Shader::setUniform(const char* name, const glm::vec3& data)
{
	glUniform3f(glGetUniformLocation(m_Id, name), data.x, data.y, data.z);
}

void Shader::setUniform(const char* name, const glm::vec4& data)
{
	glUniform4f(glGetUniformLocation(m_Id, name), data.x, data.y, data.z, data.w);
}

void Shader::setUniform(const char* name, const glm::mat4& data)
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, glm::value_ptr(data));
}

} // SnakeGame