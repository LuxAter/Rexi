#include "core.hpp"

#include <algorithm>
#include <experimental/filesystem>
#include <map>
#include <set>
#include <string>
#include <variant>

#include "files.hpp"

#include <iostream>

namespace fs = std::experimental::filesystem;

bool in(std::string key,
        std::map<std::string, std::variant<std::string, int, bool>> mp) {
  if (mp.find(key) == mp.end()) {
    return false;
  } else {
    return true;
  }
}
std::string relative(fs::path a, fs::path root) {
  for (fs::path::iterator it = a.begin(), root_it = root.begin();
       it != a.end() && root_it != root.end(); ++it, ++root_it) {
    std::cout << *it << "\n";
  }
  std::cout << "|N\n";
}

bool path_comp::operator()(const fs::path& lhs, const fs::path& rhs) {
  fs::path lhs_copy = lhs, rhs_copy = rhs;
  std::string lhs_filename = lhs.filename(), rhs_filename = rhs.filename();
  if (lhs_filename[0] == '.') {
    lhs_filename.erase(lhs_filename.begin());
  }
  if (rhs_filename[0] == '.') {
    rhs_filename.erase(rhs_filename.begin());
  }
  lhs_copy.replace_filename(lhs_filename);
  rhs_copy.replace_filename(rhs_filename);
  std::string lhs_str = lhs_copy, rhs_str = rhs_copy;
  std::transform(lhs_str.begin(), lhs_str.end(), lhs_str.begin(), ::tolower);
  std::transform(rhs_str.begin(), rhs_str.end(), rhs_str.begin(), ::tolower);
  return lhs_str < rhs_str;
}

std::set<fs::path, path_comp> ReadPaths(fs::path root, bool show_hidden) {
  std::set<fs::path, path_comp> paths;
  for (fs::directory_entry p : fs::directory_iterator(root)) {
    if (p.path().filename().c_str()[0] != '.' || show_hidden == true) {
      paths.insert(p.path());
    }
  }
  return paths;
}

int RunRecurse(
    std::map<std::string, std::variant<std::string, int, bool>> args) {}

int RunTerminal(
    std::map<std::string, std::variant<std::string, int, bool>> args) {
  bool show_hidden = false;
  if (in("all", args)) {
    show_hidden = true;
  }
  fs::path current_path = fs::current_path();
  std::set<fs::path, path_comp> paths = ReadPaths(current_path, show_hidden);
  for (std::set<fs::path>::iterator it = paths.begin(); it != paths.end();
       ++it) {
    std::cout << (*it).filename() << ":" << fs::is_directory(*it) << "\n";
  }
}

int Run(std::map<std::string, std::variant<std::string, int, bool>> args) {
  if (in("recurse", args)) {
    return RunRecurse(args);
  } else {
    return RunTerminal(args);
  }
}
