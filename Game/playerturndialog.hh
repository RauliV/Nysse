#ifndef PLAYERTURNDIALOG_HH
#define PLAYERTURNDIALOG_HH

#include <QDialog>
#include "player.hh"

namespace Ui {
class PlayerTurnDialog;
}

class PlayerTurnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerTurnDialog(QWidget *parent = nullptr);
    ~PlayerTurnDialog();

private slots:

    void on_WalkcheckBox_toggled(bool checked);

    void on_ScootercheckBox_2_toggled(bool checked);

    void on_NyssecheckBox_3_toggled(bool checked);

    void on_TaxicheckBox_4_toggled(bool checked);

    void on_WithdrawPushButton_clicked();

private:
    Ui::PlayerTurnDialog *ui;
};

#endif // PLAYERTURNDIALOG_HH
