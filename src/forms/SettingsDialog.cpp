#include <obs-module.h>
#include <obs.hpp>
#include "../plugin-macros.generated.h"

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	auto cb = [this](obs_source_t *source) {
		uint32_t caps = obs_source_get_output_flags(source);
		char* name = obs_source_get_name(source);
		blog(LOG_INFO, "Source : %s", name);
		return true;
	};

	using cb_t = decltype(cb);
	obs_enum_sources(
		[](void *data, obs_source_t *source) {
			return (*static_cast<cb_t *>(data))(source);
		},
		&cb);
	ui->source->blockSignals(false);
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