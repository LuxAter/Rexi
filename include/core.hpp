#ifndef REXI_CORE_HPP_
#define REXI_CORE_HPP_

#include <experimental/filesystem>
#include <map>
#include <set>
#include <string>
#include <variant>

namespace fs = std::experimental::filesystem;

struct path_comp {
  bool operator()(const std::experimental::filesystem::path& lhs,
                  const std::experimental::filesystem::path& rhs);
};

std::set<std::experimental::filesystem::path, path_comp> ReadPaths(
    std::experimental::filesystem::path root, bool show_hidden);

int RunRecurse(
    std::map<std::string, std::variant<std::string, int, bool>> args);
int RunTerminal(
    std::map<std::string, std::variant<std::string, int, bool>> args);
int Run(std::map<std::string, std::variant<std::string, int, bool>> args);

#endif  // REXI_CORE_HPP_
