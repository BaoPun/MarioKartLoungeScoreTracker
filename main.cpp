#include "./Processor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Processor p;
    p.run_main_window();
    return a.exec();
}
