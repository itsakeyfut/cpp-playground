// std::optionalのサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <optional>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的なstd::optionalの使い方
// ============================================================================

void basic_examples() {
  std::cout << "=== 基本的なstd::optional ===" << std::endl;

  // 値を持つoptional
  std::optional<int> opt1 = 42;
  std::cout << "opt1 has value: " << opt1.has_value() << std::endl;
  std::cout << "opt1 value: " << *opt1 << std::endl;

  // 値を持たないoptional
  std::optional<int> opt2 = std::nullopt;
  std::cout << "opt2 has value: " << opt2.has_value() << std::endl;

  // if文で値の存在確認
  if (opt1) {
    std::cout << "opt1 contains: " << *opt1 << std::endl;
  }

  if (!opt2) {
    std::cout << "opt2 is empty" << std::endl;
  }

  // value_or: 値がない場合のデフォルト値
  std::cout << "opt2 with default: " << opt2.value_or(-1) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 検索関数の戻り値としてのoptional (Rustの Option<T> と同じ用途)
// ============================================================================

std::optional<int> find_value(const std::vector<int>& v, int target) {
  for (int x : v) {
    if (x == target) {
      return x;  // 値を返す
    }
  }
  return std::nullopt;  // 見つからなかった（Rustの None）
}

void search_example() {
  std::cout << "=== 検索関数の例 ===" << std::endl;

  std::vector<int> numbers = {1, 3, 5, 7, 9};

  // 存在する値を検索
  if (auto result = find_value(numbers, 5); result) {
    std::cout << "Found: " << *result << std::endl;
  }

  // 存在しない値を検索
  if (auto result = find_value(numbers, 4); !result) {
    std::cout << "4 not found" << std::endl;
  }

  // value_or を使った書き方
  int val = find_value(numbers, 10).value_or(-1);
  std::cout << "Result with default: " << val << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. 文字列の検索
// ============================================================================

std::optional<std::string> find_name(const std::vector<std::string>& names,
                                     char first_letter) {
  for (const auto& name : names) {
    if (!name.empty() && name[0] == first_letter) {
      return name;
    }
  }
  return std::nullopt;
}

void string_search_example() {
  std::cout << "=== 文字列検索の例 ===" << std::endl;

  std::vector<std::string> names = {"Alice", "Bob", "Carol", "David"};

  // 'C'で始まる名前を検索
  if (auto name = find_name(names, 'C'); name.has_value()) {
    std::cout << "Found name starting with C: " << name.value() << std::endl;
  }

  // 'Z'で始まる名前を検索（存在しない）
  auto result = find_name(names, 'Z');
  std::cout << "Name starting with Z: "
            << result.value_or("(not found)") << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. optionalの比較と演算
// ============================================================================

void optional_operations() {
  std::cout << "=== optionalの比較と演算 ===" << std::endl;

  std::optional<int> opt1 = 10;
  std::optional<int> opt2 = 20;
  std::optional<int> opt3 = std::nullopt;

  // 比較演算
  std::cout << "opt1 == opt2: " << (opt1 == opt2) << std::endl;
  std::cout << "opt1 < opt2: " << (opt1 < opt2) << std::endl;

  // nulloptとの比較
  std::cout << "opt3 == nullopt: " << (opt3 == std::nullopt) << std::endl;

  // 値の変更
  opt1 = 100;
  std::cout << "Updated opt1: " << *opt1 << std::endl;

  // optionalをリセット
  opt1.reset();
  std::cout << "After reset, opt1 has value: " << opt1.has_value()
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 実践例: 簡易的な設定値の取得
// ============================================================================

// 設定のキーと値のペア
struct Config {
  std::vector<std::pair<std::string, std::string>> settings;

  std::optional<std::string> get(const std::string& key) const {
    for (const auto& [k, v] : settings) {
      if (k == key) {
        return v;
      }
    }
    return std::nullopt;
  }
};

void config_example() {
  std::cout << "=== 設定値の取得例 ===" << std::endl;

  Config config;
  config.settings = {
      {"width", "1920"},
      {"height", "1080"},
      {"fullscreen", "true"}};

  // 存在するキーを取得
  if (auto width = config.get("width"); width) {
    std::cout << "Width: " << *width << std::endl;
  }

  // 存在しないキーを取得
  std::string title = config.get("title").value_or("Untitled Game");
  std::cout << "Title: " << title << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. optionalとif初期化式の組み合わせ (C++17の強力な組み合わせ)
// ============================================================================

std::optional<int> parse_int(const std::string& str) {
  try {
    return std::stoi(str);
  } catch (...) {
    return std::nullopt;
  }
}

void optional_with_if_init() {
  std::cout << "=== optionalとif初期化式 ===" << std::endl;

  std::vector<std::string> inputs = {"123", "abc", "456"};

  for (const auto& input : inputs) {
    // if初期化式とoptionalの組み合わせ
    if (auto value = parse_int(input); value) {
      std::cout << input << " is a valid number: " << *value << std::endl;
    } else {
      std::cout << input << " is not a valid number" << std::endl;
    }
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 std::optionalのサンプル\n" << std::endl;

  basic_examples();
  search_example();
  string_search_example();
  optional_operations();
  config_example();
  optional_with_if_init();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
