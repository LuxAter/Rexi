#include <string>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char const *argv[]) {
  std::string path = fs::current_path();
    for (auto & p : fs::recursive_directory_iterator(path))
        std::cout << p << std::endl;
  return 0;
}
