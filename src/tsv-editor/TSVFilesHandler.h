#pragma once

#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>

class TSVFilesHandler
{
public:
  TSVFilesHandler(std::string tableFilesDirName = "../tableFiles");
  void open(std::string fileName);
  void close(std::string fileName);
  void write(std::string fileName, std::vector<std::string> fileLines);
  void read(std::string fileName);
private:
  void writeLine(std::string fileName, std::string line);

  std::map<std::string, std::shared_ptr<std::fstream>> m_openedFiles;
  std::string m_tableFilesDirName;
  std::vector<std::string> m_headers;
  std::vector<std::vector<std::string>> m_curReadenFileCells;
};