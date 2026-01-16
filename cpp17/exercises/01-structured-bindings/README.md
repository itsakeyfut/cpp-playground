# 1.1 構造化束縛（Structured Bindings）

## 概要

C++17で導入された構造化束縛は、タプルや構造体、配列などを簡潔に分解できる機能です。

**Rustとの比較**: パターンマッチングの分解（destructuring）に相当します。

```rust
// Rust
let (x, y) = (1, 2);
```

```cpp
// C++17
auto [x, y] = std::make_pair(1, 2);
```

## 学習内容

1. **基本的な構造化束縛**
   - pair/tupleの分解
   - 構造体の分解
   - 配列の分解

2. **実用例**
   - mapのイテレーション
   - 複数の戻り値を受け取る

3. **注意点**
   - 参照の扱い
   - const修飾

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.1.1
3D空間の点(x, y, z)を表す構造体を作り、構造化束縛で分解して出力せよ。

### 演習 1.1.2
`std::map<std::string, std::tuple<int, int, int>>`（名前→RGB値）を作成し、構造化束縛でイテレーションせよ。

## ビルド方法

```bash
# cpp17/exercises/01-structured-bindings/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Structured binding](https://en.cppreference.com/w/cpp/language/structured_binding)
- [modern-cpp-curriculum.md セクション 1.1](../../../docs/modern-cpp-curriculum.md)

## 次のステップ

この演習を完了したら：
1. GitHubの Issue #1 をクローズ
2. 次の演習: [02-if-init](../02-if-init/)
