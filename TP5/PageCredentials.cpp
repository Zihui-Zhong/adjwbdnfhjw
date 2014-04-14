#include "PageCredentials.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

PageCredentials::PageCredentials(QWidget *parent) : QWidget(parent)
{

    QLabel * devParLbl = new QLabel("Développé par:");
    QLabel * etudiant1Lbl = new QLabel("   Zihui Zhong (1687994)");
    QLabel * etudiant2Lbl = new QLabel("   Pascal Desrochers (1689838");
    QLabel * versionLbl = new QLabel("Version du logiciel:");
    QLabel * versionNoLbl = new QLabel("   1.0.0.1");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(devParLbl);
    layout->addWidget(etudiant1Lbl);
    layout->addWidget(etudiant2Lbl);
    layout->addWidget(versionLbl);
    layout->addWidget(versionNoLbl);

    setLayout(layout);

}
