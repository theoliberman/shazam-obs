#include <obs-module.h>
#include <obs.hpp>
#include <obs-frontend-api.h>
#include "../plugin-macros.generated.h"
#include "SettingsDialog.h"
#include <util/config-file.h>
#include <QString>

#define CONFIG_SECTION_NAME "ShazamOBS"

#define PARAM_SOURCE "SourceName"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	connect(ui->applyButton, &QPushButton::clicked, this,
		&SettingsDialog::ApplyButton);
	connect(ui->recordButton, &QPushButton::clicked, this,
		&SettingsDialog::RecordButton);
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

void SettingsDialog::showEvent(QShowEvent *)
{
	auto cb = [this](obs_source_t *source) {
		const char *name = obs_source_get_name(source);
		ui->comboBox->addItem(name);
		return true;
	};

	using cb_t = decltype(cb);

	obs_enum_sources(
		[](void *d, obs_source_t *source) {
			return (*static_cast<cb_t *>(d))(source);
		},
		&cb);

	config_t *obsConfig = obs_frontend_get_global_config();
	auto SourceName =
		config_get_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCE);
	int index = ui->comboBox->findText(SourceName);
	if (index != -1) {
		ui->comboBox->setCurrentIndex(index);
	}
}

void SettingsDialog::hideEvent(QHideEvent *)
{
	ui->comboBox->clear();
}

void SettingsDialog::ApplyButton()
{
	config_t *obsConfig = obs_frontend_get_global_config();
	QString str1 = ui->comboBox->currentText();
	QByteArray ba = str1.toLocal8Bit();
	const char *selected_source = ba.data();
	config_set_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCE,
			  selected_source);
}

void SettingsDialog::RecordButton()
{
	config_t *obsConfig = obs_frontend_get_global_config();
	auto SourceName =
		config_get_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCE);
	obs_source_t *source = obs_get_source_by_name(SourceName);
	obs_properties_t *props = obs_source_properties(source);
	blog(LOG_INFO, "Add audio callback to : %s", props->id);
}