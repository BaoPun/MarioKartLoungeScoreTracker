#include "./Processor.h"

Processor::Processor(){}

void Processor::run_main_window(){
    this->main_window.execute();

    connect(&this->main_window, SIGNAL(get_format(int)), this, SLOT(run_score_window(int)), Qt::UniqueConnection);
    connect(&this->score_window, SIGNAL(return_main_menu()), this, SLOT(rerun_main_window()), Qt::UniqueConnection);
}


void Processor::run_score_window(int format){
    cout << "Format: ";
    if(format == 2){
        cout << "2v2" << endl;
    }
    else if(format == 3){
        cout << "3v3" << endl;
    }
    else if(format == 4){
        cout << "4v4" << endl;
    }
    else if(format == 6){
        cout << "6v6" << endl;
    }

    this->score_window.execute(format);
}

void Processor::rerun_main_window(){
    this->run_main_window();
}
