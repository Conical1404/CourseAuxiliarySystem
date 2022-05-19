#include "src/UI/widget.h"

#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QImage>
#include <QPainter>
#include <QPalette>
#include <QPixmap>

#include "./ui_widget.h"

Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->user->hide();

    curTime = curTime.currentDateTime();
    setTime(true);
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, [=]() {
        curTime = curTime.addSecs(360);
        setTime(false);
        qDebug() << curTime.time().hour() << endl;
        emit sendTime();
    });
    timer->start();

    login = new loginWidget(curTime.date().weekNumber(), curTime.date().day());
    login->show();
    connect(login, &loginWidget::showMainWidget,
            this, [=]() { this->show(); });

    RCornerWindow();
    userMode();

    opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.99);

    ui->expand->hide();
    ui->leftWidget->setGraphicsEffect(opacity);
    ui->closebtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    ui->mini->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    ui->expand->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#00ff00;color:black;}");

    connect(ui->closebtn, &QPushButton::clicked,
            this, &Widget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &Widget::showMinimized);
    connect(ui->mini, &QPushButton::clicked,
            this, &Widget::slideIn);
    connect(ui->expand, &QPushButton::clicked,
            this, &Widget::slideOut);
    connect(ui->acceleration, &QPushButton::clicked,
            this, &Widget::changeTimePage);
    connect(ui->arrange, &QPushButton::clicked, this, [=]() {
        calander = new calanderWidget(&curTime, timer);
        connect(this, &Widget::sendTime, calander, &calanderWidget::setTime);
        calander->show();
    });
    connect(ui->guide, &QPushButton::clicked, this, [=]() {
        guide = new guideWidget(&curTime, timer);
        connect(this, &Widget::sendTime, guide, [=]() {
            guide->setTime(false);
        });
        timer->stop();
        guide->show();
    });
    connect(ui->manage, &QPushButton::clicked, this, [=]() {
        manage = new manageWidget(&curTime, timer);
        manage->show();
        connect(this, &Widget::sendTime, manage, [=]() {
            manage->setTime(false);
        });
    });
    connect(ui->clock, &QPushButton::clicked, this, [=]() {
        clock = new clockWidget(&curTime, timer);
        clock->show();
        connect(this, &Widget::sendTime, clock, [=]() {
            clock->setTime(false);
        });
        connect(this, &Widget::sendTime, clock, &clockWidget::checkAlarm);
    });
    connect(ui->admin, &QPushButton::clicked, this, [=]() {
        adminMode();
    });
    connect(ui->user, &QPushButton::clicked, this, [=]() {
        userMode();
    });
    connect(ui->inform, &QPushButton::clicked,
            this, &Widget::announcement);
    connect(ui->exam, &QPushButton::clicked,
            this, &Widget::exam);
}

Widget::~Widget() {
    delete ui;
}

void Widget::RCornerWindow() {
    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(),
                cornerRadius - 1, cornerRadius - 1);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name()
    + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
    ui->mainWidget->setStyleSheet(mainStyle);

    windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    ui->mainWidget->setGraphicsEffect(windowShadow);

    border = new QWidget(this);
    border->move(ui->mainWidget->pos() - QPoint(1, 1));
    border->resize(ui->mainWidget->size() + QSize(2, 2));
    QString borderStyle;
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid #686868;" +
    "border-radius:" + QString::asprintf("%d", cornerRadius) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();
}
void Widget::mousePressEvent(QMouseEvent *e) {
    mousePressedPosition = e->globalPos();
    windowPositionAsDrag = pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e)
    mousePressedPosition = QPoint();
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    if (!mousePressedPosition.isNull()) {
        QPoint delta = e->globalPos() - mousePressedPosition;
        move(windowPositionAsDrag + delta);
    }
}

void Widget::changeTimePage() {
    timer->stop();
    QDialog *timeEdit = new QDialog();
    timeEdit->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout *mainLayout = new QVBoxLayout(timeEdit);
    QPushButton *okbtn = new QPushButton("OK", timeEdit);
    QPushButton *cancelbtn = new QPushButton("cancel", timeEdit);
    QDateTimeEdit *edit = new QDateTimeEdit(curTime, timeEdit);
    mainLayout->addWidget(edit);
    mainLayout->addWidget(okbtn);
    mainLayout->addWidget(cancelbtn);
    timeEdit->show();
    connect(okbtn, &QPushButton::clicked, this, [=]() {
        curTime = edit->dateTime();
        setTime(true);
        timeEdit->close();
        timer->start(1000);
    });
    connect(cancelbtn, &QPushButton::clicked, timeEdit, [=]() {
        timeEdit->close();
        timer->start(1000);
    });
}

void Widget::slideIn() {
    if (curAni) {
        curAni->stop();
        curAni->deleteLater();
        curAni = nullptr;
    }
    QParallelAnimationGroup *inGroup =
        new QParallelAnimationGroup(ui->mainWidget);
    QPropertyAnimation *slideinAni =
        new QPropertyAnimation(ui->mainWidget, "pos");
    slideinAni->setStartValue(ui->mainWidget->pos());
    slideinAni->setEndValue(QPoint(-ui->leftWidget->width() + 25, 20));
    slideinAni->setDuration(1000);
    slideinAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *borderAni =
        new QPropertyAnimation(border, "geometry");
    borderAni->setStartValue(QRect(border->pos(), border->size()));
    borderAni->setEndValue(QRect(border->pos(), ui->rightWidget->size()));
    borderAni->setDuration(1000);
    borderAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *fadeInAni =
        new QPropertyAnimation(opacity, "opacity", this);
    fadeInAni->setStartValue(opacity->opacity());
    fadeInAni->setEndValue(0);
    fadeInAni->setDuration(1000);
    fadeInAni->setEasingCurve(QEasingCurve::InCubic);
    inGroup->addAnimation(borderAni);
    inGroup->addAnimation(slideinAni);
    inGroup->addAnimation(fadeInAni);
    connect(inGroup, &QParallelAnimationGroup::finished, this, [=]() {
        ui->leftWidget->hide();
        this->curAni = nullptr;
        ui->rightWidget->setStyleSheet(
            "QWidget#rightWidget{border-image: url(:/right);"
            "border-radius:20px};");
        border->setGraphicsEffect(windowShadow);
        ui->expand->show();
    });
    inGroup->start(QAbstractAnimation::DeleteWhenStopped);
    curAni = inGroup;
}

void Widget::slideOut() {
    if (curAni) {
        curAni->stop();
        curAni->deleteLater();
        curAni = nullptr;
    }
    ui->leftWidget->show();
    QParallelAnimationGroup *inGroup =
        new QParallelAnimationGroup(ui->mainWidget);
    QPropertyAnimation *slideinAni =
        new QPropertyAnimation(ui->mainWidget, "pos");
    slideinAni->setStartValue(ui->mainWidget->pos());
    slideinAni->setEndValue(QPoint(20, 20));
    slideinAni->setDuration(1000);
    slideinAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *borderAni = new QPropertyAnimation(border, "geometry");
    QPoint endPoint(border->x(), border->y());
    borderAni->setStartValue(QRect(border->pos(), border->size()));
    borderAni->setEndValue(QRect(border->pos(),
                           ui->mainWidget->size() + QSize(4, 4)));
    borderAni->setDuration(1000);
    borderAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *fadeInAni =
        new QPropertyAnimation(opacity, "opacity", this);
    fadeInAni->setStartValue(opacity->opacity());
    fadeInAni->setEndValue(0.99);
    fadeInAni->setDuration(1000);
    inGroup->addAnimation(borderAni);
    inGroup->addAnimation(slideinAni);
    inGroup->addAnimation(fadeInAni);
    connect(inGroup, &QParallelAnimationGroup::finished, this, [=]() {
        this->curAni = nullptr;
        ui->rightWidget->
            setStyleSheet("QWidget#rightWidget{border-image: url(:/right);}");
        border->setGraphicsEffect(windowShadow);
        ui->expand->hide();
    });
    inGroup->start(QAbstractAnimation::DeleteWhenStopped);
    curAni = inGroup;
}

void Widget::setTime(bool reset) {
    QTime time = curTime.time();
    int hour = time.hour();
    int min = time.minute();
    QDate date = curTime.date();
    int year, month, day, nOfWeek, week;
    date.getDate(&year, &month, &day);
    nOfWeek = date.dayOfWeek();
    week = date.weekNumber();
    ui->min1->setText(QString::number(min / 10));
    ui->min2->setText(QString::number(min % 10));
    ui->hour1->setText(QString::number(hour / 10));
    ui->hour2->setText(QString::number(hour % 10));
    if (hour == 0 || reset) {
        ui->month->setText(QString::number(month));
        ui->date->setText(QString::number(day));
        ui->num->setText(QString::number(nOfWeek));
        ui->week->setText(QString::number(week));
    }
}

void Widget::userMode() {
    ui->leftWidget->
        setStyleSheet("QWidget#leftWidget{border-image: url(:/left);}");
    ui->rightWidget->
        setStyleSheet("QWidget#rightWidget{border-image: url(:/right);}");
    ui->inform->hide();
    ui->exam->hide();
    ui->admin->show();
    ui->clock->show();
    ui->manage->show();
    ui->guide->show();
    ui->arrange->show();
    ui->user->hide();
    ui->admin->show();
}

void Widget::adminMode() {
    ui->leftWidget->
        setStyleSheet("QWidget#leftWidget{border-image: url(:/left1);}");
    ui->rightWidget->
        setStyleSheet("QWidget#rightWidget{border-image: url(:/right1);}");
    ui->admin->hide();
    ui->clock->hide();
    ui->manage->hide();
    ui->guide->hide();
    ui->arrange->hide();
    ui->user->show();
    ui->inform->show();
    ui->exam->show();
}

void Widget::announcement() {
    {}
}

void Widget::exam() {
    {}
}
