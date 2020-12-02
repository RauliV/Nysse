#ifndef PLAYERTURNDIALOG_HH
#define PLAYERTURNDIALOG_HH

#include <QDialog>
#include <QtDebug>

#include "actors/player.hh"

namespace Ui {
class PlayerTurnDialog;
}

class PlayerTurnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerTurnDialog(QWidget *parent = nullptr, Player* playerInTurn = new Player("Kalle", "musta") );
    ~PlayerTurnDialog();

private slots:

    void on_WalkcheckBox_toggled(bool checked);

    void on_ScootercheckBox_2_toggled(bool checked);

    void on_NyssecheckBox_3_toggled(bool checked);

    void on_TaxicheckBox_4_toggled(bool checked);

    void on_WithdrawPushButton_clicked();

    void on_MovePushButton_2_clicked();

    void updateLabels();

    void on_EnterBarPushButton_3_clicked();
    
    void on_DirectionCheckBox_toggled(bool checked);

    void on_DirectionCheckBox_2_toggled(bool checked);

    void on_DirectionCheckBox_3_toggled(bool checked);

    void on_DirectionCheckBox_4_toggled(bool checked);


private:
    Player* playerInTurn_;
    Ui::PlayerTurnDialog *ui;
    QString vehicle_;
    QString direction_;
    Interface::Location destination_;
};

#endif // PLAYERTURNDIALOG_HH
