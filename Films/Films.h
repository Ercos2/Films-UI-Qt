#ifndef FUNC_H
#define FUNC_H

#include <QMessageBox>
#include <QSqlDatabase>>
#include <QSqlQuery>
#include <QComboBox>

//class for working with movies stored in the db

class Films {

public:

    Films();

QSqlDatabase db;
QSqlQuery *query;

std::shared_ptr<QString> choose(int begin);                                   //for select-ui, return film-name
int insert(std::shared_ptr<QString> p_name, std::shared_ptr<QString> p_ganre, int w_unw);  //for ad-ui, insert film in db
std::shared_ptr<QString> get_name(int num_2);                             //return name by id
std::shared_ptr<QString> get_ganre(int num_2);                            //return ganre by id
int get_w_unw(int num_2);                                //return view status by id
int get_num();                                           //return the number of submitted films
int get_id(std::shared_ptr<QString> name);
int change_w_unw(QString name, bool p_w_unw);            //change view status by name
bool copy_check(std::shared_ptr<QString> p_name);                         //searches for duplicate movies by name. 1 - found, 0 - not found
void ErrorMessage(char* message);
void SuccessMessage(char* message);

};
#endif // FUNC_H
