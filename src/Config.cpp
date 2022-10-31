#include <obs-frontend-api.h>

#include "Config.h"
#include "utils/Platform.h"

#define CONFIG_SECTION_NAME "ShazamOBS"

#define PARAM_SOURCENAME "SourceName"

Config::Config()
	: SourceName("")
{
	SetDefaultsToGlobalStore();
}

void Config::Load()
{
	config_t *obsConfig = GetConfigStore();
	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::Load] Unable to fetch OBS config!");
		return;
	}

	SourceName = config_get_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCENAME);
}

void Config::Save()
{
	config_t *obsConfig = GetConfigStore();
	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::Save] Unable to fetch OBS config!");
		return;
	}

    config_set_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCENAME, SourceName);

	config_save(obsConfig);
}

void Config::SetDefaultsToGlobalStore()
{
	config_t *obsConfig = GetConfigStore();
	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::SetDefaultsToGlobalStore] Unable to fetch OBS config!");
		return;
	}

	config_set_default_string(obsConfig, CONFIG_SECTION_NAME, PARAM_SOURCENAME, SourceName);
}

config_t *Config::GetConfigStore()
{
	return obs_frontend_get_global_config();
}