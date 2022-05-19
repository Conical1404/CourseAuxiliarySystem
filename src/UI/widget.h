#ifndef SRC_UI_WIDGET_H_
#define SRC_UI_WIDGET_H_

#include <QDateTime>
#include <QDateTimeEdit>
#include <QDialog>
#include <QFormLayout>
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "./calanderwidget.h"
#include "./clockwidget.h"
#include "./guidewidget.h"
#include "./loginwidget.h"
#include "./managewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE
struct FramelessWindowPrivate;
class Widget : public QWidget {
    Q_OBJECT
 signals:
    void sendTime();

 public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void RCornerWindow();
    void RCornerbtn(QPushButton *);
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

 private:
    Ui::Widget *ui;
    int cornerRadius = 20;
    QDateTime curTime;
    QTimer *timer;
    QWidget *border = nullptr;
    QColor mainBackGround = QColor(251, 251, 251);
    QPoint mousePressedPosition;
    QPoint windowPositionAsDrag;
    QParallelAnimationGroup *curAni = nullptr;
    QGraphicsOpacityEffect *opacity = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;

    calanderWidget *calander;
    guideWidget *guide;
    loginWidget *login;
    manageWidget *manage;
    clockWidget *clock;
    void changeTimePage();

 public:
    void slideIn();
    void slideOut();
    void setTime(bool);
    void userMode();
    void adminMode();
    void announcement();
    void exam();
};
#endif  // SRC_UI_WIDGET_H_
