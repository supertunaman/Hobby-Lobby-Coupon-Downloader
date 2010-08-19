#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <QSettings>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    QSettings settings;
    void applySettings();
    void resetDefaults();

private slots:
    void on_buttonBox_clicked(QAbstractButton* button);
};

#endif // SETTINGSDIALOG_H
