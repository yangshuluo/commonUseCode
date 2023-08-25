#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

std::string GetFileMd5(const std::string& filePath) {
    if (filePath.empty()) {
        return { "" };
    }
    MD5_CTX md5Context;
    unsigned char result[MD5_DIGEST_LENGTH];
    char          buf[1024 * 16] = { "" };
    std::ifstream file(filePath, std::ifstream::binary);

    if (!file.is_open()) {
        return { "" };
    }

    MD5_Init(&md5Context);
    while (file.good()) {
        file.read(buf, sizeof(buf));
        MD5_Update(&md5Context, buf, file.gcount());
    }
    MD5_Final(result, & md5Context);

    std::stringstream md5String;
    md5String << std::hex <<std::nouppercase << std::setfill('0');
    for(const auto &byte : result) {
        md5String << std::setw(2) << (int)byte;
    }
    return md5String.str();
}

int main() {
    std::cout << GetFileMd5("Makefile") << std::endl;;
    return 0;
}
