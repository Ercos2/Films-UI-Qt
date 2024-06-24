#ifndef DIALOG_CHANGE1_H
#define DIALOG_CHANGE1_H

#include <QDialog>
#include "film_manager.h"

namespace Ui {
class Dialog_change;
}

class Dialog_change : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_change(std::shared_ptr<Film_manager> film_manager, QWidget *parent = nullptr);
    ~Dialog_change();

private slots:
    void on_Dia_ok_clicked();
    void on_Dia_cancel_clicked();
    void closeEvent(QCloseEvent *);

private:
    std::unique_ptr<Ui::Dialog_change> ui;
    std::shared_ptr<Film_manager> film_manager;

signals:
    void dialog_closed();
};

#endif // DIALOG_CHANGE1_H
