#include "overlay.h"
#include "ui_overlay.h"

Overlay::Overlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Overlay)
{
    ui->setupUi(this);
}

Overlay::~Overlay()
{
    delete ui;
}

QPushButton* Overlay::getPushButton() const
{
    return ui->pushButton;
}
