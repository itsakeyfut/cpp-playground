# 1.4 constexpr if

## 概要

C++17で導入された`constexpr if`は、コンパイル時の条件分岐を可能にします。テンプレート内で型に応じた処理の切り替えが簡潔に書けるようになりました。

**Rustとの比較**: Rustではトレイト境界や`where`句で型による分岐を実現しますが、C++の`constexpr if`は同一関数内でコンパイル時に条件分岐できます。

```rust
// Rust（トレイト境界で分岐）
fn process<T: Display>(value: T) {
    println!("{}", value);
}
```

```cpp
// C++17（constexpr ifで分岐）
template<typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // 整数型の処理
    } else if constexpr (std::is_floating_point_v<T>) {
        // 浮動小数点型の処理
    }
}
```

## 学習内容

1. **基本的なconstexpr if**
   - 型による条件分岐
   - コンパイル時評価

2. **型特性（Type Traits）との組み合わせ**
   - std::is_integral_v
   - std::is_floating_point_v
   - std::is_same_v

3. **実用例**
   - シリアライゼーション
   - 型に応じた最適化

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.4.1
シリアライゼーション関数を作成せよ：
- 整数型: バイト列として出力
- 文字列型: 長さ + データとして出力
- その他の型: `static_assert`でコンパイルエラー

## ビルド方法

```bash
# cpp17/exercises/04-constexpr-if/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - if statement](https://en.cppreference.com/w/cpp/language/if)
- [modern-cpp-curriculum.md セクション 1.4](../../../docs/modern-cpp-curriculum.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [05-fold-expressions](../05-fold-expressions/)
