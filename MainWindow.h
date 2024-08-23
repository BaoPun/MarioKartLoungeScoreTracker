#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Q_OBJECT
    Ui::MainWindow *ui;
    int format;

    bool eventFilter(QObject *, QEvent *) override; // Event filtering

private slots:
    void pass_format_to_processor();

signals:
    void get_format(int);
    void button_clicked();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void execute();


};
#endif // MAINWINDOW_H
