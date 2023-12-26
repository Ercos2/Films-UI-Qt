#ifndef DIALOG_CHANGE1_H
#define DIALOG_CHANGE1_H

#include <QDialog>
#include <Films.h>

namespace Ui {
class Dialog_change;
}

class Dialog_change : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_change(std::shared_ptr<Films> films, QWidget *parent = nullptr);
    ~Dialog_change();

private slots:
    void on_Dia_ok_clicked();

    void on_Dia_cancel_clicked();

    void closeEvent(QCloseEvent *);

private:
    Ui::Dialog_change *ui;
    std::shared_ptr<Films> films;
};

#endif // DIALOG_CHANGE1_H
