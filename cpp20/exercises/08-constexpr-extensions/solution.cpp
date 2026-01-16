// constexpr拡張とconstevalの演習 - 解答例

#include <array>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.4.1: constexpr仮想関数
// ============================================================================

struct Shape {
  constexpr virtual ~Shape() = default;
  constexpr virtual double area() const = 0;
};

struct Circle : Shape {
  double radius;

  constexpr explicit Circle(double r) : radius(r) {}

  constexpr double area() const override { return 3.14159 * radius * radius; }
};

struct Square : Shape {
  double side;

  constexpr explicit Square(double s) : side(s) {}

  constexpr double area() const override { return side * side; }
};

constexpr double calculate_total_area() {
  Circle c(5.0);    // 円の面積: π * 5^2 ≈ 78.54
  Square s(10.0);   // 正方形の面積: 10^2 = 100
  return c.area() + s.area();
}

void exercise_2_5_4_1() {
  std::cout << "=== 演習 2.5.4.1: constexpr仮想関数 ===" << std::endl;

  constexpr double total = calculate_total_area();
  std::cout << "Total area (compile-time): " << total << std::endl;

  // ランタイムでも使用可能
  Circle c(3.0);
  std::cout << "Circle(3.0) area: " << c.area() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.4.2: constevalでフィボナッチ数
// ============================================================================

consteval int fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void exercise_2_5_4_2() {
  std::cout << "=== 演習 2.5.4.2: constevalでフィボナッチ数 ===" << std::endl;

  constexpr int fib5 = fibonacci(5);    // 5
  constexpr int fib10 = fibonacci(10);  // 55
  constexpr int fib15 = fibonacci(15);  // 610

  std::cout << "fibonacci(5): " << fib5 << std::endl;
  std::cout << "fibonacci(10): " << fib10 << std::endl;
  std::cout << "fibonacci(15): " << fib15 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.4.3: ゲーム用ダメージ計算テーブル
// ============================================================================

constexpr auto generate_damage_table() {
  std::array<int, 100> table{};
  for (int level = 0; level < 100; ++level) {
    // ダメージ = 基礎値(20) + レベル * 成長率(3) + レベル^2 / 10
    table[level] = 20 + level * 3 + (level * level) / 10;
  }
  return table;
}

constexpr auto damage_table = generate_damage_table();

int get_damage(int level) {
  if (level < 0 || level >= 100) return 0;
  return damage_table[level];
}

void exercise_2_5_4_3() {
  std::cout << "=== 演習 2.5.4.3: ゲーム用ダメージテーブル ===" << std::endl;

  std::cout << "レベル別ダメージ:" << std::endl;
  for (int level : {1, 10, 25, 50, 99}) {
    std::cout << "Level " << level << ": " << get_damage(level) << " damage"
              << std::endl;
  }

  std::cout << "\n計算式: damage = 20 + level * 3 + level^2 / 10"
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: コンパイル時のハッシュ計算
// ============================================================================

consteval unsigned int hash_string(const char* str) {
  unsigned int hash = 2166136261u;  // FNV offset basis
  while (*str) {
    hash ^= static_cast<unsigned int>(*str++);
    hash *= 16777619u;  // FNV prime
  }
  return hash;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: コンパイル時ハッシュ ===" << std::endl;

  // コンパイル時にハッシュ値を計算
  constexpr unsigned int hash_player = hash_string("Player");
  constexpr unsigned int hash_enemy = hash_string("Enemy");
  constexpr unsigned int hash_item = hash_string("Item");

  std::cout << "Hash(\"Player\"): 0x" << std::hex << hash_player << std::endl;
  std::cout << "Hash(\"Enemy\"): 0x" << std::hex << hash_enemy << std::endl;
  std::cout << "Hash(\"Item\"): 0x" << std::hex << hash_item << std::endl;
  std::cout << std::dec;

  std::cout << "\n実用例: ゲームエンジンでの高速文字列比較" << std::endl;
  std::cout << "- コンパイル時に文字列をハッシュ値に変換" << std::endl;
  std::cout << "- ランタイムでは整数比較のみ（高速）" << std::endl;
  std::cout << "- switch文でも使用可能" << std::endl;

  // 使用例
  constexpr unsigned int entity_type_hash = hash_string("Player");

  // ランタイムでswitch文で使用可能
  switch (entity_type_hash) {
    case hash_string("Player"):
      std::cout << "\nEntity type: Player detected!" << std::endl;
      break;
    case hash_string("Enemy"):
      std::cout << "\nEntity type: Enemy detected!" << std::endl;
      break;
    default:
      break;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "constexpr拡張とconstevalの演習 - 解答例\n" << std::endl;

  exercise_2_5_4_1();
  exercise_2_5_4_2();
  exercise_2_5_4_3();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
