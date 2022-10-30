#include <obs-module.h>
#include <obs.hpp>

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	ui->comboBox->addItem("A");
	ui->comboBox->addItem("B");
	ui->comboBox->addItem("C");
	ui->comboBox->addItem("D");
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::ToggleShowHide()
{
	if (!isVisible())
		setVisible(true);
	else
		setVisible(false);
}