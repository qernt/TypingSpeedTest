#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QtWidgets>


namespace Ui { class Overlay; }

class Overlay : public QWidget
{
    Q_OBJECT

public:
    explicit Overlay(QWidget *parent = nullptr);
    ~Overlay();

private:
    Ui::Overlay *ui;
};

#endif // OVERLAY_H
