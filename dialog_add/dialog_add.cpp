#include "dialog_add.h"
#include "./ui_dialog_add.h"

Dialog_add::Dialog_add(std::shared_ptr<Film_manager> film_manager, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog_add) {
    std::vector<QString> ganres_types = {" ", "Thriller", "Action", "Biography", "Western",
                                         "Detective", "Documentary", "Catastrophe", "Horror",
                                         "Сomedy", "Fiction", "Melodrama", "Musical",
                                         "Noir", "Post-apocalypse", "Drama", "Romcom"};
    ui->setupUi(this);
    this->film_manager = film_manager;

    //display a list of ganres to choose from
    for (auto&& ganre : ganres_types) {
        ui->Dia_ganre->addItem(ganre);
    }
}

Dialog_add::~Dialog_add(){}

void Dialog_add::on_Dia_cancel_clicked(){
    close();
}


void Dialog_add::on_Dia_ok_clicked() {
    int w_unw = 0;
    auto s_name = std::make_unique<QString>(ui->Dia_name->text());

    //check the filling of the fields
    if (s_name->size() < 1) {
        QMessageBox::warning(NULL, "Warning", (char*)"Введите название");
       return;
    }
    auto s_ganre = std::make_unique<QString>(ui->Dia_ganre->currentText());
    if (*s_ganre == " ") {
        QMessageBox::warning(NULL, "Warning", (char*)"ВЫберите жанр");
        return;
    }
    if (ui->Dia_w->isChecked()) w_unw = 1;
    if (ui->Dia_unw->isChecked()) w_unw = 0;
    if (!(ui->Dia_w->isChecked()) && !(ui->Dia_unw->isChecked())) {
       QMessageBox::warning(NULL, "Warning", (char*)"ВЫберите статус просмотра");
       return;
    }
    //enter the movie through the function
    //close the window if succes signal is returned
    if (film_manager->insert(std::move(s_name), std::move(s_ganre), w_unw) == 1)
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

    // signal that dialog is closed and something can be different
    emit dialog_closed();
}


