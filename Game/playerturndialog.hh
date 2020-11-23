#ifndef PLAYERTURNDIALOG_HH
#define PLAYERTURNDIALOG_HH

#include <QDialog>

namespace Ui {
class PlayerTurnDialog;
}

class PlayerTurnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerTurnDialog(QWidget *parent = nullptr);
    ~PlayerTurnDialog();

private:
    Ui::PlayerTurnDialog *ui;
};

#endif // PLAYERTURNDIALOG_HH
