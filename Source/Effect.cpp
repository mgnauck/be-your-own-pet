#include "Effect.h"

Effect::Effect(float stime) : startTime(stime) {}

Effect::~Effect() {
}

void Effect::updateStartTime(float stime) {
	startTime = stime;
}

int Effect::getStartTime() const {
	return static_cast<int>( startTime );
}