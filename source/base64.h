#ifndef BASE64_H
#define BASE64_H

extern void base64_encode(const unsigned char *str, int length,unsigned char *result, int *ret_length);
extern void base64_decode(const unsigned char *str, int length,unsigned char *result, int *ret_length);


#endif /* BASE64_H */
