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
	obs_enum_sources(SettingsDialog::enumAudioSources, nullptr);
}

static bool SettingsDialog::enumAudioSources(void *, obs_source_t *source)
{
	uint32_t flags = obs_source_get_output_flags(source);

	if ((flags & OBS_SOURCE_AUDIO) != 0) {
		const char *name = obs_source_get_name(source);
		blog(LOG_INFO, "Source : %s", name);
	}
	return true;
}