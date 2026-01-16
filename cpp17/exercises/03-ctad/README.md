# 1.3 クラステンプレート引数推論（CTAD: Class Template Argument Deduction）

## 概要

C++17で導入されたクラステンプレート引数推論（CTAD）により、コンストラクタの引数からテンプレート引数を自動推論できるようになりました。

**Rustとの比較**: Rustでは型推論が標準的に機能しますが、C++17以前はクラステンプレートで明示的な型指定が必要でした。

```rust
// Rust（型推論が自然に動く）
let v = vec![1, 2, 3];
```

```cpp
// C++14以前
std::vector<int> v{1, 2, 3};

// C++17（型推論）
std::vector v{1, 2, 3};  // std::vector<int>が推論される
```

## 学習内容

1. **標準ライブラリでのCTAD**
   - std::pair, std::vector, std::tuple
   - 型推論の仕組み

2. **カスタムクラスでのCTAD**
   - 推論ガイド（deduction guide）の作成
   - 暗黙的な推論

3. **実用例**
   - コードの簡潔化
   - テンプレートコードの可読性向上

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.3.1
推論ガイドを持つカスタムクラスを作成せよ。以下の要件を満たすこと：
- クラステンプレート `Container<T>` を定義
- コンストラクタから型を推論できるようにする
- 推論ガイドを追加して、イテレータのペアから要素型を推論

## ビルド方法

```bash
# cpp17/exercises/03-ctad/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Class template argument deduction](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)
- [modern-cpp-curriculum.md セクション 1.3](../../../docs/modern-cpp-curriculum.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [04-constexpr-if](../04-constexpr-if/)
