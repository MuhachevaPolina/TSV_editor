#include <src/tsv-editor/TSVTable.h>

#include <iostream>

TSVTable::TSVTable() 
{
  this->m_tableData = std::vector<std::vector<std::string>>();
  this->m_tableData.push_back(std::vector<std::string>({" "}));
  this->m_headers.push_back("some header");
}

TSVTable::TSVTable(int rowNum, int columnNum)
{
  this->m_tableData = std::vector<std::vector<std::string>>();
  std::vector<std::string> tempRow(columnNum, " ");

  for (int i = 0; i < rowNum; ++i)
  {
    this->m_tableData.push_back(tempRow);
  }  

  for (int i = 0; i < columnNum; ++i)
  {
    this->m_headers.push_back("some header");
  }
}

std::string TSVTable::getCellData(int rowNum, int columnNum) const
{
  if(rowNum < this->rowCount() && columnNum < this->columnCount())
  {
    return this->m_tableData[rowNum][columnNum];
  }
  else
  {
    return "wrong idx";
  }
}

std::vector<std::string> TSVTable::getRowData(int rowNum) const
{
  return this->m_tableData[rowNum];
}

std::vector<std::string> TSVTable::getColumnData(int columnNum) const
{
  std::vector<std::string> column(this->rowCount());

  for (int i = 0; i < this->rowCount(); ++i)
  {
    column[i] = this->m_tableData[i][columnNum];
  }

  return column;
}

void TSVTable::setCellData(int rowNum, int columnNum, std::string cellData)
{
  if (this->rowCount() > rowNum && this->columnCount() > columnNum)
  {
    this->m_tableData[rowNum][columnNum] = cellData;
  }
}

// look again
void TSVTable::setRowData(int rowNum, std::vector<std::string> rowData)
{
  if (this->rowCount() > rowNum)
  {
    this->m_tableData[rowNum] = rowData;
  }
}

void TSVTable::setColumnData(int columnNum, std::vector<std::string> columnData)
{
  if (this->columnCount() > columnNum)
  {
    for (int i = 0; i < this->m_tableData.size(); ++i)
    {
      this->setCellData(i, columnNum, columnData[i]);
    }
  }
}

void TSVTable::deleteRow(int rowNum)
{
  if (rowNum < this->rowCount())
  {
    this->m_tableData.erase(this->m_tableData.begin() + rowNum);
  }
}

void TSVTable::deleteColumn(int columnNum)
{
  if (columnNum < this->columnCount())
  {
    for (int i = 0; i < this->rowCount(); ++i)
    {
      this->m_tableData[i].erase(this->m_tableData[i].begin() + columnNum);
    }
    this->m_headers.erase(this->m_headers.begin() + columnNum);
  }
}

int TSVTable::rowCount() const
{
  return this->m_tableData.size();
}

int TSVTable::columnCount() const
{
  if (this->rowCount() != 0)
  {
    return this->m_tableData[0].size();
  }
  return 0;
}

void TSVTable::addRow(int rowNum)
{
  int columnCount;
  if (this->columnCount() == 0)
  {
    columnCount = 1;
  }
  std::vector<std::string> row(this->columnCount());

  if (this->rowCount() > rowNum)
  {
    this->m_tableData.insert(this->m_tableData.begin() + rowNum, row);
  }
  else if (this->rowCount() == rowNum || this->rowCount() == 0)
  {
    this->m_tableData.insert(this->m_tableData.end(), row);
  }
}

void TSVTable::addColumn(std::string header, int columnNum)
{
  if (this->columnCount() > columnNum)
  {
    this->m_headers.insert(this->m_headers.begin() + columnNum, header);

    for (int i = 0; i < rowCount(); ++i)
    {
      this->m_tableData[i].insert(this->m_tableData[i].begin() + columnNum, std::string());
    }
  }
  else if (this->columnCount() == columnNum || this->columnCount() == 0)
  {
    this->m_headers.insert(this->m_headers.end(), header);
    for (int i = 0; i < rowCount(); ++i)
    {
      this->m_tableData[i].insert(this->m_tableData[i].end(), std::string());
    }
  }
}

std::string TSVTable::getHeaderData(int columnNum) const
{
  if(columnNum < this->columnCount())
  {
    return this->m_headers[columnNum];
  }
  else
  {
    return "wrong idx";
  }
}

void TSVTable::debugOutput()
{
  int maxCellSize = 0;
  for (int i = 0; i < this->rowCount(); ++i)
  {
    for (int j = 0; j < this->columnCount(); ++j)
    {
      if (this->m_tableData[i][j].length() > maxCellSize)
      {
        maxCellSize = this->m_tableData[i][j].length();
      }
    }
  }

  std::string curSpace;
  for (int i = 0; i < this->rowCount(); ++i)
  {
    for (int j = 0; j < this->columnCount(); ++j)
    {
      curSpace = std::string(" ", maxCellSize - this->m_tableData[i][j].length());
      std::cout << this->m_tableData[i][j] << curSpace << " | ";
    }
    std::cout << std::endl;
  }
}

void TSVTable::setHeaderData(int colunmNum, std::string headerData)
{
  if(colunmNum < this->columnCount())
  {
    this->m_headers[colunmNum] = headerData;
  }
  else if(colunmNum == this->columnCount())
  {
    this->m_headers.push_back(std::string());
  }
}
