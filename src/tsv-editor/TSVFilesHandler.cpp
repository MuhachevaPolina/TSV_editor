#include <src/tsv-editor/TSVFilesHandler.h>

TSVFilesHandler::TSVFilesHandler(std::string tableFilesDirName): m_tableFilesDirName(tableFilesDirName)
{}

void TSVFilesHandler::open(std::string fileName)
{
  this->m_openedFiles[fileName] = std::make_shared<std::fstream>(fileName, std::ios::in | std::ios::out | std::ios::app);
}

void TSVFilesHandler::close(std::string fileName)
{
  
}