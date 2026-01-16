// constexpr if のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// ============================================================================
// 1. 基本的なconstexpr if
// ============================================================================

template <typename T>
void basic_process(T value) {
  std::cout << "=== basic_process ===" << std::endl;

  if constexpr (std::is_integral_v<T>) {
    std::cout << "整数型: " << value << " を2倍にします" << std::endl;
    std::cout << "結果: " << value * 2 << std::endl;
  } else if constexpr (std::is_floating_point_v<T>) {
    std::cout << "浮動小数点型: " << value << " を2.5倍にします" << std::endl;
    std::cout << "結果: " << value * 2.5 << std::endl;
  } else {
    std::cout << "その他の型: そのまま出力します" << std::endl;
    std::cout << "値: " << value << std::endl;
  }

  std::cout << std::endl;
}

void basic_examples() {
  std::cout << "=== 基本的なconstexpr if ===" << std::endl;

  basic_process(10);           // 整数型
  basic_process(3.14);         // 浮動小数点型
  basic_process(std::string("hello"));  // その他の型

  std::cout << std::endl;
}

// ============================================================================
// 2. 型特性との組み合わせ
// ============================================================================

template <typename T>
std::string get_type_name() {
  if constexpr (std::is_integral_v<T>) {
    if constexpr (std::is_signed_v<T>) {
      return "符号付き整数型";
    } else {
      return "符号なし整数型";
    }
  } else if constexpr (std::is_floating_point_v<T>) {
    return "浮動小数点型";
  } else if constexpr (std::is_pointer_v<T>) {
    return "ポインタ型";
  } else if constexpr (std::is_same_v<T, std::string>) {
    return "std::string型";
  } else {
    return "その他の型";
  }
}

void type_traits_examples() {
  std::cout << "=== 型特性との組み合わせ ===" << std::endl;

  std::cout << "int: " << get_type_name<int>() << std::endl;
  std::cout << "unsigned int: " << get_type_name<unsigned int>() << std::endl;
  std::cout << "double: " << get_type_name<double>() << std::endl;
  std::cout << "int*: " << get_type_name<int*>() << std::endl;
  std::cout << "std::string: " << get_type_name<std::string>() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. コンテナの処理
// ============================================================================

template <typename T>
void print_container(const T& container) {
  std::cout << "コンテナの要素: ";

  // コンテナかどうかを判定
  if constexpr (requires { container.begin(); container.end(); }) {
    // コンテナの場合
    for (const auto& elem : container) {
      std::cout << elem << " ";
    }
  } else {
    // コンテナでない場合
    std::cout << container;
  }

  std::cout << std::endl;
}

void container_examples() {
  std::cout << "=== コンテナの処理 ===" << std::endl;

  std::vector<int> vec{1, 2, 3, 4, 5};
  print_container(vec);

  int single_value = 42;
  print_container(single_value);

  std::cout << std::endl;
}

// ============================================================================
// 4. 最適化の例：サイズに応じた処理の切り替え
// ============================================================================

template <typename T>
void process_by_size(T value) {
  std::cout << "型のサイズ: " << sizeof(T) << " バイト - ";

  if constexpr (sizeof(T) == 1) {
    std::cout << "1バイト型: 高速処理" << std::endl;
  } else if constexpr (sizeof(T) <= 4) {
    std::cout << "小型（4バイト以下）: 通常処理" << std::endl;
  } else {
    std::cout << "大型（5バイト以上）: 参照で処理を推奨" << std::endl;
  }
}

void size_based_examples() {
  std::cout << "=== サイズに応じた処理 ===" << std::endl;

  process_by_size<char>('A');
  process_by_size<int>(42);
  process_by_size<double>(3.14);
  process_by_size<std::string>(std::string("hello"));

  std::cout << std::endl;
}

// ============================================================================
// 5. 実用例：簡易シリアライゼーション
// ============================================================================

template <typename T>
std::vector<uint8_t> serialize(const T& value) {
  std::vector<uint8_t> result;

  if constexpr (std::is_integral_v<T>) {
    // 整数型: バイト列として保存
    for (size_t i = 0; i < sizeof(T); ++i) {
      result.push_back(static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
    }
  } else if constexpr (std::is_same_v<T, std::string>) {
    // 文字列型: 長さ + データ
    size_t len = value.size();
    // 長さを4バイトで保存
    for (size_t i = 0; i < 4; ++i) {
      result.push_back(static_cast<uint8_t>((len >> (i * 8)) & 0xFF));
    }
    // データを保存
    for (char c : value) {
      result.push_back(static_cast<uint8_t>(c));
    }
  } else if constexpr (std::is_floating_point_v<T>) {
    // 浮動小数点型: バイト列として保存
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
    for (size_t i = 0; i < sizeof(T); ++i) {
      result.push_back(bytes[i]);
    }
  } else {
    // その他の型はサポートしない
    static_assert(!std::is_same_v<T, T>, "この型はシリアライズできません");
  }

  return result;
}

void serialization_example() {
  std::cout << "=== シリアライゼーション ===" << std::endl;

  // 整数のシリアライゼーション
  auto int_bytes = serialize(42);
  std::cout << "整数42をシリアライズ: ";
  for (auto byte : int_bytes) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  // 文字列のシリアライゼーション
  auto str_bytes = serialize(std::string("Hi"));
  std::cout << "文字列\"Hi\"をシリアライズ: ";
  for (auto byte : str_bytes) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  // 浮動小数点のシリアライゼーション
  auto float_bytes = serialize(3.14f);
  std::cout << "浮動小数点3.14fをシリアライズ: ";
  for (auto byte : float_bytes) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 通常のifとの比較
// ============================================================================

void comparison_with_normal_if() {
  std::cout << "=== 通常のifとの比較 ===" << std::endl;

  // 通常のif: 実行時評価
  int x = 10;
  if (x > 5) {
    std::cout << "通常のif: 実行時に評価される" << std::endl;
  }

  // constexpr if: コンパイル時評価
  // 条件が偽の分岐はコンパイルされない
  if constexpr (sizeof(int) == 4) {
    std::cout << "constexpr if: コンパイル時に評価される" << std::endl;
    std::cout << "この環境ではintは4バイトです" << std::endl;
  } else {
    // この分岐はコンパイルされない（sizeof(int) == 4なので）
    std::cout << "この行は実行されません" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 constexpr if のサンプル\n" << std::endl;

  basic_examples();
  type_traits_examples();
  container_examples();
  size_based_examples();
  serialization_example();
  comparison_with_normal_if();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
