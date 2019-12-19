#include "performancebenchmark.h"

PerformanceBenchmark::PerformanceBenchmark(QString name):
    _name(name)
{
    _timer.start();
}

PerformanceBenchmark::~PerformanceBenchmark()
{
    float nSecsElapsed = _timer.nsecsElapsed() / nSecsToMs;
    qDebug() << "Benchmark " << _name << ": " << nSecsElapsed << " ms";
}
