#ifndef H_RENDERABLE__
#define H_RENDERABLE__

#include <vector>
#include "Matrix.h"
#include "Material.h"
#include "Vertex.h"
#include "Triangle.h"

class Scene;

class Renderable {
public:
	Renderable();
	virtual ~Renderable();

	void							setMatrix(Matrix const& m);
	void							setMaterial(Material const& m);

	Matrix&							getMatrix();
	Material&						getMaterial();

	virtual void					prepareRender() = 0;

	virtual vertexList&				getVertices() = 0;
	virtual renderTriangleList&		getRenderTriangles() = 0;

private:
	Matrix							transformation;
	Material						material;
};

#endif
