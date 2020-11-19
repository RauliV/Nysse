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

void settingsDialog::on_NumberOfPlayersSpinBox_valueChanged(int arg1)
{
    //Riippuen pelaajien määrästä
    switch(arg1){
        case 0: ui->PlayerNameLineEdit_1->setEnabled(false);
                ui->PlayerNameLineEdit_2->setEnabled(false);
                ui->PlayerNameLineEdit_3->setEnabled(false);
                ui->PlayerNameLineEdit_4->setEnabled(false);

                ui->PlayerColorComboBox_1->setEnabled(false);
                ui->PlayerColorComboBox_2->setEnabled(false);
                ui->PlayerColorComboBox_3->setEnabled(false);
                ui->PlayerColorComboBox_4->setEnabled(false);

        case 1: ui->PlayerNameLineEdit_1->setEnabled(true);
                ui->PlayerNameLineEdit_2->setEnabled(false);
                ui->PlayerNameLineEdit_3->setEnabled(false);
                ui->PlayerNameLineEdit_4->setEnabled(false);

                ui->PlayerColorComboBox_1->setEnabled(true);
                ui->PlayerColorComboBox_2->setEnabled(false);
                ui->PlayerColorComboBox_3->setEnabled(false);
                ui->PlayerColorComboBox_4->setEnabled(false);

        case 2: ui->PlayerNameLineEdit_1->setEnabled(true);
                ui->PlayerNameLineEdit_2->setEnabled(true);
                ui->PlayerNameLineEdit_3->setEnabled(false);
                ui->PlayerNameLineEdit_4->setEnabled(false);

                ui->PlayerColorComboBox_1->setEnabled(true);
                ui->PlayerColorComboBox_2->setEnabled(true);
                ui->PlayerColorComboBox_3->setEnabled(false);
                ui->PlayerColorComboBox_4->setEnabled(false);

        case 3: ui->PlayerNameLineEdit_1->setEnabled(true);
                ui->PlayerNameLineEdit_2->setEnabled(true);
                ui->PlayerNameLineEdit_3->setEnabled(true);
                ui->PlayerNameLineEdit_4->setEnabled(false);

                ui->PlayerColorComboBox_1->setEnabled(true);
                ui->PlayerColorComboBox_2->setEnabled(true);
                ui->PlayerColorComboBox_3->setEnabled(true);
                ui->PlayerColorComboBox_4->setEnabled(false);

        case 4: ui->PlayerNameLineEdit_1->setEnabled(true);
                ui->PlayerNameLineEdit_2->setEnabled(true);
                ui->PlayerNameLineEdit_3->setEnabled(true);
                ui->PlayerNameLineEdit_4->setEnabled(true);

                ui->PlayerColorComboBox_1->setEnabled(true);
                ui->PlayerColorComboBox_2->setEnabled(true);
                ui->PlayerColorComboBox_3->setEnabled(true);
                ui->PlayerColorComboBox_4->setEnabled(true);
    }
}

void settingsDialog::on_buttonBox_accepted()
{
    int players = ui->NumberOfPlayersSpinBox->value();
    switch (players) {
    case 0:;

    }
}
