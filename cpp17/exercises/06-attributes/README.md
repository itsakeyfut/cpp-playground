# 1.6 Attributes（属性）

## 概要

C++11以降、属性（attributes）を使ってコンパイラに追加情報を提供できます。C++17ではいくつかの重要な属性が標準化されました。

**Rustとの比較**: Rustの`#[derive]`、`#[allow]`、`#[deprecated]`などの属性に相当します。

```rust
// Rust
#[deprecated(since = "1.0.0", note = "use new_function instead")]
fn old_function() {}

#[allow(dead_code)]
fn unused_function() {}
```

```cpp
// C++17
[[deprecated("use new_function instead")]]
void old_function() {}

[[maybe_unused]]
void unused_function() {}
```

## 学習内容

1. **主要な属性**
   - `[[nodiscard]]`: 戻り値の無視を警告
   - `[[maybe_unused]]`: 未使用警告を抑制
   - `[[fallthrough]]`: 意図的なfall-through
   - `[[deprecated]]`: 非推奨マーク

2. **属性の使い方**
   - 関数への適用
   - 変数への適用
   - 型への適用

3. **実用例**
   - エラー検出の強化
   - コードの意図を明確化

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

各属性を使った簡単な演習を行います：
- `[[nodiscard]]`を使ったエラーハンドリング
- `[[deprecated]]`を使った移行警告
- `[[maybe_unused]]`を使ったデバッグコード

## ビルド方法

```bash
# cpp17/exercises/06-attributes/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - C++ attribute](https://en.cppreference.com/w/cpp/language/attributes)
- [modern-cpp-curriculum.md セクション 1.6](../../../docs/modern-cpp-curriculum.md)

## 次のステップ

この演習を完了したら：
1. Phase 1の他の演習に進む
2. [std::optional](../07-optional/)（追加課題）
