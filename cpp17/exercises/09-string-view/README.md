# 1.9 std::string_view

## 概要

C++17で導入された`std::string_view`は、文字列を所有せずに参照する軽量なビューです。

**Rustとの比較**: `&str` に相当（所有しない文字列スライス）します。

```rust
// Rust
fn print_info(s: &str) {
    println!("{}", s);
}
```

```cpp
// C++17
void print_info(std::string_view sv) {
    std::cout << sv << "\n";
}
```

## 学習内容

1. **基本的な使い方**
   - string_viewの宣言と初期化
   - stringとの相互運用
   - 部分文字列の取得

2. **利点**
   - コピーが不要（パフォーマンス向上）
   - stringリテラル、string、char*から生成可能
   - 部分文字列の効率的な扱い

3. **注意点**
   - ダングリング参照の危険性
   - 元のデータを所有しない
   - nullポインタの扱い

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.9.1
CSVの1行をパースする関数を作れ。`std::string_view`を受け取り、`std::vector<std::string_view>`を返すこと。

## ビルド方法

```bash
mkdir build && cd build
cmake ..
make
./example
```

## 参考リンク

- [cppreference - std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view)
- [modern-cpp-curriculum.md セクション 1.9](../../../docs/modern-cpp-curriculum.md)
