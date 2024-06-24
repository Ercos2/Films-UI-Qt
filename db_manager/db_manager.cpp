#include "db_manager.h"

DB_manager::DB_manager() {
    db = std::make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("./filmsDB.db");
    db->open();
    query = std::make_unique<QSqlQuery>(*db);

    //check table exists
    if (!query->exec("SELECT \"Hello Films\" FROM Films")) {
        query->exec("CREATE TABLE Films(Id INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Ganre TEXT NOT NULL, W_unw INT NOT NULL);");
    }
}

std::unique_ptr<QString> DB_manager::get_str_by_sql(std::unique_ptr<QString> sql) {
    auto copy_str = std::make_unique<QString>();

    if (query->exec(*sql)) {
        query->next();
        *copy_str = query->value(0).toString();
        return copy_str;
    }
    else {
        *copy_str = "SQL reuest error";
        return copy_str;
    }
}

int DB_manager::get_num_by_sql(std::unique_ptr<QString> sql) {
    if (query->exec(*sql)) {
        query->next();
        return query->value(0).toInt();
    }
    else
        return -1;
}

int DB_manager::change_db_by_sql(std::unique_ptr<QString> sql) {
    query->prepare(*sql);
    if (query->exec())
        return 1;
    else
        return -1;
}

bool DB_manager::is_exec_by_sql(std::unique_ptr<QString> sql) {
    if(query->exec(*sql)) {
        if(query->next()) return 1;
        else return 0;
    }
    else return 0;
}
