# 🧠 C++ Compiler Error Cheat Sheet (cloudsyncbackup 專用)

這是一份針對本專案常見的 C++ 編譯錯誤診斷對照表，協助快速定位錯誤原因並修正。  
適用於所有使用 CMake、Header 檔拆分、模組化設計的現代 C++ 專案。

---

## 🔧 ❶ `expected ';'` → 結構定義沒收尾！

### 錯誤範例：
```cpp
struct Config {
    std::string path;
}  // ❌ 少了分號
```

### 正確寫法：
```cpp
struct Config {
    std::string path;
};  // ✅ 要有分號！
```

### 特別注意：
- 巢狀 `struct`（例如 `AppConfig::CloudConfig`）也要寫名稱與分號：

```cpp
struct AppConfig {
    struct CloudConfig {
        bool enabled;
    } cloud;  // ✅ cloud 是成員名稱，不能漏掉
};
```

---

## 🔧 ❷ 錯誤報在 `.cpp`，但實際出錯在 `.hpp`？

### 原因：
- `.cpp` 中 `#include "xxx.hpp"` 等同把 `.hpp` 的內容「貼進來」
- 如果 `.hpp` 裡的語法有錯，**錯誤會在 `.cpp` 中被觸發**

### 快速判斷：
- 發現 `.cpp` 開頭報錯又沒問題
- 請先檢查前面 `#include` 的 `.hpp` 檔案

---

## 🔧 ❸ `undefined reference to ...` → 函式沒定義 / 沒連結

### 情境：
```cpp
// database.hpp 中有
void initialize();

// 但在 database.cpp 裡漏寫這個函式
```

### 也可能是 CMake 漏掉：
```cmake
target_sources(cloudsyncbackup PRIVATE
    src/main.cpp
    src/database.cpp  # ✅ 要確保有這行
)
```

---

## 🔧 ❹ `multiple definition of ...` → 缺少 `inline` 或 `constexpr`

### 錯誤範例：
```cpp
// emoji.hpp
std::string Rocket() { return "🚀"; }  // ❌ 會在多個 cpp 重複定義
```

### 正確寫法：
```cpp
inline std::string Rocket() { return "🚀"; }  // ✅ 加 inline
```

---

## 🔧 ❺ `no matching function` / 型別不符 → 參數錯誤

### 錯誤範例：
```cpp
Database::insertTestData(int id);  // ❌ insertTestData 沒有參數
```

### 修正：
- 檢查 header 裡的函式定義
- 確保傳入參數型別一致

---

## 🔧 ❻ 找不到 `json.hpp` → include 路徑錯

### 錯誤：
```
fatal error: nlohmann/json.hpp: No such file or directory
```

### 修正：
- 確保路徑為：
```
include/nlohmann/json.hpp
```
- 使用這樣的編譯指令：
```bash
g++ main.cpp -std=c++17 -Iinclude
```

---

## 💡 編譯提示技巧

加上以下參數讓編譯更嚴謹：

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -Werror
```

---

## 📦 建議放置位置

將本檔案放於：

```
cloudsyncbackup/
└── docs/
    └── cpp_compiler_error_cheatsheet.md
```

或在 `README.md` 最下方加上連結：

```markdown
👉 [查看 C++ Compiler Error 小抄](docs/cpp_compiler_error_cheatsheet.md)
```

---

## 🧠 小提醒：錯誤訊息不代表真正的錯誤點！

> 看到錯誤報在哪裡 ≠ 錯誤發生在那裡  
> 請根據錯誤行上下文 + `.hpp` include 內容綜合判斷