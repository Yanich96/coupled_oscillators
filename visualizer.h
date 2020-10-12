#ifndef CODE_VISUALIZER_H
#define CODE_VISUALIZER_H

#include <QApplication>
#include <QRadioButton>
#include <QDebug>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>
#include <QtGui/QWindow>
#include <QtGui/QBitmap>
#include "system.h"

class Visualizer {
    QApplication application;
    QPixmap bitmap;
    QLabel myLabel;
    const System &system;
public:
    Visualizer(int argc, char **argv, const System &system) :
            application(argc, argv),
            bitmap(1800, 500),
            system(system) {
        myLabel.setPixmap(bitmap);
        myLabel.show();
        update();
    }


    void update() {
        clean();
        redraw();
        QApplication::processEvents();
    }

private:
    void clean() {
        QPainter p(&bitmap);
        QBrush brush2(Qt::blue);
        brush2.setColor(Qt::white);
        p.setBrush(brush2);
        p.drawRect(0, 0, bitmap.width(), bitmap.height());
        p.end();
        myLabel.setPixmap(bitmap);
    }

    void redraw() {
        QPainter p(&bitmap);
        QBrush brush2(Qt::blue);
        p.setBrush(brush2);
        brush2.setColor(Qt::blue);
        for (const auto &atom : system.atoms)
            p.drawRect(atom.position.x * 5 + 10, 250, 5, 5);
        p.end();
        myLabel.setPixmap(bitmap);
    }
};


#endif //CODE_VISUALIZER_H
