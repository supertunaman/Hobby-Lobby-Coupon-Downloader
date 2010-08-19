#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QString tba = settings.value("toolbar/area", "left").toString();
    if (tba == "top")
        ui->topRad->setChecked(true);
    else if (tba == "right")
        ui->rightRad->setChecked(true);
    else if (tba == "bottom")
        ui->bottomRad->setChecked(true);
    else
        ui->leftRad->setChecked(true);  // You've tried the rest, now try the left!

    ui->grayscaleChck->setChecked(settings.value("printing/grayscale", false).toBool());
    ui->paddingBox->setValue(settings.value("printing/padding", 15).toInt());
    ui->printDialogChck->setChecked(settings.value("printing/showdialog", true).toBool());

    ui->updatesChck->setChecked(settings.value("update/checkonstartup", true).toBool());
    ui->updateUrl->setText(settings.value("update/url", "http://supertunaman.com/hlcdupdate.txt").toString());

    ui->couponPageUrl->setText(settings.value("coupon/pageurl", "http://hobbylobby.com/weekly/coupon.cfm").toString());
    ui->discrimText->setText(settings.value("coupon/discriminatorytext", "/assets/dynamic/_weekly.coupon/").toString());
    ui->leftTrim->setText(settings.value("coupon/lefttrim", "<a href=\"").toString());
    ui->rightTrim->setText(settings.value("coupon/righttrim", "\">").toString());
    ui->prefix->setText(settings.value("coupon/prefix", "http://hobbylobby.com").toString());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button->text() == "OK")
        this->applySettings();
    else if (button->text() == "Restore Defaults")
        this->resetDefaults();
}

void SettingsDialog::applySettings()
{
    if (ui->topRad->isChecked())
        settings.setValue("toolbar/area", "top");
    else if (ui->rightRad->isChecked())
        settings.setValue("toolbar/area", "right");
    else if (ui->bottomRad->isChecked())
        settings.setValue("toolbar/area", "bottom");
    else
        settings.setValue("toolbar/area", "left");

    settings.setValue("printing/grayscale", ui->grayscaleChck->isChecked());
    settings.setValue("printing/padding", ui->paddingBox->value());
    settings.setValue("printing/showdialog", ui->printDialogChck->isChecked());

    settings.setValue("update/checkonstartup", ui->updatesChck->isChecked());
    settings.setValue("update/url", ui->updateUrl->text());

    settings.setValue("coupon/pageurl", ui->couponPageUrl->text());
    settings.setValue("coupon/discriminatorytext", ui->discrimText->text());
    settings.setValue("coupon/leftrim", ui->leftTrim->text());
    settings.setValue("coupon/righttrim", ui->rightTrim->text());
    settings.setValue("coupon/prefix", ui->prefix->text());
}

void SettingsDialog::resetDefaults()
{
    ui->leftRad->setChecked(true);

    ui->grayscaleChck->setChecked(false);
    ui->paddingBox->setValue(15);
    ui->printDialogChck->setChecked(true);

    ui->updatesChck->setChecked(true);
    ui->updateUrl->setText("http://supertunaman.com/hlcdupdate.txt");

    ui->couponPageUrl->setText("http://hobbylobby.com/weekly/coupon.cfm");
    ui->discrimText->setText("/assets/dynamic/_weekly.coupon/");
    ui->leftTrim->setText("<a href=\"");
    ui->rightTrim->setText("\">");
    ui->prefix->setText("http://hobbylobby.com");
}
