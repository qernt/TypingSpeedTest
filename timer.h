#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(int duration, QObject *parent = nullptr);

signals:
    void updateLabel(QString text);
    void finished();

public slots:
    void start();
    void onTimeout();

private:
    QTimer *timer;
    int remainingTime;
};

#endif // TIMER_H
