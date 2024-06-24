#ifndef DIALOG_ADD1_H
#define DIALOG_ADD1_H

#include <QDialog>
#include "film_manager.h"

namespace Ui {
class Dialog_add;
}

class Dialog_add : public QDialog {
    Q_OBJECT

public:
    explicit Dialog_add(std::shared_ptr<Film_manager> film_manager, QWidget *parent = nullptr);
    ~Dialog_add();

private slots:
    void on_Dia_cancel_clicked();
    void on_Dia_ok_clicked();
    void closeEvent(QCloseEvent *);

private:
    std::unique_ptr<Ui::Dialog_add> ui;
    std::shared_ptr<Film_manager> film_manager;

signals:
    void dialog_closed();
};

#endif // DIALOG_ADD1_H
