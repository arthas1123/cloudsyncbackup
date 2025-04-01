## Database Flow

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


