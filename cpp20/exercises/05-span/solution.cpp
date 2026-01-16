// std::span の演習問題 - 解答例

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

// ============================================================================
// 演習 2.5.1: 配列処理関数（解答）
// ============================================================================
// std::span を使って、様々な種類の配列を処理できる汎用関数を作成せよ。
//
// 要件:
// - sum() : 要素の合計を計算
// - average() : 平均値を計算
// - std::vector, std::array, C配列のすべてに対応

int sum(std::span<const int> data) {
  // std::accumulate を使用して合計を計算
  return std::accumulate(data.begin(), data.end(), 0);
}

double average(std::span<const int> data) {
  // 空の場合は0.0を返す
  if (data.empty()) {
    return 0.0;
  }
  // sum() を使って合計を計算し、サイズで割る
  return static_cast<double>(sum(data)) / data.size();
}

void test_array_processing() {
  std::cout << "=== 演習 2.5.1: 配列処理関数（解答） ===" << std::endl;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::array<int, 5> arr = {6, 7, 8, 9, 10};
  int c_array[] = {11, 12, 13, 14, 15};

  std::cout << "vector: sum=" << sum(vec) << ", avg=" << average(vec)
            << std::endl;
  std::cout << "array: sum=" << sum(arr) << ", avg=" << average(arr)
            << std::endl;
  std::cout << "C array: sum=" << sum(c_array) << ", avg=" << average(c_array)
            << std::endl;

  std::cout << "✓ 配列処理関数が正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.2: TArray風のコンテナとの統合（解答）
// ============================================================================
// UEのTArray風のコンテナとstd::spanを組み合わせた処理を実装せよ。

// TArray の代わりに std::vector を使用
template <typename T>
using TArray = std::vector<T>;

struct Actor {
  int id;
  float x, y, z;
};

// 指定された数の最も近いActorを返す（最初のN個を返す）
std::vector<Actor> GetNearestActors(std::span<const Actor> all_actors,
                                    int max_count) {
  // std::span の first() を使って最初のN個を取得
  // max_count が配列サイズより大きい場合に備えて、サイズを調整
  size_t count = std::min(static_cast<size_t>(max_count), all_actors.size());
  auto nearest = all_actors.first(count);

  // std::vector に変換して返す
  return std::vector<Actor>(nearest.begin(), nearest.end());
}

// Actor配列を指定サイズのバッチに分けて処理する
void ProcessActorsBatch(std::span<const Actor> actors, int batch_size) {
  size_t total_size = actors.size();
  size_t batch_index = 0;

  // ループでactorsを batch_size ずつ処理
  for (size_t offset = 0; offset < total_size; offset += batch_size) {
    // 残りのサイズを計算
    size_t current_batch_size =
        std::min(static_cast<size_t>(batch_size), total_size - offset);

    // subspan() を使って部分範囲を取得
    auto batch = actors.subspan(offset, current_batch_size);

    // 各バッチのサイズとIDを出力
    std::cout << "  バッチ " << batch_index++ << " (サイズ: "
              << current_batch_size << "): ";
    for (const auto& actor : batch) {
      std::cout << "ID=" << actor.id << " ";
    }
    std::cout << std::endl;
  }
}

void test_tarray_integration() {
  std::cout << "=== 演習 2.5.2: TArray風のコンテナとの統合（解答） ==="
            << std::endl;

  TArray<Actor> actors = {{1, 10.0f, 0.0f, 0.0f}, {2, 20.0f, 0.0f, 0.0f},
                          {3, 30.0f, 0.0f, 0.0f}, {4, 40.0f, 0.0f, 0.0f},
                          {5, 50.0f, 0.0f, 0.0f}, {6, 60.0f, 0.0f, 0.0f}};

  std::cout << "最も近い3つのActor:" << std::endl;
  auto nearest = GetNearestActors(actors, 3);
  for (const auto& actor : nearest) {
    std::cout << "  Actor ID: " << actor.id << std::endl;
  }

  std::cout << "\nバッチ処理（サイズ2）:" << std::endl;
  ProcessActorsBatch(actors, 2);

  std::cout << "✓ TArray風のコンテナとの統合が正しく動作しています。"
            << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 std::span の演習問題 - 解答例\n" << std::endl;

  test_array_processing();
  test_tarray_integration();

  std::cout << "全ての演習が完了しました！" << std::endl;
  std::cout << "std::spanを使うことで、様々なコンテナ型を統一的に扱えます。"
            << std::endl;
  return 0;
}
