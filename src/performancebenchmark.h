#pragma once
#include <QDebug>
#include <QElapsedTimer>

class PerformanceBenchmark
{
public:
    PerformanceBenchmark(QString name);
    ~PerformanceBenchmark();

private:
    QString _name;

    static constexpr int nSecsToMs = 1000000;
    QElapsedTimer _timer;
};

