#include <QtWidgets>
// #include "mainwidget.h"

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

// #include <QWidget>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
};

#endif // MAINWIDGET_H

// #include <QtWidgets>
// #include "mainwidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
   button_ = new QPushButton(tr("Push Me!"));
   textBrowser_ = new QTextBrowser();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   mainLayout->addWidget(textBrowser_,1,0);
   setLayout(mainLayout);
   setWindowTitle(tr("Connecting buttons to processes.."));
}

// Destructor
MainWidget::~MainWidget()
{
   delete button_;
   delete textBrowser_;
}
int main(int argc, char *argv[])
{
    // Creates an instance of QApplication
    QApplication a(argc, argv);

    // This is our MainWidget class containing our GUI and functionality
    MainWidget w;
    w.show(); // Show main window

    // run the application and return execs() return value/code
    return a.exec();
}