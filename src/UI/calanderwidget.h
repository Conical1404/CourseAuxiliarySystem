#ifndef SRC_UI_CALANDERWIDGET_H_
#define SRC_UI_CALANDERWIDGET_H_

#include <QColor>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QFormLayout>
#include <QGraphicsEffect>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimeEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class calanderWidget;
}

class calanderWidget : public QWidget {
    Q_OBJECT

 public:
    explicit calanderWidget(QDateTime *, QTimer *, QWidget *parent = nullptr);
    ~calanderWidget();
    void setTime();

 private:
    Ui::calanderWidget *ui;
    int weekNum, month, date, nOfWeek;
    bool isCurWeek = true;
    QTimer *timer;
    QColor defaultColor = QColor(0, 0, 0);
    QColor afterChangeColor = QColor(255, 0, 0);
    QDateTime *curTime;
    QDateTime displayTime;
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
    void init();
    void showActivity(QString, int, int, int, QColor);
    void addActivity();
    void showNextWeek();
    void showPrevWeek();
};

#endif  // SRC_UI_CALANDERWIDGET_H_
