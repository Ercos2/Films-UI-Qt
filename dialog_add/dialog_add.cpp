
#include "dialog_add.h"
#include "./ui_dialog_add.h"
#include "Films.h"

Dialog_add::Dialog_add(std::shared_ptr<Films> films, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog_add) {
    std::vector<QString> ganres_types = {" ", "Thriller", "Action", "Biography", "Western",
                                         "Detective", "Documentary", "Catastrophe", "Horror",
                                         "Сomedy", "Fiction", "Melodrama", "Musical",
                                         "Noir", "Post-apocalypse", "Drama", "Romcom"};
    ui->setupUi(this);
    this->films = films;

    //display a list of ganres to choose from
    for (auto&& ganre : ganres_types) {
        ui->Dia_ganre->addItem(ganre);
    }
}

Dialog_add::~Dialog_add(){
    delete ui;
}

void Dialog_add::on_Dia_cancel_clicked(){
    close();
}


void Dialog_add::on_Dia_ok_clicked() {
    int w_unw = 0, a = 0;
    QString s_name = ui->Dia_name->text();

    //check the filling of the fields
    if (s_name.size() < 1) {
        films->ErrorMessage((char*)"Введите название");
       return;
    }
    QString s_ganre = ui->Dia_ganre->currentText();
    if (s_ganre == " ") {
        films->ErrorMessage((char*)"ВЫберите жанр");
        return;
    }
    if (ui->Dia_w->isChecked()) w_unw = 1;
    if (ui->Dia_unw->isChecked()) w_unw = 0;
    if (!(ui->Dia_w->isChecked()) && !(ui->Dia_unw->isChecked())) {
       films->ErrorMessage((char*)"ВЫберите статус просмотра");
       return;
    }
    //enter the movie through the function
    a = films->insert(std::make_shared<QString>(s_name), std::make_shared<QString>(s_ganre), w_unw);

    //close the window if a succes signal is returned
    if (a == 1)
        close();
    else
        return;
}

void Dialog_add::closeEvent(QCloseEvent *) {
    //clear window
    ui->Dia_name->clear();
    ui->Dia_ganre->setCurrentText(" ");

    //by default, at least one button should be active,
    //so we remove this rule,
    //remove the values from both buttons
    //and turn the rule back on

    ui->Dia_unw->setAutoExclusive(false);
    ui->Dia_unw->setChecked(false);

    ui->Dia_w->setAutoExclusive(false);
    ui->Dia_w->setChecked(false);

    ui->Dia_unw->setAutoExclusive(true);
    ui->Dia_w->setAutoExclusive(true);
}


