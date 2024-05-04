#pragma once

#include "common/types/SmartPointers.h"
#include "common/types/OpenGLTypes.h"
#include <iostream>

#define ASSERT(x) \
	if (!(x))     \
	std::cerr << "Assertion failed: " << #x << std::endl

#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogError(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogError(const char* function, const char* file, int line);

void ERROR(const char* message);