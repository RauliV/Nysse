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

}

