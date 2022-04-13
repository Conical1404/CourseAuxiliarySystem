#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QImage>
#include <QGraphicsEffect>
#include <QDesktopWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    RCornerWindow();

    opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.99);

    ui->leftWidget->setGraphicsEffect(opacity);
    ui->closebtn->setStyleSheet("QPushButton{background-color:rgba(210,210,210,80%);border:2px;border-radius: 10px;}"
                            "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet("QPushButton{background-color:rgba(210,210,210,80%);border:2px;border-radius: 10px;}"
                            "QPushButton:hover{background-color:#F9D64B;color:black;}");
    ui->mini->setStyleSheet("QPushButton{background-color:rgba(210,210,210,80%);border:2px;border-radius: 10px;}"
                            "QPushButton:hover{background-color:#F9D64B;color:black;}");
    ui->expand->setStyleSheet("QPushButton{background-color:rgba(210,210,210,80%);border:2px;border-radius: 10px;}"
                            "QPushButton:hover{background-color:#00ff00;color:black;}");

    connect(ui->closebtn,&QPushButton::clicked,this,&Widget::close);
    connect(ui->minibtn,&QPushButton::clicked,this,&Widget::showMinimized);
    connect(ui->mini,&QPushButton::clicked,this,&Widget::slideIn);
    connect(ui->expand,&QPushButton::clicked,this,&Widget::slideOut);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::RCornerWindow()
{
    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
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
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid #686868; border-radius:" + QString::asprintf("%d",cornerRadius) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();

    /*QPixmap pixmap(":/left");
    pixmap.scaled(ui->leftWidget->width(),ui->leftWidget->height(),Qt::KeepAspectRatio);
    QPalette palette = ui->leftWidget->palette();
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    ui->leftWidget->setPalette(palette);*/
}
void Widget::mousePressEvent(QMouseEvent *e) {
    // 记录鼠标按下时全局的位置和窗口左上角的位置
    mousePressedPosition = e->globalPos();
    windowPositionAsDrag = pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e)
    // 鼠标放开始设置鼠标按下的位置为 null，表示鼠标没有被按下
    mousePressedPosition = QPoint();
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    if (!mousePressedPosition.isNull()) {
        // 鼠标按下并且移动时，移动窗口, 相对于鼠标按下时的位置计算，是为了防止误差累积
        QPoint delta = e->globalPos() - mousePressedPosition;
        move(windowPositionAsDrag + delta);
    }
}

void Widget::slideIn()
{
    if(curAni){
        curAni->stop();
        curAni->deleteLater();
        curAni = nullptr;
    }
    QParallelAnimationGroup *inGroup = new QParallelAnimationGroup(ui->mainWidget);
    QPropertyAnimation *slideinAni = new QPropertyAnimation(ui->mainWidget,"pos");
    slideinAni->setStartValue(ui->mainWidget->pos());
    slideinAni->setEndValue(QPoint(-ui->leftWidget->width()+25,20));
    slideinAni->setDuration(1000);
    slideinAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *borderAni = new QPropertyAnimation(border,"geometry");
    borderAni->setStartValue(QRect(border->pos(),border->size()));
    borderAni->setEndValue(QRect(border->pos(),ui->rightWidget->size()));
    borderAni->setDuration(1000);
    borderAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *fadeInAni = new QPropertyAnimation(opacity, "opacity", this);
    fadeInAni->setStartValue(opacity->opacity());
    fadeInAni->setEndValue(0);
    fadeInAni->setDuration(1000);
    fadeInAni->setEasingCurve(QEasingCurve::InCubic);
    inGroup->addAnimation(borderAni);
    inGroup->addAnimation(slideinAni);
    inGroup->addAnimation(fadeInAni);
    connect(inGroup, &QParallelAnimationGroup::finished, this, [=](){
        ui->leftWidget->hide();
        this->curAni = nullptr;
        ui->rightWidget->setStyleSheet("QWidget#rightWidget{border-image: url(:/right);"
                                       "border-radius:20px};");
        border->setGraphicsEffect(windowShadow);
        ui->expand->show();
    });
    inGroup->start(QAbstractAnimation::DeleteWhenStopped);
    curAni = inGroup;
}

void Widget::slideOut()
{
    if(curAni){
        curAni->stop();
        curAni->deleteLater();
        curAni = nullptr;
    }
    ui->leftWidget->show();
    QParallelAnimationGroup *inGroup = new QParallelAnimationGroup(ui->mainWidget);
    QPropertyAnimation *slideinAni = new QPropertyAnimation(ui->mainWidget,"pos");
    slideinAni->setStartValue(ui->mainWidget->pos());
    slideinAni->setEndValue(QPoint(20,20));
    slideinAni->setDuration(1000);
    slideinAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *borderAni = new QPropertyAnimation(border,"geometry");
    QPoint endPoint(border->x(),border->y());
    borderAni->setStartValue(QRect(border->pos(),border->size()));
    borderAni->setEndValue(QRect(border->pos(),ui->mainWidget->size()+QSize(4,4)));
    borderAni->setDuration(1000);
    borderAni->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *fadeInAni = new QPropertyAnimation(opacity, "opacity", this);
    fadeInAni->setStartValue(opacity->opacity());
    fadeInAni->setEndValue(0.99);
    fadeInAni->setDuration(1000);
    inGroup->addAnimation(borderAni);
    inGroup->addAnimation(slideinAni);
    inGroup->addAnimation(fadeInAni);
    connect(inGroup, &QParallelAnimationGroup::finished, this, [=](){
        this->curAni = nullptr;
        ui->rightWidget->setStyleSheet("QWidget#rightWidget{border-image: url(:/right);}");
        border->setGraphicsEffect(windowShadow);
        ui->expand->hide();
    });
    inGroup->start(QAbstractAnimation::DeleteWhenStopped);
    curAni = inGroup;
}
