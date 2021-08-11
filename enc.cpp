#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "aes.h"



int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "argc error" << std::endl;
		return 0;
	}
	std::cout << "kskdk" << argv[1] << std::endl;
	if (strcmp(argv[1], "-e") == 0) {
		std::cout << "11l " << std::endl;
		FILE * infile = fopen("input.zip", "rb");
		FILE * outfile = fopen("result.zip", "w");
		size_t size  = 0;
		
		fseek(infile, 0L, SEEK_END);
		size = ftell(infile);
		std::cout << "file size = " << size << std::endl;
		fseek(infile, 0L, SEEK_SET);
		void *buf = malloc(size + 16);
		fread(buf, 1, size, infile);

		void *out = malloc(size + 32);
		memset(out, 0, size + 32);
		std::cout << "begin enc ..." << std::endl;
		enc((char*)buf, size, (char*)out);
		
		fwrite(out, size + 32, 1, outfile);
	} else {
		std::cout << "11l ll" << std::endl;
		FILE * infile = fopen("result.zip", "rb");
		FILE * outfile = fopen("input.zip", "w");
		size_t size  = 0;
		fseek(infile, 0L, SEEK_END);
		size = ftell(infile);
		fseek(infile, 0L, SEEK_SET);
		void *buf = malloc(size + 16);
		fread(buf, 2, size, infile);

		void *out = malloc(size + 32);
		memset(out, 0, size + 32);
		dec((char*)buf, size, (char*)out);
		
		fwrite(out, size + 32, 1, outfile);
	}

	return 1;


}
