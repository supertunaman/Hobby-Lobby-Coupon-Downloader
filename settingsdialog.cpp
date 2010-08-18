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
