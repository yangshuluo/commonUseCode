#include "Decompress.h"
#include "log/log.h"

Decompress::Decompress() {}

Decompress::~Decompress() {}

/**
 * @brief 解压文件
 *
 * @param filePath 文件路径
 * @param extractPath 解压路径
 * @return true
 * @return false
 */
bool Decompress::extractArchive(const std::string& filePath, const std::string& extractPath) {
    try {
        struct archive*       a = archive_read_new();
        struct archive_entry* entry;
        int                   result;

        // 启用所有支持的压缩过滤器，可以自动检测压缩包类型，不需要手动指定过滤器
        archive_read_support_filter_all(a);

        // 设置输入文件格式自动检测
        archive_read_support_format_all(a);

        // 打开压缩包文件
        result = archive_read_open_filename(a, filePath.c_str(), 10240);
        if (result != ARCHIVE_OK) {
            archive_read_free(a);
            return false;
        }

        // 解压压缩包中的文件
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char*       currentFile    = archive_entry_pathname(entry);
            const std::string fullOutputPath = extractPath + currentFile;

            // 设置解压后文件的路径
            archive_entry_set_pathname(entry, fullOutputPath.c_str());

            // 解压文件
            result = archive_read_extract(
                a, entry, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);

            //保留解压后用户组和用户权限
            uid_t uid = archive_entry_uid(entry);
            gid_t gid = archive_entry_gid(entry);
             if (chown(fullOutputPath.c_str(), uid, gid) != 0) {
                LOG_ERROR("failed to modify the user group");
            }

            if (result != ARCHIVE_OK) {
                archive_read_close(a);
                archive_read_free(a);
                LOG_WARN("Extracting  %s failed.", fullOutputPath.c_str());
                return false;
            }
            LOG_INFO("Extracting: %s", fullOutputPath.c_str());
        }

        // 关闭压缩包文件
        archive_read_close(a);
        archive_read_free(a);
    }
    catch (...) {
        LOG_ERROR("the program may crash if it fails to extract the file.");
    }

    return true;
}

/**
 * @brief 获取压缩包中的文件列表
 *
 * @param filePath 压缩包文件路径
 * @return std::vector<std::string> 包含压缩包中所有文件的列表
 */
std::vector<std::string> Decompress::getCompressedFileList(const std::string& filePath) {
    std::vector<std::string> fileList;
    struct archive*          a = archive_read_new();
    struct archive_entry*    entry;
    int                      result;

    // 启用所有支持的压缩过滤器，可以自动检测压缩包类型，不需要手动指定过滤器
    archive_read_support_filter_all(a);

    // 设置输入文件格式自动检测
    archive_read_support_format_all(a);

    // 打开压缩包文件
    result = archive_read_open_filename(a, filePath.c_str(), 10240);
    if (result != ARCHIVE_OK) {
        archive_read_free(a);
        return fileList;
    }

    // 获取压缩包中的文件列表
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        fileList.push_back(archive_entry_pathname(entry));
    }

    // 关闭压缩包文件
    archive_read_close(a);
    archive_read_free(a);

    return fileList;
}