
#include "dialog_change.h"
#include "./ui_dialog_change.h"
#include "Films.h"

Dialog_change::Dialog_change(std::shared_ptr<Films> films, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_change)
{
    ui->setupUi(this);
    this->films = films;

    //display the names for selection from db
    ui->Dia_name->addItem(" ");
    for (int i = 1; i <= films->get_num(); ++i) {
         ui->Dia_name->addItem(*films->get_name(i));
    }
}

Dialog_change::~Dialog_change()
{
    delete ui;
}

void Dialog_change::on_Dia_ok_clicked()
{
    int w_unw, a;
    QString name = ui->Dia_name->currentText();

    //check the filling of the fields
    if (name == " ") {
         films->ErrorMessage((char*)"Выберите название");
        return;
    }
    if (ui->Dia_w->isChecked()) w_unw = 1;
    if (ui->Dia_unw->isChecked()) w_unw = 0;
    if (!(ui->Dia_w->isChecked()) && !(ui->Dia_unw->isChecked())) {
        films->ErrorMessage((char*)"ВЫберите статус просмотра");
       return;
    }

    //make changes throgh the function
    a = films->change_w_unw(name, w_unw);

    //if no error message is returned, close window
    if (a != -1){
       films->SuccessMessage((char*)"Статус просмотра изменён");
        close();
        }
    else
        films->ErrorMessage((char*)"Не удалось изменить статус просмотра");
}

void Dialog_change::on_Dia_cancel_clicked()
{
    close();
}

void Dialog_change::closeEvent(QCloseEvent *) {
    //clean window
    ui->Dia_name->setCurrentText(" ");

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

