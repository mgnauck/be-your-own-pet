#ifndef H_EFFECT__
#define H_EFFECT__

#include "Scene.h"
#include "GLHelper.h"

class Effect {
public:
	Effect(float stime);
	virtual ~Effect();

	virtual void	run(float time) = 0;
	virtual void	updateStartTime(float stime);
	int				getStartTime() const;

protected:
	float			startTime;
	Scene			scene;
	GLHelper		glh;
};

#endif