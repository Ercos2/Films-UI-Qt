#ifndef FUNC_H
#define FUNC_H

#include <QMessageBox>
#include <QComboBox>
#include "db_manager.h"

//class for working with movies stored in the db

class Films {
public:
    std::unique_ptr<DB_manager> db_manager;

    Films();

    std::unique_ptr<QString> get_name(int id);               //return name by id
    std::unique_ptr<QString> get_ganre(int id);              //return ganre by id
    int get_w_unw(int num_2);                                //return view status by id
    int get_num();                                           //return the number of submitted films
    int get_id(std::unique_ptr<QString> name);               //return id by name
    int change_w_unw(std::unique_ptr<QString> name, bool p_w_unw);            //change view status by name
    bool copy_check(std::unique_ptr<QString> p_name);        //searches for duplicate movies by name. 1 - found, 0 - not found
};

#endif // FUNC_H
