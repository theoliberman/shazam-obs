#include <obs-module.h>
#include <obs.hpp>
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
	blog(LOG_INFO, "Show event");
}

bool SettingsDialog::EnumAudioSources(void *data, obs_source_t *source)
{
	uint32_t flags = obs_source_get_output_flags(source);

	if ((flags & OBS_SOURCE_AUDIO) != 0) {
		const char *name = obs_source_get_name(source);
		ui->comboBox->addItem(name);
	}
	return true;
}