// コルーチン（Coroutines）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <coroutine>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================================
// Generator実装（コルーチンの基盤）
// ============================================================================
// この実装は写経する必要はありません。理解することが重要です。

template <typename T>
struct Generator {
  // promise_type: コルーチンの動作を制御
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

  // ムーブのみ許可
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

  // イテレータインターフェース
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
// 1. 基本的なジェネレータ: 範囲生成
// ============================================================================

Generator<int> range(int start, int end) {
  for (int i = start; i < end; ++i) {
    co_yield i;  // 値を生成して中断
  }
}

void basic_generator_example() {
  std::cout << "=== 基本的なジェネレータ ===" << std::endl;

  std::cout << "range(0, 10): ";
  for (int i : range(0, 10)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "range(5, 15): ";
  for (int i : range(5, 15)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. フィボナッチ数列ジェネレータ
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

void fibonacci_example() {
  std::cout << "=== フィボナッチ数列 ===" << std::endl;

  std::cout << "最初の10個: ";
  int count = 0;
  for (int fib : fibonacci()) {
    if (count >= 10) break;
    std::cout << fib << " ";
    ++count;
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. 文字列ジェネレータ: カスタムシーケンス
// ============================================================================

Generator<std::string> greetings() {
  co_yield "Hello";
  co_yield "World";
  co_yield "from";
  co_yield "C++20";
  co_yield "Coroutines!";
}

void string_generator_example() {
  std::cout << "=== 文字列ジェネレータ ===" << std::endl;

  std::cout << "挨拶: ";
  for (const auto& word : greetings()) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. ファイル行読み込みジェネレータ
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

void file_reader_example() {
  std::cout << "=== ファイル行読み込み ===" << std::endl;

  // テスト用ファイルを作成
  {
    std::ofstream out("test.txt");
    out << "Line 1: Hello\n";
    out << "Line 2: World\n";
    out << "Line 3: from\n";
    out << "Line 4: C++20\n";
  }

  std::cout << "test.txtの内容:" << std::endl;
  for (const auto& line : read_lines("test.txt")) {
    std::cout << "  " << line << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. フィルタリングジェネレータ
// ============================================================================

// 範囲内の偶数のみを生成
Generator<int> even_numbers(int start, int end) {
  for (int i = start; i < end; ++i) {
    if (i % 2 == 0) {
      co_yield i;
    }
  }
}

void filtering_generator_example() {
  std::cout << "=== フィルタリングジェネレータ ===" << std::endl;

  std::cout << "0～20の偶数: ";
  for (int n : even_numbers(0, 20)) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. ゲーム開発向け: フレーム分散処理
// ============================================================================

struct Task {
  std::string name;
  int progress;  // 0-100
};

// タスクを少しずつ処理するジェネレータ
Generator<Task> process_task_incremental(const std::string& task_name) {
  for (int progress = 0; progress <= 100; progress += 10) {
    co_yield Task{task_name, progress};
    // 実際のゲームではここで重い処理を少しだけ実行
  }
}

void game_frame_distribution_example() {
  std::cout << "=== ゲーム開発: フレーム分散処理 ===" << std::endl;

  std::cout << "タスク処理（フレームごとに10%ずつ）:" << std::endl;
  for (const auto& task : process_task_incremental("AssetLoading")) {
    std::cout << "  フレーム: " << task.name << " - " << task.progress << "%"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. 組み合わせ: ジェネレータを変換
// ============================================================================

// ジェネレータの各要素を2倍にする
Generator<int> double_values(Generator<int> gen) {
  for (int value : gen) {
    co_yield value * 2;
  }
}

void generator_transformation_example() {
  std::cout << "=== ジェネレータの変換 ===" << std::endl;

  std::cout << "元の値: ";
  for (int i : range(1, 6)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "2倍した値: ";
  for (int i : double_values(range(1, 6))) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 8. UE 5.7風の例: リソースローダー
// ============================================================================

struct LoadProgress {
  std::string resource_name;
  int bytes_loaded;
  int total_bytes;

  float percentage() const {
    return total_bytes > 0 ? (100.0f * bytes_loaded / total_bytes) : 0.0f;
  }
};

Generator<LoadProgress> load_resource_async(const std::string& resource_name,
                                             int total_bytes) {
  int chunk_size = total_bytes / 10;  // 10回に分けてロード
  for (int loaded = 0; loaded <= total_bytes; loaded += chunk_size) {
    co_yield LoadProgress{resource_name, loaded, total_bytes};
    // 実際にはここでファイルI/Oや非同期処理
  }
}

void unreal_style_example() {
  std::cout << "=== UE 5.7風: リソースローダー ===" << std::endl;

  std::cout << "テクスチャをロード中..." << std::endl;
  for (const auto& progress : load_resource_async("Texture_Player.png", 1000)) {
    std::cout << "  " << progress.resource_name << ": "
              << static_cast<int>(progress.percentage()) << "% ("
              << progress.bytes_loaded << "/" << progress.total_bytes << " bytes)"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コルーチン（Coroutines）のサンプル\n" << std::endl;

  basic_generator_example();
  fibonacci_example();
  string_generator_example();
  file_reader_example();
  filtering_generator_example();
  game_frame_distribution_example();
  generator_transformation_example();
  unreal_style_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
