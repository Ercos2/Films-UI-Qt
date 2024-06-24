#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "Films.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    ui->setupUi(this);

    film_manager = std::make_shared<Film_manager>();

    select = std::make_unique<Dialog_select>(film_manager);
    change = std::make_unique<Dialog_change>(film_manager);
    add = std::make_unique<Dialog_add>(film_manager);

    // every time the windows of change and add are closing
    // it can means changes
    // so we reload windows that these changes relate to
    connect(change.get(), &Dialog_change::dialog_closed, [this]{
        select = std::make_unique<Dialog_select>(film_manager);});
    connect(add.get(), &Dialog_add::dialog_closed, [this]{
        change = std::make_unique<Dialog_change>(film_manager);
        select = std::make_unique<Dialog_select>(film_manager);});
}

MainWindow::~MainWindow(){}

void MainWindow::on_pushButton_select_clicked() {
    // check if there are movies for select

    if (*film_manager->choose(1) == "f") {
        QMessageBox::warning(NULL, "Warning", (char*)"Нет фильмов для выбора");
    }
    else {
       select->setModal(true);
       select->exec();
    }
}

void MainWindow::on_pushButton_change_clicked() {
    //check movies exist
    if (!film_manager->films->get_num()) {
       QMessageBox::warning(NULL, "Warning", (char*)"Нeт внесённых фильмов");
    }
    else {
       // Dialog_change change;
       change->setModal(true);
       change->exec();
    }
}

void MainWindow::on_pushButton_add_clicked(){
    // Dialog_add add;
    add->setModal(true);
    add->exec();
}
