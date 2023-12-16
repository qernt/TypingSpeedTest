#include "timer.h"

Timer::Timer(int duration, QObject *parent) : QObject(parent), remainingTime(duration)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::onTimeout);
    timer->setInterval(1000);
}

void Timer::start()
{
    timer->start();
}

void Timer::onTimeout()
{
    remainingTime--;
    emit updateLabel(QString::number(remainingTime));

    if (remainingTime <= 0)
    {
        timer->stop();
        emit finished();
    }
}

