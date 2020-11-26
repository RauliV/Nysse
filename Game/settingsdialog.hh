#ifndef SETTINGSDIALOG_HH
#define SETTINGSDIALOG_HH

#include <vector>
#include <QDialog>
#include <QtWidgets>
#include <tuple>

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

    void on_buttonBox_accepted();

    void on_ConfirmPushButton_clicked();

    std::tuple<QLineEdit*, QComboBox*> createPlayerOptions();

private:
    Ui::settingsDialog *ui;
    std::vector<std::tuple<QLineEdit*, QComboBox*>> players_;



};

#endif // SETTINGSDIALOG_HH
