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

void PlayerTurnDialog::on_WalkcheckBox_toggled(bool checked)
{
    if (checked) {
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
    }
    else{ui->WalkcheckBox->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_ScootercheckBox_2_toggled(bool checked)
{
    if (checked) {
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
    }
    else{ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_NyssecheckBox_3_toggled(bool checked)
{
    if (checked) {
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
    }
    else{ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_TaxicheckBox_4_toggled(bool checked)
{
    if (checked) {
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
    }
    else{ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_WithdrawPushButton_clicked()
{
    ui->WithdrawPushButton->setDisabled(true);
}

