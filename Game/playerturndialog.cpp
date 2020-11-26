#include "playerturndialog.hh"
#include "ui_playerturndialog.h"

PlayerTurnDialog::PlayerTurnDialog(QWidget *parent, Player* playerInTurn) :
    QDialog(parent),
    ui(new Ui::PlayerTurnDialog)
{
    ui->setupUi(this);
    playerInTurn_ = playerInTurn;
    vehicle_ = "Walk";
    direction_ = "None";
    ui->MovePushButton_2->setDisabled(true);
    updateLabels();
}

PlayerTurnDialog::~PlayerTurnDialog()
{
    delete ui;
}

void PlayerTurnDialog::on_WalkcheckBox_toggled(bool checked)
{
    qDebug() << "Walk";
    if (checked)
    {
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
        vehicle_ = "Walk";
    }
    else{ui->WalkcheckBox->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_ScootercheckBox_2_toggled(bool checked)
{
    qDebug() << "Scooter";
    if (checked)
    {
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
        vehicle_ = "Scooter";
    }
    else{ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_NyssecheckBox_3_toggled(bool checked)
{
    qDebug() << "Nysse";
    if (checked)
    {
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
        ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
        vehicle_ = "Nysse";
    }
    else{ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_TaxicheckBox_4_toggled(bool checked)
{
    qDebug() << "Taxi";
    if (checked)
    {
        ui->ScootercheckBox_2->setCheckState(Qt::Unchecked);
        ui->NyssecheckBox_3->setCheckState(Qt::Unchecked);
        ui->WalkcheckBox->setCheckState(Qt::Unchecked);
        vehicle_ = "Taxi";
    }
    else{ui->TaxicheckBox_4->setCheckState(Qt::Unchecked);}
}

void PlayerTurnDialog::on_WithdrawPushButton_clicked()
{
    qDebug() << "Withdraw cash";
    ui->WithdrawPushButton->setDisabled(true);
    playerInTurn_->withdrawCash(20);
    updateLabels();


}

void PlayerTurnDialog::on_MovePushButton_2_clicked()
{
    qDebug() << "Ja taas mennään";
    if(direction_ != "None")
    {
        playerInTurn_->setIdle(false);
        playerInTurn_->move(destination_);
        this->close();
    }
}

void PlayerTurnDialog::updateLabels()
{
    int cash = playerInTurn_->getCash();
    ui->CashLabel_2->setText("Cash: " + QString::number(cash));

    int bank = playerInTurn_->getBank();
    ui->BankBalanceLabel_3->setText("Bank: " + QString::number(bank));

    int drunkness = playerInTurn_->getDrunkness();
    ui->DrunknessLabel_4->setText("Drunkness: " + QString::number(drunkness));
}

void PlayerTurnDialog::on_EnterBarPushButton_3_clicked()
{
    qDebug() << "Kaljaa koneeseen";
    if(playerInTurn_->spendCash(10)){
        playerInTurn_->drink(1);
        updateLabels();
        playerInTurn_->setIdle(false);
        this->close();
    }
}

void PlayerTurnDialog::on_DirectionCheckBox_toggled(bool checked)
{
    qDebug() << "Option 1";
    if(checked)
    {
        ui->DirectionCheckBox_2->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_3->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_4->setCheckState(Qt::Unchecked);
        ui->MovePushButton_2->setEnabled(true);
        direction_ = ui->DirectionCheckBox->text();
    }
    else
    {
        ui->DirectionCheckBox->setCheckState(Qt::Unchecked);
    }
}

void PlayerTurnDialog::on_DirectionCheckBox_2_toggled(bool checked)
{
    qDebug() << "Option 2";
    if(checked)
    {
        ui->DirectionCheckBox->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_3->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_4->setCheckState(Qt::Unchecked);
        ui->MovePushButton_2->setEnabled(true);
        direction_ = ui->DirectionCheckBox_2->text();
    }
    else
    {
        ui->DirectionCheckBox_2->setCheckState(Qt::Unchecked);
    }
}

void PlayerTurnDialog::on_DirectionCheckBox_3_toggled(bool checked)
{
    qDebug() << "Option 3";
    if(checked)
    {
        ui->DirectionCheckBox_2->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_4->setCheckState(Qt::Unchecked);
        ui->MovePushButton_2->setEnabled(true);
        direction_ = ui->DirectionCheckBox_3->text();
    }
    else
    {
        ui->DirectionCheckBox_3->setCheckState(Qt::Unchecked);
    }
}

void PlayerTurnDialog::on_DirectionCheckBox_4_toggled(bool checked)
{
    qDebug() << "Option 4";
    if(checked)
    {
        ui->DirectionCheckBox_2->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox_3->setCheckState(Qt::Unchecked);
        ui->DirectionCheckBox->setCheckState(Qt::Unchecked);
        ui->MovePushButton_2->setEnabled(true);
        direction_ = ui->DirectionCheckBox_4->text();
    }
    else
    {
        ui->DirectionCheckBox_4->setCheckState(Qt::Unchecked);
    }
}
