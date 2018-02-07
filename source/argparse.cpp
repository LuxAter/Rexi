#include "argparse.hpp"

#include <algorithm>
#include <any>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <variant>
#include <vector>

std::string trim_left(std::string str, std::string chars) {
  for (int i = 0; i < str.size(); i++) {
    if (chars.find(str[i]) != std::string::npos) {
      str.erase(str.begin());
      i--;
    } else {
      break;
    }
  }
  return str;
}
bool starts_with(std::string str, std::string match) {
  if (match.size() > str.size()) {
    return false;
  } else {
    for (std::size_t i = 0; i < str.size() && i < match.size(); i++) {
      if (str[i] != match[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}
std::vector<std::string> split(std::string str, char ch) {
  std::vector<std::string> strs;
  std::string current_str;
  for (std::size_t i = 0; i < str.size(); i++) {
    if (str[i] == ch) {
      strs.push_back(current_str);
      current_str = std::string();
    } else {
      current_str += str[i];
    }
  }
  strs.push_back(current_str);
  return strs;
}

ArgumentParser::ArgumentParser(std::string help, std::string epilog) {}

void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name, std::any a,
    std::any b, std::any c, std::any d, std::any e) {
  AddAnyArg(name, a, b, c, d, e);
}

void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name,
    std::initializer_list<std::variant<std::string, int, bool>> a, std::any b,
    std::any c, std::any d, std::any e) {
  AddAnyArg(name, a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name, std::any a,
    std::initializer_list<std::variant<std::string, int, bool>> b, std::any c,
    std::any d, std::any e) {
  AddAnyArg(name, a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name, std::any a,
    std::any b, std::initializer_list<std::variant<std::string, int, bool>> c,
    std::any d, std::any e) {
  AddAnyArg(name, a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name, std::any a,
    std::any b, std::any c,
    std::initializer_list<std::variant<std::string, int, bool>> d, std::any e) {
  AddAnyArg(name, a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::variant<std::string, std::set<std::string>> name, std::any a,
    std::any b, std::any c, std::any d,
    std::initializer_list<std::variant<std::string, int, bool>> e) {
  AddAnyArg(name, a, b, c, d, e);
}
void ArgumentParser::AddArgument(std::initializer_list<std::string> name,
                                 std::any a, std::any b, std::any c, std::any d,
                                 std::any e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}

void ArgumentParser::AddArgument(
    std::initializer_list<std::string> name,
    std::initializer_list<std::variant<std::string, int, bool>> a, std::any b,
    std::any c, std::any d, std::any e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::initializer_list<std::string> name, std::any a,
    std::initializer_list<std::variant<std::string, int, bool>> b, std::any c,
    std::any d, std::any e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::initializer_list<std::string> name, std::any a, std::any b,
    std::initializer_list<std::variant<std::string, int, bool>> c, std::any d,
    std::any e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::initializer_list<std::string> name, std::any a, std::any b, std::any c,
    std::initializer_list<std::variant<std::string, int, bool>> d, std::any e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}
void ArgumentParser::AddArgument(
    std::initializer_list<std::string> name, std::any a, std::any b, std::any c,
    std::any d, std::initializer_list<std::variant<std::string, int, bool>> e) {
  AddAnyArg(std::set<std::string>(name), a, b, c, d, e);
}

void ArgumentParser::AddAnyArg(
    std::variant<std::initializer_list<std::string>,
                 std::variant<std::string, std::set<std::string>>>
        name,
    std::any a, std::any b, std::any c, std::any d, std::any e) {
  bool checks = false;
  Argument new_arg;
  std::set<std::string> name_set;
  if (std::holds_alternative<std::initializer_list<std::string>>(name)) {
    new_arg.SetNames(std::set<std::string>(
        std::get<std::initializer_list<std::string>>(name)));
  } else if (std::holds_alternative<
                 std::variant<std::string, std::set<std::string>>>(name)) {
    new_arg.SetNames(
        std::get<std::variant<std::string, std::set<std::string>>>(name));
  }
  std::vector<std::any> args = {a, b, c, d, e};
  for (std::vector<std::any>::iterator it = args.begin(); it != args.end();
       ++it) {
    if ((*it).type() == typeid(Action)) {
      new_arg.SetAction(std::any_cast<Action>(*it));
    } else if ((*it).type() == typeid(Type)) {
      new_arg.SetType(std::any_cast<Type>(*it));
    } else if ((*it).type() == typeid(std::string)) {
      checks = true;
      new_arg.SetHelp(std::any_cast<std::string>(*it));
    } else if ((*it).type() == typeid(const char*)) {
      checks = true;
      new_arg.SetHelp(std::string(std::any_cast<std::string>(*it)));
    } else if ((*it).type() ==
               typeid(std::set<std::variant<std::string, int, bool>>)) {
      new_arg.SetChoices(
          std::any_cast<std::set<std::variant<std::string, int, bool>>>(*it));
    } else if ((*it).type() == typeid(std::initializer_list<
                                      std::variant<std::string, int, bool>>)) {
      new_arg.SetChoices(std::set<std::variant<std::string, int, bool>>(
          std::any_cast<
              std::initializer_list<std::variant<std::string, int, bool>>>(
              *it)));
    } else if ((*it).type() == typeid(std::string) ||
               (*it).type() == typeid(int) || (*it).type() == typeid(bool)) {
      if ((*it).type() == typeid(std::string)) {
        new_arg.SetDefault(std::any_cast<std::string>(*it));
      } else if ((*it).type() == typeid(int)) {
        new_arg.SetDefault(std::any_cast<int>(*it));
      } else if ((*it).type() == typeid(bool)) {
        new_arg.SetDefault(std::any_cast<bool>(*it));
      }
    } else if ((*it).type() != typeid(std::monostate)) {
      std::cerr << "WARNING: Unknown type \"" << (*it).type().name() << "\"\n";
    }
  }
  arguments_.push_back(new_arg);
}
std::map<std::string, std::variant<std::string, int, bool>>
ArgumentParser::ParseArgs(int argc, const char* argv[]) {
  std::map<std::string, std::variant<std::string, int, bool>> data;
  std::vector<std::string> args(argv + 1, argv + argc);
  while (args.size() != 0) {
    bool matched = false;
    for (std::vector<Argument>::iterator it = arguments_.begin();
         it != arguments_.end(); ++it) {
      if ((*it).ParseArg(args) == true) {
        matched = true;
        break;
      }
    }
    if (matched == false) {
      std::cerr << "WARNING: Unrecognized option \"" << args.front() << "\"\n";
      args.erase(args.begin());
    }
  }
  for (std::vector<Argument>::iterator it = arguments_.begin();
       it != arguments_.end(); ++it) {
    std::variant<std::monostate, std::string, int, bool> val = (*it).GetValue();
    std::string dest = (*it).GetDest();
    if (std::holds_alternative<std::string>(val)) {
      data[dest] = std::get<std::string>(val);
    } else if (std::holds_alternative<int>(val)) {
      data[dest] = std::get<int>(val);
    } else if (std::holds_alternative<bool>(val)) {
      data[dest] = std::get<bool>(val);
    }
  }
  return data;
}

bool ArgumentParser::Argument::ParseArg(std::vector<std::string>& args) {
  if (args.size() == 0) {
    return false;
  }
  if (names_.find(args.front()) != names_.end()) {
    if (action_ == STORE && args.size() > 1) {
      if (type_ == STRING) {
        if (choices_.size() == 0 ||
            choices_.find(*(args.begin() + 1)) != choices_.end()) {
          value_ = *(args.begin() + 1);
        } else {
          ListChoices();
        }
        args.erase(args.begin(), args.begin() + 2);
        return true;
      } else if (type_ == INT) {
        std::string data = *(args.begin() + 1);
        if (data.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "ERROR: Not valid integer argument!\n";
          args.erase(args.begin());
          return true;
        } else {
          int val = std::stoi(data);
          if (choices_.size() == 0 || choices_.find(val) != choices_.end()) {
            value_ = val;
          } else {
            ListChoices();
          }
          args.erase(args.begin(), args.begin() + 2);
          return true;
        }
      } else if (type_ == BOOL) {
        bool val;
        std::string data = *(args.begin() + 1);
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        if (data == "true" || data == "t" || data == "1") {
          if (choices_.size() == 0 || choices_.find(true) != choices_.end()) {
            value_ = true;
          } else {
            ListChoices();
          }
          args.erase(args.begin(), args.begin() + 2);
          return true;
        } else if (data == "false" || data == "f" || data == "0") {
          if (choices_.size() == 0 || choices_.find(false) != choices_.end()) {
            value_ = false;
          } else {
            ListChoices();
          }
          args.erase(args.begin(), args.begin() + 2);
          return true;
        } else {
          std::cerr << "ERROR: Not valid boolean argument!\n";
          args.erase(args.begin());
          return true;
        }
      }
    } else if (action_ == STORE_TRUE) {
      value_ = true;
      args.erase(args.begin());
      return true;
    } else if (action_ == STORE_FALSE) {
      value_ = false;
      args.erase(args.begin());
      return true;
    }
  } else if (positional_ == true &&
             (starts_with(args.front(), "-") ||
              starts_with(args.front(), "--")) == false) {
    if (action_ == STORE) {
      if (type_ == STRING) {
        if (choices_.size() == 0 ||
            choices_.find(*(args.begin())) != choices_.end()) {
          value_ = *(args.begin());
        } else {
          ListChoices();
        }
        args.erase(args.begin());
        return true;
      } else if (type_ == INT) {
        std::string data = *args.begin();
        if (data.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "ERROR: Not valid integer argument!\n";
          args.erase(args.begin());
          return true;
        } else {
          int val = std::stoi(data);
          if (choices_.size() == 0 || choices_.find(val) != choices_.end()) {
            value_ = val;
          } else {
            ListChoices();
          }
          args.erase(args.begin());
          return true;
        }
      } else if (type_ == BOOL) {
        bool val;
        std::string data = *args.begin();
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        if (data == "true" || data == "t" || data == "1") {
          if (choices_.size() == 0 || choices_.find(true) != choices_.end()) {
            value_ = true;
          } else {
            ListChoices();
          }
          args.erase(args.begin());
          return true;
        } else if (data == "false" || data == "f" || data == "0") {
          if (choices_.size() == 0 || choices_.find(false) != choices_.end()) {
            value_ = false;
          } else {
            ListChoices();
          }
          args.erase(args.begin());
          return true;
        } else {
          std::cerr << "ERROR: Not valid boolean argument!\n";
          args.erase(args.begin());
          return true;
        }
      }
    } else if (action_ == STORE_TRUE) {
      value_ = true;
      args.erase(args.begin());
      return true;
    } else if (action_ == STORE_FALSE) {
      value_ = false;
      args.erase(args.begin());
      return true;
    }
  } else {
    return false;
  }
}

std::variant<std::monostate, std::string, int, bool>
ArgumentParser::Argument::GetValue() {
  if (std::holds_alternative<std::monostate>(value_)) {
    return default_;
  } else {
    return value_;
  }
}

std::string ArgumentParser::Argument::GetDest() {
  if (names_.size() == 0) {
    return "null";
  } else {
    std::string longest;
    for (std::set<std::string>::iterator it = names_.begin();
         it != names_.end(); ++it) {
      if ((*it).size() >= longest.size()) {
        longest = *it;
      }
    }
    longest = trim_left(longest, "-");
    return longest;
  }
}

void ArgumentParser::Argument::SetNames(
    std::variant<std::string, std::set<std::string>> names) {
  if (std::holds_alternative<std::string>(names)) {
    names_ = std::set<std::string>{std::get<std::string>(names)};
  } else {
    names_ = std::get<std::set<std::string>>(names);
  }
}

void ArgumentParser::Argument::SetAction(Action action) { action_ = action; }

void ArgumentParser::Argument::SetType(Type type) { type_ = type; }

void ArgumentParser::Argument::SetDefault(
    std::variant<std::monostate, std::string, int, bool> def) {
  default_ = def;
}

void ArgumentParser::Argument::SetHelp(std::string help) { help_ = help; }

void ArgumentParser::Argument::SetChoices(
    std::set<std::variant<std::string, int, bool>> choices) {
  choices_ = choices;
}

void ArgumentParser::Argument::ScanNames() {
  for (std::set<std::string>::iterator it = names_.begin(); it != names_.end();
       ++it) {
    if (starts_with(*it, "-") || starts_with(*it, "--")) {
      return;
    }
  }
  positional_ = true;
}

void ArgumentParser::Argument::ListChoices() {
  std::cerr << "ERROR: Not a valid choice!\n"
               "Choices are: {";
  for (std::set<std::variant<std::string, int, bool>>::iterator it =
           choices_.begin();
       it != choices_.end(); ++it) {
    if (std::holds_alternative<std::string>(*it)) {
      std::cerr << std::get<std::string>(*it);
    } else if (std::holds_alternative<int>(*it)) {
      std::cerr << std::get<int>(*it);
    } else if (std::holds_alternative<bool>(*it)) {
      std::cerr << std::get<bool>(*it);
    }
    if (it != (--choices_.end())) {
      std::cerr << ", ";
    }
  }
  std::cerr << "}\n";
}
