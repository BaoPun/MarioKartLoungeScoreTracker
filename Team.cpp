#include "./Team.h"

Team::Team(){
    this->tag = "";
    this->points = 0;
    this->limit = -1;
}

QString Team::get_tag(){
    return this->tag;
}

int Team::get_points() const{
    return this->points;
}

int Team::get_limit(){
    return this->limit;
}

void Team::set_tag(QString tag){
    this->tag = tag;
}

void Team::add_points(int points){
    this->points += points;
}

/**
 * @brief Either preset the limit to the format if adding the team or moving onto the next race.
 * @param limit
 */
void Team::set_limit(int format){
    if(this->limit == -1 || this->limit == 0)
        this->limit = format;
}

/**
 * @brief Decrease the # of teammates from this team by 1 after adding their points.  But has to be > 0
 * @param format
 */
void Team::added_to_race(){
    if(this->limit > 0)
        --this->limit;
}


