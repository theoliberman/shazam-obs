#pragma once

#include <obs-module.h>
#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	void ToggleShowHide();
	void showEvent(QShowEvent *event);
	void hideEvent(QHideEvent *event);
	static void audio_capture_callback(void *param, obs_source_t *source,
					   const struct audio_data *data,
					   bool muted);

private Q_SLOTS:
	void ApplyButton();
	void RecordButton();

private:
	Ui::SettingsDialog *ui;
};