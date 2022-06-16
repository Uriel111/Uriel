#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>
//  简单来说 就是按照相同的编码和解码规则 进行传输数据
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif
