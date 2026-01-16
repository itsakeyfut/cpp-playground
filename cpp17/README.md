# Phase 1: C++17学習教材

Phase 1では、C++17の主要機能を10個の演習を通じて学習します。

## 📚 演習一覧

| # | トピック | Issue | 優先度 |
|---|---------|-------|--------|
| 01 | [構造化束縛](exercises/01-structured-bindings/) | [#1](https://github.com/itsakeyfut/cpp-playground/issues/1) | ⭐⭐⭐ |
| 02 | [if/switch初期化式](exercises/02-if-init/) | [#2](https://github.com/itsakeyfut/cpp-playground/issues/2) | ⭐⭐⭐ |
| 03 | [CTAD](exercises/03-ctad/) | [#3](https://github.com/itsakeyfut/cpp-playground/issues/3) | ⭐⭐ |
| 04 | [constexpr if](exercises/04-constexpr-if/) | [#4](https://github.com/itsakeyfut/cpp-playground/issues/4) | ⭐⭐⭐ |
| 05 | [fold expressions](exercises/05-fold-expressions/) | [#5](https://github.com/itsakeyfut/cpp-playground/issues/5) | ⭐⭐ |
| 06 | [属性](exercises/06-attributes/) | [#6](https://github.com/itsakeyfut/cpp-playground/issues/6) | ⭐ |
| 07 | [std::optional](exercises/07-optional/) | [#7](https://github.com/itsakeyfut/cpp-playground/issues/7) | ⭐⭐⭐ |
| 08 | [std::variant](exercises/08-variant/) | [#8](https://github.com/itsakeyfut/cpp-playground/issues/8) | ⭐⭐⭐ |
| 09 | [std::string_view](exercises/09-string-view/) | [#9](https://github.com/itsakeyfut/cpp-playground/issues/9) | ⭐⭐⭐ |
| 10 | [std::filesystem](exercises/10-filesystem/) | [#10](https://github.com/itsakeyfut/cpp-playground/issues/10) | ⭐⭐⭐ |

## 🚀 クイックスタート

### 方法1: 個別の演習をビルド

```bash
cd exercises/01-structured-bindings
mkdir build && cd build
cmake ..
cmake --build . --config Release

# 実行
./Release/example.exe    # サンプルコードを見る
./Release/exercise.exe   # 演習に取り組む
./Release/solution.exe   # 解答例を確認
```

### 方法2: 全演習を一括ビルド

```bash
# cpp17/ ディレクトリで
mkdir build && cd build
cmake ..
cmake --build . --config Release

# 実行
./exercises/01-structured-bindings/Release/example.exe
```

## 📖 学習の流れ

### ステップ1: 写経（example.cpp）
まずサンプルコードを実行して動作を確認します。その後、コードを見ながら（または写経しながら）理解を深めます。

```bash
# サンプルを実行
./Release/example.exe

# コードを確認・写経
code example.cpp  # or vim, notepad++, etc.
```

### ステップ2: 演習（exercise.cpp）
TODOコメントを埋めて、自分で実装します。

```cpp
// TODO: 構造化束縛を使って、x, y, z を分解してください
// ヒント: auto [変数1, 変数2, 変数3] = p;
```

### ステップ3: 答え合わせ（solution.cpp）
自分の実装と解答例を比較します。

## 🎯 推奨学習順序

### 優先度：高（必ず学ぶ）⭐⭐⭐
1. 構造化束縛
2. if/switch初期化式
4. constexpr if
7. std::optional
8. std::variant
9. std::string_view
10. std::filesystem

### 優先度：中（推奨）⭐⭐
3. CTAD
5. fold expressions

### 優先度：低（余裕があれば）⭐
6. 属性

## 📁 ファイル構成

各演習ディレクトリには以下のファイルがあります：

```
01-structured-bindings/
├── README.md           # 詳細説明・Rustとの比較
├── example.cpp         # 写経用サンプル（完全動作）
├── exercise.cpp        # 演習テンプレート（TODOあり）
├── solution.cpp        # 解答例
└── CMakeLists.txt      # ビルド設定
```

## 🔧 要件

- **C++17対応コンパイラ**
  - GCC 7.0以上
  - Clang 5.0以上
  - MSVC 2017以上（Visual Studio 2017）

- **CMake 3.20以上**

## 💡 Rustユーザーへのヒント

C++17の機能をRustの概念と対応させて理解できます：

| C++17 | Rust |
|-------|------|
| `std::optional<T>` | `Option<T>` |
| `std::variant<A, B>` | `enum { A, B }` |
| `std::string_view` | `&str` |
| 構造化束縛 | パターンマッチング |

## ❓ トラブルシューティング

### Windows: 日本語が文字化けする

CMakeLists.txtに`/utf-8`フラグが含まれていることを確認してください：

```cmake
if(MSVC)
    add_compile_options(/W4 /utf-8)
endif()
```

### ビルドエラーが発生する

```bash
# ビルドディレクトリを削除して再ビルド
rm -rf build
mkdir build && cd build
cmake ..
cmake --build . --config Release --verbose
```

## 🎓 次のステップ

Phase 1を完了したら：

1. ✅ GitHubのIssue #1〜#10をクローズ
2. 📝 [Phase 1総合課題](projects/asset-manager/) に挑戦
3. 🚀 [Phase 2: C++20](../cpp20/) へ進む

## 📚 参考資料

- [モダンC++学習カリキュラム](../docs/modern-cpp-curriculum.md)
- [cppreference - C++17](https://en.cppreference.com/w/cpp/17)
- [GitHub Issues](https://github.com/itsakeyfut/cpp-playground/issues?q=is%3Aissue+label%3Aphase-1-cpp17)
