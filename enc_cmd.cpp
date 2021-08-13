#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "alg.h"



int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "argc error" << std::endl;
		return 0;
	}
	
	if (strcmp(argv[1], "-e") == 0) {
		std::cout << "11l " << std::endl;
		FILE * infile = fopen("input.zip", "rb");
		FILE * outfile = fopen("result.zip", "w");
		size_t size  = 0;
		
		fseek(infile, 0L, SEEK_END);
		size = ftell(infile);
		std::cout << "file size = " << size << std::endl;
		fseek(infile, 0L, SEEK_SET);
		void *buf = malloc(size + 1);
		fread(buf, 1, size, infile);

		void *out = malloc(size + 16);
		memset(out, 0, size + 16);
		unsigned int out_len = 0;
		
		enc_aes((unsigned char*)buf, size, (unsigned char*)out, &out_len);
		
		fwrite(out, out_len, 1, outfile);
	} else {
		FILE * infile = fopen("result.zip", "rb");
		FILE * outfile = fopen("input.zip", "w");
		size_t size  = 0;
		fseek(infile, 0L, SEEK_END);
		size = ftell(infile);
		if (size > (1L << 30)) {
			std::cout << "input file is too big, should < 1GB" << std::endl;
			return 0;
		}
		fseek(infile, 0L, SEEK_SET);
		void *buf = malloc(size + 16);
		fread(buf, 1, size, infile);

		void *out = malloc(size + 1);
		memset(out, 0, size + 1);
		unsigned int out_len;
		std::cout << "dec size = " << size << std::endl;
		dec_aes((unsigned char*)buf, size, (unsigned char*)out, &out_len);
		std::cout << "out_len = " << out_len << std::endl;
		
		fwrite(out, out_len, 1, outfile);
	}

	return 1;


}
