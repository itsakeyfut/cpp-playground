# 2.2 レンジ（Ranges）

## 概要

C++20で導入されたレンジライブラリは、コレクション操作を関数型プログラミング風に記述できる機能です。

**Rustとの比較**: イテレータアダプタ（`iter().map().filter()`）に相当します。

```rust
// Rust
let result: Vec<_> = vec![1, 2, 3, 4, 5, 6]
    .into_iter()
    .filter(|&n| n % 2 == 0)
    .map(|n| n * n)
    .take(2)
    .collect();
```

```cpp
// C++20
auto result = vec
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; })
    | std::views::take(2);
```

**UE 5.7での重要度**: ★★★★★（最優先）

## 学習内容

1. **パイプライン構文**
   - `|` 演算子でビューを連結
   - 遅延評価の仕組み

2. **主要なビュー**
   - `filter`, `transform`, `take`, `drop`
   - `reverse`, `keys`, `values`
   - `take_while`, `drop_while`

3. **レンジアルゴリズム**
   - `std::ranges::sort`, `std::ranges::find`
   - プロジェクション（メンバへのアクセス指定）

4. **UE 5.7での応用**
   - TArrayの操作
   - Actorのフィルタリング
   - 距離ベースのソート

## ファイル

- **example.cpp**: 完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.2.1: 文字列のフィルタリングと変換
文字列のリストから、5文字以上のものだけをフィルタリングし、大文字に変換して出力せよ。

### 演習 2.2.2: ゲームエンティティの処理
ゲームのエンティティリストから、アクティブなもののみをフィルタリングし、
距離でソートして最も近い3つを取得せよ。

要件:
- Entity構造体（active状態、position）を定義
- プレイヤー位置からの距離を計算
- std::ranges::sortとプロジェクションを使用

## ビルド方法

```bash
# cpp20/exercises/02-ranges/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Ranges](https://en.cppreference.com/w/cpp/ranges)
- [modern-cpp-curriculum.md セクション 2.2](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md](../../../docs/unreal-engine-cpp20-guide.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [03-coroutines](../03-coroutines/)
