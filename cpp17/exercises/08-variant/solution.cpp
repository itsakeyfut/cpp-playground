// std::variantの演習 - 解答例

#include <iostream>
#include <string>
#include <variant>
#include <vector>

// ============================================================================
// overloadedヘルパー
// ============================================================================

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// ============================================================================
// 演習 1.8.1: ゲームイベントシステム
// ============================================================================

struct PlayerMoved {
  float x;
  float y;
};

struct ItemPickedUp {
  int item_id;
  std::string item_name;
};

struct DamageTaken {
  int amount;
  std::string source;
};

using GameEvent = std::variant<PlayerMoved, ItemPickedUp, DamageTaken>;

void exercise_1_8_1() {
  std::cout << "=== 演習 1.8.1: ゲームイベントシステム ===" << std::endl;

  std::vector<GameEvent> events = {
      PlayerMoved{10.5f, 20.3f},
      ItemPickedUp{1, "Health Potion"},
      DamageTaken{15, "Goblin"},
      PlayerMoved{15.0f, 25.0f},
      ItemPickedUp{2, "Sword"}};

  // イベントを処理
  for (const auto& event : events) {
    std::visit(
        overloaded{
            [](const PlayerMoved& e) {
              std::cout << "Player moved to (" << e.x << ", " << e.y << ")"
                        << std::endl;
            },
            [](const ItemPickedUp& e) {
              std::cout << "Picked up " << e.item_name << " (ID: " << e.item_id
                        << ")" << std::endl;
            },
            [](const DamageTaken& e) {
              std::cout << "Took " << e.amount << " damage from " << e.source
                        << std::endl;
            }},
        event);
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: パーサーの結果
// ============================================================================

struct IntValue {
  int value;
};

struct FloatValue {
  double value;
};

struct StringValue {
  std::string value;
};

struct ParseError {
  std::string error_message;
};

using ParseResult = std::variant<IntValue, FloatValue, StringValue, ParseError>;

ParseResult parse_value(const std::string& str) {
  if (str.empty()) {
    return ParseError{"Empty string"};
  }

  // 整数として試みる
  try {
    size_t pos;
    int i = std::stoi(str, &pos);
    // 文字列全体が整数として解釈できた場合
    if (pos == str.length()) {
      return IntValue{i};
    }
  } catch (...) {
  }

  // 浮動小数点として試みる
  try {
    size_t pos;
    double d = std::stod(str, &pos);
    // 文字列全体が数値として解釈できた場合
    if (pos == str.length()) {
      return FloatValue{d};
    }
  } catch (...) {
  }

  // 数値でない場合は文字列として返す
  return StringValue{str};
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: パーサー ===" << std::endl;

  std::vector<std::string> inputs = {"42", "3.14", "hello", "", "123"};

  for (const auto& input : inputs) {
    auto result = parse_value(input);

    std::cout << "\"" << input << "\" -> ";
    std::visit(
        overloaded{
            [](const IntValue& v) {
              std::cout << "Integer: " << v.value << std::endl;
            },
            [](const FloatValue& v) {
              std::cout << "Float: " << v.value << std::endl;
            },
            [](const StringValue& v) {
              std::cout << "String: " << v.value << std::endl;
            },
            [](const ParseError& e) {
              std::cout << "Error: " << e.error_message << std::endl;
            }},
        result);
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::variantの演習 - 解答例\n" << std::endl;

  exercise_1_8_1();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
