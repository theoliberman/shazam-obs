#include <obs-module.h>
#include <obs.hpp>

#include "SettingsDialog.h"

bool enum_audio_sources(void *ui, obs_source_t *source)
{
	uint32_t flags = obs_source_get_output_flags(source);

	if ((flags & OBS_SOURCE_AUDIO) != 0) {
		const char *name = obs_source_get_name(source);
		ui->comboBox->addItem(name)
	}
	return true;
}

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	obs_enum_sources(enum_audio_sources, ui);
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