// #include <src/tsv-editor/TSVFilesHandler.h>
#include "TSVFilesHandler.h"

#include <iostream>
#include <sstream>

TSVFilesHandler::TSVFilesHandler(std::string tableFilesDirName) : m_tableFilesDirName(tableFilesDirName)
{
}

void TSVFilesHandler::open(std::string fileName)
{
  this->m_openedFiles[fileName] = std::make_shared<std::fstream>(this->m_tableFilesDirName + "/" + fileName, std::ios::in | std::ios::out | std::ios::app);
  /*
  std::string line;
  std::getline(*this->m_openedFiles[fileName], line);
  std::cout << line << std::endl;
  */
}

void TSVFilesHandler::close(std::string fileName)
{
  auto it = this->m_openedFiles.find(fileName);

  if (it != this->m_openedFiles.end())
  {
    if (it->second && it->second->is_open())
    {
      it->second->close();
    }

    this->m_openedFiles.erase(it);
  }
}

void TSVFilesHandler::read(std::string fileName)
{
  std::string line;

  std::getline(*this->m_openedFiles[fileName], line);
  std::stringstream headersStream(line);

  std::string cell;
  char delim = '\t';

  while (std::getline(headersStream, cell, delim))
  {
    this->m_headers.push_back(cell);
  }

  int curLineNum = 0;
  int headersNum = this->m_headers.size();
  std::stringstream lineStream;
  std::vector<std::string> emptyLine;
  while (std::getline(*this->m_openedFiles[fileName], line))
  {
    this->m_curReadenFileCells.push_back(emptyLine);
    lineStream.clear();
    lineStream.str(line);
    while (std::getline(lineStream, cell, delim))
    {
      if (this->m_curReadenFileCells[curLineNum].size() < headersNum)
      {
        this->m_curReadenFileCells[curLineNum].push_back(cell);
      }
      else
      {
        std::cerr << "too many cells" << std::endl;
      }
    }

    curLineNum++;
  }

  for (std::vector<std::string> i : this->m_curReadenFileCells)
  {
    for (std::string j : i)
    {
      std::cout << "cur cell: " << j << '\t';
    }
    std::cout << std::endl;
  }
}

void TSVFilesHandler::write(std::string fileName, std::vector<std::string> fileLines)
{
  for (auto line : fileLines)
  {
    this->writeLine(fileName, line);
  }
}

void TSVFilesHandler::writeLine(std::string fileName, std::string line)
{
  *this->m_openedFiles[fileName] << line << "\n";
}
