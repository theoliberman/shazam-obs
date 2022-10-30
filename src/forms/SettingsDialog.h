#pragma once

#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	void ToggleShowHide();
	void showEvent(QShowEvent *event);
	bool EnumAudioSources(void *data, obs_source_t *source);

private:
	Ui::SettingsDialog *ui;
};