#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "./MainWindow.h"
#include "./ScoreWindow.h"
#include <iostream>

using std::cout;
using std::endl;

class Processor : public QObject{
private:
    Q_OBJECT
    MainWindow main_window;
    ScoreWindow score_window;

private slots:
    void run_score_window(int);
    void rerun_main_window();

public:
    Processor();

    void run_main_window();
};

#endif // PROCESSOR_H
