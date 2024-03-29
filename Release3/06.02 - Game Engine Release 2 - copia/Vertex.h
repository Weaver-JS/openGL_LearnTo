#pragma once
//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 

struct Position {
	GLfloat  x;
	GLfloat  y;
	GLfloat  z;
};

struct UV
{
	GLfloat u;
	GLfloat v;
};
struct ColorRGBA8 {
	ColorRGBA8() :r(0), g(0), b(0), a(0) {	}
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A)  {}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct NormalVector
{
	GLfloat nx; GLfloat ny; GLfloat nz;
};
struct Vertex {
	
	Position position;
	ColorRGBA8 color;
	UV _uv;
	NormalVector normal;
	
	void setPosition(GLfloat  x, GLfloat  y, GLfloat  z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}
	
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	
	void setUVs(GLfloat u, GLfloat v)
	{
		_uv.u = u;
		_uv.v = v;
	}

	void setNormalVector(GLfloat _nx, GLfloat _ny, GLfloat _nz)
	{
		normal.nx = _nx;
		normal.ny = _ny;
		normal.nz = _nz;
	}
};