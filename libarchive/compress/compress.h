#ifndef __DECOMPRESS_H__
#define __DECOMPRESS_H__
#include "archive/archive.h"
#include "archive/archive_entry.h"
#include <string>
#include <vector>

class Decompress {
public:
    explicit Decompress();
    ~Decompress();

public:
    bool extractArchive(const std::string& filePath, const std::string& extractPath);
    std::vector<std::string> getCompressedFileList(const std::string& filePath);
};

#endif /*__DECOMPRESS_H__*/
