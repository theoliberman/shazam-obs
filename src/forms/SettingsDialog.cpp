#include <obs-module.h>
#include <obs.hpp>
#include <util/config-file.h>
#include "../plugin-macros.generated.h"

#include "SettingsDialog.h"

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

	char *section;
	char sectionchar[] = "ShazamOBS";
	char *conf_name;
	char conf_name_char[] = "SourceName";
	section = sectionchar;
	conf_name = conf_name_char;

	config_t **_config = nullptr;
	config_open(_config, "ShazamOBS", CONFIG_OPEN_ALWAYS);
	char *source_name = config_get_string(*_config, section, conf_name);
	blog(LOG_INFO, "Loaded conf : %s", source_name);
	config_close(*_config);

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