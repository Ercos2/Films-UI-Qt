#include "Films.h"

Films::Films() {
    db_manager = std::make_unique<DB_manager>();
};

//return name by id
std::unique_ptr<QString> Films::get_name(int id) {
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_unique<QString>("SELECT name FROM Films WHERE Id = " + *str_num + (QString)";");

    return db_manager->get_str_by_sql(std::move(sql));
}

//return ganre by id
std::unique_ptr<QString> Films::get_ganre(int id) {
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_unique<QString>("SELECT Ganre FROM Films WHERE Id = " + *str_num + (QString)";");

    return db_manager->get_str_by_sql(std::move(sql));
}

//return wacth status by num
int Films::get_w_unw(int id) {
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_unique<QString>("select W_unw from Films where Id =" + *str_num + (QString)";");

    return db_manager->get_num_by_sql(std::move(sql));
}

//return number of films in db
int Films::get_num() {
    auto sql = std::make_unique<QString>("SELECT count(Id) FROM Films");

    return db_manager->get_num_by_sql(std::move(sql));
}

int Films::get_id(std::unique_ptr<QString> name) {
    auto sql = std::make_unique<QString>("SELECT Id FROM Films WHERE Name = \"" + *name + (QString)"\";");

    return db_manager->get_num_by_sql(std::move(sql));
}

//change wacth stutas by name
int Films::change_w_unw(std::unique_ptr<QString> name, bool p_w_unw) {
    auto str_w_unw = std::make_unique<QString>((QString)"\"" + (char)(p_w_unw + 48) + (QString)"\"");
    auto sql = std::make_unique<QString>("update Films set W_unw = " + *str_w_unw + (QString)" where Name = '" + *name + "'; ");

    return db_manager->change_db_by_sql(std::move(sql));
}

//check same name in db
//1 - copy found
//0 - copy didn't find
bool Films::copy_check(std::unique_ptr<QString> p_name) {
    if (get_num() > 0) {
        auto sql = std::make_unique<QString>("SELECT Name FROM Films WHERE Name = " + (QString)"\"" + *p_name + (QString)"\";");
        return db_manager->is_exec_by_sql(std::move(sql));
    }
    return 0;
}
