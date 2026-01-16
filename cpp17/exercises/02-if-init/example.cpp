// if/switch初期化式のサンプルコード

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>

// ============================================================================
// 1. 基本的なif初期化式
// ============================================================================

void basic_if_init() {
  std::cout << "=== 基本的なif初期化式 ===" << std::endl;

  std::map<std::string, int> scores = {{"Alice", 100}, {"Bob", 85}};

  // 従来の方法（C++14以前）
  std::cout << "従来の方法:" << std::endl;
  {
    auto it = scores.find("Alice");
    if (it != scores.end()) {
      std::cout << "Alice's score: " << it->second << std::endl;
    }
    // itはこのブロックの外でも使える（スコープが広すぎる）
  }

  // C++17のif初期化式
  std::cout << "\nif初期化式を使った方法:" << std::endl;
  if (auto it = scores.find("Alice"); it != scores.end()) {
    std::cout << "Alice's score: " << it->second << std::endl;
    // itのスコープはこのif文内のみ
  }

  // 存在しないキーの検索
  if (auto it = scores.find("Charlie"); it != scores.end()) {
    std::cout << "Charlie's score: " << it->second << std::endl;
  } else {
    std::cout << "Charlie not found" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 2. switch初期化式
// ============================================================================

enum class Status { OK, Warning, Error };

Status check_status(int code) {
  if (code == 0)
    return Status::OK;
  if (code < 100)
    return Status::Warning;
  return Status::Error;
}

void basic_switch_init() {
  std::cout << "=== switch初期化式 ===" << std::endl;

  int error_code = 42;

  // 従来の方法
  {
    Status status = check_status(error_code);
    switch (status) {
      case Status::OK:
        std::cout << "OK" << std::endl;
        break;
      case Status::Warning:
        std::cout << "Warning" << std::endl;
        break;
      case Status::Error:
        std::cout << "Error" << std::endl;
        break;
    }
  }

  // C++17のswitch初期化式
  switch (Status status = check_status(error_code); status) {
    case Status::OK:
      std::cout << "Status is OK" << std::endl;
      break;
    case Status::Warning:
      std::cout << "Status is Warning" << std::endl;
      break;
    case Status::Error:
      std::cout << "Status is Error" << std::endl;
      break;
  }

  // 文字列の長さで分岐
  std::string text = "Hello";
  switch (auto len = text.length(); len) {
    case 0:
      std::cout << "Empty string" << std::endl;
      break;
    case 1:
      std::cout << "Single character" << std::endl;
      break;
    default:
      std::cout << "String length: " << len << std::endl;
      break;
  }

  std::cout << std::endl;
}

// ============================================================================
// 3. 実用例：ロックガードとの組み合わせ
// ============================================================================

class SharedResource {
 public:
  void update(int value) { data_ = value; }
  int get() const { return data_; }

 private:
  mutable std::mutex mutex_;
  int data_ = 0;

  friend void lock_guard_example();
};

void lock_guard_example() {
  std::cout << "=== ロックガードとif初期化式 ===" << std::endl;

  SharedResource resource;

  // ロックを取得してから条件チェック
  if (std::lock_guard<std::mutex> lock(resource.mutex_);
      resource.data_ > 0) {
    std::cout << "Resource has positive value: " << resource.data_
              << std::endl;
  } else {
    std::cout << "Resource has non-positive value" << std::endl;
  }
  // lockはここで自動的に解放される

  std::cout << std::endl;
}

// ============================================================================
// 4. 実用例：複雑な条件チェック
// ============================================================================

struct Config {
  int max_connections = 100;
  int timeout_seconds = 30;
  bool debug_mode = false;
};

std::map<std::string, Config> g_configs = {
    {"server1", {100, 30, false}}, {"server2", {200, 60, true}}};

void complex_example() {
  std::cout << "=== 複雑な条件チェック ===" << std::endl;

  std::string server_name = "server1";

  // 設定を検索して、存在すればdebugモードかチェック
  if (auto it = g_configs.find(server_name); it != g_configs.end()) {
    const Config& config = it->second;
    std::cout << "Found config for " << server_name << std::endl;
    std::cout << "  Max connections: " << config.max_connections << std::endl;
    std::cout << "  Timeout: " << config.timeout_seconds << " seconds"
              << std::endl;
    std::cout << "  Debug mode: " << (config.debug_mode ? "ON" : "OFF")
              << std::endl;

    // さらにネストしたif初期化式
    if (int timeout = config.timeout_seconds; timeout > 0) {
      std::cout << "  Timeout is configured: " << timeout << "s" << std::endl;
    }
  } else {
    std::cout << "Config not found for " << server_name << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. 実用例：計算結果のキャッシュ
// ============================================================================

std::unordered_map<int, int> g_fibonacci_cache;

int fibonacci(int n) {
  if (n <= 1)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void cache_example() {
  std::cout << "=== キャッシュの例 ===" << std::endl;

  int n = 10;

  // キャッシュから検索し、なければ計算して格納
  if (auto it = g_fibonacci_cache.find(n); it != g_fibonacci_cache.end()) {
    std::cout << "Cache hit! fibonacci(" << n << ") = " << it->second
              << std::endl;
  } else {
    std::cout << "Cache miss! Computing fibonacci(" << n << ")..." << std::endl;
    int result = fibonacci(n);
    g_fibonacci_cache[n] = result;
    std::cout << "fibonacci(" << n << ") = " << result << std::endl;
  }

  // 2回目は必ずキャッシュヒット
  if (auto it = g_fibonacci_cache.find(n); it != g_fibonacci_cache.end()) {
    std::cout << "Cache hit! fibonacci(" << n << ") = " << it->second
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 if/switch初期化式のサンプル\n" << std::endl;

  basic_if_init();
  basic_switch_init();
  lock_guard_example();
  complex_example();
  cache_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
