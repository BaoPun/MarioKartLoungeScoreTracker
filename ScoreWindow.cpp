#include "./ScoreWindow.h"
#include "ui_scorewindow.h"

ScoreWindow::ScoreWindow(QString icon_loc, QWidget* parent) : QMainWindow(parent), ui(new Ui::ScoreWindow){
    // Setting up the window + adding custom event filters
    this->ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->ui->centralwidget->installEventFilter(this);
    this->ui->tag_input->installEventFilter(this);
    this->ui->point_input->installEventFilter(this);
    this->setWindowIcon(QIcon(icon_loc));

    // Changing background color and other styles
    this->setStyleSheet("QWidget{background-color: lightblue;} QTextEdit{background-color: white;} QPushButton{background-color: #d8f06a} QListView{background-color: yellow} ");
    this->ui->title_label->setText("<b>" + this->ui->title_label->text() + "</b>");
    this->ui->enter_tag_label->setText("<b>" + this->ui->enter_tag_label->text() + "</b>");

    // Initializing race states
    this->race_nbr = 1;
    this->race_placement = 1;   
}

/**
 * @brief Destructor that deallocates the layouts and the entire window safely
 */
ScoreWindow::~ScoreWindow(){
    this->delete_layouts();
    if(this->ui != nullptr){
        delete this->ui;
        this->ui = nullptr;
    }
}

/**
 * @brief Submits a team with specified tag onto the vector.  Invalid if team name already exists.
 */
void ScoreWindow::process_tag(){
    QString tag = this->ui->tag_input->toPlainText().trimmed();
    bool is_valid_tag = (tag != "");

    // Make sure that the team's tag is NOT already in the list
    // Update: no 2 tags can start with the same letter. (K and KT will fail)
    for(size_t i = 0; i < this->teams.size() && is_valid_tag; i++){
        if(tag.toUpper().at(0) == this->teams.at(i).get_tag().toUpper().at(0))
            is_valid_tag = false;
    }

    // Submit the team, but only if the tag is valid
    if(is_valid_tag){
        this->teams.push_back(Team());
        this->teams.back().set_tag(tag);
        this->teams.back().set_limit(this->format);
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Tag already added");
        msgBox.setText("Error, the requested tag (" + tag + ") is already added.");
        msgBox.exec();
    }

    // After adding the team, bring focus back to the tag input and clear the field
    // However, if the maximum # of teams is added, then update the look of the window instead.
    if(this->teams.size() != 12ull / this->format){
        this->ui->tag_input->setText("");
        this->ui->tag_input->setFocus();
    }
    else{
        qDebug() << "Maximum number of teams made.  Time to update the window instead.";

        // Hide the widgets responsible for displaying/adding teams
        this->set_team_additions_display(false);

        // Show widgets responsible for allocating points after all teams are made
        this->set_point_allocations_display(true);
        this->ui->point_input->setReadOnly(false);
        this->ui->point_input->setFocus();

        // Change race label to "Race {race_nbr}"
        this->ui->race_label->setText("<b>Race " + QString::number(this->race_nbr) + "</b>");

        // Change point label to "Enter tag for {placement} place:"
        // On initial setup, always first place
        this->ui->point_label->setText("<b>Enter tag for 1st place:</b>");

        // Create layout
        QBoxLayout* team_layout = new QHBoxLayout();
        QBoxLayout* point_layout = new QHBoxLayout();
        QBoxLayout* limit_layout = new QHBoxLayout();
        for(size_t i = 0; i < this->teams.size(); i++){
            // For each team,  add both the team tag and points within the list view
            QLabel* team_label = new QLabel();
            QLabel* point_label = new QLabel();
            QLabel* limit_label = new QLabel();
            team_label->setText("<b>" + this->teams.at(i).get_tag() + "<b>");
            team_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            team_label->setStyleSheet("background-color: yellow;");
            team_layout->addWidget(team_label);
            point_label->setText(QString::number(this->teams.at(i).get_points()));
            point_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            point_label->setStyleSheet("background-color: yellow;");
            point_layout->addWidget(point_label);
            limit_label->setText(QString::number(this->format) + "/" + QString::number(this->format));
            limit_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            limit_label->setStyleSheet("background-color: yellow;");
            limit_layout->addWidget(limit_label);
        }
        this->ui->team_view->setLayout(team_layout);
        this->ui->point_view->setLayout(point_layout);
        this->ui->limit_view->setLayout(limit_layout);

        // And display the score differentials
        this->update_score_differences();
    }
}

/**
 * @brief Determines the number of points earned based on placement
 * @return the number of points earned per race.
 */
int ScoreWindow::get_points_from_placement(){
    switch(this->race_placement){
        case 1: return 15;
        case 2: return 12;
        case 3: return 10;
        case 4: return 9;
        case 5: return 8;
        case 6: return 7;
        case 7: return 6;
        case 8: return 5;
        case 9: return 4;
        case 10: return 3;
        case 11: return 2;
        case 12: return 1;
        default: return 0;
    }
}

/**
 * @brief Sorts the teams by # of points acquired in descending order
 */
void ScoreWindow::update_score_differences(){
    // First, sort the teams by highest score
    vector<Team> temp = this->teams;
    sort(temp.begin(), temp.end(), [](const Team& t1, const Team& t2){return t1.get_points() > t2.get_points();});

    // Then, display the output with the following format:
    // {t1} {t1_points} (t1_points - t2_points), {t2} {t2_points} ...
    QString score_display;
    score_display += "[" + (temp.at(0).get_tag() + "] - " + QString::number(temp.at(0).get_points())) + " pts";
    for(size_t i = 1; i < this->teams.size(); i++){
        score_display += " (+" + QString::number(temp.at(i - 1).get_points() - temp.at(i).get_points()) + ") / ";
        score_display += "[" + temp.at(i).get_tag() + "] - " + QString::number(temp.at(i).get_points()) + " pts";
    }
    this->ui->score_diff_display->setText("<b>" + score_display + "</b>");
}

/**
 * @brief Deallocate all widgets from all 3 layouts
 */
void ScoreWindow::delete_layouts(){
    if(this->ui->team_view->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->ui->team_view->layout()->isEmpty()){
            item = this->ui->team_view->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->ui->team_view->layout();
    }
    if(this->ui->point_view->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->ui->point_view->layout()->isEmpty()){
            item = this->ui->point_view->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->ui->point_view->layout();
    }
    if(this->ui->limit_view->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->ui->limit_view->layout()->isEmpty()){
            item = this->ui->limit_view->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->ui->limit_view->layout();
    }
}

/**
 * @brief Processes a team member with specified tag based on their placement.
 */
void ScoreWindow::process_points(){
    // First, validate that the input matches with one of the tags
    // Also make sure that a team does not get allocated points more than necessary
    int team_idx = -1;
    for(size_t i = 0; i < this->teams.size() && team_idx == -1; i++){
        if(this->teams.at(i).get_tag().at(0).toUpper() == this->ui->point_input->toPlainText().trimmed().at(0).toUpper() && this->teams.at(i).get_limit() > 0){
            team_idx = i;
        }
    }

    // Then, add the points to the inputted team, but only if the flag is true
    if(team_idx > -1){
        // Based on the placement and team, add that many points
        this->teams.at(team_idx).add_points(this->get_points_from_placement());

        // Also decrease the teams' limit per race by 1
        this->teams.at(team_idx).added_to_race();

        // ALso Update score differences
        this->update_score_differences();

        // Also update the point view
        QLabel* updated_point_label = static_cast<QLabel*>(this->ui->point_view->layout()->itemAt(team_idx)->widget());
        updated_point_label->setText(QString::number(this->teams.at(team_idx).get_points()));

        // Also add the team to the race placements
        this->current_placements.push_back(this->teams.at(team_idx).get_tag());

        // Increment the race placement
        this->race_placement++;

        // Update the point label (different for 2nd and 3rd)
        if(this->race_placement == 2)
            this->ui->point_label->setText("<b>Enter tag for 2nd place:</b>");
        else if(this->race_placement == 3)
            this->ui->point_label->setText("<b>Enter tag for 3rd place:</b>");
        else
            this->ui->point_label->setText("<b>Enter tag for " + QString::number(this->race_placement) + "th place:</b>");

        // If the race placement exceeds 12, then reset back to 1, and then increment the race counter
        if(this->race_placement > 12){
            this->race_placement = 1;
            this->race_nbr++;

            // Also update the race label
            this->ui->race_label->setText("<b>Race " + QString::number(this->race_nbr) + "</b>");

            // And the point label
            this->ui->point_label->setText("<b>Enter tag for 1st place:</b>");

            // And clear out the current placements vector from the previous race
            this->current_placements.clear();

            // For all teams, reset the limit and also reset the limit label
            for(size_t i = 0; i < this->teams.size(); i++){
                this->teams.at(i).set_limit(this->format);
                // Also update the limit view
                QLabel* updated_limit_label = static_cast<QLabel*>(this->ui->limit_view->layout()->itemAt(i)->widget());
                updated_limit_label->setText(QString::number(this->format) + "/" + QString::number(this->format));
            }

            // Freeze all input once the mogi is over
            if(this->race_nbr > 12){
                qDebug() << "Mogi is over";
                this->ui->race_label->setText("Mogi is over");
                this->ui->point_input->setReadOnly(true);
                //this->ui->main_menu_button->setVisible(true);
                this->ui->point_label->setText("");
            }


        }
        else{
            // Update the limit view for the affected team
            QLabel* updated_limit_label = static_cast<QLabel*>(this->ui->limit_view->layout()->itemAt(team_idx)->widget());
            updated_limit_label->setText(QString::number(this->teams.at(team_idx).get_limit()) + "/" + QString::number(this->format));
        }


    }
    else{
        if(!this->ui->point_input->isReadOnly()){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Error, requested team [" + this->ui->point_input->toPlainText().trimmed() + "] does not exist or all team members have been allocated for this race already.");
            msgBox.exec();
        }
    }

    // Focus back to the input and clear text
    this->ui->point_input->setFocus();
    this->ui->point_input->setText("");
}

/**
 * @brief Copies the score differentials from the readonly text box onto the clipboard
 */
void ScoreWindow::copy_score_differentials(){
    // Copy the text from the score_diff_display onto the clipboard
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(this->ui->score_diff_display->toPlainText());

    /*// And then display a message box afterwards
    QMessageBox msgBox;
    msgBox.setWindowTitle("Copied successfully");
    msgBox.setText("Score differentials have been copied.");
    msgBox.exec();*/
    qDebug() << "Score differentials copied: " << clipboard->text();

    // Bring focus back to the point input
    this->ui->point_input->setFocus();
}

/**
 * @brief Upon finishing a mogi and clicking on the back to main menu button,
 * a signal will be sent to return to the main menu
 */
void ScoreWindow::back_to_main_menu(){
    // Clear the old layouts
    this->delete_layouts();

    // And clear the teams
    this->teams.clear();

    // Finally, emit a signal to the processor before closing this window.
    Q_EMIT return_main_menu();
    this->close();
}

/**
 * @brief In the event of a mistake, pressing the button will reset points for the current round.
 */
void ScoreWindow::reset_points(){
    // Before doing anything, bring focus back to the point input and reset text field
    this->ui->point_input->setFocus();
    this->ui->point_input->setText("");

    // Do not do anything if there is nothing in the vector
    // Or if the mogi is over
    // Or if we have not entered the first place placement for the current race
    if(this->current_placements.empty() || this->race_nbr > 12 || this->race_placement == 1)
        return;


    // Work backwards: for each team result, subtract that many points.
    // Find the team from the list of teams, and then subtract their points (multiply placement by -1)
    for(int i = this->current_placements.size() - 1; i >= 0; i--){
        for(size_t j = 0; j < this->teams.size(); j++){
            // Once found, do the following:
            // 1. Decrement the placement first (vital step)
            // 2. Subtract the points, via multiplying the points earned by -1
            // 3. Update the point displays
            // 4. Update the score differentials
            if(this->teams.at(j).get_tag() == this->current_placements.at(i)){
                --this->race_placement;
                this->teams.at(j).add_points(-1 * this->get_points_from_placement());
                QLabel* updated_point_label = static_cast<QLabel*>(this->ui->point_view->layout()->itemAt(j)->widget());
                updated_point_label->setText(QString::number(this->teams.at(j).get_points()));
                this->update_score_differences();
                break;
            }
        }
    }

    // Reset the limit for all teams and update the limit display
    for(size_t i = 0; i < this->teams.size(); i++){
        this->teams.at(i).set_limit(this->format, true);

        QLabel* updated_limit_label = static_cast<QLabel*>(this->ui->limit_view->layout()->itemAt(i)->widget());
        updated_limit_label->setText(QString::number(this->format) + "/" + QString::number(this->format));
    }

    // Once points have been reset, clear the current_placements vector
    // Reset the race placement to 1st, and update the point label
    this->current_placements.clear();
    this->ui->point_label->setText("Enter tag for 1st place:");
    this->race_placement = 1;
}

/**
 * @brief Either show or hide the widgets responsible for adding teams.
 * @param flag - true to show, false to hide
 */
void ScoreWindow::set_team_additions_display(bool flag){
    this->ui->submit_team_button->setVisible(flag);
    this->ui->tag_input->setVisible(flag);
    this->ui->enter_tag_label->setVisible(flag);
}

/**
 * @brief Either show or hide the widgets responsible for allocating points to teams.
 * @param flag - true to show, false to hide
 */
void ScoreWindow::set_point_allocations_display(bool flag){
    this->ui->team_view->setVisible(flag);
    this->ui->point_view->setVisible(flag);
    this->ui->score_diff_display->setVisible(flag);
    this->ui->point_label->setVisible(flag);
    this->ui->point_input->setVisible(flag);
    this->ui->submit_point_button->setVisible(flag);
    this->ui->race_label->setVisible(flag);
    this->ui->copy_button->setVisible(flag);
    this->ui->limit_view->setVisible(flag);
    this->ui->pushButton->setVisible(flag);

}

/**
 * @brief Main function that will show the ScoreWindow to add teams and/or allocate points to each team
 * @param format - integer indicating the format (either 2, 3, 4, or 6)
 */
void ScoreWindow::execute(int format){
    // Initialize race states
    this->race_nbr = 1;
    this->race_placement = 1;

    // Show all information regarding team additions
    this->set_team_additions_display(true);

    // Hide extra information until all teams have been added
    this->set_point_allocations_display(false);

    // Clear the placements vector
    this->current_placements.clear();

    // Add teams: set focus to the text input
    this->format = format;
    this->setWindowTitle(QString::number(format) + "v" + QString::number(format) + " Score Tracker");
    this->ui->tag_input->setText("");
    this->ui->tag_input->setFocus();
    this->show();

    // Create a connection when the user presses the button(s)
    connect(this->ui->submit_team_button, SIGNAL(clicked()), this, SLOT(process_tag()), Qt::UniqueConnection);
    connect(this->ui->submit_point_button, SIGNAL(clicked()), this, SLOT(process_points()), Qt::UniqueConnection);
    connect(this->ui->copy_button, SIGNAL(clicked()), this, SLOT(copy_score_differentials()), Qt::UniqueConnection);
    connect(this->ui->main_menu_button, SIGNAL(clicked()), this, SLOT(back_to_main_menu()), Qt::UniqueConnection);
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(reset_points()));
}

/**
 * @brief Customized event filter for specific actions
 * @param object - which part of the window (widget) was affected?
 * @param event - how was the object interacted with (key press or mouse press)?
 * @return True if a specific event(s) on the object(s) was triggered or false otherwise
 */
bool ScoreWindow::eventFilter(QObject* object, QEvent* event){

    // Handle keyboard input events
    if((object == this->ui->tag_input || object == this->ui->point_input || object == this->ui->centralwidget) && event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // Pressing CTRL Q
        if(keyEvent->key() == Qt::Key_Q && (keyEvent->modifiers() & Qt::ControlModifier)){
            this->close();
            return true;
        }

        // Pressing Enter
        else if(keyEvent->key() == Qt::Key_Return){
            // If we are focused on the tag input (textbox), pressing ENTER will also submit the team
            if(object == this->ui->tag_input && this->ui->tag_input->isVisible()){
                this->process_tag();
                return true;
            }

            // If we are focused on the point input (textbox) and it's not on readonly, pressing ENTER will also submit the points
            else if(object == this->ui->point_input && this->ui->point_input->isVisible() && !this->ui->point_input->isReadOnly()){
                this->process_points();
                return true;
            }
        }

        // Pressing TAB
        else if(keyEvent->key() == Qt::Key_Tab){
            // Pressing TAB on tag input will force focus onto the tag input still
            if(object == this->ui->tag_input && this->ui->tag_input->isVisible()){
                this->ui->tag_input->setFocus();
                return true;
            }
            else if(object == this->ui->point_input && this->ui->point_input->isVisible()){
                this->ui->point_input->setFocus();
                return true;
            }
        }

        // Pressing ESC should also trigger the "back to main menu" slot
        else if(keyEvent->key() == Qt::Key_Escape){
            this->back_to_main_menu();
            return true;
        }
    }


    return false;
}


