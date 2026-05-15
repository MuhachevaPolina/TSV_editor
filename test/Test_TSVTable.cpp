#include <src/tsv-editor/TSVTable.h>

#include <test/testUtilities.h>

#include <gtest/gtest.h>

//add tests for wrong indexes and for wrong row/column lengthes and think some more

TEST(TSVTableTests, EmptyTableRowsCount)
{
  TSVTable table;
  EXPECT_TRUE(table.rowCount() == 1);
}

TEST(TSVTableTests, EmptyTableColumnsCount)
{
  TSVTable table;
  EXPECT_TRUE(table.columnCount() == 1);
}

TEST(TSVTableTests, ConstructorWithSizeParams)
{
  TSVTable* table = utilities::makeTestTable();
  EXPECT_TRUE(table->rowCount() == 3);
}

TEST(TSVTableTests, GetCellData)
{
  TSVTable* table = utilities::makeTestTable();
  
  EXPECT_TRUE(table->getCellData(0, 0).length() >= 1 && table->getCellData(0, 0).length() <= 15);
}

TEST(TSVTableTests, GetRowData)
{
  TSVTable* table = utilities::makeTestTable();

  std::vector<std::string> gottenRow = table->getRowData(0);
  EXPECT_TRUE(gottenRow.size() == 3);
}

TEST(TSVTableTests, GetColumnData)
{
  TSVTable* table = utilities::makeTestTable();

  std::vector<std::string> gottenColumn = table->getColumnData(0);
  EXPECT_EQ(gottenColumn[1], table->getCellData(1, 0));
}

TEST(TSVTableTests, SetCellData)
{
  TSVTable* table = utilities::makeTestTable();

  table->setCellData(1, 1, "true");
  EXPECT_EQ("true", table->getCellData(1, 1));
}

TEST(TSVTableTests, SetRowData)
{
  TSVTable* table = utilities::makeTestTable();

  std::vector<std::string> row(3, "true");
  table->setRowData(1, row);
  EXPECT_EQ("true", table->getCellData(1, 1));
  EXPECT_EQ("true", table->getCellData(1, 0));
  EXPECT_EQ("true", table->getCellData(1, 2));
}

TEST(TSVTableTests, SetColumnData)
{
  TSVTable* table = utilities::makeTestTable();

  std::vector<std::string> row(3, "true");
  table->setColumnData(1, row);
  EXPECT_EQ("true", table->getCellData(0, 1));
  EXPECT_EQ("true", table->getCellData(1, 1));
  EXPECT_EQ("true", table->getCellData(2, 1));
}

TEST(TSVTableTests, DeleteRow)
{
  TSVTable* table = utilities::makeTestTable();

  EXPECT_TRUE(table->rowCount() == 3);
  table->deleteRow(1);
  EXPECT_TRUE(table->rowCount() == 2);
}

TEST(TSVTableTests, DeleteColumn)
{
  TSVTable* table = utilities::makeTestTable();

  EXPECT_TRUE(table->columnCount() == 3);
  std::vector<std::string> lastColumn(3);
  for(int i = 0; i < table->rowCount(); ++i)
  {
    lastColumn[i] = table->getCellData(i, 2);
  }

  table->deleteColumn(1);
  EXPECT_TRUE(table->columnCount() == 2);
  EXPECT_EQ(table->getCellData(0, 1), lastColumn[0]); // column num. 1 is the last now
  EXPECT_EQ(table->getCellData(1, 1), lastColumn[1]);
  EXPECT_EQ(table->getCellData(2, 1), lastColumn[2]);
}

TEST(TSVTableTests, AddRow)
{
  TSVTable* table = utilities::makeTestTable();

  table->addRow(0);
  EXPECT_TRUE(table->rowCount() == 4);
  EXPECT_TRUE(table->getCellData(0, 0).empty());
  EXPECT_FALSE(table->getCellData(1, 0).empty());
  table->addRow(4);
  EXPECT_TRUE(table->rowCount() == 5);
  EXPECT_TRUE(table->getCellData(4, 0).empty());
}

TEST(TSVTableTests, AddColumn)
{
  TSVTable* table = utilities::makeTestTable();

  table->addColumn("new header", 0);
  EXPECT_TRUE(table->columnCount() == 4);
  EXPECT_TRUE(table->getCellData(0, 0).empty());
  EXPECT_FALSE(table->getCellData(0, 1).empty());
  EXPECT_EQ(table->getHeaderData(0), "new header");

  table->addColumn("new header for 5th", 4);
  EXPECT_TRUE(table->columnCount() == 5);
  EXPECT_TRUE(table->getCellData(0, 4).empty());
  EXPECT_EQ(table->getHeaderData(4), "new header for 5th");
}

TEST(TSVTableTests, WrongIdxForAddRow)
{
  TSVTable* table = utilities::makeTestTable();

  table->addRow(5);
  EXPECT_EQ(table->getCellData(4, 0), "wrong idx");
}

TEST(TSVTableTests, WrongIdxForAddColumn)
{
  TSVTable* table = utilities::makeTestTable();

  table->addColumn("new header", 5);
  EXPECT_EQ(table->getCellData(0, 4), "wrong idx");
  EXPECT_EQ(table->getHeaderData(4), "wrong idx");
}