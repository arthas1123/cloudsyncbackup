# 📦 cloudsyncbackup

一個用 C++ + SQLite 實作的小型資料同步備份系統。

## ✅ 目前進度

- [x] 專案結構建立（src/include/build）
- [x] CMake 編譯環境測試通過
- [x] Database 模組建立（支援 SQLite）
- [x] 建立資料表與測試資料
- [x] 成功產生 mydata.db

## 🔁 資料庫互動流程

```text
+----------------+
|  C++ Program   |
+----------------+
        |
        | Execute SQL
        v
+------------------------+
|  SQLite Engine (C API) |
+------------------------+
        |
        | Read / Write
        v
+----------------+
|  mydata.db     |
|  (SQLite file) |
+----------------+

備份功能規劃

🔹 功能目標：

	1.	將 mydata.db 複製成 backup_YYYYMMDD_HHMMSS.db
	2.	備份檔儲存在 backup_storage/ 資料夾中
	3.	可以從主程式呼叫備份功能（例如 Backup::run()）


✅ Backup 模組：

	•	使用 std::filesystem 複製 .db 檔案
	•	自動產生含時間戳的備份檔名
	•	備份結果儲存在 backup_storage/
	•	如果目錄不存在則自動建立

🔧 路徑管理優化：

	•	使用 std::filesystem::path 管理路徑
	•	以 basePath = ".." 作為專案根目錄基準
	•	所有讀寫動作都指向根目錄資料夾，避免 build 目錄路徑混亂
🧪 測試結果：

	•	Build 成功（macOS + Clang）
	•	cloudsyncbackup 執行後會自動初始化資料庫並備份
	•	產出檔案：
	•	mydata.db
	•	backup_YYYYMMDD_HHMMSS.db in backup_storage/
