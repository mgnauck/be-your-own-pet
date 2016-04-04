#ifndef H_BMP__
#define H_BMP__

#include <iostream>
#include <string>

class Map;

class BMP {
public:
	static Map*	load(std::string const& filename);
	static bool	save(std::string const& filename, Map const& map);

private:
	BMP();
	BMP(BMP const&);
	BMP& operator=(BMP const&);
};

#endif