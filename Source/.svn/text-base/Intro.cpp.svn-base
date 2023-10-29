#include "Intro.h"
#include "Map.h"

#include "../data/tune.h"

int const		BPP			= 32;
bool const		FULLSCREEN	= false;

// 20110501/supah: changed this a bit to have a more user friendly window :)
char const*		TITLE		= "bypass :: be your own pet";

int const		RESX		= 1024;
int const		RESY		= 768;
float const		ASPECT		= 16.0f / 9.0f;

int const		LEFT		= 0;
int const		BOTTOM		= (RESY - (int)(RESY / ASPECT)) / 2;
int const		WIDTH		= RESX;
int const		HEIGHT		= (int)(RESY / ASPECT);

int				renderTexture;
int				framebufferTexture;

float rnd(float min, float max) {
	return min + (max - min) * (rand() / (float)RAND_MAX);
}

Map* load_from_h(unsigned char* src, int w, int h, bool alphaSet) {

	Map*	m = new Map(w, h);
	int		i = 0;

	for(int y=0; y<h; y++) {
		for(int x=0; x<w; x++) {

			unsigned char r = src[i * 3 + 0];
			unsigned char g = src[i * 3 + 1];
			unsigned char b = src[i * 3 + 2];
			unsigned char a = 0xff;

			if(alphaSet)
				a = r;

			m->set(x, y, (a << 24) | (r << 16) | (g << 8) | b);

			i++;
		}
	}

	return m;
}

Map* noiseMap(int w, int h) {

	Map* m = new Map(w, h);

	for(int j=0; j<h; j++)
		for(int i=0; i<w; i++) {
			unsigned char c = rand()%0xff;
			m->set(i, j, (0xff<<24)|(c<<16)|(c<<8)|c);
		}

	return m;
}

unsigned int memopen(char *name) {
	MEMFILE *memfile;

	memfile = (MEMFILE *)calloc(sizeof(MEMFILE),1);

	memfile->pos = 0;
	memfile->data = tune;
	memfile->length = sizeof(tune);

	return (unsigned int)memfile;
}

void memclose(unsigned int handle) {
	MEMFILE *memfile = (MEMFILE *)handle;

	free(memfile);
}

int memread(void *buffer, int size, unsigned int handle) {
	MEMFILE *memfile = (MEMFILE *)handle;

	if (memfile->pos + size >= memfile->length)
		size = memfile->length - memfile->pos;

	memcpy(buffer, (char *)memfile->data+memfile->pos, size);
	memfile->pos += size;
	
	return size;
}

void memseek(unsigned int handle, int pos, signed char mode) {
	MEMFILE *memfile = (MEMFILE *)handle;

	if (mode == SEEK_SET) 
		memfile->pos = pos;
	else if (mode == SEEK_CUR) 
		memfile->pos += pos;
	else if (mode == SEEK_END)
		memfile->pos = memfile->length + pos;

	if (memfile->pos > memfile->length)
		memfile->pos = memfile->length;
}

int memtell(unsigned int handle) {
	MEMFILE *memfile = (MEMFILE *)handle;
	return memfile->pos;
}