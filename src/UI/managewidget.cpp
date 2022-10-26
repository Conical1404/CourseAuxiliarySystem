#include "src/UI/managewidget.h"

#include "./ui_managewidget.h"

manageWidget::manageWidget(QDateTime* sysTime,
                           QTimer* sysTimer, QWidget* parent) :
QWidget(parent),
ui(new Ui::manageWidget) {
    ui->setupUi(this);
    time = sysTime;
    timer = sysTimer;
    init();
    ui->infoList->hide();
    ui->closebtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#ff6767;color:black;}");
    ui->minibtn->setStyleSheet(
        "QPushButton{background-color:rgba(210,210,210,80%);" +
        "border:2px;border-radius: 10px;}"
        "QPushButton:hover{background-color:#F9D64B;color:black;}");
    connect(ui->closebtn, &QPushButton::clicked,
            this, &manageWidget::close);
    connect(ui->minibtn, &QPushButton::clicked,
            this, &manageWidget::showMinimized);
}

manageWidget::~manageWidget() {
    delete ui;
}

void manageWidget::init() {
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

    QScrollBar* tmp = new QScrollBar(this);
    ui->classTable->setHorizontalScrollBar(tmp);
    tmp->setStyleSheet(
        "QScrollBar:horizontal{background:transparent; height:10px;" +
        "margin:0px 0px 0px 0px;}"
        "QScrollBar::handle:horizontal{background:rgba(200, 200, 200, 100);"+
        "border:0px;border-radius:5px; margin:0px 0px 0px 0px;}"
        "QScrollBar::sub-page:horizontal{background:transparent;}"
        "QScrollBar::add-page:horizontal{background:transparent;}"
        "QScrollBar::up-arrow:horizontal{subcontrol-origin:margin;" +
        "background:transparent;}"
        "QScrollBar::down-arrow:horizontal{background:transparent;}"
        "QScrollBar::sub-line:horizontal{subcontrol-origin:margin;"+
        "background:transparent; width:0px;}"
        "QScrollBar::add-line:horizontal{subcontrol-origin:margin;" +
        "background:transparent; width:0px;}");

    for (int i = 0; i < ui->classTable->rowCount(); i++)
        ui->classTable->setRowHeight(i, 165);

    setTime(true);

    curMode = homework;
    homeworkMode();
    connect(ui->homeworkbtn, &QPushButton::clicked, this, [=]() {
        if (curMode != homework) {
            homeworkMode();
            curMode = homework;
        }
    });
    connect(ui->databtn, &QPushButton::clicked, this, [=]() {
        if (curMode != data) {
            dataMode();
            curMode = data;
        }
    });
    connect(ui->informbtn, &QPushButton::clicked, this, [=]() {
        if (curMode != inform) {
            informMode();
            curMode = inform;
        }
    });
    connect(ui->exambtn, &QPushButton::clicked, this, [=]() {
        if (curMode != exam) {
            examMode();
            curMode = exam;
        }
    });
    connect(ui->addbtn, &QPushButton::clicked, this, [=]() { addCourse(); });
    connect(ui->submitbtn, &QPushButton::clicked,
            this, &manageWidget::uploadHomework);
    connect(ui->uploadbtn, &QPushButton::clicked,
            this, &manageWidget::uploadData);
}

void manageWidget::defaultStyle() {
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/class);}");
    ui->searchInput->clear();
    ui->resultList->clear();
    ui->dataTable->clearContents();
    ui->searchInput->show();
    ui->resultList->show();
    ui->dataTable->show();
    ui->infoList->hide();
}

void manageWidget::informStyle() {
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/class2);}");
    ui->searchInput->hide();
    ui->resultList->hide();
    ui->dataTable->hide();
    ui->infoList->clear();
    ui->infoList->show();
}

void manageWidget::homeworkMode() {
    defaultStyle();
    // 按下作业按钮后的逻辑
}

void manageWidget::dataMode() {
    defaultStyle();
    // 按下资料按钮后的逻辑
}

void manageWidget::informMode() {
    informStyle();
    // 按下通知按钮后的逻辑
}

void manageWidget::examMode() {
    informStyle();
    // 按下考试按钮后的逻辑
}

void manageWidget::addCourse() {
    timer->stop();
    QDialog* add = new QDialog(this);
    add->setAttribute(Qt::WA_DeleteOnClose);
    add->resize(300, 200);
    QVBoxLayout* mainLayout = new QVBoxLayout(add);
    QFormLayout* form = new QFormLayout();
    QLabel* str = new QLabel("Course Name", add);
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

void manageWidget::uploadHomework() {
    QDialog* upload = new QDialog();
    upload->resize(400, 100);
    upload->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* mainLayout = new QVBoxLayout(upload);
    mainLayout->addWidget(new QLabel("class:"));
    QComboBox* className = new QComboBox(upload);
    mainLayout->addWidget(className);
    QPushButton* okbtn = new QPushButton("OK", upload);
    mainLayout->addWidget(okbtn);
    upload->show();
    connect(okbtn, &QPushButton::clicked,
            this, &manageWidget::uploadData);
    connect(okbtn, &QPushButton::clicked,
            this, [=]() { upload->close(); });
}

void manageWidget::uploadData() {
    uploadPath = QFileDialog::getOpenFileName(this,
                "Upload Data", "D:\\", "All Files(*)");
}

void manageWidget::setTime(bool reset) {
    if (time->time().hour() == 0 || reset) {
        ui->weekNum->setText(QString::number(time->date().weekNumber()));
        ui->date->setText(QString::number(time->date().day()));
    }
}
