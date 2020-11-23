#include "playerturndialog.hh"
#include "ui_playerturndialog.h"

PlayerTurnDialog::PlayerTurnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerTurnDialog)
{
    ui->setupUi(this);
}

PlayerTurnDialog::~PlayerTurnDialog()
{
    delete ui;
}
