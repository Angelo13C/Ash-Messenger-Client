#include "performancebenchmark.h"

PerformanceBenchmark::PerformanceBenchmark(QString name, bool start):
    _name(name)
{
    if(start)
        _timer.start();
}

PerformanceBenchmark::~PerformanceBenchmark()
{
    stop();
}

void PerformanceBenchmark::start()
{
    _timer.start();
}

void PerformanceBenchmark::stop()
{
    float nSecsElapsed = _timer.nsecsElapsed() / nSecsToMs;
    qDebug() << "Benchmark" << _name << ":" << nSecsElapsed << "ms";
}
