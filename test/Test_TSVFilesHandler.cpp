#include <src/tsv-editor/TSVFilesHandler.h>
#include <src/tsv-editor/TSVTable.h>

#include <gtest/gtest.h>

#include <QFile>
#include <QTemporaryDir>
#include <QTextStream>

TEST(TSVFilesHandlerTests, ReadFileWithSeveralRows)
{
  QTemporaryDir tempDir;
  ASSERT_TRUE(tempDir.isValid());

  QString fileName = tempDir.path() + "/input.tsv";

  QFile file(fileName);
  ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Text));

  QTextStream stream(&file);
  stream.setCodec("UTF-8");
  stream << "name\tage\tcity\n";
  stream << "Polina\t22\tSPb\n";
  stream << "Anna\t20\tMoscow\n";
  file.close();

  TSVFilesHandler filesHandler;
  TSVTable table;

  EXPECT_TRUE(filesHandler.read(fileName, table));

  EXPECT_EQ(table.columnCount(), 3);
  EXPECT_EQ(table.rowCount(), 2);

  EXPECT_EQ(table.getHeaderData(0), "name");
  EXPECT_EQ(table.getHeaderData(1), "age");
  EXPECT_EQ(table.getHeaderData(2), "city");

  EXPECT_EQ(table.getCellData(0, 0), "Polina");
  EXPECT_EQ(table.getCellData(0, 1), "22");
  EXPECT_EQ(table.getCellData(0, 2), "SPb");

  EXPECT_EQ(table.getCellData(1, 0), "Anna");
  EXPECT_EQ(table.getCellData(1, 1), "20");
  EXPECT_EQ(table.getCellData(1, 2), "Moscow");
}

TEST(TSVFilesHandlerTests, WriteFileCreatesCorrectTsv)
{
  QTemporaryDir tempDir;
  ASSERT_TRUE(tempDir.isValid());

  QString fileName = tempDir.path() + "/output.tsv";

  TSVTable table(2, 3);

  table.setHeaderData(0, "name");
  table.setHeaderData(1, "age");
  table.setHeaderData(2, "city");

  table.setCellData(0, 0, "Polina");
  table.setCellData(0, 1, "22");
  table.setCellData(0, 2, "SPb");

  table.setCellData(1, 0, "Anna");
  table.setCellData(1, 1, "20");
  table.setCellData(1, 2, "Moscow");

  TSVFilesHandler filesHandler;

  EXPECT_TRUE(filesHandler.write(fileName, table));

  QFile file(fileName);
  ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));

  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  QString result = stream.readAll();

  EXPECT_EQ(result, QString("name\tage\tcity\nPolina\t22\tSPb\nAnna\t20\tMoscow\n"));
}

TEST(TSVFilesHandlerTests, ReadFileWithShortRow)
{
  QTemporaryDir tempDir;
  ASSERT_TRUE(tempDir.isValid());

  QString fileName = tempDir.path() + "/short_row.tsv";

  QFile file(fileName);
  ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Text));

  QTextStream stream(&file);
  stream.setCodec("UTF-8");
  stream << "name\tage\tcity\n";
  stream << "Polina\t22\n";
  stream << "Anna\t20\tMoscow\n";
  file.close();

  TSVFilesHandler filesHandler;
  TSVTable table;

  EXPECT_TRUE(filesHandler.read(fileName, table));

  EXPECT_EQ(table.columnCount(), 3);
  EXPECT_EQ(table.rowCount(), 2);

  EXPECT_EQ(table.getCellData(0, 0), "Polina");
  EXPECT_EQ(table.getCellData(0, 1), "22");
  EXPECT_EQ(table.getCellData(0, 2), "");

  EXPECT_EQ(table.getCellData(1, 0), "Anna");
  EXPECT_EQ(table.getCellData(1, 1), "20");
  EXPECT_EQ(table.getCellData(1, 2), "Moscow");
}

TEST(TSVFilesHandlerTests, ReadFileWithTooManyCells)
{
  QTemporaryDir tempDir;
  ASSERT_TRUE(tempDir.isValid());

  QString fileName = tempDir.path() + "/too_many_cells.tsv";

  QFile file(fileName);
  ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Text));

  QTextStream stream(&file);
  stream.setCodec("UTF-8");
  stream << "name\tage\n";
  stream << "Polina\t22\tSPb\n";
  file.close();

  TSVFilesHandler filesHandler;
  TSVTable table;

  EXPECT_FALSE(filesHandler.read(fileName, table));
}