#ifndef DIALOG_ADD1_H
#define DIALOG_ADD1_H

#include <QDialog>
#include <Films.h>

namespace Ui {
class Dialog_add;
}

class Dialog_add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add(std::shared_ptr<Films> films, QWidget *parent = nullptr);
    ~Dialog_add();

private slots:

    void on_Dia_cancel_clicked();

    void on_Dia_ok_clicked();

    void closeEvent(QCloseEvent *);

private:
    Ui::Dialog_add *ui;
    std::shared_ptr<Films> films;
};

#endif // DIALOG_ADD1_H
