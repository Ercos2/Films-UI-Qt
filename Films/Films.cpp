#include "Films.h"

Films::Films() {};

//return name by id
std::shared_ptr<QString> Films::get_name(int id) {
    auto copy_name = std::make_shared<QString>();
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_shared<QString>("SELECT name FROM FILMS WHERE ID = " + *str_num + (QString)";");

    if (query->exec(*sql)) {
        query->next();
        *copy_name = query->value(0).toString();
        return copy_name;
    }
    else
        return std::make_shared<QString>("SQL reuest error");
}

//return ganre by id
std::shared_ptr<QString> Films::get_ganre(int id) {
    auto copy_ganre = std::make_shared<QString>();;
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_shared<QString>("SELECT Ganre FROM Films WHERE Id = " + *str_num + (QString)";");

    if (query->exec(*sql)) {
        query->next();
        *copy_ganre = query->value(0).toString();
        return copy_ganre;
    }
    else
        return std::make_shared<QString>("SQL reuest error");
}

//return wacth status by num
int Films::get_w_unw(int id) {
    int w_unw;
    auto str_num = std::make_unique<QString>((QString)"\"" + (char)(id + 48) + (QString)"\"");
    auto sql = std::make_shared<QString>("select W_unw from Films where Id =" + *str_num + (QString)";");

    if (query->exec(*sql)) {
        query->next();
        w_unw = query->value(0).toInt();
        return w_unw;
    }
    else
        return -1;
}

//return number of films in db
int Films::get_num() {
    auto sql = std::make_shared<QString>("SELECT count(Id) FROM Films");
    int num_film = 0;

    if (query->exec(*sql)) {
        query->next();
        num_film = query->value(0).toInt();
        return num_film;
    }
    else
        return -1;
}

int Films::get_id(std::shared_ptr<QString> name) {
    int id = 0;
    auto sql = std::make_shared<QString>("SELECT Id FROM Films WHERE Name = \"" + *name + (QString)"\";");

    if (query->exec(*sql)) {
        query->next();
        id = query->value(0).toInt();
        return id;
    }
    else
        return -1;
}


//change wacth stutas by name
int Films::change_w_unw(QString name, bool p_w_unw) {
    auto str_w_unw = std::make_unique<QString>((QString)"\"" + (char)(p_w_unw + 48) + (QString)"\"");
    auto sql = std::make_shared<QString>("update Films set W_unw = " + *str_w_unw + (QString)" where Name = '" + name + "'; ");

    query->prepare(*sql);
    if (query->exec())
        return 1;
    else
        return -1;
}


//return unwacth films after num (a)
std::shared_ptr<QString> Films::choose(int begin) {
    for ( ; begin <= get_num(); begin++) {

        //ask wacth status and, if it is 1, skip ather and set next number
        //2 - no films anymore, skip cyrcle
        //0 - film is unwacth and we can return it's name

        if (get_w_unw(begin) == 1) continue;
        else if (get_w_unw(begin) == 2) break;
        else if (get_w_unw(begin) == 0)
            return get_name(begin);
    }
    //return f, if can't return unwacth films
    return std::make_shared<QString>("f");
}

//insert new film in db
int Films::insert(std::shared_ptr<QString> p_name, std::shared_ptr<QString> p_ganre, int w_unw) {

    //check film with same name
    //if it found, return error_code 2 and error_message

    if (copy_check(p_name)) {
        ErrorMessage((char*)"copy found");
        return 2;
    }
    auto id = std::make_unique<QString>((QString)"" + (char)(get_num() + 48 + 1) + (QString)"");
    auto str_w_unw = std::make_unique<QString>((QString)"" + (char)(w_unw + 48) + (QString)"");
    auto sql = std::make_shared<QString>("insert into Films values (" + *id + (QString)",'" + *p_name + (QString)"','" + *p_ganre + (QString)"'," + *str_w_unw + (QString)"); ");
    query->prepare(*sql);
    if(query->exec()){
        SuccessMessage((char*)"Фильм внесён");
        return 1;
    }
    else {
        ErrorMessage((char*)"Фильм не внесён");
        return -1;
    }
    return 1;
}

//check same name in db
//1 - copy found
//0 - copy didn't find
bool Films::copy_check(std::shared_ptr<QString> p_name) {
    if (get_num() > 0) {
        auto sql = std::make_shared<QString>("SELECT Name FROM Films WHERE Name = " + (QString)"\"" + *p_name + (QString)"\";");
        if(query->exec(*sql)) {
            if(query->next()) return 1;
            else return 0;
        }
        else return 0;
    }
    return 0;
}

//error pattern for beauty
void Films::ErrorMessage(char* message) {
    QMessageBox::warning(NULL, "Warning", message);
}

//success pattern for beauty
void Films::SuccessMessage(char* message) {
    QMessageBox::about(NULL, "Success", message);
}
