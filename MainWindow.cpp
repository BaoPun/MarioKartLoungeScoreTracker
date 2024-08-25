#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString icon_loc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->ui->centralwidget->installEventFilter(this);
    this->ui->v2_button->installEventFilter(this);
    this->ui->v3_button->installEventFilter(this);
    this->ui->v4_button->installEventFilter(this);
    this->ui->v6_button->installEventFilter(this);
    this->setWindowIcon(QIcon(icon_loc));
    this->format = -1;
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

/**
 * @brief Sets up the main window and displays it afterwards
 */
void MainWindow::execute(){
    this->setWindowTitle("Choose non-FFA format");
    this->ui->v2_button->setFocus();
    this->show();

    // Add 4 connections: one corresponding to each button
    connect(this->ui->v2_button, SIGNAL(clicked()), this, SLOT(pass_format_to_processor()), Qt::UniqueConnection);
    connect(this->ui->v3_button, SIGNAL(clicked()), this, SLOT(pass_format_to_processor()), Qt::UniqueConnection);
    connect(this->ui->v4_button, SIGNAL(clicked()), this, SLOT(pass_format_to_processor()), Qt::UniqueConnection);
    connect(this->ui->v6_button, SIGNAL(clicked()), this, SLOT(pass_format_to_processor()), Qt::UniqueConnection);
}

/**
 * @brief Helper function that closes this window and then sends a signal to the Processor indicating the format type
 * @param format - either 2 for 2v2, 3 for 3v3, 4 for 4v4, or 6 for 6v6.
 */
void MainWindow::pass_format_to_processor(){
    // Close this window and then emit a signal with the format back to the processor
    if(this->format == 6 || (this->format >= 2 && this->format <= 4))
        Q_EMIT get_format(this->format);
    this->close();
}

/**
 * @brief Specifically overloading a few hotkeys to interact with the window.  CTRL Q.
 * @param object - which part of the window?
 * @param event - any interaction with the window (mouse, key, etc)
 * @return True if a specific hotkey was used, False otherwise
 */
bool MainWindow::eventFilter(QObject* object, QEvent* event){
    // Handle CTRL Q
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Q && (keyEvent->modifiers() & Qt::ControlModifier)){
            this->close();
            return true;
        }
    }

    // Handle different buttons being clicked
    // Needed to use specific event filtering because we want to pass the format type to the processorq
    else if(object == this->ui->v2_button && event->type() == QEvent::MouseButtonRelease){
        this->format = 2;
        Q_EMIT QPushButton().clicked();
        return QMainWindow::eventFilter(object, event);
    }
    else if(object == this->ui->v3_button && event->type() == QEvent::MouseButtonRelease){
        this->format = 3;
        Q_EMIT QPushButton().clicked();
        return QMainWindow::eventFilter(object, event);
    }
    else if(object == this->ui->v4_button && event->type() == QEvent::MouseButtonRelease){
        this->format = 4;
        Q_EMIT QPushButton().clicked();
        return QMainWindow::eventFilter(object, event);
    }
    else if(object == this->ui->v6_button && event->type() == QEvent::MouseButtonRelease){
        this->format = 6;
        Q_EMIT QPushButton().clicked();
        return QMainWindow::eventFilter(object, event);
    }


    // Safely ignore all other events
    return false;
}
