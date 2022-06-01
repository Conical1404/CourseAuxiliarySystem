#ifndef SRC_UI_CLOCKWIDGET_H_
#define SRC_UI_CLOCKWIDGET_H_

#include <QColor>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QFormLayout>
#include <QGraphicsEffect>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QTimeEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

namespace Ui {
class clockWidget;
}

enum clockType {
    onlyOnce = 0x01,
    onceAWeek = 0x02,
    everyDay = 0x04
};

class alarmClock {
 public:
    alarmClock();
    alarmClock(clockType, QDate, QTime, QString);
    clockType getType() const;
    void setType(clockType);
    QTime alarmTime;
    QString desc;
    bool shouldTrigger(QTime, int);
    bool getEnabled() const;
    void setEnabled(bool newEnabled);
    QString toString();

 private:
    clockType cType;
    bool enabled;
    QDate date;
};

class clockWidget : public QWidget {
    Q_OBJECT

 public:
    explicit clockWidget(QDateTime *, QTimer *, QWidget *parent = nullptr);
    ~clockWidget();
    void setTime(bool);
    void checkAlarm();

 private:
    Ui::clockWidget *ui;
    QTimer *timer;
    QDateTime *curTime;
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
    QVector<alarmClock> alarm;
    void init();
    void addClockPage();
    void addClock();
    void deleteAlarm();
};
#endif  // SRC_UI_CLOCKWIDGET_H_
