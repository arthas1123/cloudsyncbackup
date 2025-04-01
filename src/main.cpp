#include <iostream>
#include "database.hpp"
#pragma message("💡 使用到的 database.hpp 成功被 include 了！")

int main()
{
    std::cout << "🚀 cloudsyncbackup 啟動中...\n";

    Database db("mydata.db");
    db.initialize();
    db.insertTestData();

    return 0;
}
