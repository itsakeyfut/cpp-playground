# モダン C++学習カリキュラム（C++17〜C++26）

## このドキュメントについて

このドキュメントは、Claude Code と一緒にモダン C++を学習するためのカリキュラムです。
学習者は中級エンジニアで、Rust/C/C++/Assembler の経験があり、個人開発歴 10 年以上です。
最終目標は Unreal Engine でのゲーム開発ですが、本カリキュラムでは UE を使わず純粋な C++を学びます。

## 学習者プロファイル

- **スキルレベル**: 中級（基礎文法は理解済み）
- **得意言語**: Rust, C/C++, Assembler
- **関心分野**: ゲーム開発、グラフィックス、マルチメディア処理、ゲームエンジン
- **Rust の知識**: 所有権、ライフタイム、トレイト、Result 型などを理解

## Claude Code への指示

### 基本方針

1. **説明は簡潔に**: 学習者は経験者なので、冗長な説明は不要
2. **Rust との比較**: 可能な限り Rust の類似概念と比較して説明する
3. **実践重視**: 概念説明より先にコード例を示す
4. **段階的な演習**: 各トピックに小さな演習 → 発展課題の流れで進める
5. **ゲーム開発視点**: 例やユースケースはゲーム開発に関連するものを優先

### 学習セッションの進め方

```
1. トピックの概要説明（Rustとの比較を含む）
2. 最小限のコード例を示す
3. 学習者にコードを書いてもらう（写経ではなく自力で）
4. 発展課題を提示
5. 進捗をPROGRESS.mdに記録
```

### コード作成時のルール

- C++標準: 学習中のバージョンに合わせる（C++17, C++20, C++23, C++26）
- コンパイラ: clang++ または g++（最新版推奨）
- コンパイルオプション例:
  - C++17: `-std=c++17 -Wall -Wextra -pedantic`
  - C++20: `-std=c++20 -Wall -Wextra -pedantic`
  - C++23: `-std=c++23 -Wall -Wextra -pedantic`
- ビルドシステム: 単一ファイルはコマンドライン、複数ファイルは CMake

---

## カリキュラム全体像

```
Phase 1: C++17（2週間）    — モダンC++の土台
Phase 2: C++20（3〜4週間） — パラダイムシフト
Phase 3: C++23（2週間）    — 実用性の強化
Phase 4: C++26（1〜2週間） — 最新動向
横断トピック（全Phase並行）— テンプレート、並行性、最適化
```

---

## Phase 1: C++17 — モダン C++の土台

### 学習目標

C++17 で導入された「書きやすさ」の改善を習得し、モダンな C++コードを書けるようになる。


### 1.0 モダンC++の基礎（C++11〜C++14の重要機能）

**このセクションは必要に応じてスキップ可能。ただし、以降の学習で必須となる概念。**

#### 1.0.1 スマートポインタとRAII

**Rust との比較**: `Box<T>`, `Rc<T>`, `Arc<T>`, `Weak<T>` に相当

```cpp
#include <memory>

// unique_ptr: 単一所有権（Rustの Box<T>）
std::unique_ptr<int> up = std::make_unique<int>(42);
auto up2 = std::move(up);  // ムーブはできるがコピー不可、up は null

// shared_ptr: 参照カウント（Rustの Rc<T>/Arc<T>）
std::shared_ptr<int> sp1 = std::make_shared<int>(100);
std::shared_ptr<int> sp2 = sp1;  // 参照カウント増加

// weak_ptr: 循環参照を防ぐ（Rustの Weak<T>）
std::weak_ptr<int> wp = sp1;
if (auto sp = wp.lock()) {  // 生存確認
    std::cout << *sp << "\n";
}

// 配列のunique_ptr
auto arr = std::make_unique<int[]>(10);
```

**RAII パターン**: コンストラクタでリソース取得、デストラクタで自動解放

```cpp
class FileHandle {
    FILE* file;
public:
    explicit FileHandle(const char* path) : file(fopen(path, "r")) {
        if (!file) throw std::runtime_error("File not found");
    }
    ~FileHandle() { if (file) fclose(file); }

    // コピー禁止、ムーブ許可
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    FileHandle(FileHandle&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }

    FILE* get() const { return file; }
};
```

#### 1.0.2 ムーブセマンティクスと右辺値参照

**Rust との比較**: Rust の所有権システムに対応

```cpp
// 左辺値（lvalue）と右辺値（rvalue）
int x = 10;      // x は左辺値
int y = x + 5;   // x + 5 は右辺値

// 右辺値参照（&&）
std::vector<int> create_vector() {
    return std::vector<int>{1, 2, 3};  // 右辺値
}
std::vector<int> v = create_vector();  // ムーブされる（コピーなし）

// std::move: 左辺値を右辺値にキャスト
std::vector<int> v1{1, 2, 3};
std::vector<int> v2 = std::move(v1);  // v1の内容をv2にムーブ（Rustのmoveと同じ）

// Perfect Forwarding
template<typename T>
void wrapper(T&& arg) {
    target(std::forward<T>(arg));  // argの値カテゴリを保持して転送
}
```

#### 1.0.3 ラムダ式の詳細

**Rust との比較**: クロージャに相当

```cpp
// 基本形
auto add = [](int a, int b) { return a + b; };

// キャプチャ
int x = 10;
auto f1 = [x]() { return x * 2; };          // 値キャプチャ
auto f2 = [&x]() { x *= 2; };               // 参照キャプチャ
auto f3 = [=]() { return x + y; };          // すべて値キャプチャ
auto f4 = [&]() { x++; y++; };              // すべて参照キャプチャ
auto f5 = [x, &y]() { return x + y; };      // 混在

// ムーブキャプチャ（C++14）
auto ptr = std::make_unique<int>(42);
auto f6 = [ptr = std::move(ptr)]() { return *ptr; };

// mutable: キャプチャした値を変更
int count = 0;
auto counter = [count]() mutable { return ++count; };

// ジェネリックラムダ（C++14）
auto print = [](const auto& x) { std::cout << x << "\n"; };

// テンプレートラムダ（C++20）
auto compare = []<typename T>(const T& a, const T& b) { return a < b; };
```

#### 1.0.4 例外処理とnoexcept

**Rust との比較**: パニックとは異なる回復可能なエラー処理

```cpp
#include <exception>
#include <stdexcept>

try {
    throw std::runtime_error("Something went wrong");
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << "General error: " << e.what() << "\n";
} catch (...) {
    std::cerr << "Unknown error\n";
}

// カスタム例外
class GameException : public std::exception {
    std::string message;
public:
    explicit GameException(std::string msg) : message(std::move(msg)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// noexcept: 例外を投げないことを保証（最適化のヒント）
int safe_add(int a, int b) noexcept { return a + b; }

// 条件付きnoexcept
template<typename T>
void swap_values(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}
```

#### 1.0.5 STLコンテナ選択ガイド

```cpp
// シーケンスコンテナ
std::array<int, 5> arr;      // 固定長配列（スタック）
std::vector<int> vec;        // 動的配列（最もよく使う）
std::deque<int> deq;         // 両端キュー
std::list<int> lst;          // 双方向リンクリスト

// 連想コンテナ（ソート済み、通常は赤黒木）
std::set<int> s;             // 一意集合
std::map<K, V> m;            // キー・バリュー
std::multiset<int> ms;       // 重複を許すset
std::multimap<K, V> mm;      // 重複を許すmap

// 非順序連想コンテナ（ハッシュテーブル）
std::unordered_set<int> us;  // ハッシュセット
std::unordered_map<K, V> um; // ハッシュマップ（最速の検索）

// 選択基準:
// - ランダムアクセス必要 → vector
// - 両端挿入/削除が多い → deque
// - 中間挿入/削除が多い → list
// - キーでソート必要 → map/set
// - 検索速度重視（O(1)） → unordered_map/set
// - スタック/キュー → deque（または専用のstack/queue）
```

#### 1.0.6 型推論（auto, decltype）

```cpp
// auto: 変数の型を推論
auto x = 42;                    // int
auto y = 3.14;                  // double
auto s = std::string("hello");  // std::string
auto vec = std::vector<int>{};  // std::vector<int>

// const/参照の維持には明示的指定が必要
const auto& ref = vec;          // const std::vector<int>&
auto&& universal_ref = foo();   // ユニバーサル参照

// decltype: 式の型を取得
int a = 10;
decltype(a) b = 20;             // int b = 20;

// decltype(auto): 式の型をそのまま推論（C++14）
decltype(auto) get_value() {
    static int x = 42;
    return (x);  // int& を返す（括弧があるため）
}
```

**演習 1.0.1**: リソースを管理する RAII クラス（ソケットやファイル）を実装せよ。
**演習 1.0.2**: ムーブ専用型を作成し、`std::vector`に格納して動作確認せよ。
**演習 1.0.3**: ジェネリックラムダを使って、任意の型のコンテナをフィルタリングする関数を作れ。

---


### 1.0 モダンC++の基礎（C++11〜C++14の重要機能）

**このセクションは必要に応じてスキップ可能。ただし、以降の学習で必須となる概念。**

#### 1.0.1 スマートポインタとRAII

**Rust との比較**: `Box<T>`, `Rc<T>`, `Arc<T>`, `Weak<T>` に相当

```cpp
#include <memory>

// unique_ptr: 単一所有権（Rustの Box<T>）
std::unique_ptr<int> up = std::make_unique<int>(42);
auto up2 = std::move(up);  // ムーブはできるがコピー不可、up は null

// shared_ptr: 参照カウント（Rustの Rc<T>/Arc<T>）
std::shared_ptr<int> sp1 = std::make_shared<int>(100);
std::shared_ptr<int> sp2 = sp1;  // 参照カウント増加

// weak_ptr: 循環参照を防ぐ（Rustの Weak<T>）
std::weak_ptr<int> wp = sp1;
if (auto sp = wp.lock()) {  // 生存確認
    std::cout << *sp << "\n";
}

// 配列のunique_ptr
auto arr = std::make_unique<int[]>(10);
```

**RAII パターン**: コンストラクタでリソース取得、デストラクタで自動解放

```cpp
class FileHandle {
    FILE* file;
public:
    explicit FileHandle(const char* path) : file(fopen(path, "r")) {
        if (!file) throw std::runtime_error("File not found");
    }
    ~FileHandle() { if (file) fclose(file); }

    // コピー禁止、ムーブ許可
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    FileHandle(FileHandle&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }

    FILE* get() const { return file; }
};
```

#### 1.0.2 ムーブセマンティクスと右辺値参照

**Rust との比較**: Rust の所有権システムに対応

```cpp
// 左辺値（lvalue）と右辺値（rvalue）
int x = 10;      // x は左辺値
int y = x + 5;   // x + 5 は右辺値

// 右辺値参照（&&）
std::vector<int> create_vector() {
    return std::vector<int>{1, 2, 3};  // 右辺値
}
std::vector<int> v = create_vector();  // ムーブされる（コピーなし）

// std::move: 左辺値を右辺値にキャスト
std::vector<int> v1{1, 2, 3};
std::vector<int> v2 = std::move(v1);  // v1の内容をv2にムーブ（Rustのmoveと同じ）

// Perfect Forwarding
template<typename T>
void wrapper(T&& arg) {
    target(std::forward<T>(arg));  // argの値カテゴリを保持して転送
}
```

#### 1.0.3 ラムダ式の詳細

**Rust との比較**: クロージャに相当

```cpp
// 基本形
auto add = [](int a, int b) { return a + b; };

// キャプチャ
int x = 10;
auto f1 = [x]() { return x * 2; };          // 値キャプチャ
auto f2 = [&x]() { x *= 2; };               // 参照キャプチャ
auto f3 = [=]() { return x + y; };          // すべて値キャプチャ
auto f4 = [&]() { x++; y++; };              // すべて参照キャプチャ
auto f5 = [x, &y]() { return x + y; };      // 混在

// ムーブキャプチャ（C++14）
auto ptr = std::make_unique<int>(42);
auto f6 = [ptr = std::move(ptr)]() { return *ptr; };

// mutable: キャプチャした値を変更
int count = 0;
auto counter = [count]() mutable { return ++count; };

// ジェネリックラムダ（C++14）
auto print = [](const auto& x) { std::cout << x << "\n"; };

// テンプレートラムダ（C++20）
auto compare = []<typename T>(const T& a, const T& b) { return a < b; };
```

#### 1.0.4 例外処理とnoexcept

**Rust との比較**: パニックとは異なる回復可能なエラー処理

```cpp
#include <exception>
#include <stdexcept>

try {
    throw std::runtime_error("Something went wrong");
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << "General error: " << e.what() << "\n";
} catch (...) {
    std::cerr << "Unknown error\n";
}

// カスタム例外
class GameException : public std::exception {
    std::string message;
public:
    explicit GameException(std::string msg) : message(std::move(msg)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// noexcept: 例外を投げないことを保証（最適化のヒント）
int safe_add(int a, int b) noexcept { return a + b; }

// 条件付きnoexcept
template<typename T>
void swap_values(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}
```

#### 1.0.5 STLコンテナ選択ガイド

```cpp
// シーケンスコンテナ
std::array<int, 5> arr;      // 固定長配列（スタック）
std::vector<int> vec;        // 動的配列（最もよく使う）
std::deque<int> deq;         // 両端キュー
std::list<int> lst;          // 双方向リンクリスト

// 連想コンテナ（ソート済み、通常は赤黒木）
std::set<int> s;             // 一意集合
std::map<K, V> m;            // キー・バリュー
std::multiset<int> ms;       // 重複を許すset
std::multimap<K, V> mm;      // 重複を許すmap

// 非順序連想コンテナ（ハッシュテーブル）
std::unordered_set<int> us;  // ハッシュセット
std::unordered_map<K, V> um; // ハッシュマップ（最速の検索）

// 選択基準:
// - ランダムアクセス必要 → vector
// - 両端挿入/削除が多い → deque
// - 中間挿入/削除が多い → list
// - キーでソート必要 → map/set
// - 検索速度重視（O(1)） → unordered_map/set
// - スタック/キュー → deque（または専用のstack/queue）
```

#### 1.0.6 型推論（auto, decltype）

```cpp
// auto: 変数の型を推論
auto x = 42;                    // int
auto y = 3.14;                  // double
auto s = std::string("hello");  // std::string
auto vec = std::vector<int>{};  // std::vector<int>

// const/参照の維持には明示的指定が必要
const auto& ref = vec;          // const std::vector<int>&
auto&& universal_ref = foo();   // ユニバーサル参照

// decltype: 式の型を取得
int a = 10;
decltype(a) b = 20;             // int b = 20;

// decltype(auto): 式の型をそのまま推論（C++14）
decltype(auto) get_value() {
    static int x = 42;
    return (x);  // int& を返す（括弧があるため）
}
```

**演習 1.0.1**: リソースを管理する RAII クラス（ソケットやファイル）を実装せよ。
**演習 1.0.2**: ムーブ専用型を作成し、`std::vector`に格納して動作確認せよ。
**演習 1.0.3**: ジェネリックラムダを使って、任意の型のコンテナをフィルタリングする関数を作れ。

---

### 1.1 構造化束縛（Structured Bindings）

**Rust との比較**: パターンマッチングの分解（destructuring）に相当

```cpp
// 基本形
auto [x, y] = std::make_pair(1, 2);

// mapのイテレーション
std::map<std::string, int> scores = {{"Alice", 100}, {"Bob", 85}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}

// 構造体の分解
struct Point { int x, y, z; };
Point p{1, 2, 3};
auto [px, py, pz] = p;
```

**演習 1.1.1**: 3D 空間の点（x, y, z）を表す構造体を作り、構造化束縛で分解して出力せよ。

**演習 1.1.2**: `std::map<std::string, std::tuple<int, int, int>>`（名前 →RGB 値）を作成し、構造化束縛でイテレーションせよ。

---

### 1.2 if/switch 初期化式

**Rust との比較**: `if let` に近い用途

```cpp
// 従来
auto it = map.find(key);
if (it != map.end()) {
    // use it
}

// C++17
if (auto it = map.find(key); it != map.end()) {
    // use it（itのスコープはこのif文内のみ）
}

// switchでも使える
switch (auto len = str.length(); len) {
    case 0: /* empty */ break;
    case 1: /* single char */ break;
    default: /* multiple */ break;
}
```

**演習 1.2.1**: キャッシュ（`std::unordered_map`）からデータを取得し、なければ計算して格納するコードを if 初期化式で書け。

---

### 1.3 クラステンプレート引数推論（CTAD）

```cpp
// C++14以前
std::pair<int, double> p1(1, 3.14);
std::vector<int> v1{1, 2, 3};

// C++17（型推論）
std::pair p2(1, 3.14);      // std::pair<int, double>
std::vector v2{1, 2, 3};    // std::vector<int>
std::tuple t(1, 2.0, "hi"); // std::tuple<int, double, const char*>
```

**注意点**: 自作クラスで CTAD を使うには推論ガイド（deduction guide）が必要な場合がある。

---

### 1.4 constexpr if

**Rust との比較**: ジェネリクス内での条件分岐（Rust ではトレイト境界で解決することが多い）

```cpp
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;  // 整数型の場合
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 2.5; // 浮動小数点の場合
    } else {
        return value; // その他
    }
}
```

**演習 1.4.1**: シリアライズ関数を作れ。整数型はそのままバイト列に、文字列型は長さ+データに、その他は`static_assert`でエラーにせよ。

---

### 1.5 fold expressions

**Rust との比較**: イテレータの`fold`に近いが、コンパイル時に展開される

```cpp
// 可変長引数の合計
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // 右畳み込み: a + (b + (c + d))
}

// 左畳み込み
template<typename... Args>
auto sum_left(Args... args) {
    return (... + args);  // 左畳み込み: ((a + b) + c) + d
}

// 初期値付き
template<typename... Args>
auto sum_init(Args... args) {
    return (0 + ... + args);
}

// すべてがtrueか判定
template<typename... Args>
bool all(Args... args) {
    return (args && ...);
}
```

**演習 1.5.1**: 任意個の文字列を連結する関数を作れ。
**演習 1.5.2**: 任意個の述語（predicate）を AND で結合する関数を作れ。

---

### 1.6 属性（Attributes）

```cpp
[[nodiscard]] int compute();  // 戻り値を無視すると警告

[[maybe_unused]] int debug_counter = 0;  // 未使用でも警告なし

switch (value) {
    case 1:
        do_something();
        [[fallthrough]];  // 意図的なフォールスルー
    case 2:
        do_other();
        break;
}

[[deprecated("Use newFunction() instead")]]
void oldFunction();
```

---

### 1.7 std::optional

**Rust との比較**: `Option<T>` に相当

```cpp
#include <optional>

std::optional<int> find_value(const std::vector<int>& v, int target) {
    for (int x : v) {
        if (x == target) return x;
    }
    return std::nullopt;  // Rustの None
}

// 使用方法
if (auto result = find_value(vec, 42); result) {
    std::cout << "Found: " << *result << "\n";
    // または result.value()
}

// value_or: Rustの unwrap_or
int val = find_value(vec, 42).value_or(-1);
```

**演習 1.7.1**: 設定ファイルのパーサーを作れ。キーが存在しない場合は`std::nullopt`を返すこと。

---

### 1.8 std::variant

**Rust との比較**: `enum`（タグ付きユニオン）に相当

```cpp
#include <variant>

using Value = std::variant<int, double, std::string>;

Value v = 42;
v = 3.14;
v = "hello";

// 型の取得
if (std::holds_alternative<int>(v)) {
    std::cout << std::get<int>(v);
}

// visit（Rustのmatchに相当）
std::visit([](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "int: " << arg;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "double: " << arg;
    } else {
        std::cout << "string: " << arg;
    }
}, v);

// overloadパターン（より洗練された方法）
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::visit(overloaded{
    [](int i) { std::cout << "int: " << i; },
    [](double d) { std::cout << "double: " << d; },
    [](const std::string& s) { std::cout << "string: " << s; }
}, v);
```

**演習 1.8.1**: ゲームイベント（`PlayerMoved{x,y}`, `ItemPickedUp{item_id}`, `DamageTaken{amount}`）を`std::variant`で表現し、イベントハンドラを実装せよ。

---

### 1.9 std::string_view

**Rust との比較**: `&str` に相当（所有しない文字列スライス）

```cpp
#include <string_view>

void print_info(std::string_view sv) {  // コピーなし
    std::cout << sv << " (length: " << sv.length() << ")\n";
}

std::string s = "Hello, World!";
print_info(s);              // std::stringから
print_info("literal");      // リテラルから
print_info(s.substr(0, 5)); // 部分文字列

// 注意: string_viewは元のデータを所有しない
std::string_view dangerous() {
    std::string local = "temporary";
    return local;  // ダングリング参照！
}
```

**演習 1.9.1**: CSV の 1 行をパースする関数を作れ。`std::string_view`を受け取り、`std::vector<std::string_view>`を返すこと。

---

### 1.10 std::filesystem

```cpp
#include <filesystem>
namespace fs = std::filesystem;

// パス操作
fs::path p = "/home/user/game/assets/texture.png";
std::cout << p.filename() << "\n";    // texture.png
std::cout << p.stem() << "\n";        // texture
std::cout << p.extension() << "\n";   // .png
std::cout << p.parent_path() << "\n"; // /home/user/game/assets

// ディレクトリ走査
for (const auto& entry : fs::recursive_directory_iterator("assets")) {
    if (entry.is_regular_file() && entry.path().extension() == ".png") {
        std::cout << entry.path() << " (" << entry.file_size() << " bytes)\n";
    }
}

// ファイル操作
fs::create_directories("output/textures");
fs::copy("src.txt", "dst.txt", fs::copy_options::overwrite_existing);
fs::remove("temp.txt");
```

**演習 1.10.1**: 指定ディレクトリ内の全画像ファイル（.png, .jpg, .bmp）を再帰的に検索し、合計サイズを計算するツールを作れ。

---

### 1.11 並列アルゴリズム

```cpp
#include <algorithm>
#include <execution>
#include <vector>

std::vector<int> data(10000000);

// 順次実行
std::sort(data.begin(), data.end());

// 並列実行
std::sort(std::execution::par, data.begin(), data.end());

// 並列ベクトル化（SIMDも使用）
std::sort(std::execution::par_unseq, data.begin(), data.end());

// 他のアルゴリズムも対応
std::for_each(std::execution::par, data.begin(), data.end(), [](int& x) { x *= 2; });
auto sum = std::reduce(std::execution::par, data.begin(), data.end());
```

**注意**: 並列実行ポリシーはコンパイラ/環境によってサポート状況が異なる。

---

### Phase 1 総合課題

**課題 P1-1: ミニアセットマネージャー**

以下の機能を持つアセット管理システムを作成せよ：

- 指定ディレクトリからアセットファイル（画像、音声、データ）を再帰的に検索
- アセット情報（パス、サイズ、種類）を`std::variant`で管理
- アセットのフィルタリング・ソート機能（並列アルゴリズム使用）
- 結果を`std::optional`で返す検索機能

---

## Phase 2: C++20 — パラダイムシフト

### 学習目標

C++20 の 4 大機能（Concepts, Ranges, Coroutines, Modules）を習得し、現代的な C++設計ができるようになる。

---

### 2.1 コンセプト（Concepts）

**Rust との比較**: トレイト境界（trait bounds）に相当

#### 2.1.1 基本構文

```cpp
#include <concepts>

// requires節（トレイト境界的な使い方）
template<typename T>
requires std::integral<T>
T double_value(T x) {
    return x * 2;
}

// 省略構文
template<std::integral T>
T triple_value(T x) {
    return x * 3;
}

// auto + コンセプト
std::integral auto quad_value(std::integral auto x) {
    return x * 4;
}
```

#### 2.1.2 標準コンセプト

```cpp
// 型カテゴリ
std::integral<T>       // 整数型
std::floating_point<T> // 浮動小数点型
std::signed_integral<T>
std::unsigned_integral<T>

// 比較
std::equality_comparable<T>
std::totally_ordered<T>

// オブジェクト
std::movable<T>
std::copyable<T>
std::regular<T>  // copyable + default_initializable + equality_comparable

// 呼び出し可能
std::invocable<F, Args...>
std::predicate<F, Args...>

// イテレータ/レンジ
std::input_iterator<I>
std::forward_iterator<I>
std::random_access_iterator<I>
std::ranges::range<R>
```

#### 2.1.3 自作コンセプト

```cpp
// requires式でコンセプトを定義
template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};

// 複合要件
template<typename T>
concept Number = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};

// 入れ子要件
template<typename T>
concept Container = requires(T c) {
    typename T::value_type;
    typename T::iterator;
    { c.begin() } -> std::input_iterator;
    { c.end() } -> std::input_iterator;
    { c.size() } -> std::convertible_to<std::size_t>;
};

// コンセプトの組み合わせ
template<typename T>
concept GameEntity = std::movable<T> && requires(T e) {
    { e.update(0.0f) } -> std::same_as<void>;
    { e.render() } -> std::same_as<void>;
    { e.get_position() } -> std::convertible_to<std::tuple<float, float, float>>;
};
```

**演習 2.1.1**: `Hashable`コンセプトを作れ（`std::hash<T>`が使用可能な型）。
**演習 2.1.2**: `Serializable`コンセプトを作れ（`serialize()`と`deserialize()`メソッドを持つ型）。
**演習 2.1.3**: ゲーム用の`Component`コンセプトを設計せよ。

---

### 2.2 レンジ（Ranges）

**Rust との比較**: イテレータアダプタ（`iter().map().filter()`）に相当

#### 2.2.1 基本

```cpp
#include <ranges>
#include <vector>

std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// パイプライン構文
auto result = nums
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; })
    | std::views::take(3);

// 遅延評価（この時点では計算されていない）
for (int x : result) {
    std::cout << x << " ";  // 4 16 36
}

// vectorに変換（C++23では std::ranges::to<std::vector>()）
std::vector<int> vec(result.begin(), result.end());
```

#### 2.2.2 主要なビュー

```cpp
// filter: 条件に合う要素のみ
auto evens = nums | std::views::filter([](int n) { return n % 2 == 0; });

// transform: 各要素を変換
auto squares = nums | std::views::transform([](int n) { return n * n; });

// take / drop
auto first_five = nums | std::views::take(5);
auto skip_three = nums | std::views::drop(3);

// take_while / drop_while
auto until_five = nums | std::views::take_while([](int n) { return n < 5; });

// reverse
auto reversed = nums | std::views::reverse;

// elements（tupleの特定要素）
std::vector<std::pair<int, std::string>> pairs = {{1, "a"}, {2, "b"}};
auto keys = pairs | std::views::keys;     // 1, 2
auto values = pairs | std::views::values; // "a", "b"

// iota（連番生成）
auto one_to_ten = std::views::iota(1, 11);
auto infinite = std::views::iota(0);  // 無限シーケンス

// split / join
std::string csv = "a,b,c,d";
for (auto word : csv | std::views::split(',')) {
    // 各要素を処理
}
```

#### 2.2.3 レンジアルゴリズム

```cpp
namespace ranges = std::ranges;

std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// ranges版アルゴリズム（イテレータペアの代わりにレンジを渡せる）
ranges::sort(v);
auto it = ranges::find(v, 5);
bool has_even = ranges::any_of(v, [](int n) { return n % 2 == 0; });

// プロジェクション（メンバへのアクセスを指定）
struct Player {
    std::string name;
    int score;
};
std::vector<Player> players = {{"Alice", 100}, {"Bob", 85}, {"Carol", 92}};

// scoreでソート
ranges::sort(players, {}, &Player::score);

// scoreが最大のプレイヤーを検索
auto max_player = ranges::max_element(players, {}, &Player::score);
```

**演習 2.2.1**: 文字列のリストから、5 文字以上のものだけを大文字に変換して取り出せ。
**演習 2.2.2**: ゲームのエンティティリストから、アクティブなもののみを距離でソートして最も近い 3 つを取得せよ。

---

### 2.3 コルーチン（Coroutines）

**Rust との比較**: `async/await` に相当するが、より低レベルで汎用的

#### 2.3.1 基本概念

```cpp
// コルーチンは以下のいずれかを含む関数
// - co_await: 非同期操作の待機
// - co_yield: 値を生成して中断
// - co_return: コルーチンを終了

// ジェネレータの例（簡易実装）
#include <coroutine>

template<typename T>
struct Generator {
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
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

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

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

// 使用例
Generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

// 呼び出し
for (int i : range(0, 10)) {
    std::cout << i << " ";
}
```

#### 2.3.2 非同期タスク（概念）

```cpp
// 非同期タスクの骨格（実際にはより複雑な実装が必要）
template<typename T>
struct Task {
    struct promise_type {
        T result;
        std::coroutine_handle<> continuation;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        auto final_suspend() noexcept {
            struct awaiter {
                std::coroutine_handle<> cont;
                bool await_ready() noexcept { return false; }
                std::coroutine_handle<> await_suspend(std::coroutine_handle<>) noexcept {
                    return cont ? cont : std::noop_coroutine();
                }
                void await_resume() noexcept {}
            };
            return awaiter{continuation};
        }
        void return_value(T value) { result = value; }
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;
};

// 使用イメージ
Task<int> async_compute() {
    co_return 42;
}

Task<int> async_main() {
    int result = co_await async_compute();
    co_return result * 2;
}
```

**演習 2.3.1**: フィボナッチ数列を生成するジェネレータを作れ。
**演習 2.3.2**: ファイルを 1 行ずつ読み込むジェネレータを作れ。

---

### 2.4 モジュール（Modules）

**Rust との比較**: `mod` / `use` に相当

#### 2.4.1 基本構文

```cpp
// math.ixx または math.cppm（モジュールインターフェースユニット）
export module math;

export int add(int a, int b) {
    return a + b;
}

export namespace geometry {
    struct Point {
        double x, y;
    };

    double distance(Point a, Point b);
}

// 非公開（exportなし）
int internal_helper() {
    return 42;
}
```

```cpp
// main.cpp
import math;

int main() {
    int sum = add(1, 2);
    geometry::Point p{0, 0};
}
```

#### 2.4.2 モジュールパーティション

```cpp
// math-impl.ixx（実装パーティション）
module math:impl;

int internal_detail() {
    return 100;
}

// math.ixx
export module math;
import :impl;

export int public_func() {
    return internal_detail() * 2;
}
```

**注意**: モジュールのビルドシステム対応は発展途上。CMake 3.28+で実験的サポート。

---

### 2.5 その他の C++20 機能

#### 2.5.1 std::span

**Rust との比較**: `&[T]`（スライス）に相当

```cpp
#include <span>

void process(std::span<int> data) {
    for (int& x : data) {
        x *= 2;
    }
}

std::vector<int> vec = {1, 2, 3, 4, 5};
std::array<int, 5> arr = {1, 2, 3, 4, 5};
int c_arr[] = {1, 2, 3, 4, 5};

process(vec);   // OK
process(arr);   // OK
process(c_arr); // OK

// 部分ビュー
process(std::span(vec).subspan(1, 3)); // 2, 3, 4 のみ
```

#### 2.5.2 std::format

**Rust との比較**: `format!`マクロに相当

```cpp
#include <format>

std::string s = std::format("Hello, {}!", "World");
std::string n = std::format("Value: {}, Hex: {:x}, Binary: {:b}", 42, 42, 42);
std::string f = std::format("Pi: {:.2f}", 3.14159);  // "Pi: 3.14"

// 位置指定
std::string p = std::format("{1} before {0}", "World", "Hello");

// 幅とアラインメント
std::string w = std::format("{:>10}", "test");  // "      test"
std::string l = std::format("{:<10}", "test");  // "test      "
std::string c = std::format("{:^10}", "test");  // "   test   "
```

#### 2.5.3 三方比較演算子（Spaceship Operator）

**Rust との比較**: `Ord`トレイトの`cmp`メソッドに相当

```cpp
#include <compare>

struct Point {
    int x, y;

    // これだけで <, >, <=, >=, ==, != がすべて生成される
    auto operator<=>(const Point&) const = default;
};

// カスタム実装
struct Version {
    int major, minor, patch;

    std::strong_ordering operator<=>(const Version& other) const {
        if (auto cmp = major <=> other.major; cmp != 0) return cmp;
        if (auto cmp = minor <=> other.minor; cmp != 0) return cmp;
        return patch <=> other.patch;
    }
    bool operator==(const Version&) const = default;
};
```

#### 2.5.4 consteval / constinit

```cpp
// consteval: 必ずコンパイル時に評価
consteval int compile_time_only(int x) {
    return x * x;
}

constexpr int a = compile_time_only(5);  // OK
// int b = compile_time_only(runtime_value);  // エラー

// constinit: 静的初期化を保証（初期化順序問題を防ぐ）
constinit int global = 42;  // 必ず静的初期化される
```

#### 2.5.5 指示付き初期化（Designated Initializers）

```cpp
struct Config {
    int width = 800;
    int height = 600;
    bool fullscreen = false;
    std::string title = "Game";
};

Config cfg = {
    .width = 1920,
    .height = 1080,
    .fullscreen = true
    // titleはデフォルト値のまま
};
```

#### 2.5.6 std::jthread / std::stop_token

```cpp
#include <thread>
#include <stop_token>

void worker(std::stop_token stoken) {
    while (!stoken.stop_requested()) {
        // 作業を続ける
    }
    // 停止要求を受けた
}

{
    std::jthread t(worker);
    // 何か処理...
}  // スコープを抜けると自動的にstop_request()してjoin()

// コールバック登録
std::jthread t([](std::stop_token stoken) {
    std::stop_callback callback(stoken, []() {
        std::cout << "Stop requested!\n";
    });
    // ...
});
```


#### 2.5.7 std::source_location（C++20）

デバッグ情報の取得（関数名、ファイル名、行番号）

```cpp
#include <source_location>

void log_message(const std::string& msg,
                 const std::source_location& loc = std::source_location::current()) {
    std::cout << "[" << loc.file_name() << ":" << loc.line()
              << " " << loc.function_name() << "] " << msg << "\n";
}

// 使用例
log_message("Starting process");
// 出力: [main.cpp:42 main] Starting process
```

#### 2.5.8 std::bit_cast（C++20）

型安全なビット再解釈

```cpp
#include <bit>

// 従来の危険な方法
float f = 3.14f;
uint32_t bits = *reinterpret_cast<uint32_t*>(&f);  // UB（未定義動作）

// C++20の安全な方法
float f = 3.14f;
uint32_t bits = std::bit_cast<uint32_t>(f);  // OK、型安全

// エンディアンの判定
if (std::endian::native == std::endian::little) {
    // リトルエンディアン環境
}
```

#### 2.5.9 std::any（C++17）

**Rust との比較**: `Box<dyn Any>` に相当

```cpp
#include <any>

std::any value = 42;
value = 3.14;
value = std::string("hello");

// 型チェックと取得
if (value.type() == typeid(std::string)) {
    std::string s = std::any_cast<std::string>(value);
    std::cout << s << "\n";
}

// 安全な取得（ポインタ版）
if (auto* str = std::any_cast<std::string>(&value)) {
    std::cout << *str << "\n";
}

// 型が違う場合は例外（std::bad_any_cast）
try {
    int x = std::any_cast<int>(value);  // valueがstringの場合は例外
} catch (const std::bad_any_cast& e) {
    std::cerr << e.what() << "\n";
}
```

**注意**: `std::any`は型安全だが、型情報が実行時まで分からないため、`std::variant`を使える場合はそちらを優先すべき。

---

### Phase 2 総合課題

**課題 P2-1: 型安全なイベントシステム**

コンセプトとテンプレートを使用して、型安全なイベントシステムを設計せよ：

- イベント型を制約するコンセプト
- イベントの購読・発行機能
- 優先度付きハンドラ

**課題 P2-2: データ処理パイプライン**

Ranges を使用して、ゲームデータの処理パイプラインを構築せよ：

- CSV からデータを読み込み
- フィルタリング・変換・集計
- 結果の出力

**課題 P2-3: 非同期リソースローダー**

コルーチンを使用して、非同期リソースローダーを実装せよ：

- ファイルの非同期読み込み
- 進捗の報告（yield）
- エラーハンドリング

---

## Phase 3: C++23 — 実用性の強化

### 学習目標

C++23 で追加された実用的な機能を習得し、より安全で表現力の高いコードを書けるようになる。

---

### 3.1 std::expected

**Rust との比較**: `Result<T, E>` に完全に相当

```cpp
#include <expected>

enum class ParseError {
    InvalidFormat,
    OutOfRange,
    Empty
};

std::expected<int, ParseError> parse_int(std::string_view sv) {
    if (sv.empty()) {
        return std::unexpected(ParseError::Empty);
    }
    // パース処理...
    return 42;  // 成功
}

// 使用方法
auto result = parse_int("123");

if (result) {
    std::cout << "Value: " << *result << "\n";
} else {
    switch (result.error()) {
        case ParseError::InvalidFormat:
            std::cout << "Invalid format\n";
            break;
        // ...
    }
}

// value_or
int val = parse_int("abc").value_or(-1);

// and_then（Rustのand_then/map相当）
auto doubled = parse_int("21")
    .and_then([](int x) -> std::expected<int, ParseError> {
        return x * 2;
    });

// transform（値を変換、エラーはそのまま）
auto as_string = parse_int("42")
    .transform([](int x) { return std::to_string(x); });
```

**演習 3.1.1**: ファイル読み込み関数を`std::expected`で実装せよ（エラー: FileNotFound, PermissionDenied, IoError）。
**演習 3.1.2**: 複数の`std::expected`を連鎖させるユーティリティ関数を作れ。

---

### 3.2 std::mdspan

**Rust との比較**: `ndarray`クレートの`ArrayView`に近い

```cpp
#include <mdspan>

// 2D配列のビュー
std::vector<int> data(12);
std::mdspan<int, std::extents<size_t, 3, 4>> matrix(data.data());

matrix[0, 0] = 1;
matrix[1, 2] = 5;
// matrix(row, col) でもアクセス可能

// 動的サイズ
std::mdspan<int, std::dextents<size_t, 2>> dynamic_matrix(data.data(), 3, 4);

// レイアウト指定
std::mdspan<int, std::extents<size_t, 3, 4>, std::layout_left> col_major(data.data());

// 3D以上も可能
std::vector<float> volume(1000);
std::mdspan<float, std::extents<size_t, 10, 10, 10>> cube(volume.data());
cube[5, 5, 5] = 1.0f;
```

**演習 3.2.1**: 画像データ（width × height × channels）を`std::mdspan`で扱い、グレースケール変換を実装せよ。

---

### 3.3 std::generator

```cpp
#include <generator>

std::generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        auto tmp = a;
        a = b;
        b = tmp + b;
    }
}

// 使用
for (int fib : fibonacci() | std::views::take(10)) {
    std::cout << fib << " ";
}
// 0 1 1 2 3 5 8 13 21 34

// ファイル読み込みジェネレータ
std::generator<std::string> read_lines(const std::filesystem::path& path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        co_yield line;
    }
}
```

---

### 3.4 std::print / std::println

```cpp
#include <print>

std::print("Hello, {}!\n", "World");
std::println("Value: {}", 42);  // 自動改行

// stderrへ出力
std::print(stderr, "Error: {}\n", "something went wrong");

// ファイルへ出力
std::ofstream file("output.txt");
std::print(file, "Data: {}\n", 123);
```

---

### 3.5 Deducing this（明示的オブジェクトパラメータ）

**Rust との比較**: `self`, `&self`, `&mut self` の明示的な受け取りに近い

```cpp
struct Widget {
    std::string name;

    // 従来: const/非constで2つのオーバーロードが必要だった
    // std::string& get_name() { return name; }
    // const std::string& get_name() const { return name; }

    // C++23: 1つで済む
    template<typename Self>
    auto&& get_name(this Self&& self) {
        return std::forward<Self>(self).name;
    }

    // メソッドチェーン（ビルダーパターン）で便利
    template<typename Self>
    auto&& set_name(this Self&& self, std::string n) {
        self.name = std::move(n);
        return std::forward<Self>(self);
    }
};

// CRTP（Curiously Recurring Template Pattern）の簡略化
struct Base {
    template<typename Self>
    void do_something(this Self&& self) {
        self.impl();  // 派生クラスのimpl()を呼ぶ
    }
};
```

---

### 3.6 std::flat_map / std::flat_set

```cpp
#include <flat_map>
#include <flat_set>

// 内部的にソート済みvectorで実装（キャッシュ効率が良い）
std::flat_map<std::string, int> scores;
scores["Alice"] = 100;
scores["Bob"] = 85;

std::flat_set<int> unique_ids;
unique_ids.insert(1);
unique_ids.insert(2);

// std::mapよりメモリ効率が良く、イテレーションが速い
// 挿入/削除は遅い（頻繁な更新がない場合に最適）
```

---

### 3.7 拡張された Ranges

```cpp
// zip: 複数のレンジを並行してイテレート
std::vector<int> ids = {1, 2, 3};
std::vector<std::string> names = {"Alice", "Bob", "Carol"};

for (auto [id, name] : std::views::zip(ids, names)) {
    std::cout << id << ": " << name << "\n";
}

// chunk: 指定サイズで分割
std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
for (auto chunk : data | std::views::chunk(3)) {
    // [1,2,3], [4,5,6], [7,8]
}

// slide: スライディングウィンドウ
for (auto window : data | std::views::slide(3)) {
    // [1,2,3], [2,3,4], [3,4,5], ...
}

// cartesian_product: 直積
std::vector<int> xs = {1, 2};
std::vector<int> ys = {10, 20};
for (auto [x, y] : std::views::cartesian_product(xs, ys)) {
    // (1,10), (1,20), (2,10), (2,20)
}

// ranges::to（コンテナへの変換）
auto vec = some_range | std::ranges::to<std::vector>();
```

---

### 3.8 std::stacktrace

```cpp
#include <stacktrace>

void debug_function() {
    auto st = std::stacktrace::current();
    std::cout << st << "\n";

    // 個別のフレームにアクセス
    for (const auto& entry : st) {
        std::cout << entry.source_file() << ":"
                  << entry.source_line() << " "
                  << entry.description() << "\n";
    }
}
```

---

### 3.9 import std;

```cpp
// 標準ライブラリ全体を一括インポート
import std;

int main() {
    std::vector<int> v = {1, 2, 3};
    std::println("Size: {}", v.size());
}
```

---

### Phase 3 総合課題

**課題 P3-1: 堅牢なコンフィグパーサー**

`std::expected`を使用して、型安全なコンフィグファイルパーサーを実装せよ：

- TOML/INI 形式のパース
- 詳細なエラー情報（行番号、エラー種別）
- `and_then`/`transform`チェーンによるデータ変換

**課題 P3-2: 画像処理ライブラリ**

`std::mdspan`を使用して、基本的な画像処理機能を実装せよ：

- 畳み込みフィルタ
- リサイズ
- 色空間変換

---

## Phase 4: C++26 — 最新動向

### 学習目標

策定中の C++26 の主要機能を理解し、将来の変化に備える。

---

### 4.1 静的リフレクション（Static Reflection）

**提案段階だが、最も革命的な機能**

```cpp
// 想定される構文（P2996）
struct Player {
    std::string name;
    int score;
    float health;
};

// メンバをコンパイル時に列挙
template<typename T>
void print_members() {
    constexpr auto members = std::meta::members_of(^T);
    [:expand(members):] >> [&]<auto M>() {
        std::println("{}: {}", std::meta::name_of(M), /* 値 */);
    };
}

// 自動シリアライズ
template<typename T>
std::string to_json(const T& obj) {
    std::string result = "{";
    constexpr auto members = std::meta::nonstatic_data_members_of(^T);
    // メンバを自動的に列挙してJSONに変換
    return result + "}";
}
```

**ゲーム開発への応用**:

- 自動シリアライズ/デシリアライズ
- エディタでのプロパティ自動表示
- スクリプトバインディングの自動生成

---

### 4.2 契約プログラミング（Contracts）

**Rust との比較**: `debug_assert!`に近いが、より体系的

```cpp
// 想定される構文
int divide(int a, int b)
    pre(b != 0)  // 事前条件
    post(r: r * b == a)  // 事後条件（rは戻り値）
{
    return a / b;
}

class Vector {
    int* data;
    size_t size;

public:
    int& operator[](size_t i)
        pre(i < size)  // 境界チェック
    {
        return data[i];
    }

    void push_back(int value)
        post(size == old(size) + 1)  // 古い値との比較
    {
        // ...
    }
};

// 契約違反時の動作はビルド設定で制御
// - ignore: 無視
// - observe: ログのみ
// - enforce: 例外/終了
```

---

### 4.3 std::execution（Senders/Receivers）

**非同期処理の標準化された抽象化**

```cpp
#include <execution>
namespace ex = std::execution;

// 基本的な使い方（概念的）
auto work = ex::schedule(scheduler)
    | ex::then([] { return compute(); })
    | ex::then([](int result) { return process(result); })
    | ex::upon_error([](auto error) { handle_error(error); });

ex::sync_wait(work);  // 完了を待つ

// 並列処理
auto parallel_work = ex::when_all(
    ex::schedule(scheduler) | ex::then(task1),
    ex::schedule(scheduler) | ex::then(task2),
    ex::schedule(scheduler) | ex::then(task3)
) | ex::then([](auto... results) {
    return combine(results...);
});
```

---

### 4.4 パターンマッチング（提案段階）

**Rust との比較**: `match`式に相当

```cpp
// 想定される構文（P2688等）
inspect (value) {
    0 => std::println("zero");
    1 | 2 | 3 => std::println("small");
    x if x < 10 => std::println("less than 10: {}", x);
    _ => std::println("other");
}

// 構造体の分解
inspect (point) {
    {.x = 0, .y = 0} => std::println("origin");
    {.x = x, .y = 0} => std::println("on x-axis at {}", x);
    {.x = 0, .y = y} => std::println("on y-axis at {}", y);
    {.x = x, .y = y} => std::println("at ({}, {})", x, y);
}

// variant
inspect (variant_value) {
    <int> i => std::println("int: {}", i);
    <std::string> s => std::println("string: {}", s);
    _ => std::println("other");
}
```

---

### 4.5 学習方法

1. **WG21 の提案書を読む**: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/
2. **Compiler Explorer で実験**: trunk 版の clang/gcc で実験
3. **CppCon の動画を視聴**: 最新の発表をチェック

---

## 横断的トピック（全 Phase 並行）

### T.1 テンプレートメタプログラミング

#### SFINAE → Concepts への移行

```cpp
// 旧: SFINAE
template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void old_style(T value);

// 新: Concepts
template<std::integral T>
void new_style(T value);
```

#### Type Traits

```cpp
#include <type_traits>

// 型の特性を調べる
static_assert(std::is_integral_v<int>);
static_assert(std::is_floating_point_v<double>);
static_assert(std::is_same_v<int, int>);
static_assert(std::is_base_of_v<Base, Derived>);

// 型を変換する
using NoRef = std::remove_reference_t<int&>;  // int
using NoConst = std::remove_const_t<const int>;  // int
using Decayed = std::decay_t<int[10]>;  // int*
```

---

### T.2 メモリモデルと並行性

#### std::atomic の詳細

```cpp
#include <atomic>

std::atomic<int> counter = 0;

// メモリオーダー
counter.fetch_add(1, std::memory_order_relaxed);  // 最も緩い
counter.fetch_add(1, std::memory_order_acquire);  // 読み込みバリア
counter.fetch_add(1, std::memory_order_release);  // 書き込みバリア
counter.fetch_add(1, std::memory_order_seq_cst);  // 最も厳格（デフォルト）

// compare_exchange
int expected = 0;
counter.compare_exchange_strong(expected, 1);
```

#### 同期プリミティブ（C++20）

```cpp
#include <latch>
#include <barrier>
#include <semaphore>

// latch: 一度だけカウントダウン
std::latch done(3);
// 各スレッドで done.count_down();
done.wait();  // カウントが0になるまで待機

// barrier: 再利用可能な同期ポイント
std::barrier sync_point(3, []() noexcept {
    // すべてのスレッドが到達したときに実行
});
sync_point.arrive_and_wait();

// semaphore: リソースへのアクセス制限
std::counting_semaphore<10> sem(10);
sem.acquire();  // カウントを減らして待機
sem.release();  // カウントを増やす
```

---

### T.3 データ指向設計（DOD）

#### SoA vs AoS

```cpp
// AoS（Array of Structures）- オブジェクト指向的
struct Entity_AoS {
    float x, y, z;
    float vx, vy, vz;
    int health;
    bool active;
};
std::vector<Entity_AoS> entities;

// SoA（Structure of Arrays）- データ指向的
struct Entities_SoA {
    std::vector<float> x, y, z;
    std::vector<float> vx, vy, vz;
    std::vector<int> health;
    std::vector<bool> active;
};

// SoAの方がキャッシュ効率が良い場合が多い
// 例: すべてのエンティティの位置を更新
void update_positions_soa(Entities_SoA& e, float dt) {
    // x, y, z, vx, vy, vz がメモリ上で連続
    for (size_t i = 0; i < e.x.size(); ++i) {
        e.x[i] += e.vx[i] * dt;
        e.y[i] += e.vy[i] * dt;
        e.z[i] += e.vz[i] * dt;
    }
}
```

#### キャッシュ効率を意識した設計

```cpp
// ホットデータとコールドデータを分離
struct EntityHot {  // 頻繁にアクセス
    float x, y, z;
    float vx, vy, vz;
};

struct EntityCold {  // まれにアクセス
    std::string name;
    int health;
    std::vector<int> inventory;
};

struct EntityRef {
    size_t hot_index;
    size_t cold_index;
};
```

---

## 進捗管理

### PROGRESS.md のフォーマット

```markdown
# 学習進捗

## 現在の Phase: Phase 1

## 完了したトピック

- [x] 1.1 構造化束縛
- [x] 1.2 if/switch 初期化式
- [ ] 1.3 CTAD

## 演習課題の状態

| 課題  | 状態   | メモ                 |
| ----- | ------ | -------------------- |
| 1.1.1 | 完了   | 構造体の分解         |
| 1.1.2 | 進行中 | map のイテレーション |

## 質問・疑問点

- Q: constexpr if と通常の if の使い分けは？
- A: （回答を記録）

## 次回のセッション

- 1.4 constexpr if から開始
- 演習 1.1.2 を完了させる
```

---

## 参考リソース

| リソース                                                            | 用途               |
| ------------------------------------------------------------------- | ------------------ |
| [cppreference.com](https://en.cppreference.com/)                    | 公式リファレンス   |
| [Compiler Explorer](https://godbolt.org/)                           | コンパイル確認     |
| [C++ Weekly](https://www.youtube.com/@cppweekly)                    | 機能解説動画       |
| [WG21 Papers](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/) | 標準化提案         |
| 『C++20: The Complete Guide』                                       | C++20 の決定版書籍 |
| 『A Tour of C++ (3rd Ed)』                                          | C++23 対応概観     |

### T.4 時間操作（std::chrono）

#### 時間の測定

```cpp
#include <chrono>

using namespace std::chrono;

// 時間計測
auto start = high_resolution_clock::now();
// 処理...
auto end = high_resolution_clock::now();

// 経過時間を取得
auto duration_ms = duration_cast<milliseconds>(end - start);
std::cout << "Elapsed: " << duration_ms.count() << "ms\n";

// 経過時間を秒単位で
auto duration_s = duration_cast<duration<double>>(end - start);
std::cout << "Elapsed: " << duration_s.count() << "s\n";
```

#### 時間リテラル（C++14）

```cpp
using namespace std::chrono_literals;

auto delay = 500ms;          // 500ミリ秒
auto timeout = 5s;           // 5秒
auto hour = 1h;              // 1時間
auto minute = 30min;         // 30分

// スリープ
std::this_thread::sleep_for(100ms);
```

#### ゲーム用タイマー

```cpp
class GameTimer {
    using clock = std::chrono::high_resolution_clock;
    using time_point = clock::time_point;

    time_point last_frame;
    double delta_time;

public:
    GameTimer() : last_frame(clock::now()), delta_time(0.0) {}

    void tick() {
        auto now = clock::now();
        auto duration = std::chrono::duration<double>(now - last_frame);
        delta_time = duration.count();
        last_frame = now;
    }

    double get_delta_time() const { return delta_time; }
    double get_fps() const { return 1.0 / delta_time; }
};
```

---

### T.5 正規表現（std::regex）

```cpp
#include <regex>

std::string text = "Email: test@example.com";
std::regex pattern(R"(\b\w+@\w+\.\w+\b)");

// 検索
if (std::regex_search(text, pattern)) {
    std::cout << "Email found\n";
}

// マッチ結果の取得
std::smatch match;
if (std::regex_search(text, match, pattern)) {
    std::cout << "Email: " << match[0] << "\n";
}

// 全体マッチ
std::string ip = "192.168.1.1";
std::regex ip_pattern(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})");
if (std::regex_match(ip, ip_pattern)) {
    std::cout << "Valid IP\n";
}

// 置換
std::string censored = std::regex_replace(text,
    std::regex(R"(\w+@)"), "****@");
// 結果: "Email: ****@example.com"

// イテレータで全マッチを取得
std::string log = "Error 404, Warning 200, Error 500";
std::regex code_pattern(R"(\d+)");
auto begin = std::sregex_iterator(log.begin(), log.end(), code_pattern);
auto end = std::sregex_iterator();

for (auto it = begin; it != end; ++it) {
    std::cout << "Code: " << it->str() << "\n";
}
```

**パフォーマンス注意**: `std::regex`はコンパイル時にパターンを処理するため、頻繁にパターンを変更する場合は遅い。可能な限りregexオブジェクトを再利用すること。

---

### T.6 値カテゴリ（Value Categories）

**C++の値カテゴリ（完全版）**

```
         expression
          /      \
      glvalue    rvalue
       /  \       /  \
  lvalue  xvalue  prvalue
```

#### 分類の説明

```cpp
// lvalue（left value）: 名前を持つオブジェクト
int x = 10;         // x は lvalue
int& ref = x;       // ref は lvalue

// prvalue（pure rvalue）: 一時オブジェクト
int y = 42;         // 42 は prvalue
std::string s = std::string("temp");  // std::string("temp") は prvalue

// xvalue（expiring value）: ムーブ元
int&& rref = std::move(x);  // std::move(x) は xvalue
std::vector<int> v = std::vector<int>{1, 2, 3};  // 右辺は xvalue

// glvalue（generalized lvalue）: lvalue または xvalue
// rvalue: prvalue または xvalue
```

#### 実用例

```cpp
template<typename T>
struct Widget {
    // lvalue参照: コピー
    void process(T& value) {
        std::cout << "lvalue\n";
    }

    // rvalue参照: ムーブ
    void process(T&& value) {
        std::cout << "rvalue\n";
    }
};

Widget<std::string> w;
std::string s = "hello";
w.process(s);                // lvalue版が呼ばれる
w.process(std::move(s));     // rvalue版が呼ばれる
w.process(std::string("hi")); // rvalue版が呼ばれる
```

---

### T.7 アルゴリズムライブラリ（主要関数）

モダンC++でよく使うアルゴリズム

```cpp
#include <algorithm>
#include <numeric>

std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// ソート
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), std::greater<>());  // 降順

// 検索
auto it = std::find(v.begin(), v.end(), 5);
auto it2 = std::find_if(v.begin(), v.end(), [](int n) { return n > 5; });

// 存在チェック
bool exists = std::any_of(v.begin(), v.end(), [](int n) { return n > 8; });
bool all_positive = std::all_of(v.begin(), v.end(), [](int n) { return n > 0; });

// 変換
std::vector<int> doubled(v.size());
std::transform(v.begin(), v.end(), doubled.begin(), [](int n) { return n * 2; });

// フィルタ（コピー）
std::vector<int> evens;
std::copy_if(v.begin(), v.end(), std::back_inserter(evens),
    [](int n) { return n % 2 == 0; });

// 削除（erase-removeイディオム）
v.erase(std::remove(v.begin(), v.end(), 1), v.end());

// 集計
int sum = std::accumulate(v.begin(), v.end(), 0);
int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());

// reduce（C++17、並列化可能）
int sum2 = std::reduce(std::execution::par, v.begin(), v.end());

// ユニーク化（重複削除）
std::sort(v.begin(), v.end());
v.erase(std::unique(v.begin(), v.end()), v.end());

// パーティション（条件で分割）
std::partition(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
// 結果: [偶数...][奇数...]
```

