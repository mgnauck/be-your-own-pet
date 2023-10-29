#ifndef H_MAP__
#define H_MAP__

#include <vector>

class Map {
public:
	Map() : width(0), height(0) {}

	Map(int w, int h, unsigned int c = 0xffffffff) : width(w), height(h), data(w * h, c) {
	}

	virtual ~Map() {
		data.clear();
	}

	Map(Map const& rhs) {

		width	= rhs.getWidth();
		height	= rhs.getHeight();

		data.clear();

		for(int j=0; j<height; j++)
			for(int i=0; i<width; i++)
				data.push_back(rhs.get(i, j));
	}

	void resize(int w, int h) {

		width	= w;
		height	= h;
		data.resize(w * h);
	}

	void set(int x, int y, unsigned int c) {
		data[width * y + x] = c;
	}

	unsigned int get(int x, int y) const {
		return data[width * y + x];
	}


	int const getWidth() const {
		return width;
	}

	int const getHeight() const {
		return height;
	}

	void* getPtr() {
		return &data[0];
	}

	unsigned int getSize() const {
		return width * height;
	}

	Map& operator=(Map const& rhs) {
		if( &rhs == this )
			return *this;

		width	= rhs.getWidth();
		height	= rhs.getHeight();

		data.clear();

		for(int j=0; j<height; j++)
			for(int i=0; i<width; i++)
				data.push_back(rhs.get(i, j));

		return *this;
	}

protected:
	int							width;
	int							height;
	std::vector<unsigned int>	data;
};

#endif
