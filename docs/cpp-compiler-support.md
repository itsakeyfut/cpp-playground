# C++ コンパイラサポート状況

## 現在の環境

### コンパイラ情報

```
コンパイラ: Clang 20.1.6
ターゲット: x86_64-pc-windows-msvc
インストール先: C:\Program Files\LLVM\bin
```

### サポートされているC++標準

| C++標準 | サポート状況 | `__cplusplus` 値 | 備考 |
|---------|------------|-----------------|------|
| **C++17** | ✅ 完全サポート | 201703L | 安定版 |
| **C++20** | ✅ 完全サポート | 202002L | 安定版、本プロジェクトのデフォルト |
| **C++23** | ✅ サポート | 202302L | ほぼ完全、一部機能は実装中 |
| **C++26** | ⚠️ 実験的サポート | 202400L | 標準化未完了、実験的機能のみ |

## C++バージョン別の主要機能

### C++20（完全サポート）

このプロジェクトのデフォルトバージョンです。以下の主要機能が使用可能：

- ✅ **コンセプト（Concepts）**: テンプレート制約
- ✅ **モジュール（Modules）**: `import`/`export`
- ✅ **コルーチン（Coroutines）**: `co_await`/`co_yield`/`co_return`
- ✅ **範囲（Ranges）**: `std::ranges`ライブラリ
- ✅ **3方比較演算子（Three-way comparison）**: `<=>`演算子
- ✅ **指定初期化子（Designated initializers）**: `.member = value`
- ✅ **ラムダ式のテンプレート**: `[]<typename T>(T x) {}`
- ✅ **constexpr仮想関数**
- ✅ **consteval、constinit**
- ✅ **std::format**: フォーマット文字列
- ✅ **std::span**: 配列ビュー
- ✅ **std::source_location**: ソースコード位置情報

### C++23（サポート）

Clang 20では、ほぼすべてのC++23機能が使用可能です：

- ✅ **if consteval**: コンパイル時評価の分岐
- ✅ **マルチ次元添字演算子**: `operator[](x, y, z)`
- ✅ **auto(x)、decay-copy**: 自動型推論の改善
- ✅ **std::expected**: エラーハンドリング型
- ✅ **std::flat_map/flat_set**: フラットコンテナ
- ✅ **std::print/println**: 標準出力の改善
- ✅ **std::stacktrace**: スタックトレース
- ✅ **範囲の改善**: `std::ranges::to`など
- ✅ **デダクションガイドの改善**
- ✅ **静的operator()**: ラムダの改善

### C++26（実験的サポート）

⚠️ **注意**: C++26はまだ標準化が完了していません（2026年に完成予定）。Clang 20では一部の機能が実験的にサポートされています。

**実装済みの可能性がある機能**:
- ⚠️ **静的リフレクション（Static Reflection）**: 一部実装
- ⚠️ **パターンマッチング（Pattern Matching）**: 提案段階
- ⚠️ **std::hive**: コンテナの追加
- ⚠️ **契約プログラミング（Contracts）**: 提案段階

**本プロジェクトでの使用について**:
- CMakeLists.txtで`BUILD_CPP26`オプションはデフォルトで`OFF`に設定されています
- C++26の機能は実験的であり、将来的に仕様が変更される可能性があります
- 学習目的で使用する場合は、`-std=c++26`フラグで有効化できます

## コンパイラによるC++サポート比較

| コンパイラ | バージョン | C++20 | C++23 | C++26 |
|-----------|----------|-------|-------|-------|
| **Clang** | 20.x | ✅ 完全 | ✅ ほぼ完全 | ⚠️ 実験的 |
| **GCC** | 14.x | ✅ 完全 | ✅ ほぼ完全 | ⚠️ 実験的 |
| **MSVC** | 19.39+ | ✅ 完全 | 🔶 部分的 | ❌ 限定的 |

**凡例**:
- ✅ 完全: すべての主要機能がサポート済み
- 🔶 部分的: 一部機能が未実装
- ⚠️ 実験的: 実験的機能のみ、仕様が変更される可能性あり
- ❌ 限定的: ほとんど未実装

## 本プロジェクトの推奨設定

### デフォルト: C++20（Unreal Engine 5.7互換）

```cmake
cmake_minimum_required(VERSION 3.20...4.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

**理由**:
- ✅ **Unreal Engine 5.7の必須要件**
- ✅ Clang 20.1.6で完全にサポートされている
- ✅ UEで実際に使用する機能（コンセプト、範囲、コルーチンなど）を学習できる
- ✅ 本番コードとの互換性を保ちながら学習可能

### Unreal Engine 5.7との互換性

**重要**: このプロジェクトはUnreal Engine 5.7でのゲーム開発を目的としています。

| C++標準 | UE 5.7 | 推奨用途 |
|---------|--------|---------|
| C++17 | ⚠️ 非推奨 | UE 5.6以前で使用 |
| **C++20** | ✅ **必須** | **UE本番コード・学習** |
| C++23 | ❌ 未サポート | 学習用のみ（UEでは使用不可） |
| C++26 | ❌ 未サポート | 実験的学習のみ |

### C++23/26を学習用に試す場合

個別のターゲットで異なる標準を指定可能：

```cmake
# C++23の学習用ターゲット（UEでは使用不可）
target_compile_features(learning_cpp23 PRIVATE cxx_std_23)
```

### C++26を試す場合（実験的）

```bash
# CMakeオプションで有効化
cmake -B build -DBUILD_CPP26=ON
```

または、個別のターゲットで：

```cmake
if(BUILD_CPP26)
    target_compile_features(my_cpp26_target PRIVATE cxx_std_26)
endif()
```

## コンパイラのアップグレード

### Clangの最新版確認

```bash
clang++ --version
```

### 他のコンパイラのインストール（オプション）

#### GCC（MinGW-w64経由）

```bash
# MSYS2を使用している場合
pacman -S mingw-w64-x86_64-gcc
```

#### Visual Studio（MSVC）

Windows環境では、Visual Studio 2022以降をインストールすることで、MSVCコンパイラが使用可能になります。

## 機能サポートの確認方法

### マクロで確認

```cpp
#include <iostream>

int main() {
    std::cout << "C++ version: " << __cplusplus << std::endl;

    #ifdef __cpp_concepts
        std::cout << "Concepts: " << __cpp_concepts << std::endl;
    #endif

    #ifdef __cpp_modules
        std::cout << "Modules: " << __cpp_modules << std::endl;
    #endif

    #ifdef __cpp_coroutines
        std::cout << "Coroutines: " << __cpp_coroutines << std::endl;
    #endif

    return 0;
}
```

### コンパイラドキュメント

- **Clang**: https://clang.llvm.org/cxx_status.html
- **GCC**: https://gcc.gnu.org/projects/cxx-status.html
- **MSVC**: https://learn.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance

## まとめ

✅ **現在の環境（Clang 20.1.6、CMake 4.0.3）は以下をサポート**:
- C++20: 完全サポート（**本プロジェクトのデフォルト、UE 5.7必須**）
- C++23: ほぼ完全サポート（学習用のみ、UEでは未サポート）
- C++26: 実験的サポート（学習目的で使用可能、ただし注意が必要）

✅ **Unreal Engine 5.7開発を目的とする場合の推奨**:
- **C++20をデフォルトに設定**: UE 5.7の必須要件
- **CMake 3.20...4.0の範囲構文を使用**: 最新のCMakeポリシーを活用しながら後方互換性を維持
- **プロジェクトバージョン管理の追加**: `project()`コマンドにVERSIONとDESCRIPTIONを追加
- **C++20の機能を重点的に学習**: コンセプト、範囲、コルーチン、モジュールなど

✅ **C++23/26についての結論**:
- コンパイル環境としてはサポートされています
- ただし、**Unreal Engine 5.7では使用できません**
- 純粋な学習目的や、将来的な標準機能の先行学習には有用
- 本プロジェクトでは`BUILD_CPP23`/`BUILD_CPP26`オプションで制御可能
- UEで使用する予定のコードは必ずC++20で記述してください

✅ **学習戦略**:
1. **最優先**: C++20の機能を完全にマスター（UE 5.7で使用可能）
2. **次点**: C++23の便利な機能を理解（将来のUEバージョンで使える可能性）
3. **参考**: C++26の先進的な機能を実験（長期的な視野）

## Unreal Engine 5.7 固有の注意事項

### 使用可能なC++20機能

Unreal Engine 5.7では以下のC++20機能が使用可能です：

✅ **推奨される機能**:
- **コンセプト（Concepts）**: テンプレート制約で型安全性を向上
- **範囲（Ranges）**: `std::ranges`でコレクション操作を簡潔に
- **コルーチン（Coroutines）**: 非同期処理の実装
- **指定初期化子（Designated Initializers）**: 構造体初期化の明確化
- **ラムダ式のテンプレート**: ジェネリックラムダの強化
- **constexpr仮想関数**: コンパイル時多態性
- **std::span**: 配列ビューの安全な操作
- **std::format**: 型安全な文字列フォーマット

⚠️ **制限される可能性がある機能**:
- **構造化束縛（Structured Bindings）**: Epicコーディング規約で制限される場合あり
- **モジュール（Modules）**: UEのビルドシステムとの互換性を要確認

### Epicコーディング規約との整合性

このプロジェクトの設定（Google C++スタイル + Clang-Tidy）は、Epicコーディング規約と一部異なります。

**主な違い**:
- **命名規則**: Googleスタイル（CamelCase）vs Epicスタイル（PascalCase + プレフィックス）
- **ポインタ配置**: Googleスタイル（左寄せ`int*`）vs Epicスタイル（右寄せ`int *`）

**推奨アプローチ**:
1. **学習フェーズ**: このプロジェクトでGoogleスタイルを使用して基礎を固める
2. **UE実装フェーズ**: Epicコーディング規約に従ってコードを書く
3. **重要なのは**: C++20の機能自体の理解（スタイルは後で調整可能）

### 参考リンク

**Unreal Engine公式ドキュメント**:
- [Epic C++ Coding Standard for Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)
- [Programming with C++ in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-with-cplusplus-in-unreal-engine)

**C++標準のサポート状況**:
- [Unreal Engine Public Roadmap](https://portal.productboard.com/epicgames/1-unreal-engine-public-roadmap/c/1165-c-20-default-version)

## References

- [Clang C++ Status](https://clang.llvm.org/cxx_status.html)
- [C++ Standards Support in GCC](https://gcc.gnu.org/projects/cxx-status.html)
- [cppreference - C++ compiler support](https://en.cppreference.com/w/cpp/compiler_support)
- [C++ Standards Committee Papers](https://www.open-std.org/jtc1/sc22/wg21/)
- [Epic C++ Coding Standard for Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)
- [Programming with C++ in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-with-cplusplus-in-unreal-engine)
