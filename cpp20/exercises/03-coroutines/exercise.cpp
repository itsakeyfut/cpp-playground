// コルーチン（Coroutines）の演習問題
// TODOを埋めて、プログラムを完成させてください。

#include <coroutine>
#include <fstream>
#include <iostream>
#include <string>

// ============================================================================
// Generator実装（提供済み - そのまま使用してください）
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
// 演習 2.3.1: フィボナッチ数列ジェネレータ
// ============================================================================
// フィボナッチ数列を生成するジェネレータを実装せよ。
//
// 要件:
// - Generator<int>を返す
// - co_yieldで値を生成
// - 無限に生成可能（whileループ）
//
// ヒント:
// フィボナッチ数列: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
// - a = 0, b = 1 から開始
// - 次の値 = a + b

// TODO: fibonacci()関数を実装してください
Generator<int> fibonacci() {
  // ヒント:
  // int a = 0;
  // int b = 1;
  // while (true) {
  //     co_yield a;
  //     int tmp = a;
  //     a = b;
  //     b = tmp + b;
  // }
  co_return;  // この行を削除して実装してください
}

void test_fibonacci() {
  std::cout << "=== 演習 2.3.1: フィボナッチ数列ジェネレータ ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // std::cout << "最初の10個: ";
  // int count = 0;
  // for (int fib : fibonacci()) {
  //     if (count >= 10) break;
  //     std::cout << fib << " ";
  //     ++count;
  // }
  // std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.3.2: ファイル行読み込みジェネレータ
// ============================================================================
// ファイルを1行ずつ読み込むジェネレータを実装せよ。
//
// 要件:
// - Generator<std::string>を返す
// - ファイルを開いて1行ずつco_yield
// - ファイルが開けない場合はco_returnで終了
//
// ヒント:
// - std::ifstream でファイルを開く
// - std::getline() で1行ずつ読み込む

// TODO: read_lines()関数を実装してください
Generator<std::string> read_lines(const std::string& filename) {
  // ヒント:
  // std::ifstream file(filename);
  // if (!file.is_open()) {
  //     co_return;
  // }
  // std::string line;
  // while (std::getline(file, line)) {
  //     co_yield line;
  // }
  co_return;  // この行を削除して実装してください
}

void test_file_reader() {
  std::cout << "=== 演習 2.3.2: ファイル行読み込みジェネレータ ===" << std::endl;

  // テスト用ファイルを作成
  {
    std::ofstream out("exercise_test.txt");
    out << "Hello from line 1\n";
    out << "Hello from line 2\n";
    out << "Hello from line 3\n";
  }

  // TODO: 以下のコメントを外して動作確認してください
  // std::cout << "ファイルの内容:" << std::endl;
  // for (const auto& line : read_lines("exercise_test.txt")) {
  //     std::cout << "  " << line << std::endl;
  // }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コルーチン（Coroutines）の演習問題\n" << std::endl;

  test_fibonacci();
  test_file_reader();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout
      << "全てのTODOを実装し、コンパイルエラーがなくなったら成功です。"
      << std::endl;
  return 0;
}
