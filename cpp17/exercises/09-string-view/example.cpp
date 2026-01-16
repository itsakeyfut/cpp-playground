// std::string_viewのサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ============================================================================
// 1. 基本的なstd::string_viewの使い方
// ============================================================================

void basic_examples() {
  std::cout << "=== 基本的なstd::string_view ===" << std::endl;

  // 文字列リテラルから
  std::string_view sv1 = "Hello, World!";
  std::cout << "sv1: " << sv1 << std::endl;

  // std::stringから
  std::string str = "C++ string";
  std::string_view sv2 = str;
  std::cout << "sv2: " << sv2 << std::endl;

  // char*から
  const char* cstr = "C string";
  std::string_view sv3 = cstr;
  std::cout << "sv3: " << sv3 << std::endl;

  // 長さとデータアクセス
  std::cout << "sv1 length: " << sv1.length() << std::endl;
  std::cout << "sv1 size: " << sv1.size() << std::endl;
  std::cout << "sv1 first char: " << sv1[0] << std::endl;
  std::cout << "sv1 front: " << sv1.front() << std::endl;
  std::cout << "sv1 back: " << sv1.back() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. パフォーマンス: コピーなしの文字列処理
// ============================================================================

// 従来の方法: std::stringでコピーが発生
void print_traditional(const std::string& str) {
  std::cout << str << std::endl;
}

// C++17の方法: コピーなし
void print_view(std::string_view sv) {
  std::cout << sv << std::endl;
}

void performance_example() {
  std::cout << "=== パフォーマンスの例 ===" << std::endl;

  std::string long_string = "This is a very long string...";

  // string_viewはコピーを作らない
  print_view(long_string);          // OK: stringから
  print_view("literal");            // OK: リテラルから
  print_view(long_string.c_str());  // OK: char*から

  std::cout << "string_viewは全てのケースでコピーなし！" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. 部分文字列の取得（コピーなし）
// ============================================================================

void substring_example() {
  std::cout << "=== 部分文字列の取得 ===" << std::endl;

  std::string_view sv = "Hello, World!";

  // substr: 部分文字列のビューを取得（コピーなし）
  auto part1 = sv.substr(0, 5);  // "Hello"
  auto part2 = sv.substr(7, 5);  // "World"

  std::cout << "part1: " << part1 << std::endl;
  std::cout << "part2: " << part2 << std::endl;

  // remove_prefix / remove_suffix: 先頭・末尾を削除
  std::string_view sv2 = "  trimmed  ";
  sv2.remove_prefix(2);  // 先頭2文字を削除
  sv2.remove_suffix(2);  // 末尾2文字を削除
  std::cout << "trimmed: '" << sv2 << "'" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. 文字列の検索と比較
// ============================================================================

void search_example() {
  std::cout << "=== 文字列の検索と比較 ===" << std::endl;

  std::string_view sv = "Hello, World!";

  // find: 文字列を検索
  auto pos = sv.find("World");
  if (pos != std::string_view::npos) {
    std::cout << "Found 'World' at position " << pos << std::endl;
  }

  // starts_with / ends_with (C++20だが、手動でも実装可能)
  if (sv.substr(0, 5) == "Hello") {
    std::cout << "Starts with 'Hello'" << std::endl;
  }

  // 比較
  std::string_view sv1 = "apple";
  std::string_view sv2 = "banana";
  std::cout << "sv1 < sv2: " << (sv1 < sv2) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 注意: ダングリング参照の危険性
// ============================================================================

// 危険な例（コンパイルはできるが実行時に問題）
std::string_view dangerous_function() {
  std::string local = "temporary";
  return local;  // ダングリング参照！localはここで破棄される
}

// 安全な例
std::string_view safe_function() {
  // 文字列リテラルはプログラムの終了まで存在する
  return "literal string";  // OK
}

void dangling_reference_warning() {
  std::cout << "=== ダングリング参照の注意 ===" << std::endl;

  // 安全な使い方
  auto sv1 = safe_function();
  std::cout << "Safe: " << sv1 << std::endl;

  // 危険な使い方（実行しない）
  // auto sv2 = dangerous_function();  // 未定義動作！
  // std::cout << sv2 << std::endl;

  std::cout << "string_viewは元のデータを所有しないため、"
            << "元のデータが破棄されると無効になります" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 実用例: トークン分割
// ============================================================================

std::vector<std::string_view> split(std::string_view str, char delimiter) {
  std::vector<std::string_view> tokens;

  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string_view::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }

  // 最後のトークン
  tokens.push_back(str.substr(start));

  return tokens;
}

void tokenize_example() {
  std::cout << "=== トークン分割の例 ===" << std::endl;

  std::string data = "apple,banana,cherry,date";
  auto tokens = split(data, ',');

  std::cout << "Tokens:" << std::endl;
  for (const auto& token : tokens) {
    std::cout << "  - " << token << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. string_viewとstringの変換
// ============================================================================

void conversion_example() {
  std::cout << "=== string_viewとstringの変換 ===" << std::endl;

  // string_view -> string
  std::string_view sv = "view";
  std::string str(sv);  // コピーが発生
  std::cout << "string: " << str << std::endl;

  // string -> string_view
  std::string str2 = "original";
  std::string_view sv2 = str2;  // コピーなし
  std::cout << "string_view: " << sv2 << std::endl;

  // string_viewを使う関数にstringを渡す
  auto print = [](std::string_view s) { std::cout << "Print: " << s << "\n"; };
  print(str2);       // 暗黙的に変換される
  print("literal");  // リテラルも使える

  std::cout << std::endl;
}

// ============================================================================
// 8. 実用例: パスの拡張子取得
// ============================================================================

std::string_view get_extension(std::string_view path) {
  auto pos = path.rfind('.');
  if (pos != std::string_view::npos) {
    return path.substr(pos);
  }
  return "";
}

void extension_example() {
  std::cout << "=== 拡張子の取得 ===" << std::endl;

  std::vector<std::string_view> paths = {
      "image.png", "document.pdf", "archive.tar.gz", "noextension"};

  for (const auto& path : paths) {
    auto ext = get_extension(path);
    std::cout << path << " -> extension: '"
              << (ext.empty() ? "(none)" : std::string(ext)) << "'"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 std::string_viewのサンプル\n" << std::endl;

  basic_examples();
  performance_example();
  substring_example();
  search_example();
  dangling_reference_warning();
  tokenize_example();
  conversion_example();
  extension_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
