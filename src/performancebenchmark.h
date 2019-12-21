#pragma once
#include <QElapsedTimer>

class PerformanceBenchmark
{
public:
    PerformanceBenchmark(QString name, bool start = true);
    ~PerformanceBenchmark();

    void start();
    void stop();

private:
    QString _name;

    static constexpr float nSecsToMs = 1000000;
    QElapsedTimer _timer;
};

