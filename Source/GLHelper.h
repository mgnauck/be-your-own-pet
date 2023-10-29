#ifndef H_GLHELPER__
#define H_GLHELPER__

#include "GLContext.h"
#include "Vector.h"

class Material;
class Matrix;
class Light;
class Map;
class Scene;

class GLHelper {
public:
	void	setViewport(int l, int b, int w, int h) const;
	void	clear(Vector const& c = Vector(0.0f, 0.0f, 0.0f)) const;
	void	setLight(int n, Light const& l) const;
	void	disableLights() const;
	void	setMaterial(Material const& m) const;
	void	setMVP(Matrix const& mv, Matrix const& pr) const;
	void	bindTexture(int id) const;
	int		uploadTexture(Map const& m, bool mipmap, int minFilter = GL_LINEAR, int magFilter = GL_LINEAR) const;
	int		createRenderTexture(int w, int h, int minFilter = GL_LINEAR, int magFilter = GL_LINEAR) const;
	void	copyToTexture(int texture, int l, int b, int w, int h) const;
	void	drawViewportQuad(int id, float tx, float ty, Vector const& col) const;
	void	drawOvl(int id, float tx, float ty, float sx, float sy, float a);
	void	blend(float alpha, Vector const& c);
	void	renderScene(float time, Scene& scene, bool low = false) const;
};

#endif