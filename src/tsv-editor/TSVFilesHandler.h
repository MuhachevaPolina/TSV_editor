#pragma once

#include <fstream>
#include <string>
#include <map>
#include <memory>

class TSVFilesHandler
{
public:
  TSVFilesHandler(std::string tableFilesDirName = "../tableFiles");
  void open(std::string fileName);
  void close(std::string fileName);
  void write(std::string fileName);
  void read(std::string fileName);
private:
  std::map<std::string, std::shared_ptr<std::fstream>> m_openedFiles;
  std::string m_tableFilesDirName;
};