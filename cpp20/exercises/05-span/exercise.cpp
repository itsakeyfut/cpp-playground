// std::span の演習問題
// TODOを埋めて、プログラムを完成させてください。

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

// ============================================================================
// 演習 2.5.1: 配列処理関数
// ============================================================================
// std::span を使って、様々な種類の配列を処理できる汎用関数を作成せよ。
//
// 要件:
// - sum() : 要素の合計を計算
// - average() : 平均値を計算
// - std::vector, std::array, C配列のすべてに対応

// TODO: sum() 関数を実装してください
int sum(std::span<const int> data) {
  // ヒント: std::accumulate を使用
  return 0;  // この行を修正してください
}

// TODO: average() 関数を実装してください
double average(std::span<const int> data) {
  // ヒント: sum() を使って合計を計算し、サイズで割る
  // 空の場合は0.0を返す
  return 0.0;  // この行を修正してください
}

void test_array_processing() {
  std::cout << "=== 演習 2.5.1: 配列処理関数 ===" << std::endl;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::array<int, 5> arr = {6, 7, 8, 9, 10};
  int c_array[] = {11, 12, 13, 14, 15};

  // TODO: 以下のコメントを外して動作確認してください
  // std::cout << "vector: sum=" << sum(vec) << ", avg=" << average(vec)
  //           << std::endl;
  // std::cout << "array: sum=" << sum(arr) << ", avg=" << average(arr)
  //           << std::endl;
  // std::cout << "C array: sum=" << sum(c_array) << ", avg=" <<
  // average(c_array)
  //           << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.2: TArray風のコンテナとの統合
// ============================================================================
// UEのTArray風のコンテナとstd::spanを組み合わせた処理を実装せよ。

// TArray の代わりに std::vector を使用
template <typename T>
using TArray = std::vector<T>;

struct Actor {
  int id;
  float x, y, z;
};

// TODO: GetNearestActors() 関数を実装してください
// 指定された数の最も近いActorを返す（最初のN個を返すだけでOK）
std::vector<Actor> GetNearestActors(std::span<const Actor> all_actors,
                                    int max_count) {
  // ヒント:
  // 1. std::span の first() または subspan() を使う
  // 2. std::vector に変換して返す
  return {};  // この行を修正してください
}

// TODO: ProcessActorsBatch() 関数を実装してください
// Actor配列を指定サイズのバッチに分けて処理する
void ProcessActorsBatch(std::span<const Actor> actors, int batch_size) {
  // ヒント:
  // 1. ループでactorsを batch_size ずつ処理
  // 2. subspan() を使って部分範囲を取得
  // 3. 各バッチのサイズとIDを出力

  // TODO: 実装してください
  std::cout << "  バッチ処理未実装" << std::endl;
}

void test_tarray_integration() {
  std::cout << "=== 演習 2.5.2: TArray風のコンテナとの統合 ===" << std::endl;

  TArray<Actor> actors = {{1, 10.0f, 0.0f, 0.0f}, {2, 20.0f, 0.0f, 0.0f},
                          {3, 30.0f, 0.0f, 0.0f}, {4, 40.0f, 0.0f, 0.0f},
                          {5, 50.0f, 0.0f, 0.0f}, {6, 60.0f, 0.0f, 0.0f}};

  // TODO: 以下のコメントを外して動作確認してください
  // std::cout << "最も近い3つのActor:" << std::endl;
  // auto nearest = GetNearestActors(actors, 3);
  // for (const auto& actor : nearest) {
  //     std::cout << "  Actor ID: " << actor.id << std::endl;
  // }

  // std::cout << "\nバッチ処理（サイズ2）:" << std::endl;
  // ProcessActorsBatch(actors, 2);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 std::span の演習問題\n" << std::endl;

  test_array_processing();
  test_tarray_integration();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout
      << "全てのTODOを実装し、コンパイルエラーがなくなったら成功です。"
      << std::endl;
  return 0;
}
