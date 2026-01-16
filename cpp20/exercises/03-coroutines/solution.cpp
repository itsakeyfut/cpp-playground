// コルーチン（Coroutines）の演習問題 - 解答例

#include <coroutine>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// Generator実装（提供済み）
// ============================================================================

template <typename T>
struct Generator {
  struct promise_type {
    T current_value;

    Generator get_return_object() {
      return Generator{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    std::suspend_always yield_value(T value) {
      current_value = value;
      return {};
    }

    void return_void() {}
    void unhandled_exception() { std::terminate(); }
  };

  std::coroutine_handle<promise_type> handle;

  explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}

  ~Generator() {
    if (handle) handle.destroy();
  }

  Generator(const Generator&) = delete;
  Generator& operator=(const Generator&) = delete;

  Generator(Generator&& other) noexcept : handle(other.handle) {
    other.handle = nullptr;
  }

  Generator& operator=(Generator&& other) noexcept {
    if (this != &other) {
      if (handle) handle.destroy();
      handle = other.handle;
      other.handle = nullptr;
    }
    return *this;
  }

  struct iterator {
    std::coroutine_handle<promise_type> handle;

    iterator& operator++() {
      handle.resume();
      return *this;
    }

    T operator*() const { return handle.promise().current_value; }

    bool operator==(std::default_sentinel_t) const { return handle.done(); }
  };

  iterator begin() {
    handle.resume();
    return {handle};
  }

  std::default_sentinel_t end() { return {}; }
};

// ============================================================================
// 演習 2.3.1: フィボナッチ数列ジェネレータ（解答）
// ============================================================================

Generator<int> fibonacci() {
  int a = 0;
  int b = 1;
  while (true) {
    co_yield a;
    int tmp = a;
    a = b;
    b = tmp + b;
  }
}

void test_fibonacci() {
  std::cout << "=== 演習 2.3.1: フィボナッチ数列ジェネレータ（解答） ==="
            << std::endl;

  std::cout << "最初の15個: ";
  int count = 0;
  for (int fib : fibonacci()) {
    if (count >= 15) break;
    std::cout << fib << " ";
    ++count;
  }
  std::cout << std::endl;

  // vectorに変換して検証
  std::vector<int> fibs;
  count = 0;
  for (int fib : fibonacci()) {
    if (count >= 10) break;
    fibs.push_back(fib);
    ++count;
  }

  std::cout << "検証: ";
  std::vector<int> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
  bool correct = (fibs == expected);
  std::cout << (correct ? "✓ 正しく動作しています" : "✗ エラーがあります")
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.3.2: ファイル行読み込みジェネレータ（解答）
// ============================================================================

Generator<std::string> read_lines(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
    co_return;
  }

  std::string line;
  while (std::getline(file, line)) {
    co_yield line;
  }
}

void test_file_reader() {
  std::cout << "=== 演習 2.3.2: ファイル行読み込みジェネレータ（解答） ==="
            << std::endl;

  // テスト用ファイルを作成
  const std::string filename = "solution_test.txt";
  {
    std::ofstream out(filename);
    out << "Hello from line 1\n";
    out << "Hello from line 2\n";
    out << "Hello from line 3\n";
    out << "Hello from line 4\n";
  }

  std::cout << filename << "の内容:" << std::endl;
  int line_num = 0;
  for (const auto& line : read_lines(filename)) {
    std::cout << "  " << ++line_num << ": " << line << std::endl;
  }

  std::cout << "\n✓ ファイル読み込みが正しく動作しています" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// おまけ: より実践的な例
// ============================================================================

// 範囲内の素数を生成
Generator<int> prime_numbers(int max) {
  auto is_prime = [](int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
      if (n % i == 0) return false;
    }
    return true;
  };

  for (int i = 2; i <= max; ++i) {
    if (is_prime(i)) {
      co_yield i;
    }
  }
}

// カウントダウンタイマー
Generator<int> countdown(int from) {
  for (int i = from; i >= 0; --i) {
    co_yield i;
  }
}

void advanced_examples() {
  std::cout << "=== おまけ: より実践的な例 ===" << std::endl;

  // 素数生成
  std::cout << "100以下の素数: ";
  for (int prime : prime_numbers(100)) {
    std::cout << prime << " ";
  }
  std::cout << std::endl;

  // カウントダウン
  std::cout << "\nカウントダウン: ";
  for (int count : countdown(10)) {
    std::cout << count << " ";
  }
  std::cout << "発射！" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// おまけ: ゲーム開発向け - アニメーションシーケンス
// ============================================================================

struct AnimationFrame {
  int frame_number;
  float time;
  std::string action;
};

Generator<AnimationFrame> animation_sequence() {
  co_yield AnimationFrame{0, 0.0f, "Start"};
  co_yield AnimationFrame{1, 0.1f, "Jump"};
  co_yield AnimationFrame{2, 0.2f, "Peak"};
  co_yield AnimationFrame{3, 0.3f, "Fall"};
  co_yield AnimationFrame{4, 0.4f, "Land"};
  co_yield AnimationFrame{5, 0.5f, "End"};
}

void game_animation_example() {
  std::cout << "=== おまけ: アニメーションシーケンス ===" << std::endl;

  std::cout << "ジャンプアニメーション:" << std::endl;
  for (const auto& frame : animation_sequence()) {
    std::cout << "  Frame " << frame.frame_number << " (t=" << frame.time
              << "s): " << frame.action << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コルーチン（Coroutines）の演習問題 - 解答例\n"
            << std::endl;

  test_fibonacci();
  test_file_reader();
  advanced_examples();
  game_animation_example();

  std::cout << "全ての演習が完了しました！" << std::endl;
  std::cout << "\nコルーチンの利点:" << std::endl;
  std::cout << "  ✓ 状態を保持したまま中断・再開" << std::endl;
  std::cout << "  ✓ 遅延評価（必要な分だけ生成）" << std::endl;
  std::cout << "  ✓ 無限シーケンスも扱える" << std::endl;
  std::cout << "  ✓ 非同期処理の基盤" << std::endl;

  return 0;
}
