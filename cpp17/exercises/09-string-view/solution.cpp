// std::string_viewの演習 - 解答例

#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ============================================================================
// 演習 1.9.1: CSVパーサー
// ============================================================================

std::vector<std::string_view> parse_csv_line(std::string_view line) {
  std::vector<std::string_view> fields;

  size_t start = 0;
  size_t end = line.find(',');

  while (end != std::string_view::npos) {
    fields.push_back(line.substr(start, end - start));
    start = end + 1;
    end = line.find(',', start);
  }

  // 最後のフィールド
  fields.push_back(line.substr(start));

  return fields;
}

void exercise_1_9_1() {
  std::cout << "=== 演習 1.9.1: CSVパーサー ===" << std::endl;

  std::vector<std::string> csv_lines = {
      "Alice,100,Tokyo",
      "Bob,85,New York",
      "Carol,92,London",
      "David,78,Paris"};

  for (const auto& line : csv_lines) {
    auto fields = parse_csv_line(line);

    bool first = true;
    for (const auto& field : fields) {
      if (!first) std::cout << " | ";
      std::cout << field;
      first = false;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習1: 空白文字のトリミング
// ============================================================================

std::string_view trim(std::string_view sv) {
  // 前方の空白を削除
  while (!sv.empty() && std::isspace(sv.front())) {
    sv.remove_prefix(1);
  }

  // 後方の空白を削除
  while (!sv.empty() && std::isspace(sv.back())) {
    sv.remove_suffix(1);
  }

  return sv;
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習1: トリミング ===" << std::endl;

  std::vector<std::string> strings = {
      "  hello  ", "\tworld\n", "  C++  ", "  no trim needed"};

  for (const auto& str : strings) {
    auto trimmed = trim(str);
    std::cout << "'" << str << "' -> '" << trimmed << "'" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習2: ファイルパスの解析
// ============================================================================

struct PathInfo {
  std::string_view directory;
  std::string_view filename;
  std::string_view stem;
  std::string_view extension;
};

PathInfo parse_path(std::string_view path) {
  PathInfo info;

  // 最後のスラッシュを探す
  auto last_slash = path.rfind('/');
  if (last_slash == std::string_view::npos) {
    last_slash = path.rfind('\\');
  }

  if (last_slash != std::string_view::npos) {
    info.directory = path.substr(0, last_slash + 1);
    info.filename = path.substr(last_slash + 1);
  } else {
    info.directory = "";
    info.filename = path;
  }

  // 拡張子を探す
  auto last_dot = info.filename.rfind('.');
  if (last_dot != std::string_view::npos && last_dot > 0) {
    info.stem = info.filename.substr(0, last_dot);
    info.extension = info.filename.substr(last_dot);
  } else {
    info.stem = info.filename;
    info.extension = "";
  }

  return info;
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習2: パス解析 ===" << std::endl;

  std::vector<std::string_view> paths = {
      "/home/user/document.txt",
      "C:\\Windows\\System32\\kernel32.dll",
      "image.png",
      "archive.tar.gz"};

  for (const auto& path : paths) {
    auto info = parse_path(path);
    std::cout << "Path: " << path << std::endl;
    std::cout << "  - Directory: "
              << (info.directory.empty() ? "(none)" : std::string(info.directory))
              << std::endl;
    std::cout << "  - Filename: " << info.filename << std::endl;
    std::cout << "  - Stem: " << info.stem << std::endl;
    std::cout << "  - Extension: "
              << (info.extension.empty() ? "(none)" : std::string(info.extension))
              << std::endl;
    std::cout << std::endl;
  }
}

// ============================================================================
// ボーナス演習3: 大文字小文字を無視した比較
// ============================================================================

bool equal_ignore_case(std::string_view sv1, std::string_view sv2) {
  if (sv1.size() != sv2.size()) {
    return false;
  }

  for (size_t i = 0; i < sv1.size(); ++i) {
    if (std::tolower(sv1[i]) != std::tolower(sv2[i])) {
      return false;
    }
  }

  return true;
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習3: 大文字小文字を無視した比較 ===" << std::endl;

  std::vector<std::pair<std::string_view, std::string_view>> pairs = {
      {"Hello", "hello"},
      {"World", "WORLD"},
      {"C++", "c++"},
      {"Test", "TEST"}};

  for (const auto& [str1, str2] : pairs) {
    bool equal = equal_ignore_case(str1, str2);
    std::cout << "\"" << str1 << "\" == \"" << str2 << "\" (ignore case): "
              << (equal ? "true" : "false") << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::string_viewの演習 - 解答例\n" << std::endl;

  exercise_1_9_1();
  bonus_exercise_1();
  bonus_exercise_2();
  bonus_exercise_3();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
