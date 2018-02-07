#ifndef REXI_ARGPARSE_HPP_
#define REXI_ARGPARSE_HPP_

#include <any>
#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

class ArgumentParser {
 public:
  enum Action { STORE = 0, STORE_TRUE = 1, STORE_FALSE = 2 };
  enum Type { STRING = 0, INT = 1, BOOL = 2 };
  ArgumentParser(std::string help = std::string(),
                 std::string epilog = std::string());

  void SetVersion(std::string version);

  void AddArgument(std::variant<std::string, std::set<std::string>> name,
                   std::any a = std::monostate(), std::any b = std::monostate(),
                   std::any c = std::monostate(), std::any d = std::monostate(),
                   std::any e = std::monostate());
  void AddArgument(
      std::variant<std::string, std::set<std::string>> name,
      std::initializer_list<std::variant<std::string, int, bool>> a,
      std::any b = std::monostate(), std::any c = std::monostate(),
      std::any d = std::monostate(), std::any e = std::monostate());
  void AddArgument(
      std::variant<std::string, std::set<std::string>> name, std::any a,
      std::initializer_list<std::variant<std::string, int, bool>> b,
      std::any c = std::monostate(), std::any d = std::monostate(),
      std::any e = std::monostate());
  void AddArgument(
      std::variant<std::string, std::set<std::string>> name, std::any a,
      std::any b, std::initializer_list<std::variant<std::string, int, bool>> c,
      std::any d = std::monostate(), std::any e = std::monostate());
  void AddArgument(
      std::variant<std::string, std::set<std::string>> name, std::any a,
      std::any b, std::any c,
      std::initializer_list<std::variant<std::string, int, bool>> d,
      std::any e = std::monostate());
  void AddArgument(
      std::variant<std::string, std::set<std::string>> name, std::any a,
      std::any b, std::any c, std::any d,
      std::initializer_list<std::variant<std::string, int, bool>> e);
  void AddArgument(std::initializer_list<std::string> name,
                   std::any a = std::monostate(), std::any b = std::monostate(),
                   std::any c = std::monostate(), std::any d = std::monostate(),
                   std::any e = std::monostate());
  void AddArgument(
      std::initializer_list<std::string> name,
      std::initializer_list<std::variant<std::string, int, bool>> a,
      std::any b = std::monostate(), std::any c = std::monostate(),
      std::any d = std::monostate(), std::any e = std::monostate());
  void AddArgument(
      std::initializer_list<std::string> name, std::any a,
      std::initializer_list<std::variant<std::string, int, bool>> b,
      std::any c = std::monostate(), std::any d = std::monostate(),
      std::any e = std::monostate());
  void AddArgument(
      std::initializer_list<std::string> name, std::any a, std::any b,
      std::initializer_list<std::variant<std::string, int, bool>> c,
      std::any d = std::monostate(), std::any e = std::monostate());
  void AddArgument(
      std::initializer_list<std::string> name, std::any a, std::any b,
      std::any c, std::initializer_list<std::variant<std::string, int, bool>> d,
      std::any e = std::monostate());
  void AddArgument(
      std::initializer_list<std::string> name, std::any a, std::any b,
      std::any c, std::any d,
      std::initializer_list<std::variant<std::string, int, bool>> e);

  std::map<std::string, std::variant<std::string, int, bool>> ParseArgs(
      int argc, const char* argv[]);

  std::string GetVersion();
  std::string GetHelp();
  std::string GetUsage();

 private:
  class Argument {
   public:
    bool ParseArg(std::vector<std::string>& args);
    std::variant<std::monostate, std::string, int, bool> GetValue();
    std::string GetDest();
    std::string GetHelp();
    bool IsPositional();

    void SetNames(std::variant<std::string, std::set<std::string>> names);
    void SetAction(Action action);
    void SetType(Type type);
    void SetDefault(std::variant<std::monostate, std::string, int, bool> def);
    void SetHelp(std::string help);
    void SetChoices(std::set<std::variant<std::string, int, bool>> choices);

   private:
    Action action_ = STORE;
    Type type_ = STRING;
    bool positional_ = false;
    std::set<std::string> names_;
    std::variant<std::monostate, std::string, int, bool> value_;
    std::variant<std::monostate, std::string, int, bool> default_;
    std::string help_;
    std::set<std::variant<std::string, int, bool>> choices_;

    void ScanNames();
    void ListChoices();
  };

  std::vector<Argument> arguments_;
  std::string prog_, prolog_, epilog_;
  std::string version_;

  void AddAnyArg(std::variant<std::initializer_list<std::string>,
                              std::variant<std::string, std::set<std::string>>>
                     name,
                 std::any a, std::any b, std::any c, std::any d, std::any e);
};

#endif  // REXI_ARGPARSE_HPP_
