#include "src/UI/calanderwidget.h"

#include "./ui_calanderwidget.h"

calanderWidget::calanderWidget(QDateTime* sysCurTime,
                QTimer* sysTimer, QWidget* parent) :
QWidget(parent),
ui(new Ui::calanderWidget) {
    ui->setupUi(this);
    curTime = sysCurTime;
    displayTime = *sysCurTime;
    timer = sysTimer;
    setTime();
    init();
    ui->closebtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    connect(ui->closebtn, &QPushButton::clicked,
            this, &calanderWidget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &calanderWidget::showMinimized);
    QColor tmp = Qt::cyan;
    showActivity("数据结构", 1, 8, 10, tmp);
}

calanderWidget::~calanderWidget() {
    delete ui;
}

void calanderWidget::init() {
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), 19, 19);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle =
        "QWidget#mainWidget{background-color:rgb(251,251,251);" +
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

    for (int i = 0; i < 15; i++) {
        ui->tableWidget->setRowHeight(i, 100);
    }
    ui->tableWidget->setColumnWidth(0, 50);
    for (int i = 2; i < 8; i++) {
        ui->tableWidget->setColumnWidth(i, 175);
    }

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet(
        "QHeaderView::section{background-color: rgba(0,0,0,0%);}");

    weekNum = curTime->date().weekNumber();
    month = curTime->date().month();
    date = curTime->date().day();
    nOfWeek = curTime->date().dayOfWeek();

    connect(ui->addbtn, &QPushButton::clicked, this, [=]() { addActivity(); });
    connect(ui->prevbtn, &QPushButton::clicked,
            this, &calanderWidget::showPrevWeek);
    connect(ui->nextbtn, &QPushButton::clicked,
            this, &calanderWidget::showNextWeek);
}

void calanderWidget::showActivity(QString desc, int nOfWeek,
                                  int start, int end, QColor background) {
    ui->tableWidget->setItem(start - 8, nOfWeek, new QTableWidgetItem);
    ui->tableWidget->setSpan(start - 8, nOfWeek, end - start, 1);
    ui->tableWidget->item(start - 8, nOfWeek)->setText(desc);
    ui->tableWidget->item(start - 8, nOfWeek)->setBackground(background);
}

void calanderWidget::addActivity() {
    timer->stop();
    QDialog* add = new QDialog(this);
    add->setAttribute(Qt::WA_DeleteOnClose);
    add->resize(400, 200);
    QVBoxLayout* mainLayout = new QVBoxLayout(add);
    QFormLayout* form = new QFormLayout();
    QLabel* str = new QLabel("Activity Name", add);
    QLineEdit* input = new QLineEdit(add);
    form->addRow(str, input);
    str = new QLabel("Loc", add);
    input = new QLineEdit(add);
    form->addRow(str, input);
    str = new QLabel("Start Time", add);
    QTimeEdit* tInput = new QTimeEdit(add);
    form->addRow(str, tInput);
    str = new QLabel("End Time", add);
    tInput = new QTimeEdit(add);
    form->addRow(str, tInput);
    QPushButton* okbtn = new QPushButton("OK", add);
    QPushButton* cancelbtn = new QPushButton("Cancel", add);
    mainLayout->addItem(form);
    mainLayout->addWidget(okbtn);
    mainLayout->addWidget(cancelbtn);
    connect(okbtn, &QPushButton::clicked, add, [=]() {
        add->close();
        timer->start(1000);
    });
    connect(cancelbtn, &QPushButton::clicked, add, [=]() {
        add->close();
        timer->start(1000);
    });
    add->show();
}

void calanderWidget::showNextWeek() {
    isCurWeek = false;
    displayTime = displayTime.addDays(7);
    if (++weekNum == curTime->date().weekNumber())
        isCurWeek = true;
    ui->tableWidget->clearContents();
    setTime();
    if (!isCurWeek) {
        ui->weekNum->setStyleSheet("color: red");
        ui->date->setStyleSheet("color: red");
        ui->nOfWeek->setStyleSheet("color: red");
        ui->month->setStyleSheet("color: red");
    } else {
        ui->weekNum->setStyleSheet("color: black");
        ui->date->setStyleSheet("color: black");
        ui->nOfWeek->setStyleSheet("color: black");
        ui->month->setStyleSheet("color: black");
    }
}

void calanderWidget::showPrevWeek() {
    isCurWeek = false;
    displayTime = displayTime.addDays(-7);
    if (--weekNum == curTime->date().weekNumber())
        isCurWeek = true;
    ui->tableWidget->clearContents();
    setTime();
    if (!isCurWeek) {
        ui->weekNum->setStyleSheet("color: red");
        ui->date->setStyleSheet("color: red");
        ui->nOfWeek->setStyleSheet("color: red");
        ui->month->setStyleSheet("color: red");
    } else {
        ui->weekNum->setStyleSheet("color: black");
        ui->date->setStyleSheet("color: black");
        ui->nOfWeek->setStyleSheet("color: black");
        ui->month->setStyleSheet("color: black");
    }
}

void calanderWidget::setTime() {
    if (isCurWeek) {
        QDate date = curTime->date();
        int year, month, day, nOfWeek, week;
        date.getDate(&year, &month, &day);
        nOfWeek = date.dayOfWeek();
        week = date.weekNumber();
        ui->month->setText(QString::number(month));
        ui->date->setText(QString::number(day));
        ui->nOfWeek->setText(QString::number(nOfWeek));
        ui->weekNum->setText(QString::number(week));
    } else if (!isCurWeek) {
        QDate date = displayTime.date();
        int year, month, day, nOfWeek, week;
        date.getDate(&year, &month, &day);
        nOfWeek = date.dayOfWeek();
        week = date.weekNumber();
        ui->month->setText(QString::number(month));
        ui->date->setText(QString::number(day));
        ui->nOfWeek->setText(QString::number(nOfWeek));
        ui->weekNum->setText(QString::number(week));
    }
}
