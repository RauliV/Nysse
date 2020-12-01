#ifndef SETTINGSDIALOG_HH
#define SETTINGSDIALOG_HH

#include <vector>
#include <QDialog>
#include <QtWidgets>
#include <utility>
#include <string>

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
    void settingsSet(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs);


private slots:

    void on_buttonBox_accepted();

    void on_ConfirmPushButton_clicked();

    std::pair<QLineEdit*, QComboBox*> createPlayerOptions();

private:
    Ui::settingsDialog *ui;
    int playerCount_;
    std::vector<std::pair<QLineEdit*, QComboBox*>> players_;
    std::vector<std::pair<std::string, std::string>> playerSpecs_;


};

#endif // SETTINGSDIALOG_HH
