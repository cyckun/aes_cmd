
#include "aes.h"

int enc(char *in, unsigned int len, char *out);
int dec(char *in, unsigned int len, char *out);
int enc_aes(unsigned char *in, unsigned int len, unsigned char *out, unsigned int* out_len);
int dec_aes(unsigned char *in, unsigned int len, unsigned char *out, unsigned int* out_len);
