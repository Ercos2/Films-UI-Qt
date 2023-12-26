#ifndef DIALOG_SELECT1_H
#define DIALOG_SELECT1_H

#include <QDialog>
#include <Films.h>

namespace Ui {
class Dialog_select;
}

class Dialog_select : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_select(std::shared_ptr<Films> new_films, QWidget *parent = nullptr);
    ~Dialog_select();

private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_info_clicked();

    void on_pushButton_yes_clicked();

    void closeEvent(QCloseEvent *);

private:
    Ui::Dialog_select *ui;
    std::shared_ptr<Films> films;
};

#endif // DIALOG_SELECT1_H
