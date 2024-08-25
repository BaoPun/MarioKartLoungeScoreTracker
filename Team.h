#ifndef TEAM_H
#define TEAM_H

#include <QString>

class Team{
private:
    QString tag;
    int points;
    int limit;      // limit to how many additions can be made per race

public:
    Team();

    QString get_tag();
    int get_points() const;
    int get_limit();

    void set_tag(QString);
    void add_points(int);


    void set_limit(int, bool = false);
    void added_to_race();
};

#endif // TEAM_H
