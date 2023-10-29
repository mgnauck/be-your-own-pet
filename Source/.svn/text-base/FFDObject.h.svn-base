#ifndef H_FFDOBJECT__
#define H_FFDOBJECT__

#include "Mesh.h"

class FFDObject : public Renderable {
public:
	FFDObject(Mesh* m);
	~FFDObject();

	void						setPoint(int n, Vector const& v);
	Vector const&				getPoint(int n);
	void						prepareRender();

	vertexList&					getVertices();
	virtual renderTriangleList&	getRenderTriangles();

	void						resetPoints();

private:
	void						findBounds(	);
	void						setupRestStatePoints();
	void						transformToLatticeSpace();
	void						transformToObjectSpace();
	Vector						evalPoint(float u, float v, float w);

	Mesh*						originalMesh;			// rest state mesh
	Mesh						deformedMesh;			// deformed mesh
	vectorList					points;					// controlpoints to be moved
	vectorList					restStatePoints;		// controlpoints in rest state
	vectorList					latticeSpacePoints;		// points in lattice space (0..1)
	Vector						min;
	Vector						max;
	bool						valid;
	std::vector<float>			bu;
	std::vector<float>			bv;
	std::vector<float>			bw;

};

#endif