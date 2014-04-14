#include "HelpWindow.h"
#include "PageCredentials.h"
#include "PageRules.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCoreApplication>


HelpWindow::HelpWindow(QWidget *parent) : QDialog(parent)
{
    QTabWidget * tab = new QTabWidget();

    PageRules * pageRules = new PageRules(parent);
    tab->addTab(pageRules, "Règlements" );

    PageCredentials * pageCred = new PageCredentials(parent);
    tab->addTab(pageCred, "Crédits");



    QPushButton * okBtn = new QPushButton("Ok", parent);


    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(tab);
    layout->addWidget(okBtn);


    connect(okBtn, SIGNAL(clicked()),this, SLOT(quitClicked()));

    setWindowTitle(tr("Aide"));
    setLayout(layout);

    show();

}

void HelpWindow::quitClicked()
{
    QCoreApplication::quit();
}
