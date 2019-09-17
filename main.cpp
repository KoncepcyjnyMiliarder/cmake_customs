#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::ifstream filein(argc == 2 ? argv[1] : "/dev/stdin");
  if (!filein) {
    std::cerr << "File does not exist\n";
    return 2;
  }

  std::vector<std::string> vals_to_sort;
  std::string input_line;

  while (std::getline(filein, input_line))
    vals_to_sort.emplace_back(std::move(input_line));

  std::sort(begin(vals_to_sort), end(vals_to_sort));

  for (const auto &str : vals_to_sort)
    std::puts(str.c_str());

  return 0;
}
