#include <src/tsv-editor/TSVTable.h>

std::string TSVTable::getCellData(int rowNum, int columnNum) const
{
  return this->m_tableData[rowNum][columnNum];
}

std::vector<std::string> TSVTable::getRowData(int rowNum) const
{
  return this->m_tableData[rowNum];
}

// look again
std::vector<std::string> TSVTable::getColumnData(int columnNum) const
{
  std::vector<std::string> column(this->m_tableData.size());

  for(int i = 0; i < this->m_tableData.size(); ++i)
  {
    column[i] = this->m_tableData[i][columnNum]; // how is this copying?
  }

  return column;
}

void TSVTable::setCellData(int rowNum, int columnNum, std::string cellData)
{
  if(this->m_tableData.size() > rowNum && this->m_tableData[0].size() > columnNum)
  {
    this->m_tableData[rowNum][columnNum] = cellData;
  }
}

// look again
void TSVTable::setRowData(int rowNum, std::vector<std::string> rowData)
{
  if(this->m_tableData.size() > rowNum)
  {
    this->m_tableData[rowNum] = rowData; // how is this copying?
  }
}

void TSVTable::setColumnData(int columnNum, std::vector<std::string> columnData)
{
  if(this->m_tableData[0].size() > columnNum)
  {
    for(int i = 0; i < this->m_tableData.size(); ++i)
    {
      this->setCellData(i, columnNum, columnData[i]);
    }
  }
}

void TSVTable::deleteRow(int rowNum)
{

}


