#ifndef H_FIRST__
#define H_FIRST__

#include "Effect.h"

class First : public Effect {
public:
	First(float stime);
	void run(float time);

private:
};

#endif