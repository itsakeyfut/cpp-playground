# Clang-Tidy について

## Clang-Tidy とは

**Clang-Tidy**は、C++コードの静的解析ツールです。LLVMプロジェクトの一部で、コードの潜在的なバグ、スタイル違反、パフォーマンス問題、モダンC++への移行機会などを検出します。

**clang-format**がコードの**見た目**を整えるのに対し、**clang-tidy**はコードの**品質と安全性**を向上させます。

## なぜ使うのか

### 検出できる問題

1. **バグと潜在的エラー**
   - 初期化されていない変数の使用
   - メモリリーク
   - バッファオーバーフロー
   - use-after-free（解放後使用）
   - null pointer dereference

2. **パフォーマンス問題**
   - 不要なコピー
   - 非効率的なアルゴリズム
   - 最適化の機会

3. **モダンC++への移行**
   - 生ポインタ → スマートポインタ
   - `NULL` → `nullptr`
   - C形式キャスト → C++キャスト
   - ループ → 範囲ベースfor

4. **スタイルとベストプラクティス**
   - Google C++ Style Guide準拠
   - C++ Core Guidelines準拠
   - 命名規則の一貫性

## 基本的な使い方

### コマンドライン

```bash
# 単一ファイルをチェック
clang-tidy main.cpp

# コンパイルデータベースを使用（推奨）
clang-tidy main.cpp -- -std=c++20

# 自動修正を適用
clang-tidy -fix main.cpp

# 特定のチェックのみ実行
clang-tidy -checks="-*,modernize-*" main.cpp
```

### CMakeとの統合

このプロジェクトでは、CMakeビルド時にClang-Tidyを自動実行できます：

```bash
# Clang-Tidyを有効にしてビルド
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build

# 警告をエラーとして扱う（厳格モード）
cmake -B build -DENABLE_CLANG_TIDY=ON -DENABLE_WARNINGS_AS_ERRORS=ON
cmake --build build
```

## このプロジェクトの設定

`.clang-tidy`ファイルで以下のチェックカテゴリを有効にしています：

### 有効なチェックカテゴリ

#### 1. `bugprone-*` - バグ検出
潜在的なバグやエラーを検出します。

**例：**
```cpp
// NG: 初期化されていない変数
int x;
std::cout << x;  // bugprone-uninitialized

// OK: 初期化する
int x = 0;
std::cout << x;
```

#### 2. `cert-*` - CERT C++ Coding Standard
セキュアコーディング標準に準拠します。

**例：**
```cpp
// NG: 安全でないキャスト
char* ptr = (char*)malloc(100);  // cert-err34-c

// OK: C++のキャストを使用
auto ptr = static_cast<char*>(malloc(100));
```

#### 3. `cppcoreguidelines-*` - C++ Core Guidelines
C++の公式ガイドラインに準拠します。

**例：**
```cpp
// NG: 生ポインタでの所有権管理
int* ptr = new int(42);
delete ptr;

// OK: スマートポインタを使用
auto ptr = std::make_unique<int>(42);
// 自動でメモリ解放
```

#### 4. `google-*` - Google C++ Style Guide
Googleのスタイルガイドに準拠します。

**例：**
```cpp
// NG: Google style違反の命名
class myClass {  // google-readability-namespace-comments
    int MyVar;   // google-readability-naming
};

// OK: Google styleに準拠
class MyClass {
    int my_var_;  // メンバ変数は末尾にアンダースコア
};
```

#### 5. `modernize-*` - モダンC++への移行
古いC++をモダンなC++に更新します。

**例：**
```cpp
// NG: 古いC++
int* ptr = NULL;  // modernize-use-nullptr
for (int i = 0; i < vec.size(); i++) {  // modernize-loop-convert
    std::cout << vec[i];
}

// OK: モダンC++
int* ptr = nullptr;
for (const auto& item : vec) {
    std::cout << item;
}
```

#### 6. `performance-*` - パフォーマンス最適化
パフォーマンス改善の機会を検出します。

**例：**
```cpp
// NG: 不要なコピー
void Process(std::string str) {  // performance-unnecessary-value-param
    // ...
}

// OK: const参照で受け取る
void Process(const std::string& str) {
    // ...
}
```

#### 7. `readability-*` - 可読性の向上
コードの可読性を向上させます。

**例：**
```cpp
// NG: マジックナンバー
if (speed > 100) {  // readability-magic-numbers
    // ...
}

// OK: 名前付き定数
const int kMaxSpeed = 100;
if (speed > kMaxSpeed) {
    // ...
}
```

### 命名規則（Google Style）

このプロジェクトでは、Googleの命名規則を適用しています：

```cpp
// namespace: lower_case
namespace my_namespace {

// Class/Struct/Enum: CamelCase
class MyClass {
public:
    // Function: CamelCase
    void DoSomething();

    // Member variable: lower_case with trailing underscore
    int member_variable_;

private:
    // Private member
    std::string private_member_;
};

// Constant: CamelCase with 'k' prefix
const int kMaxSize = 100;
const std::string kDefaultName = "default";

// Enum: CamelCase
enum class Color {
    kRed,    // Enum constant: CamelCase with 'k' prefix
    kGreen,
    kBlue
};

// Variable/Parameter: lower_case
int local_variable = 42;
void Function(int parameter_name) {
    // ...
}

}  // namespace my_namespace
```

### 無効化したチェック

以下のチェックは実用上の理由で無効化しています：

- `readability-magic-numbers`: マジックナンバーの警告（過剰に厳しいため）
- `modernize-use-trailing-return-type`: 後置戻り値型の強制（好みの問題）
- `bugprone-easily-swappable-parameters`: 入れ替わりやすいパラメータ（誤検出が多い）

## 実際の使用例

### 例1: 初期化されていない変数

```cpp
// 元のコード（危険）
void ProcessData() {
    int result;
    if (condition) {
        result = 42;
    }
    std::cout << result;  // 初期化されていない可能性
}

// Clang-Tidy警告:
// warning: variable 'result' is used uninitialized [bugprone-uninitialized]

// 修正後
void ProcessData() {
    int result = 0;  // 初期化する
    if (condition) {
        result = 42;
    }
    std::cout << result;
}
```

### 例2: メモリ管理

```cpp
// 元のコード（危険）
void LoadData() {
    int* data = new int[100];
    // ... 処理 ...
    // delete[] を忘れている！メモリリーク
}

// Clang-Tidy警告:
// warning: use of owning raw pointer [cppcoreguidelines-owning-memory]

// 修正後
void LoadData() {
    auto data = std::make_unique<int[]>(100);
    // ... 処理 ...
    // 自動でメモリ解放される
}
```

### 例3: パフォーマンス

```cpp
// 元のコード（非効率）
void PrintVector(std::vector<std::string> vec) {  // コピーが発生
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << "\n";
    }
}

// Clang-Tidy警告:
// warning: unnecessary copy [performance-unnecessary-value-param]
// warning: use range-based for loop [modernize-loop-convert]

// 修正後
void PrintVector(const std::vector<std::string>& vec) {  // const参照
    for (const auto& item : vec) {  // 範囲ベースfor
        std::cout << item << "\n";
    }
}
```

## 他のツールとの組み合わせ

### 完全な安全性チェーン

```bash
# 1. フォーマットチェック（スタイル統一）
clang-format --dry-run -Werror src/**/*.cpp

# 2. 静的解析（バグ検出）
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build

# 3. コンパイラ警告（厳格）
cmake -B build -DENABLE_WARNINGS_AS_ERRORS=ON
cmake --build build

# 4. サニタイザー（実行時チェック）
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build
./build/my_program
```

### CI/CDパイプラインでの活用

```yaml
# .github/workflows/ci.yml (例)
- name: Static Analysis
  run: |
    cmake -B build -DENABLE_CLANG_TIDY=ON -DENABLE_WARNINGS_AS_ERRORS=ON
    cmake --build build

- name: Run with Sanitizers
  run: |
    cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
    cmake --build build
    ./build/tests
```

## よくある質問

### Q: Clang-Tidyは遅いですか？

A: はい、コンパイル時間が2-3倍になることがあります。開発時は無効にし、CIやコミット前に有効化する運用が一般的です。

### Q: 全ての警告を修正すべきですか？

A: 理想的には全て修正すべきですが、既存のコードベースでは段階的に対応することも現実的です。新規コードは必ず対応しましょう。

### Q: 特定の警告を無効化したい場合は？

A: コード内でコメントを使用できます：

```cpp
// NOLINTNEXTLINE(modernize-use-trailing-return-type)
int MyFunction() {
    return 42;
}
```

## References

- [Clang-Tidy 公式ドキュメント](https://clang.llvm.org/extra/clang-tidy/)
- [Clang-Tidy Checks リスト](https://clang.llvm.org/extra/clang-tidy/checks/list.html)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [CERT C++ Coding Standard](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=88046682)
