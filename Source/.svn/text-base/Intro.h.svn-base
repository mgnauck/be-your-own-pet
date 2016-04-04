#ifndef H_INTRO__
#define H_INTRO__

class Map;

extern int const	RESX;
extern int const	RESY;
extern float const	ASPECT;
extern int const	LEFT;
extern int const	BOTTOM;
extern int const	WIDTH;
extern int const	HEIGHT;
extern int const	BPP;
extern bool const	FULLSCREEN;
extern char const*	TITLE;
extern int			renderTexture;
extern int			framebufferTexture;

#define FRAMBUFFERTEXTURE_SIZEX		512
#define FRAMBUFFERTEXTURE_SIZEY		512
#define RENDERTEXTURE_SIZEX			256
#define RENDERTEXTURE_SIZEY			256

typedef struct {
	int length;
	int pos;
	void *data;
} MEMFILE;

float	rnd(float min, float max);
Map*	load_from_h(unsigned char* src, int w, int h, bool alpha = false);
Map*	noiseMap(int w, int h);

unsigned int memopen(char *name);
void memclose(unsigned int handle);
int memread(void *buffer, int size, unsigned int handle);
void memseek(unsigned int handle, int pos, signed char mode);
int memtell(unsigned int handle);

#endif