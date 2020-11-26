#include "settingsdialog.hh"
#include "ui_settingsdialog.h"

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);

}

settingsDialog::~settingsDialog()
{
    delete ui;
}



void settingsDialog::on_buttonBox_accepted()
{
    //extracting player names and colors from the widgets
    for(unsigned int i = 0; i < players_.size(); i++)
    {
        QLineEdit* nameEdit = std::get<0>(players_.at(i));
        QComboBox* colorEdit = std::get<1>(players_.at(i));
        QString name = nameEdit->text();
        QString color = colorEdit->currentText();
    }
}

void settingsDialog::on_ConfirmPushButton_clicked()
{
    int numberOfPlayers = ui->NumberOfPlayersSpinBox->value();
    for(int i = 0; i< numberOfPlayers; i++)
    {
        std::tuple<QLineEdit*, QComboBox*> player = createPlayerOptions();
        players_.push_back(player);
    }
    ui->ConfirmPushButton->setDisabled(true);
}

std::tuple<QLineEdit*, QComboBox*> settingsDialog::createPlayerOptions()
{
    //Creating widgets for player options
    QLineEdit *playerName = new QLineEdit();
    QLabel *label = new QLabel("Player Name");
    QComboBox *playerColor = new QComboBox();
    QStringList colors = {"Red", "Blue", "Green", "Yellow"};
    playerColor->addItems(colors);
    std::tuple<QLineEdit*, QComboBox*> specs(playerName, playerColor);

    //Creating layout for the widgets
    QVBoxLayout *pLayout = new QVBoxLayout;
    QHBoxLayout *hNameColor = new QHBoxLayout;
    hNameColor->addWidget(playerName);
    hNameColor->addWidget(playerColor);
    pLayout->addWidget(label);
    pLayout->addLayout(hNameColor);
    //Adding layout to ui
    ui->verticalLayout->addLayout(pLayout);

    return specs;
}
