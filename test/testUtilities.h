#include <src/tsv-editor/TSVTable.h>

#include <iostream>
#include <random>

namespace utilities
{
  std::string generateRandomString(std::size_t length);

  TSVTable *makeTestTable();
}