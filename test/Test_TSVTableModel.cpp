#include <src/tsv-editor/TSVTableModel.h>

#include <gtest/gtest.h>

TEST(TSVTableModelTests, DefaultModelSize)
{
  TSVTableModel model;

  EXPECT_EQ(model.rowCount(), 1);
  EXPECT_EQ(model.columnCount(), 1);
}

TEST(TSVTableModelTests, SetData)
{
  TSVTableModel model;

  QModelIndex index = model.index(0, 0);

  EXPECT_TRUE(model.setData(index, "hello", Qt::EditRole));

  EXPECT_EQ(model.data(index, Qt::DisplayRole).toString().toStdString(), "hello");
  EXPECT_EQ(model.data(index, Qt::EditRole).toString().toStdString(), "hello");
}

TEST(TSVTableModelTests, SetHeaderData)
{
  TSVTableModel model;

  EXPECT_TRUE(model.setHeaderData(0, Qt::Horizontal, "name", Qt::EditRole));

  EXPECT_EQ(model.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString(), "name");
}

TEST(TSVTableModelTests, AddRow)
{
  TSVTableModel model;

  EXPECT_EQ(model.rowCount(), 1);

  EXPECT_TRUE(model.insertRow(1));

  EXPECT_EQ(model.rowCount(), 2);
}

TEST(TSVTableModelTests, AddColumn)
{
  TSVTableModel model;

  EXPECT_EQ(model.columnCount(), 1);

  EXPECT_TRUE(model.insertColumn(1));

  EXPECT_EQ(model.columnCount(), 2);
}

TEST(TSVTableModelTests, DeleteRow)
{
  TSVTableModel model;

  model.insertRow(1);
  model.insertRow(2);

  EXPECT_EQ(model.rowCount(), 3);

  QModelIndex index0 = model.index(0, 0);
  QModelIndex index1 = model.index(1, 0);
  QModelIndex index2 = model.index(2, 0);

  model.setData(index0, "first", Qt::EditRole);
  model.setData(index1, "second", Qt::EditRole);
  model.setData(index2, "third", Qt::EditRole);

  EXPECT_TRUE(model.removeRow(1));

  EXPECT_EQ(model.rowCount(), 2);

  EXPECT_EQ(model.data(model.index(0, 0), Qt::DisplayRole).toString().toStdString(), "first");
  EXPECT_EQ(model.data(model.index(1, 0), Qt::DisplayRole).toString().toStdString(), "third");
}

TEST(TSVTableModelTests, DeleteColumn)
{
  TSVTableModel model;

  model.insertColumn(1);
  model.insertColumn(2);

  EXPECT_EQ(model.columnCount(), 3);

  model.setHeaderData(0, Qt::Horizontal, "first", Qt::EditRole);
  model.setHeaderData(1, Qt::Horizontal, "second", Qt::EditRole);
  model.setHeaderData(2, Qt::Horizontal, "third", Qt::EditRole);

  model.setData(model.index(0, 0), "A", Qt::EditRole);
  model.setData(model.index(0, 1), "B", Qt::EditRole);
  model.setData(model.index(0, 2), "C", Qt::EditRole);

  EXPECT_TRUE(model.removeColumn(1));

  EXPECT_EQ(model.columnCount(), 2);

  EXPECT_EQ(model.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString(), "first");
  EXPECT_EQ(model.headerData(1, Qt::Horizontal, Qt::DisplayRole).toString().toStdString(), "third");

  EXPECT_EQ(model.data(model.index(0, 0), Qt::DisplayRole).toString().toStdString(), "A");
  EXPECT_EQ(model.data(model.index(0, 1), Qt::DisplayRole).toString().toStdString(), "C");
}
TEST(TSVTableModelTests, RemoveWrongRow)
{
  TSVTableModel model;

  EXPECT_FALSE(model.removeRow(-1));
  EXPECT_FALSE(model.removeRow(10));
}

TEST(TSVTableModelTests, RemoveWrongColumn)
{
  TSVTableModel model;

  EXPECT_FALSE(model.removeColumn(-1));
  EXPECT_FALSE(model.removeColumn(10));
}