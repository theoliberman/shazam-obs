#pragma once

#include <util/config-file.h>

#include "plugin-macros.generated.h"

struct Config {
	Config();
	void Load();
	void Save();
	void SetDefaultsToGlobalStore();
	config_t *GetConfigStore();

	char* SourceName;
};