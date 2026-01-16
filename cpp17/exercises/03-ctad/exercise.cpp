// クラステンプレート引数推論（CTAD）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 1.3.1: 推論ガイドを持つカスタムクラス
// ============================================================================

// TODO: Container<T>クラステンプレートを定義してください
// 要件:
// - std::vector<T>型のメンバ変数 elements を持つ
// - デフォルトコンストラクタ
// - std::vector<T>を受け取るコンストラクタ
// - イテレータのペア(begin, end)を受け取るコンストラクタ
// - print()メソッド（要素を出力）
// - size()メソッド（要素数を返す）

template <typename T>
class Container {
  // TODO: メンバ変数を定義

 public:
  // TODO: デフォルトコンストラクタを定義

  // TODO: std::vectorを受け取るコンストラクタを定義

  // TODO: イテレータのペアを受け取るコンストラクタを定義（テンプレート）

  // TODO: print()メソッドを定義

  // TODO: size()メソッドを定義
};

// TODO: イテレータのペアから要素型を推論する推論ガイドを定義
// ヒント: template <typename Iterator>
//        Container(Iterator, Iterator) -> Container<typename std::iterator_traits<Iterator>::value_type>;

void exercise_1_3_1() {
  std::cout << "=== 演習 1.3.1: カスタムコンテナ ===" << std::endl;

  // TODO: std::vectorから型を推論してContainerを作成
  std::vector<int> vec{1, 2, 3, 4, 5};
  // ヒント: Container c1(vec.begin(), vec.end());

  // TODO: 作成したContainerのprint()とsize()を呼び出し

  // TODO: 文字列のContainerを作成して同様に操作
  std::vector<std::string> words{"hello", "world", "CTAD"};
  // ヒント: Container c2(words.begin(), words.end());

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.3.2: ペアとタプルの推論
// ============================================================================

void exercise_1_3_2() {
  std::cout << "=== 演習 1.3.2: ペアとタプルの推論 ===" << std::endl;

  // TODO: 型推論を使ってpairを作成（int, std::string）
  // ヒント: std::pair p(...);

  // TODO: 型推論を使ってtupleを作成（int, double, std::string）
  // ヒント: std::tuple t(...);

  // TODO: 作成したpairとtupleの内容を出力

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: カスタム推論ガイド
// ============================================================================

// Point2Dクラス（完成済み）
template <typename T>
struct Point2D {
  T x;
  T y;

  void print() const {
    std::cout << "Point2D: (" << x << ", " << y << ")" << std::endl;
  }
};

// TODO: Point2Dの推論ガイドを定義
// ヒント: template <typename T>
//        Point2D(T, T) -> Point2D<T>;

void bonus_exercise() {
  std::cout << "=== ボーナス演習: Point2Dの推論 ===" << std::endl;

  // TODO: 型推論を使ってPoint2Dを作成（int型）
  // ヒント: Point2D p1{10, 20};

  // TODO: 型推論を使ってPoint2Dを作成（double型）
  // ヒント: Point2D p2{1.5, 2.5};

  // TODO: 作成したPointのprint()を呼び出し

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "クラステンプレート引数推論（CTAD）の演習\n" << std::endl;

  exercise_1_3_1();
  exercise_1_3_2();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
