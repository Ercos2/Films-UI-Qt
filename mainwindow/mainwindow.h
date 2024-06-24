#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_select.h"
#include "dialog_change.h"
#include "dialog_add.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_change_clicked();
    void on_pushButton_select_clicked();
    void on_pushButton_add_clicked();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<Film_manager> film_manager;
    std::unique_ptr<Dialog_select> select;
    std::unique_ptr<Dialog_change> change;
    std::unique_ptr<Dialog_add> add;

};

#endif // MAINWINDOW_H
