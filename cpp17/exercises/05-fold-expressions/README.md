# 1.5 Fold Expressions（畳み込み式）

## 概要

C++17で導入されたFold Expressionsは、可変長テンプレート引数に対する演算をコンパイル時に展開します。

**Rustとの比較**: Rustの`fold`メソッドは実行時の畳み込みですが、C++のfold expressionsはコンパイル時に展開される点が異なります。

```rust
// Rust（実行時の畳み込み）
let sum = vec![1, 2, 3, 4].iter().fold(0, |acc, x| acc + x);
```

```cpp
// C++17（コンパイル時の畳み込み）
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // 右畳み込み
}
```

## 学習内容

1. **基本的なFold Expressions**
   - 右畳み込み（Right Fold）
   - 左畳み込み（Left Fold）
   - 初期値付き畳み込み

2. **様々な演算子**
   - 算術演算（+, -, *, /）
   - 論理演算（&&, ||）
   - カンマ演算子

3. **実用例**
   - 可変長引数の合計
   - 文字列連結
   - 述語の結合

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.5.1
任意個の文字列を連結する関数を作成せよ。

### 演習 1.5.2
任意個の述語（predicate）をANDで結合する関数を作成せよ。

## ビルド方法

```bash
# cpp17/exercises/05-fold-expressions/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Fold expression](https://en.cppreference.com/w/cpp/language/fold)
- [modern-cpp-curriculum.md セクション 1.5](../../../docs/modern-cpp-curriculum.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [06-attributes](../06-attributes/)
