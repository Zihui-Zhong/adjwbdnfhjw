#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include <QDialog>

class HelpWindow : public QDialog
{
    Q_OBJECT
public:
    HelpWindow(QWidget *parent = 0);

private slots:
    void quitClicked();
};

#endif // HELPWINDOW_H
