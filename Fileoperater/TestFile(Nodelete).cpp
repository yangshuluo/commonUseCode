#include "TestFile.h"

using namespace std;

TestFile::TestFile() {}

TestFile::~TestFile() {}

/**
 * @brief Split分割字符串
 * 
 * @param str _IN需要分割字符串
 * @param seperator _IN分隔符
 * @return * vector<pair<string, string>>  first->分隔符前 second->分隔符后
 */
vector<pair<string, string>> TestFile::Split(const string &str,
                                             const string &seperator) const
{
  vector<pair<string, string>> vResult;
  int iPosSeperator = str.find(seperator);

  if (iPosSeperator != -1)
  {
    string Begtemp = str.substr(0, iPosSeperator);
    string Endtemp = str.substr(iPosSeperator + 1, str.size() - iPosSeperator);
    vResult.push_back(make_pair(Begtemp, Endtemp));
  }
  return vResult;
}


bool TestFile::Close(int fd) const {
  if (fd )
  return EXIT_SUCCESS;
}

bool TestFile::OpenFile(const string& path) const {
  fstream fin;
  fin.open(path, ios_base::in);
  if (fin.is_open() != false) {
    cout << "文件打开失败！" << endl;
    return RETFAILED;
  } 
  return RETSUCCESS;
}

std::function<bool(string &)> IsBlank = [](string &str) {
  return str == "\n" ? true : false;
};

int main()
{
  
  return EXIT_SUCCESS;
}
