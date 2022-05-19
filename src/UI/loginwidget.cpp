#include "src/UI/loginwidget.h"

#include "./ui_loginwidget.h"

loginWidget::loginWidget(int sysWeek, int sysDate, QWidget* parent) :
QWidget(parent),
ui(new Ui::loginWidget) {
    ui->setupUi(this);
    ui->date->setText(QString::number(sysDate));
    ui->week->setText(QString::number(sysWeek));
    ui->passwdInput->hide();
    ui->loginbtn->hide();
    ui->accInput->hide();
    ui->errorMsg->hide();
    init();
    ui->startbtn->setAttribute(Qt::WA_DeleteOnClose);
    ui->closebtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    connect(ui->closebtn, &QPushButton::clicked,
            this, &loginWidget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &loginWidget::showMinimized);
    connect(ui->startbtn, &QPushButton::clicked,
            this, &loginWidget::startAnimation);
    connect(ui->loginbtn, &QPushButton::clicked,
            this, &loginWidget::login);
}

loginWidget::~loginWidget() {
    delete ui;
}

void loginWidget::init() {
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);

    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), 19, 19);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:rgb(251,251,251);" +
    "border-radius:19px}";
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
    borderStyle = "background-color:#00FFFFFF;" +
    "border:1.5px solid #686868; border-radius:19px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();
}

void loginWidget::startAnimation() {
    opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(0.99);
    ui->widget->setGraphicsEffect(opacity);
    QPropertyAnimation* fadeOut = new QPropertyAnimation(opacity, "opacity");
    fadeOut->setStartValue(opacity->opacity());
    fadeOut->setEndValue(0);
    fadeOut->setDuration(500);
    fadeOut->setEasingCurve(QEasingCurve::InCubic);
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    connect(fadeOut, &QPropertyAnimation::finished, this, [&]() {
        ui->widget->setStyleSheet(
            "QWidget#widget{border-image: url(:/login);}");
        QPropertyAnimation* fadeIn =
            new QPropertyAnimation(opacity, "opacity");
        fadeIn->setStartValue(opacity->opacity());
        fadeIn->setEndValue(0.99);
        fadeIn->setDuration(1000);
        fadeIn->setEasingCurve(QEasingCurve::InCubic);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
        ui->startbtn->close();
        ui->date->close();
        ui->week->close();
        connect(fadeIn, &QPropertyAnimation::finished, this, [=]() {
            ui->date1->setText(ui->date->text());
            ui->week1->setText(ui->week->text());
            ui->passwdInput->show();
            ui->loginbtn->show();
            ui->accInput->show();
        });
    });
}

void loginWidget::login() {
    QString account = ui->accInput->text();
    QString passwd = ui->passwdInput->text();
    if (account.isEmpty() || (account == "test" && passwd == "123456")) {
        this->close();
        emit showMainWidget();
    } else {
        ui->errorMsg->show();
    }
}
