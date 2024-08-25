#include "./Processor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/ICANT_KEKW.ico"));
    Processor p;
    p.run_main_window();
    return a.exec();
}
