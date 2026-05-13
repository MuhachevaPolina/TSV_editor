#include <test/testUtilities.h>

std::string utilities::generateRandomString(std::size_t length)
{
  const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::random_device rd;
  std::mt19937 generator(rd());

  // Range: [0, characters.size() - 1]
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);

  std::string random_string;
  for (std::size_t i = 0; i < length; ++i)
  {
    random_string += characters[distribution(generator)];
  }

  return random_string;
}

TSVTable *utilities::makeTestTable()
{
  TSVTable *table = new TSVTable(3, 3);
  std::string randomStr;

  for (int i = 0; i < table->rowCount(); ++i)
  {
    for (int j = 0; j < table->columnCount(); ++j)
    {
      randomStr = generateRandomString(15);
      table->setCellData(i, j, randomStr);
    }
  }

  return table;
}
