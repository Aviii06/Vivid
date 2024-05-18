#include "Error.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
		;
}

bool GLLogError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{

		std::cout << "[OpenGL Error] (" << error << ")\nIn File " << file << "\nIn line" << line << "\nIn Function"
		          << function;
		return false;
	}
	return true;
}

/// Standard Error Log
void ERROR(const char* message)
{
	// Error Message in Red
	std::cerr << "\033[1;31m" << message << "\033[0m" << std::endl;
}
