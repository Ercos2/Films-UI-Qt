#include "dialog_select.h"
#include "./ui_dialog_select.h"

Dialog_select::Dialog_select(std::shared_ptr<Film_manager> film_manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_select)
{
    ui->setupUi(this);
    this->film_manager = film_manager;

    //set start value
    ui->Dia_name->setText(*film_manager->choose(1));
    ui->Dia_ganre->setText(" ");
}

Dialog_select::~Dialog_select() {}

void Dialog_select::on_pushButton_next_clicked() {
    auto temp_id = film_manager->films->get_id(std::make_unique<QString>(ui->Dia_name->text())) + 1;
    std::unique_ptr<QString> name = film_manager->choose(temp_id);

    //f is error if there are no more movies for select
    if (*name == "f") {
        QMessageBox::warning(NULL, "Warning", (char*)"Больше нечего предложить");
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
    auto temp_id = film_manager->films->get_id(std::make_unique<QString>(ui->Dia_name->text()));
    ui->Dia_ganre->setText(*film_manager->films->get_ganre(temp_id));
}


void Dialog_select::on_pushButton_yes_clicked() {
    QMessageBox::about(NULL, "Success", (char*)"Приятного просмотра");
    close();
    return;
}

void Dialog_select::closeEvent(QCloseEvent *) {
    //set default value for window
    ui->Dia_name->setText(*film_manager->choose(1));
    ui->Dia_ganre->setText(" ");
}
