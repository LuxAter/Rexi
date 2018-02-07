#include <experimental/filesystem>
#include <iostream>
#include <string>

#include "argparse.hpp"

namespace fs = std::experimental::filesystem;

std::ostream& operator<<(std::ostream& out,
                         std::variant<std::string, int, bool> lhs) {
  if (std::holds_alternative<std::string>(lhs)) {
    out << std::get<std::string>(lhs);
  } else if (std::holds_alternative<int>(lhs)) {
    out << std::get<int>(lhs);
  } else if (std::holds_alternative<bool>(lhs)) {
    out << std::get<bool>(lhs);
  }
  return out;
}

std::ostream& operator<<(
    std::ostream& out,
    std::map<std::string, std::variant<std::string, int, bool>> lhs) {
  out << "{ ";
  for (std::map<std::string, std::variant<std::string, int, bool>>::iterator
           it = lhs.begin();
       it != lhs.end(); ++it) {
    out << (*it).first << ": " << (*it).second;
    if (it != --lhs.end()) {
      out << ", ";
    }
  }
  out << " }";
  return out;
}

int main(int argc, char const* argv[]) {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  ArgumentParser parser("Hello", "Goodbye");
  parser.AddArgument("--list", ArgumentParser::INT, {2, 4, 6, 8, 10}, 15);
  parser.AddArgument({"-a", "--all"}, ArgumentParser::STORE_TRUE);
  auto args = parser.ParseArgs(argc, argv);
  std::cout << "ARGS: " << args << "\n";
  // std::string path = fs::current_path();
  // for (auto& p : fs::directory_iterator(path)) std::cout << p << std::endl;
  return 0;
}
