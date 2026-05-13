#pragma once

#include <vector>
#include <string>

// headers.size == row.size

class TSVTable
{
public:
  TSVTable();
  TSVTable(int rowNum, int columnNum);

  std::string getCellData(int rowNum, int columnNum) const;
  std::vector<std::string> getRowData(int rowNum) const;
  std::vector<std::string> getColumnData(int columnNum) const;
  
  void setCellData(int rowNum, int columnNum, std::string cellData);
  void setRowData(int rowNum, std::vector<std::string> rowData);
  void setColumnData(int columnNum, std::vector<std::string> columnData);

  void deleteRow(int rowNum);
  void deleteColumn(int columnNum);

  std::string getHeaderData(int columnNum) const;
  void setHeaderData(int columnNum, std::string headerData);

  int rowCount() const;
  int columnCount() const;

  void addRow(int rowNum);
  void addColumn(const std::string header, int columnNum);

  void debugOutput();

private:
  std::vector<std::vector<std::string>> m_tableData;
  std::vector<std::string> m_headers;
};