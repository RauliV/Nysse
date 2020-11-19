#ifndef SETTINGSDIALOG_HH
#define SETTINGSDIALOG_HH

#include <vector>
#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = nullptr);
    ~settingsDialog();

signals:
    //void settingsSet(int numberOfPlayers, std::vector<player> players );

private slots:
    void on_NumberOfPlayersSpinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::settingsDialog *ui;


};

#endif // SETTINGSDIALOG_HH
