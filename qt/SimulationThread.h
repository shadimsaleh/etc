#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Simulator;

class SimulationThread : public QThread
{
    Q_OBJECT

public:
    SimulationThread(Simulator* simulator, QObject* parent = NULL);
    ~SimulationThread();

    void abortThread();
    bool startThread();
    bool pause();
    void wakeSimulation();

private:
    void run();

    Simulator*  simulator_;
    QMutex          mutex_;
    QWaitCondition  pauseCondition_;
    unsigned int    interval_;
    bool            abort_;
    bool            pause_;
};
