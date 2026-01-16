# 2.5 std::span

## 概要

C++20で導入された`std::span`は、連続したメモリ領域への非所有ビューを提供します。

**Rustとの比較**: `&[T]`（スライス）に相当します。

```rust
// Rust
fn process_data(data: &[i32]) {
    for &value in data {
        println!("{}", value);
    }
}

let vec = vec![1, 2, 3, 4, 5];
process_data(&vec);
```

```cpp
// C++20
void process_data(std::span<int> data) {
    for (int value : data) {
        std::cout << value << std::endl;
    }
}

std::vector<int> vec = {1, 2, 3, 4, 5};
process_data(vec);
```

**UE 5.7での重要度**: ★★★★☆（重要 - TArrayとの統合に便利）

## 学習内容

1. **基本的な使い方**
   - `std::span<T>` - 可変ビュー
   - `std::span<const T>` - 読み取り専用ビュー
   - コピー不要のビュー

2. **様々なコンテナとの互換性**
   - `std::vector`
   - `std::array`
   - C配列
   - TArray（UE）

3. **部分ビュー**
   - `subspan()` - 部分範囲の取得
   - `first()`, `last()` - 先頭/末尾のN個

4. **UE 5.7での応用**
   - TArrayの効率的な受け渡し
   - コピーなしのデータ処理
   - メモリ安全性の向上

## ファイル

- **example.cpp**: 完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.5.1: 配列処理関数
`std::span`を使って、様々な種類の配列を処理できる汎用関数を作成せよ。

要件:
- `std::vector`, `std::array`, C配列のすべてに対応
- 要素の合計を計算
- 平均値を計算

### 演習 2.5.2: TArray風のコンテナとの統合
UEの`TArray`風のコンテナと`std::span`を組み合わせた処理を実装せよ。

要件:
- `std::vector`を`TArray`の代わりに使用
- `std::span`で効率的にデータを受け渡す
- 部分範囲の処理（`subspan`使用）

## ビルド方法

```bash
# cpp20/exercises/05-span/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - std::span](https://en.cppreference.com/w/cpp/container/span)
- [modern-cpp-curriculum.md セクション 2.5.1](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md セクション 4](../../../docs/unreal-engine-cpp20-guide.md)

## 次のステップ

この演習を完了したら：
1. Phase 2（C++20）の学習を振り返る
2. より高度なC++機能（Phase 3）に進む
