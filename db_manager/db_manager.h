#ifndef DB_MANAGER_H
#define DB_MANAGER_H

//#include <QSqlDatabase>
#include <QSqlQuery>

class DB_manager
{
public:
    std::unique_ptr<QSqlDatabase> db;
    std::unique_ptr<QSqlQuery> query;

    DB_manager();

    int get_num_by_sql(std::unique_ptr<QString> sql);
    std::unique_ptr<QString> get_str_by_sql(std::unique_ptr<QString> sql);
    int change_db_by_sql(std::unique_ptr<QString> sql);
    bool is_exec_by_sql(std::unique_ptr<QString> sql);
};

#endif // DB_MANAGER_H
