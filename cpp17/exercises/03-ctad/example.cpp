// クラステンプレート引数推論（CTAD）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// ============================================================================
// 1. 標準ライブラリでのCTAD
// ============================================================================

void standard_library_ctad() {
  std::cout << "=== 標準ライブラリでのCTAD ===" << std::endl;

  // C++14以前: 型を明示的に指定
  std::pair<int, double> p1(1, 3.14);
  std::vector<int> v1{1, 2, 3};

  // C++17: 型推論
  std::pair p2(1, 3.14);        // std::pair<int, double>
  std::vector v2{1, 2, 3};      // std::vector<int>
  std::tuple t(1, 2.0, "hi");   // std::tuple<int, double, const char*>

  std::cout << "p2: (" << p2.first << ", " << p2.second << ")" << std::endl;
  std::cout << "v2 size: " << v2.size() << std::endl;
  std::cout << "tuple size: " << std::tuple_size_v<decltype(t)> << std::endl;

  // 文字列とstd::string
  std::pair p3("hello", std::string("world"));  // pair<const char*, std::string>
  std::cout << "p3: (" << p3.first << ", " << p3.second << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. カスタムクラスでのCTAD（明示的な推論ガイド不要）
// ============================================================================

template <typename T>
class SimpleContainer {
 public:
  T value;

  // コンストラクタから型が推論される
  explicit SimpleContainer(T val) : value(val) {}

  void print() const {
    std::cout << "Value: " << value << std::endl;
  }
};

void simple_custom_class() {
  std::cout << "=== シンプルなカスタムクラス ===" << std::endl;

  // C++17: 型推論
  SimpleContainer c1(42);          // SimpleContainer<int>
  SimpleContainer c2(3.14);        // SimpleContainer<double>
  SimpleContainer c3(std::string("hello"));  // SimpleContainer<std::string>

  c1.print();
  c2.print();
  c3.print();

  std::cout << std::endl;
}

// ============================================================================
// 3. 推論ガイドを使ったカスタムクラス
// ============================================================================

template <typename T>
class Wrapper {
 public:
  T data;

  explicit Wrapper(T d) : data(d) {}

  void print() const {
    std::cout << "Wrapped data: " << data << std::endl;
  }
};

// 推論ガイド: C文字列をstd::stringとして推論
Wrapper(const char*) -> Wrapper<std::string>;

void deduction_guide_example() {
  std::cout << "=== 推論ガイドの例 ===" << std::endl;

  Wrapper w1(42);           // Wrapper<int>
  Wrapper w2("hello");      // Wrapper<std::string>（推論ガイドによる）

  w1.print();
  w2.print();

  std::cout << std::endl;
}

// ============================================================================
// 4. より複雑な推論ガイド：イテレータから要素型を推論
// ============================================================================

template <typename T>
class Container {
 private:
  std::vector<T> elements;

 public:
  Container() = default;

  explicit Container(std::vector<T> elems) : elements(std::move(elems)) {}

  // イテレータのペアから構築
  template <typename Iterator>
  Container(Iterator begin, Iterator end) : elements(begin, end) {}

  void print() const {
    std::cout << "Container elements: ";
    for (const auto& elem : elements) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }

  size_t size() const { return elements.size(); }
};

// 推論ガイド: イテレータのペアから要素型を推論
template <typename Iterator>
Container(Iterator, Iterator) -> Container<typename std::iterator_traits<Iterator>::value_type>;

void iterator_deduction_guide() {
  std::cout << "=== イテレータからの推論 ===" << std::endl;

  std::vector<int> v{1, 2, 3, 4, 5};

  // イテレータから型を推論
  Container c1(v.begin(), v.end());  // Container<int>
  c1.print();

  // 初期化リストから直接
  Container c2(std::vector{10, 20, 30});
  c2.print();

  std::cout << std::endl;
}

// ============================================================================
// 5. 集約型とCTAD（C++20でさらに強化）
// ============================================================================

template <typename T>
struct Point {
  T x;
  T y;
};

// C++17では集約型の推論ガイドが必要
template <typename T>
Point(T, T) -> Point<T>;

void aggregate_type_example() {
  std::cout << "=== 集約型とCTAD ===" << std::endl;

  // 型推論
  Point p1{1, 2};         // Point<int>
  Point p2{1.5, 2.5};     // Point<double>

  std::cout << "p1: (" << p1.x << ", " << p1.y << ")" << std::endl;
  std::cout << "p2: (" << p2.x << ", " << p2.y << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 実用例：ペアとタプルの生成
// ============================================================================

void practical_example() {
  std::cout << "=== 実用例 ===" << std::endl;

  // make_pairやmake_tupleの代わりに直接構築
  // C++14以前
  auto old_pair = std::make_pair(1, "hello");
  auto old_tuple = std::make_tuple(1, 2.0, "world");

  // C++17（より簡潔）
  std::pair new_pair(1, "hello");
  std::tuple new_tuple(1, 2.0, "world");

  std::cout << "新しいpair: (" << new_pair.first << ", " << new_pair.second << ")" << std::endl;
  std::cout << "新しいtupleの要素数: " << std::tuple_size_v<decltype(new_tuple)> << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 クラステンプレート引数推論（CTAD）のサンプル\n" << std::endl;

  standard_library_ctad();
  simple_custom_class();
  deduction_guide_example();
  iterator_deduction_guide();
  aggregate_type_example();
  practical_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
