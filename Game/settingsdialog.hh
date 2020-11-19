#ifndef SETTINGSDIALOG_HH
#define SETTINGSDIALOG_HH

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

private slots:
    void on_NumberOfPlayersSpinBox_valueChanged(int arg1);

private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_HH
