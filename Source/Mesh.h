#ifndef H_MESH__
#define H_MESH__

#include <vector>
#include "Vertex.h"
#include "Triangle.h"
#include "Renderable.h"

class Mesh : public Renderable {
public:
	Mesh();
	virtual ~Mesh();

	void						add(Vertex const& v);
	void						add(Triangle const& t);

	void						triangulate(int subx, int suby);
	void						calcNormals();

	void						clear(bool clearTriangles);
	virtual void				prepareRender();

	vertexList&					getVertices();
	triangleList&				getTriangles();
	renderTriangleList&			getRenderTriangles();

	void						setInvalid();

protected:
	std::vector<Vertex>			vertices;
	std::vector<Triangle>		triangles;
	std::vector<RenderTriangle>	renderTriangles;

	bool						validRenderObject;
};

typedef std::vector<Vertex>		vertexList;
typedef std::vector<Triangle>	triangleList;

#endif