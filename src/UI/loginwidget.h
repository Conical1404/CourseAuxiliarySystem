#ifndef  SRC_UI_LOGINWIDGET_H_
#define  SRC_UI_LOGINWIDGET_H_

#include <QComboBox>
#include <QGraphicsOpacityEffect>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QString>
#include <QTimer>
#include <QWidget>

namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget {
    Q_OBJECT
 signals:
    void showMainWidget();

 public:
    explicit loginWidget(int, int, QWidget *parent = nullptr);
    ~loginWidget();

 private:
    Ui::loginWidget *ui;
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
    QGraphicsOpacityEffect *opacity = nullptr;
    void init();
    void startAnimation();
    void login();
};

#endif  //  SRC_UI_LOGINWIDGET_H_
