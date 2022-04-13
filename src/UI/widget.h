#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QMouseEvent>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
struct FramelessWindowPrivate;
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void RCornerWindow();
    void RCornerbtn(QPushButton*);
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
private:
    Ui::Widget *ui;
    int cornerRadius = 20;
    QWidget *border = nullptr;
    QColor mainBackGround = QColor(251,251,251);
    QPoint mousePressedPosition;
    QPoint windowPositionAsDrag;
    QParallelAnimationGroup *curAni = nullptr;
    QGraphicsOpacityEffect *opacity = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
public slots:
    void slideIn();
    void slideOut();
};
#endif // WIDGET_H
