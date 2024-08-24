#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include "./Team.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QBoxLayout>
#include <QClipboard>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

QT_BEGIN_NAMESPACE
namespace Ui{
class ScoreWindow;
}
QT_END_NAMESPACE

class ScoreWindow : public QMainWindow{
private:
    Q_OBJECT
    Ui::ScoreWindow* ui;

    vector<Team> teams;
    int format;
    int race_nbr;
    int race_placement;

    void set_team_additions_display(bool);
    void set_point_allocations_display(bool);
    int get_points_from_placement();
    void update_score_differences();

    void delete_layouts();

    bool eventFilter(QObject*, QEvent*);



private slots:
    void process_tag();
    void process_points();
    void copy_score_differentials();
    void back_to_main_menu();

signals:
    void return_main_menu();


public:
    ScoreWindow(QWidget* parent = nullptr);
    ~ScoreWindow();

    void execute(int);
};

#endif // SCOREWINDOW_H
