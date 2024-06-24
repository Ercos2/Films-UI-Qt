#ifndef FILM_MANAGER_H
#define FILM_MANAGER_H

#include "Films.h"

class Film_manager
{
public:
    std::unique_ptr<Films> films;

    Film_manager();

    std::unique_ptr<QString> choose(int begin);                                                //for select-ui, return film-name
    int insert(std::unique_ptr<QString> p_name, std::unique_ptr<QString> p_ganre, int w_unw);  //for ad-ui, insert film in db
};

#endif // FILM_MANAGER_H
