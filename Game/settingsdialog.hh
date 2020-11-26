#ifndef SETTINGSDIALOG_HH
#define SETTINGSDIALOG_HH

#include <vector>
#include <QDialog>
#include <QtWidgets>
#include <utility>

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
    void settingsSet(std::vector<std::pair<QString , QString>>);

private slots:

    void on_buttonBox_accepted();

    void on_ConfirmPushButton_clicked();

    std::pair<QLineEdit*, QComboBox*> createPlayerOptions();

private:
    Ui::settingsDialog *ui;
    std::vector<std::pair<QLineEdit*, QComboBox*>> players_;


};

#endif // SETTINGSDIALOG_HH
