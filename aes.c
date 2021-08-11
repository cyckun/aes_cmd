#include "aes.h"

int enc(char *in, unsigned int len, char *out) {
    for (unsigned int i = 0; i < len; i++)
        if (i % 2) out[i] = in[i] ^ 0x5a;
        else out[i] = in[i] ^ 0x3b;
    return 0;
}
int dec(char *in, unsigned int len, char *out) {
        for (unsigned int i = 0; i < len; i++)
        if (i % 2) out[i] = in[i] ^ 0x5a;
        else out[i] = in[i] ^ 0x3b;
    return 0;
}

