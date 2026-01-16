// std::span のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

// ============================================================================
// 1. 基本的な std::span の使い方
// ============================================================================

// 従来の方法（オーバーロードが必要）
void print_vector(const std::vector<int>& data) {
  for (int value : data) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void print_array(const int* data, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

// std::span を使った統一的な方法
void print_span(std::span<const int> data) {
  for (int value : data) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void basic_span_example() {
  std::cout << "=== 基本的な std::span の使い方 ===" << std::endl;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::array<int, 5> arr = {6, 7, 8, 9, 10};
  int c_array[] = {11, 12, 13, 14, 15};

  std::cout << "従来の方法:" << std::endl;
  std::cout << "  vector: ";
  print_vector(vec);
  std::cout << "  C array: ";
  print_array(c_array, 5);

  std::cout << "\nstd::span を使った方法:" << std::endl;
  std::cout << "  vector: ";
  print_span(vec);
  std::cout << "  array: ";
  print_span(arr);
  std::cout << "  C array: ";
  print_span(c_array);

  std::cout << std::endl;
}

// ============================================================================
// 2. 可変ビューと読み取り専用ビュー
// ============================================================================

// 可変ビュー（要素を変更可能）
void double_values(std::span<int> data) {
  for (int& value : data) {
    value *= 2;
  }
}

// 読み取り専用ビュー（要素を変更不可）
int sum_values(std::span<const int> data) {
  return std::accumulate(data.begin(), data.end(), 0);
}

void mutable_vs_const_span() {
  std::cout << "=== 可変ビューと読み取り専用ビュー ===" << std::endl;

  std::vector<int> nums = {1, 2, 3, 4, 5};

  std::cout << "元の値: ";
  print_span(nums);

  int sum = sum_values(nums);
  std::cout << "合計: " << sum << std::endl;

  double_values(nums);
  std::cout << "2倍後: ";
  print_span(nums);

  std::cout << std::endl;
}

// ============================================================================
// 3. 部分ビュー（subspan, first, last）
// ============================================================================

void subspan_examples() {
  std::cout << "=== 部分ビュー ===" << std::endl;

  std::vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::cout << "全体: ";
  print_span(data);

  // subspan(offset, count)
  std::cout << "subspan(2, 5): ";
  print_span(std::span(data).subspan(2, 5));

  // subspan(offset) - 末尾まで
  std::cout << "subspan(5): ";
  print_span(std::span(data).subspan(5));

  // first(count) - 先頭からN個
  std::cout << "first(3): ";
  print_span(std::span(data).first(3));

  // last(count) - 末尾からN個
  std::cout << "last(4): ";
  print_span(std::span(data).last(4));

  std::cout << std::endl;
}

// ============================================================================
// 4. サイズ情報の取得
// ============================================================================

void size_info_examples() {
  std::cout << "=== サイズ情報 ===" << std::endl;

  std::vector<int> data = {1, 2, 3, 4, 5};
  std::span<int> s(data);

  std::cout << "size(): " << s.size() << std::endl;
  std::cout << "size_bytes(): " << s.size_bytes() << " バイト" << std::endl;
  std::cout << "empty(): " << (s.empty() ? "空" : "非空") << std::endl;

  std::span<int> empty_span;
  std::cout << "空のspan - empty(): " << (empty_span.empty() ? "空" : "非空")
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 動的サイズと固定サイズの span
// ============================================================================

// 動的サイズのspan（サイズは実行時に決定）
void process_dynamic(std::span<int> data) {
  std::cout << "  動的span（サイズ: " << data.size() << "）: ";
  print_span(data);
}

// 固定サイズのspan（サイズはコンパイル時に決定）
void process_fixed(std::span<int, 5> data) {
  std::cout << "  固定span（サイズ: " << data.size() << "）: ";
  print_span(data);
}

void dynamic_vs_fixed_span() {
  std::cout << "=== 動的サイズと固定サイズのspan ===" << std::endl;

  std::array<int, 5> arr = {1, 2, 3, 4, 5};
  std::vector<int> vec = {6, 7, 8};

  process_dynamic(arr);
  process_dynamic(vec);

  process_fixed(arr);
  // process_fixed(vec);  // エラー: サイズが合わない

  std::cout << std::endl;
}

// ============================================================================
// 6. 実践例: データ処理パイプライン
// ============================================================================

struct DataStats {
  int min;
  int max;
  double average;
  int sum;
};

DataStats calculate_stats(std::span<const int> data) {
  if (data.empty()) {
    return {0, 0, 0.0, 0};
  }

  int min_val = *std::min_element(data.begin(), data.end());
  int max_val = *std::max_element(data.begin(), data.end());
  int sum_val = std::accumulate(data.begin(), data.end(), 0);
  double avg = static_cast<double>(sum_val) / data.size();

  return {min_val, max_val, avg, sum_val};
}

void data_processing_example() {
  std::cout << "=== データ処理パイプライン ===" << std::endl;

  std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};

  std::cout << "データ: ";
  print_span(data);

  DataStats stats = calculate_stats(data);
  std::cout << "統計情報:" << std::endl;
  std::cout << "  最小値: " << stats.min << std::endl;
  std::cout << "  最大値: " << stats.max << std::endl;
  std::cout << "  平均値: " << stats.average << std::endl;
  std::cout << "  合計: " << stats.sum << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 7. UE 5.7風の例: TArray との統合
// ============================================================================

// 簡易的な TArray 風のエイリアス
template <typename T>
using TArray = std::vector<T>;

// TArray を span で受け取る（コピー不要）
void ProcessActors(std::span<const int> actor_ids) {
  std::cout << "  処理するActor数: " << actor_ids.size() << std::endl;
  std::cout << "  Actor IDs: ";
  for (int id : actor_ids) {
    std::cout << id << " ";
  }
  std::cout << std::endl;
}

// TArray の部分範囲を処理
void ProcessNearbyActors(std::span<const int> actor_ids, int max_count) {
  auto nearby = std::span(actor_ids).first(
      std::min(static_cast<size_t>(max_count), actor_ids.size()));
  std::cout << "  近くのActor（最大" << max_count << "個）: ";
  print_span(nearby);
}

void unreal_style_example() {
  std::cout << "=== UE 5.7風の例: TArray との統合 ===" << std::endl;

  TArray<int> all_actors = {101, 102, 103, 104, 105, 106, 107};

  std::cout << "全Actorを処理:" << std::endl;
  ProcessActors(all_actors);

  std::cout << "\n最も近い3つのActorを処理:" << std::endl;
  ProcessNearbyActors(all_actors, 3);

  std::cout << "\n部分範囲（インデックス2〜5）:" << std::endl;
  auto subset = std::span(all_actors).subspan(2, 4);
  ProcessActors(subset);

  std::cout << std::endl;
}

// ============================================================================
// 8. メモリ安全性の向上
// ============================================================================

// 危険な従来の方法
void unsafe_process(int* data, size_t size) {
  // サイズチェックがないと危険
  for (size_t i = 0; i < size; ++i) {
    data[i] *= 2;
  }
}

// 安全な std::span を使った方法
void safe_process(std::span<int> data) {
  // サイズ情報が含まれているため安全
  for (int& value : data) {
    value *= 2;
  }
}

void memory_safety_example() {
  std::cout << "=== メモリ安全性の向上 ===" << std::endl;

  std::vector<int> data = {1, 2, 3, 4, 5};

  std::cout << "元のデータ: ";
  print_span(data);

  safe_process(data);
  std::cout << "安全に処理後: ";
  print_span(data);

  // span は境界チェックを提供
  std::span<int> s(data);
  std::cout << "s[0] = " << s[0] << std::endl;
  // std::cout << s.at(10);  // std::out_of_range 例外

  std::cout << std::endl;
}

// ============================================================================
// 9. 2次元データの扱い（応用）
// ============================================================================

// 1次元配列を2次元的に扱う
void process_2d_data(std::span<int> data, size_t width, size_t height) {
  std::cout << "2次元データ (" << width << " x " << height << "):" << std::endl;
  for (size_t y = 0; y < height; ++y) {
    std::cout << "  行" << y << ": ";
    auto row = data.subspan(y * width, width);
    print_span(row);
  }
}

void two_dimensional_example() {
  std::cout << "=== 2次元データの扱い ===" << std::endl;

  // 3x4 の行列
  std::vector<int> matrix = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  process_2d_data(matrix, 4, 3);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 std::span のサンプル\n" << std::endl;

  basic_span_example();
  mutable_vs_const_span();
  subspan_examples();
  size_info_examples();
  dynamic_vs_fixed_span();
  data_processing_example();
  unreal_style_example();
  memory_safety_example();
  two_dimensional_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
