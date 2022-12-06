#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <string>
#include <iostream>
#include "base64.h"
using namespace std;

char * base64Encode(const char *buffer, int length, bool newLine);
char * base64Decode(char *input, int length, bool newLine);

//int main(int argc, char* argv[]) {}
int test()
{
    bool newLine = false;
    string input = "Hello World!";

    char * encode = base64Encode(input.c_str(), input.length(), newLine);
    char * decode = base64Decode(encode, strlen(encode), newLine);

    cout << "Base64 Encoded : " << encode << endl;
    cout << "Base64 Decoded : " << decode << endl;

//    cin.get();
	return 1;
}

// base64 ±àÂë
char * base64Encode(const char *buffer, int length, bool newLine)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    BIO_free_all(b64);

    return buff;
}

// base64 ½âÂë
char * base64Decode(char *input, int length, bool newLine)
{
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);
    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);
    BIO_free_all(bmem);

    return buffer;
}
