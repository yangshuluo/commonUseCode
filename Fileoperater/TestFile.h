#ifndef __TESTFILE_H__
#define __TESTFILE_H__
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>

#define TEXTFILE    "test.txt"


using std::vector;
using std::string;
using std::pair;

class TestFile {
public:
  // std::shared_ptr<TestFile> Test = make_shared<TestFile>();
private:
  vector<pair<string, string>> Split(const string &s,
                                     const string &seperator) const;
  bool Close(int fd) const;
  bool OpenFile(const string& path) const;
public:
  explicit TestFile();
  ~TestFile();

private:
};

enum Ret {
    RETFAILED = 0,
    RETSUCCESS = 1
};


#endif