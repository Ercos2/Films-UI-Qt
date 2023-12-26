
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "Films.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //create db

    //films = std::make_shared<Films>();
    films = std::make_shared<Films>();

    films->db = QSqlDatabase::addDatabase("QSQLITE");
    films->db.setDatabaseName("./filmsDB.db");
    films->db.open();
    films->query = new QSqlQuery(films->db);

    //check table exists
    if (!films->query->exec("SELECT \"Hello Films\" FROM Films")) {
        films->query->exec("CREATE TABLE Films(Id INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Ganre TEXT NOT NULL, W_unw INT NOT NULL);");
    }
    select = std::make_unique<Dialog_select>(std::make_shared<Films>(*films));
    change = std::make_unique<Dialog_change>(std::make_shared<Films>(*films));
    add = std::make_unique<Dialog_add>(std::make_shared<Films>(*films));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_clicked() {
    //check if there are movies for select

    if (*films->choose(1) == "f") {
        films->ErrorMessage((char*)"Нет фильмов для выбора");
        //films->id = 1;
    }
    else {
        //Dialog_select select;
       //films->id = 1;
       //select = std::make_shared<Dialog_select>(films);
       select->setModal(true);
       select->exec();
       //films->num_film_1 = 1;
    }
}

void MainWindow::on_pushButton_change_clicked() {
    //check movies exist
    if (!films->get_num()) {
       films->ErrorMessage((char*)"Нeт внесённых фильмов");
    }
    else {
        //Dialog_change change;
       //change = std::make_shared<Dialog_change>(films);
       change->setModal(true);
       change->exec();
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    //Dialog_add add;
    //add = std::make_shared<Dialog_add>(films);
    add->setModal(true);
    add->exec();
}
