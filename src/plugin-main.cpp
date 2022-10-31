/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <QAction>
#include <QMainWindow>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <util/config-file.h>
#include "plugin-macros.generated.h"
#include "forms/SettingsDialog.h"

#define CONFIG_SECTION_NAME "ShazamOBS"

#define PARAM_SOURCE "SourceName"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

SettingsDialog *_settingsDialog = nullptr;

static void audio_capture_callback(void *param, obs_source_t *source,
				   const struct audio_data *data, bool muted)
{
	UNUSED_PARAMETER(source);

	blog(LOG_INFO, "Audio callback");
}

bool obs_module_load(void)
{

	config_t *obsConfig = obs_frontend_get_global_config();
	auto SourceName =
		config_get_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCE);
	obs_source_t source = *obs_get_source_by_name(SourceName);
	obs_source_add_audio_capture_callback(source, audio_capture_callback,
					      nullptr);

	obs_frontend_push_ui_translation(obs_module_get_string);
	QMainWindow *mainWindow =
		static_cast<QMainWindow *>(obs_frontend_get_main_window());
	_settingsDialog = new SettingsDialog(mainWindow);
	obs_frontend_pop_ui_translation();

	const char *menuActionText =
		obs_module_text("ShazamOBS.Settings.DialogTitle");
	QAction *menuAction =
		(QAction *)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, &QAction::triggered,
			 [] { _settingsDialog->ToggleShowHide(); });

	blog(LOG_INFO, "plugin loaded successfully (version %s)",
	     PLUGIN_VERSION);
	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "plugin unloaded");
}
