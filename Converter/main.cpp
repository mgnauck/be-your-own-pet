#include <stdio.h>
#include <iostream>
#include <string>
#include "BMP.h"
#include "Map.h"

using namespace std;

/*
vector<unsigned char> pic;

void load(string const& src, int w, int h) {

	FILE*	f = fopen(src.c_str(), "rb");
	int		i = 0;

	while(i < w * h) {

		unsigned char c;
		fread(&c, 1, 1, f);
		pic.push_back(c);
		i++;
	}

	assert((int)pic.size() == w*h);
	fclose(f);
}

void save(string const& src, string const& dst, string const& obj, int w, int h) {

	FILE*	f = fopen(dst.c_str(), "wb");

	fprintf(f, "\n");
	fprintf(f, "// generated from %s\n\n", src.c_str());
	fprintf(f, "int const %s_width  = %i;\n", obj.c_str(), w);
	fprintf(f, "int const %s_height = %i;\n", obj.c_str(), h);
	fprintf(f, "unsigned char const %s[%i * %i] = {\n\n", obj.c_str(), w, h);
	fprintf(f, "      ");

	int i=0;
	for(vector<unsigned char>::iterator it=pic.begin(); it!=pic.end(); ++it) {

		if(it!=pic.end() - 1)
			fprintf(f, "0x%x, ", *it);
		else
			fprintf(f, "0x%x", *it);

		if(i < 16)
			i++;
		else {
			fprintf(f, "\n");
			fprintf(f, "      ");
			i = 0;
		}
	}
	
	fprintf(f, "\n");
	fprintf(f, "};\n\n");
	fprintf(f, "// bypass rawstyle again\n");
	fprintf(f, "// hier könnte noch so viel stehen - tuts aber naet.\n");

	fclose(f);
}

int main(int argc, char* argv[]) {

	if(argc < 6) {
		cout << "use: converter.exe infile.raw width height outfile.h target_name" << endl;
		return 1;
	}

	string	infile	= argv[1];
	string	outfile	= argv[4];
	string	objname	= argv[5];
	int		width	= atoi(argv[2]);
	int		height	= atoi(argv[3]);

	load(infile, width, height);
	save(infile, outfile, objname, width, height);

	cout << "wrote file " << infile << " to " << outfile << " (width = " << width << ", height = " << height << ")" << endl;

	return 0;
}
*/

void save_to_h(string const& dst, Map* map) {

	string  nameCpp	= dst + ".cpp";
	string  nameHpp	= dst + ".h";

	// write cpp file
	FILE*	f		= fopen(nameCpp.c_str(), "wb");

	fprintf(f, "#include \"%s\"\n\n", nameHpp.c_str());
	fprintf(f, "int const %s_width  = %i;\n", dst.c_str(), map->getWidth());
	fprintf(f, "int const %s_height = %i;\n", dst.c_str(), map->getHeight());
	fprintf(f, "unsigned char %s[%i * %i * 3] = {\n\n", dst.c_str(), map->getWidth(), map->getHeight());
	fprintf(f, "      ");

	int i = 0;
	for(int y=0; y<map->getHeight(); y++) {
		for(int x=0; x<map->getWidth(); x++) {

			int c = map->get(x, y);

			fprintf(f, "0x%x, ", (c >> 16) & 0xff);
			fprintf(f, "0x%x, ", (c >>  8) & 0xff);
			fprintf(f, "0x%x, ", (c >>  0) & 0xff);

			if(i < 5)
				i++;
			else {
				fprintf(f, "\n");
				fprintf(f, "      ");
				i = 0;
			}
		}
	}
	
	fprintf(f, "\n");
	fprintf(f, "};\n\n");
	fprintf(f, "// bypass rawstyle again\n");
	fprintf(f, "// hier könnte noch so viel stehen - tuts aber naet.\n");

	fclose(f);

	// write coresponding h file
	f		= fopen(nameHpp.c_str(), "wb");
	
	fprintf(f, "#ifndef H_%s__\n", dst.c_str());
	fprintf(f, "#define H_%s__\n\n", dst.c_str());
	fprintf(f, "extern int const %s_width;\n", dst.c_str());
	fprintf(f, "extern int const %s_height;\n", dst.c_str());
	fprintf(f, "extern unsigned char %s[%i * %i * 3];\n\n", dst.c_str(), map->getWidth(), map->getHeight());

	fprintf(f, "#endif");

	fclose(f);
}

Map* load_from_h(unsigned char* src, int w, int h) {

	Map*	m = new Map(w, h);
	int		i = 0;

	for(int y=0; y<h; y++) {
		for(int x=0; x<w; x++) {

			unsigned char r = src[i * 3 + 0];
			unsigned char g = src[i * 3 + 1];
			unsigned char b = src[i * 3 + 2];
			unsigned char a = 0xff;

			if(r == g && r == b)		// hack: set alpha if grayscale
				a = r;

			m->set(x, y, (a << 24) | (r << 16) | (g << 8) | b);

			i++;
		}
	}

	return m;
}

void convertTune(std::string src, std::string dst) {

	FILE* f = fopen(src.c_str(), "rb");

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	fseek(f, 0, SEEK_SET);

	unsigned char*	buf = new unsigned char[filesize];

	fread(buf, 1, filesize, f);

	fclose(f);

	string	dstName	= dst + ".h";
	f				= fopen(dstName.c_str(), "wb");

	fprintf(f, "\n");
	fprintf(f, "// generated from %s\n\n", src.c_str());
	fprintf(f, "unsigned char %s[%i] = {\n", dst.c_str(), filesize);

	for(int i=0; i<filesize; i++) {

		if(i % 18 == 0) {
			fprintf(f, "\n");
			fprintf(f, "      ");
		}

		fprintf(f, "0x%x, ", buf[i]);
	}

	fprintf(f, "\n");
	fprintf(f, "};\n\n");
	fprintf(f, "// bypass rawstyle again\n");
	fprintf(f, "// hier könnte noch so viel stehen - tuts aber naet.\n");

	fclose(f);
	delete [] buf;
}

int main(int argc, char* argv[]) {

#define CONVERT_TUNE
#ifndef CONVERT_TUNE

	if(argc < 2) {
		std::cout << "use: converter data_file tgt_name" << std::endl;
		std::cout << "(tgt_name w/o extension!1)" << std::endl;
		return 1;
	}

	Map* map = BMP::load(argv[1]);
	save_to_h(argv[2], map);
	delete map;

	return 0;
	
#else

	if(argc < 2) {
		std::cout << "use: converter tune.xm target_name" << std::endl;
		std::cout << "(tgt_name w/o extension!1)" << std::endl;
		return 1;
	}

	convertTune(argv[1], argv[2]);
	return 0;

#endif

}
