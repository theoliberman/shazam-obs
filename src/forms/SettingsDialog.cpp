#include <obs-module.h>
#include <obs.hpp>
#include <obs-frontend-api.h>
#include "../plugin-macros.generated.h"
#include "SettingsDialog.h"

#define CONFIG_SECTION_NAME "ShazamOBS"

#define PARAM_SOURCE "SourceName"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
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

	config_t *obsConfig = obs_frontend_get_global_config();
	auto SourceName =
		config_get_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCE);
	blog(LOG_INFO, "config loaded successfully %s", SourceName);

	using cb_t = decltype(cb);

	obs_enum_sources(
		[](void *d, obs_source_t *source) {
			return (*static_cast<cb_t *>(d))(source);
		},
		&cb);
}

void SettingsDialog::hideEvent(QHideEvent *)
{
	ui->comboBox->clear();
}