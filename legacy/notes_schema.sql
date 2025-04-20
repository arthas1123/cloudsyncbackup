onst char *sql = "CREATE TABLE IF NOT EXISTS notes ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "content TEXT NOT NULL);";

 char *errMsg = nullptr;
 if (sqlite3_exec((sqlite3 *)db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
 {
     std::cerr << "❌ 建立資料表失敗：" << errMsg << std::endl;
     sqlite3_free(errMsg);
 }
