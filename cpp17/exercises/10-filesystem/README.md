# 1.10 std::filesystem

## 概要

C++17で導入された`std::filesystem`は、ファイルシステム操作のための標準ライブラリです。

**Rustとの比較**: `std::fs` および `std::path` に相当します。

```rust
// Rust
use std::fs;
use std::path::Path;

let path = Path::new("file.txt");
println!("{:?}", path.extension());
```

```cpp
// C++17
#include <filesystem>
namespace fs = std::filesystem;

fs::path p = "file.txt";
std::cout << p.extension() << std::endl;
```

## 学習内容

1. **パス操作**
   - pathの構築と操作
   - filename, stem, extension
   - parent_path, relative_path

2. **ディレクトリ走査**
   - directory_iterator
   - recursive_directory_iterator

3. **ファイル操作**
   - exists, is_regular_file, is_directory
   - file_size
   - create_directories, copy, remove

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.10.1
指定ディレクトリ内の全画像ファイル（.png, .jpg, .bmp）を再帰的に検索し、合計サイズを計算するツールを作れ。

## ビルド方法

```bash
mkdir build && cd build
cmake ..
make
./example
```

## 参考リンク

- [cppreference - std::filesystem](https://en.cppreference.com/w/cpp/filesystem)
- [modern-cpp-curriculum.md セクション 1.10](../../../docs/modern-cpp-curriculum.md)
