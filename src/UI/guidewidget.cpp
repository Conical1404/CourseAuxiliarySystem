#include "src/UI/guidewidget.h"

#include "./ui_guidewidget.h"

guideWidget::guideWidget(QDateTime* sysCurTime,
                         QTimer* sysTimer, QWidget* parent) :
QWidget(parent),
ui(new Ui::guideWidget) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    curTime = sysCurTime;
    timer = sysTimer;
    init();
    setTime(true);
    ui->closebtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    connect(ui->closebtn, &QPushButton::clicked,
            this, &guideWidget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &guideWidget::showMinimized);
    point[0] = "北京邮电大学西土城校区";
    point[1] = "北京邮电大学沙河校区";
    addDestination();
    addOrigin();
}

guideWidget::~guideWidget() {
    timer->start(1000);
    delete ui;
}

void guideWidget::init() {
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

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

    btnGroup1 = new QButtonGroup(this);
    btnGroup1->addButton(ui->yesCheck);
    btnGroup1->addButton(ui->nocheck);
    btnGroup1->setExclusive(true);
    btnGroup2 = new QButtonGroup(this);
    btnGroup2->addButton(ui->timeFirst);
    btnGroup2->addButton(ui->routeFirst);
    btnGroup2->setExclusive(true);
}

void guideWidget::addDestination() {
    for (int i = 0; i < 10; i++) {
        if (point[i].isEmpty())
            break;
        else
            ui->destBox->addItem(point[i], i);
    }
}

void guideWidget::addOrigin() {
    for (int i = 0; i < 10; i++) {
        if (point[i].isEmpty())
            break;
        else
            ui->originBox->addItem(point[i], i);
    }
}

void guideWidget::addPassingPoint() {
    QDialog* passing = new QDialog(this);
    passing->resize(200, 150);
    passing->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* mainLayout = new QVBoxLayout(passing);
    QComboBox* pointBox = new QComboBox(passing);
    QPushButton* addbtn = new QPushButton("Add", passing);
    QPushButton* hidebtn = new QPushButton("Hide", passing);
    for (int i = 0; i < 10; i++) {
        if (point[i].isNull())
            break;
        else
            pointBox->addItem(point[i], i);
    }
    mainLayout->addWidget(pointBox);
    mainLayout->addWidget(addbtn);
    mainLayout->addWidget(hidebtn);
    connect(addbtn, &QPushButton::clicked, passing, [=]() {
        passingPoint = pointBox->currentText();
        passing->close();
    });
    connect(hidebtn, &QPushButton::clicked, passing, [=]() {
        passing->close();
    });
}

void guideWidget::setTime(bool reset) {
    QTime time = curTime->time();
    int hour = time.hour();
    int min = time.minute();
    QDate date = curTime->date();
    int year, month, day, nOfWeek, week;
    date.getDate(&year, &month, &day);
    nOfWeek = date.dayOfWeek();
    week = date.weekNumber();
    ui->hour1->setText(QString::number(hour / 10));
    ui->hour2->setText(QString::number(hour % 10));
    ui->min1->setText(QString::number(min / 10));
    ui->min2->setText(QString::number(min % 10));
    if (hour == 0 || reset) {
        ui->month->setText(QString::number(month));
        ui->date->setText(QString::number(day));
        ui->nOfWeek->setText(QString::number(nOfWeek));
        ui->weekNum->setText(QString::number(week));
    }
}

void guideWidget::setPassingPoint(const QString& newPassingPoint) {
    passingPoint = newPassingPoint;
}
