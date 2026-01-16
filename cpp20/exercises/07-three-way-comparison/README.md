# 2.5.3 三方比較演算子（Spaceship Operator <=>）

## 概要

C++20で導入された三方比較演算子（<=>）は、1つの演算子で全ての比較演算子を自動生成できる機能です。

**Rustとの比較**: `Ord`トレイトの`cmp`メソッドに相当します。

```rust
// Rust
use std::cmp::Ordering;

impl Ord for Point {
    fn cmp(&self, other: &Self) -> Ordering {
        self.x.cmp(&other.x)
            .then(self.y.cmp(&other.y))
    }
}
```

```cpp
// C++20
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
};
```

**Unreal Engineとの関連**: UEのカスタム型（FVersion等）での比較実装に便利です。

## 学習内容

1. **基本的な三方比較**
   - `= default`での自動生成
   - 全ての比較演算子（<, >, <=, >=, ==, !=）が自動生成される

2. **比較カテゴリ**
   - `std::strong_ordering`: 全順序（例: 整数）
   - `std::weak_ordering`: 弱順序（例: 大文字小文字を無視した文字列）
   - `std::partial_ordering`: 部分順序（例: 浮動小数点数、NaN対応）

3. **カスタム実装**
   - 独自の比較ロジック
   - 複数フィールドの比較
   - ゲーム用の型（バージョン、優先度等）

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.5.3.1
基本的な構造体に三方比較演算子を実装し、全ての比較演算子が動作することを確認せよ。

### 演習 2.5.3.2
バージョン管理用の構造体（major, minor, patch）を作成し、適切な比較ロジックを実装せよ。

### 演習 2.5.3.3
UEスタイルのFVersion型を作成し、三方比較演算子を実装せよ。

## ビルド方法

```bash
# cpp20/exercises/07-three-way-comparison/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Three-way comparison](https://en.cppreference.com/w/cpp/language/default_comparisons)
- [cppreference - std::strong_ordering](https://en.cppreference.com/w/cpp/utility/compare/strong_ordering)
- [modern-cpp-curriculum.md セクション 2.5.3](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md セクション 8](../../../docs/unreal-engine-cpp20-guide.md)

## Unreal Engine 5.7での使用例

```cpp
// UE 5.7でのバージョン比較
USTRUCT()
struct FVersion {
    UPROPERTY()
    int32 Major;

    UPROPERTY()
    int32 Minor;

    UPROPERTY()
    int32 Patch;

    auto operator<=>(const FVersion&) const = default;
};

// 使用例
FVersion V1{1, 2, 3};
FVersion V2{1, 2, 4};

if (V1 < V2) {  // 自動的に比較可能
    UE_LOG(LogTemp, Log, TEXT("V1 is older"));
}
```

## 次のステップ

この演習を完了したら：
1. 次の演習: [08-constexpr-extensions](../08-constexpr-extensions/)
