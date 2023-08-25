#include "system1.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

int main() {
    SystemHelper s;
    char         cmd[256] = { 0 };
    char*        out      = new char[1000 * 128];
    snprintf(cmd, sizeof(cmd), "unrar l %s | awk 'NR > 8 {print $NF}'", "/home/yyz/yyz/test/rar.rar");
    s.SystemGetPopen(cmd, out, 1000 * 128 + 1);
    // cout << out << endl;

    std::vector<std::string> fileList;
    std::istringstream       ss(out);
    std::string              line;

    if (out > 0)
        cout << strlen(out) << endl;
    while (std::getline(ss, line)) {
        fileList.push_back(line);
    }
    if (fileList.size() > 2) {  // unzip会有两个无用名
        fileList.pop_back();
        fileList.pop_back();
        fileList.pop_back();
    }
    std::cout << "File list:" << std::endl;
    for (const auto& fileName : fileList) {
        std::cout << fileName << std::endl;
    }
    delete[] out;
    return 0;
}