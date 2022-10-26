#include "src/UI/clockwidget.h"

#include "./ui_clockwidget.h"

clockWidget::clockWidget(QDateTime* sysCurTime,
                        QTimer* sysTimer, QWidget* parent) :
QWidget(parent),
ui(new Ui::clockWidget) {
    ui->setupUi(this);
    curTime = sysCurTime;
    timer = sysTimer;
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
            this, &clockWidget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &clockWidget::showMinimized);
}

clockWidget::~clockWidget() {
    delete ui;
}

void clockWidget::setTime(bool reset) {
    QTime time = curTime->time();
    int hour = time.hour();
    int min = time.minute();
    QDate date = curTime->date();
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
        ui->nOfWeek->setText(QString::number(nOfWeek));
        ui->weekNum->setText(QString::number(week));
    }
}

void clockWidget::checkAlarm() {
    QTime time = curTime->time();
    for (int i = 0; i < alarm.size(); i++) {
        if (alarm[i].shouldTrigger(time, curTime->date().day())) {
            QString info = "The alarm clock : " +
            alarm[i].desc + " has arrived";
            QMessageBox::warning(this, "warning", info);
        }
    }
}

void clockWidget::init() {
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
    windowShadow->setBlurRadius(10);
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

    setTime(true);
    connect(ui->addbtn, &QPushButton::clicked,
            this, &clockWidget::addClockPage);
    connect(ui->deletebtn, &QPushButton::clicked,
            this, &clockWidget::deleteAlarm);

    ui->clockList->setStyleSheet(
        "QListWidget{background-color: rgba(255, 255, 255, 150);}"
        "QListWidget:item{height: 50px;}");
}

void clockWidget::addClockPage() {
    timer->stop();
    QDialog* add = new QDialog();
    add->resize(300, 200);
    add->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* mainLayout = new QVBoxLayout(add);
    QFormLayout* form = new QFormLayout();
    QHBoxLayout* btnGroup = new QHBoxLayout();
    QRadioButton* weeklyBtn = new QRadioButton("每周一次", add);
    QRadioButton* dailyBtn = new QRadioButton("每天", add);
    QRadioButton* onceBtn = new QRadioButton("仅一次", add);
    btnGroup->addWidget(onceBtn);
    btnGroup->addWidget(weeklyBtn);
    btnGroup->addWidget(dailyBtn);
    QTimeEdit* clock = new QTimeEdit(add);
    QLineEdit* desc = new QLineEdit(add);
    form->addRow("Time:", clock);
    form->addRow("Description:", desc);
    mainLayout->addLayout(form);
    mainLayout->addLayout(btnGroup);
    QPushButton* okbtn = new QPushButton("OK", add);
    QPushButton* cancelbtn = new QPushButton("Cancel", add);
    mainLayout->addWidget(okbtn);
    mainLayout->addWidget(cancelbtn);
    connect(cancelbtn, &QPushButton::clicked, this, [=]() {
        add->close();
        timer->start(1000);
    });
    connect(okbtn, &QPushButton::clicked, this, [=]() {
        QTime alarmTime = clock->time();
        QString d = desc->text();
        clockType t;
        if (weeklyBtn->isChecked())
            t = clockType::onceAWeek;
        else if (dailyBtn->isChecked())
            t = clockType::everyDay;
        else
            t = clockType::onlyOnce;
        alarmClock tmp = alarmClock(t, curTime->date(), alarmTime, d);
        alarm.push_back(tmp);
        ui->clockList->addItem(tmp.toString());
        add->close();
        timer->start(1000);
    });
    add->show();
}

void clockWidget::deleteAlarm() {
    if (ui->clockList->selectedItems().isEmpty())
        return;
    int row = ui->clockList->currentRow();
    QString tmp = ui->clockList->currentItem()->text();
    ui->clockList->takeItem(row);
    for (int i = 0; i < alarm.size(); i++) {
        if (tmp == alarm[i].toString())
            alarm[i].setEnabled(false);
    }
    return;
}

alarmClock::alarmClock() {
    enabled = true;
}

alarmClock::alarmClock(clockType type, QDate n, QTime t, QString description) {
    enabled = true;
    cType = type;
    date = n;
    alarmTime = t;
    desc = description;
}

clockType alarmClock::getType() const {
    return cType;
}

void alarmClock::setType(clockType newType) {
    cType = newType;
}

bool alarmClock::getEnabled() const {
    return enabled;
}

void alarmClock::setEnabled(bool newEnabled) {
    enabled = newEnabled;
}

QString alarmClock::toString() {
    QString result = desc;
    QString t;
    if (this->cType == 1)
        t = " OnlyOnce";
    else if (this->cType == 2)
        t = " OnceAWeek";
    else
        t = " EveryDay";
    result = result + " " + alarmTime.toString() + t;
    return result;
}

bool alarmClock::shouldTrigger(QTime t, int date) {
    if (!this->enabled)
        return false;
    if (this->cType == clockType::onlyOnce) {
        if (t.secsTo(this->alarmTime) >= -360 &&
            t.secsTo(this->alarmTime) <= 0) {
            this->setEnabled(false);
            return true;
        } else {
            return false;
        }
    } else if (this->cType == clockType::everyDay) {
        if (t.secsTo(this->alarmTime) >= -360 &&
            t.secsTo(this->alarmTime) <= 0) {
            return true;
        } else {
            return false;
        }
    } else if (this->cType == clockType::onceAWeek) {
        if (t.secsTo(this->alarmTime) >= -360 &&
            t.secsTo(this->alarmTime) <= 0 && date == this->date.day()) {
            this->date = this->date.addDays(7);
            return true;
        } else {
            return false;
        }
    }
    return false;
}
