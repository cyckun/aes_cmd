#include "alg.h"


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

int enc_aes(unsigned char *in, unsigned int len, unsigned char *out, unsigned int* out_len) {
    AES_KEY key;
    unsigned char usrkey[16];
    for (int i = 0; i < 16; i++) 
        usrkey[i] = 99 - i;
    AES_set_encrypt_key(usrkey, 128, &key);
    unsigned int block_num = len / 16;
    int left_bytes = len % 16;

    for (unsigned int i = 0; i < block_num; i++)
        AES_encrypt(in + 16*i, out + 16*i, &key);
    
    // deal left bytes;
    if (left_bytes != 0) {
        unsigned char buf[16];
        for (int i = 0; i < left_bytes; i++) buf[i] = in[block_num*16 + i];
        for (int i = left_bytes; i < 16; i++) buf[i] = 0x5a;
        AES_encrypt(buf, out+16*block_num, &key);
    }
    *out_len = len;
    printf("left byres: %d", left_bytes);

    if (left_bytes != 0) *out_len += (16-left_bytes);
      
    
    return 0;
}
int dec_aes(unsigned char *in, unsigned int len, unsigned char *out, unsigned int* out_len) {
  
    if (len % 16) return 1; // cipherlen is error;
    
    AES_KEY key;
    unsigned char usrkey[16];
    for (int i = 0; i < 16; i++) 
        usrkey[i] = 99 - i;
    AES_set_decrypt_key(usrkey, 128, &key);
    unsigned int block_num = len / 16;
    for (unsigned int i = 0; i < block_num; i++)
        AES_decrypt(in + 16*i, out + 16*i, &key);
    unsigned int count = 0;
    for (int i = 0; i < 16; i++) {
        printf("i = %02x\n", out[len-1-i]);
        if (out[len -1 - i] == 0x5a)  count++;
    }
    
    *out_len = len - count;
    printf(" len = %d, count = %d", *out_len, count);
    return 0;
}
