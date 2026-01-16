// クラステンプレート引数推論（CTAD）の演習 - 解答例

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// ============================================================================
// 演習 1.3.1: 推論ガイドを持つカスタムクラス
// ============================================================================

template <typename T>
class Container {
 private:
  std::vector<T> elements;

 public:
  // デフォルトコンストラクタ
  Container() = default;

  // std::vectorを受け取るコンストラクタ
  explicit Container(std::vector<T> elems) : elements(std::move(elems)) {}

  // イテレータのペアを受け取るコンストラクタ
  template <typename Iterator>
  Container(Iterator begin, Iterator end) : elements(begin, end) {}

  // print()メソッド
  void print() const {
    std::cout << "Container [";
    for (size_t i = 0; i < elements.size(); ++i) {
      if (i > 0) std::cout << ", ";
      std::cout << elements[i];
    }
    std::cout << "]" << std::endl;
  }

  // size()メソッド
  size_t size() const { return elements.size(); }
};

// イテレータのペアから要素型を推論する推論ガイド
template <typename Iterator>
Container(Iterator, Iterator) -> Container<typename std::iterator_traits<Iterator>::value_type>;

void exercise_1_3_1() {
  std::cout << "=== 演習 1.3.1: カスタムコンテナ ===" << std::endl;

  // std::vectorから型を推論してContainerを作成
  std::vector<int> vec{1, 2, 3, 4, 5};
  Container c1(vec.begin(), vec.end());  // Container<int>と推論される

  std::cout << "整数のContainer (size: " << c1.size() << "): ";
  c1.print();

  // 文字列のContainerを作成
  std::vector<std::string> words{"hello", "world", "CTAD"};
  Container c2(words.begin(), words.end());  // Container<std::string>と推論される

  std::cout << "文字列のContainer (size: " << c2.size() << "): ";
  c2.print();

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.3.2: ペアとタプルの推論
// ============================================================================

void exercise_1_3_2() {
  std::cout << "=== 演習 1.3.2: ペアとタプルの推論 ===" << std::endl;

  // 型推論を使ってpairを作成
  std::pair p(42, std::string("answer"));  // std::pair<int, std::string>

  std::cout << "Pair: (" << p.first << ", " << p.second << ")" << std::endl;

  // 型推論を使ってtupleを作成
  std::tuple t(10, 3.14, std::string("tuple"));  // std::tuple<int, double, std::string>

  std::cout << "Tuple: ("
            << std::get<0>(t) << ", "
            << std::get<1>(t) << ", "
            << std::get<2>(t) << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: カスタム推論ガイド
// ============================================================================

template <typename T>
struct Point2D {
  T x;
  T y;

  void print() const {
    std::cout << "Point2D: (" << x << ", " << y << ")" << std::endl;
  }
};

// Point2Dの推論ガイド
template <typename T>
Point2D(T, T) -> Point2D<T>;

void bonus_exercise() {
  std::cout << "=== ボーナス演習: Point2Dの推論 ===" << std::endl;

  // 型推論を使ってPoint2Dを作成（int型）
  Point2D p1{10, 20};  // Point2D<int>

  std::cout << "整数の";
  p1.print();

  // 型推論を使ってPoint2Dを作成（double型）
  Point2D p2{1.5, 2.5};  // Point2D<double>

  std::cout << "実数の";
  p2.print();

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "クラステンプレート引数推論（CTAD）の演習 - 解答例\n" << std::endl;

  exercise_1_3_1();
  exercise_1_3_2();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
