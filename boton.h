#ifndef BOTON_H
#define BOTON_H
//#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QGraphicsEffect>

using namespace std;

class Boton: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Boton(QString Url);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QString Url;
};

#endif // BOTON_H
