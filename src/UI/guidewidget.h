#ifndef SRC_UI_GUIDEWIDGET_H_
#define SRC_UI_GUIDEWIDGET_H_

#include <QButtonGroup>
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QWidget>

namespace Ui {
class guideWidget;
}

class guideWidget : public QWidget {
    Q_OBJECT

 public:
    explicit guideWidget(QDateTime *, QTimer *, QWidget *parent = nullptr);
    ~guideWidget();
    void setTime(bool);
    void setPassingPoint(const QString &newPassingPoint);

 private:
    Ui::guideWidget *ui;
    QTimer *timer;
    QDateTime *curTime;
    QString passingPoint;
    QString point[10];
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
    QButtonGroup *btnGroup1;
    QButtonGroup *btnGroup2;
    void init();
    void addDestination();
    void addOrigin();
    void addPassingPoint();
};

#endif  // SRC_UI_GUIDEWIDGET_H_
