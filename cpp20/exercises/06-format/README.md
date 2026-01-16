# 2.5.2 std::format（フォーマット文字列）

## 概要

C++20で導入されたstd::formatは、型安全で使いやすい文字列フォーマット機能です。

**Rustとの比較**: `format!`マクロに相当します。

```rust
// Rust
let s = format!("Hello, {}!", "World");
let n = format!("Value: {}, Hex: {:x}", 42, 42);
```

```cpp
// C++20
auto s = std::format("Hello, {}!", "World");
auto n = std::format("Value: {}, Hex: {:x}", 42, 42);
```

**Unreal Engineとの関連**: UEには`FString::Printf`がありますが、`std::format`の方が型安全です。優先度は低めです。

## 学習内容

1. **基本的なフォーマット**
   - プレースホルダー `{}`
   - 位置指定
   - 型の自動推論

2. **フォーマット指定子**
   - 数値フォーマット（進数、小数点）
   - 幅とアライメント
   - パディング

3. **カスタム型のフォーマット**
   - std::formatter特殊化
   - ゲーム用の型（Vector, Color等）

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.5.2.1
基本的な数値フォーマット（整数、浮動小数点、16進数、2進数）を試せ。

### 演習 2.5.2.2
テーブル形式の出力（名前、スコア、ランクを整列）を作成せよ。

### 演習 2.5.2.3
カスタム型（Point3D）用のフォーマッターを実装せよ。

## ビルド方法

```bash
# cpp20/exercises/06-format/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 注意事項

**コンパイラサポート**: std::formatは比較的新しい機能です。
- GCC 13+
- Clang 14+ (libc++は16+)
- MSVC 19.29+ (Visual Studio 2019 16.10+)

サポートされていない場合は、{fmt}ライブラリを使用できます。

## 参考リンク

- [cppreference - std::format](https://en.cppreference.com/w/cpp/utility/format/format)
- [modern-cpp-curriculum.md セクション 2.5.2](../../../docs/modern-cpp-curriculum.md)
- [{fmt} library](https://fmt.dev/) - std::formatの元になったライブラリ

## 次のステップ

この演習を完了したら：
1. 次の演習: [07-three-way-comparison](../07-three-way-comparison/)
