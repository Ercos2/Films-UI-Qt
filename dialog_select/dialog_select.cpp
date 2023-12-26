
#include "dialog_select.h"
#include "./ui_dialog_select.h"
#include "Films.h"

Dialog_select::Dialog_select(std::shared_ptr<Films> new_films, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_select)
{
    ui->setupUi(this);
    this->films = new_films;

    //set start value
    ui->Dia_name->setText(*films->choose(1));
    ui->Dia_ganre->setText(" ");
}

Dialog_select::~Dialog_select() {
    delete ui;
}

void Dialog_select::on_pushButton_next_clicked() {
    std::shared_ptr<QString> name = films->choose(films->get_id(std::make_shared<QString>(ui->Dia_name->text())) + 1);

    //f is error if there are no more movies for select
    if (*name == "f") {
        films->ErrorMessage((char*)"Больше нечего предложить");
        close();
        return;
    }

    //if it's not f, select more
    ui->Dia_name->setText(*name);
    ui->Dia_ganre->setText(" ");
    return;
}

void Dialog_select::on_pushButton_info_clicked() {
    //display ganre by id by name
    ui->Dia_ganre->setText(*films->get_ganre(films->get_id(std::make_shared<QString>(ui->Dia_name->text()))));
}


void Dialog_select::on_pushButton_yes_clicked() {
    films->SuccessMessage((char*)"Приятного просмотра");
    close();
    return;
}

void Dialog_select::closeEvent(QCloseEvent *) {
    //set default value for window
    ui->Dia_name->setText(*films->choose(1));
    ui->Dia_ganre->setText(" ");
}
