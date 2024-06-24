#include "film_manager.h"

Film_manager::Film_manager()
{
    films = std::make_unique<Films>();
}


//return unwacth films after num (a)
std::unique_ptr<QString> Film_manager::choose(int begin) {
    for ( ; begin <= films->get_num(); begin++) {

        //ask wacth status and, if it is 1, skip ather and set next number
        //2 - no films anymore, skip cyrcle
        //0 - film is unwacth and we can return it's name

        if (films->get_w_unw(begin) == 1) continue;
        else if (films->get_w_unw(begin) == 2) break;
        else if (films->get_w_unw(begin) == 0)
            return films->get_name(begin);
    }
    //return f, if can't return unwacth films
    return std::make_unique<QString>("f");
}

//insert new film in db
int Film_manager::insert(std::unique_ptr<QString> p_name, std::unique_ptr<QString> p_ganre, int w_unw) {

    //check film with same name
    //if it found, return error_code 2 and error_message

    if (films->copy_check(std::make_unique<QString>(*p_name))) {
        QMessageBox::warning(NULL, "Warning", (char*)"copy found");
        return 2;
    }
    auto id = std::make_unique<QString>((QString)"" + (char)(films->get_num() + 48 + 1) + (QString)"");
    auto str_w_unw = std::make_unique<QString>((QString)"" + (char)(w_unw + 48) + (QString)"");
    auto sql = std::make_unique<QString>("insert into Films values (" + *id + (QString)",'" + *p_name + (QString)"','" + *p_ganre + (QString)"'," + *str_w_unw + (QString)"); ");

    if (films->db_manager->change_db_by_sql(std::move(sql)) == 1) {
        QMessageBox::about(NULL, "Success", (char*)"Фильм внесён");
        return 1;
    }
    else {
        QMessageBox::warning(NULL, "Warning", (char*)"Фильм не внесён");
        return -1;
    }
}
