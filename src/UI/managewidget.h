#ifndef SRC_UI_MANAGEWIDGET_H_
#define SRC_UI_MANAGEWIDGET_H_

#include <QButtonGroup>
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScrollBar>
#include <QString>
#include <QTimeEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class manageWidget;
}

class manageWidget : public QWidget {
    Q_OBJECT

 public:
    explicit manageWidget(QDateTime *, QTimer *, QWidget *parent = nullptr);
    ~manageWidget();
    enum mode {
        homework = 0x01,
        data = 0x02,
        inform = 0x04,
        exam = 0x08
    };
    void setTime(bool);

 private:
    Ui::manageWidget *ui;
    mode curMode;
    QDateTime *time;
    QTimer *timer;
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow = nullptr;
    QString uploadPath;
    void init();
    void defaultStyle();
    void informStyle();
    void homeworkMode();
    void dataMode();
    void informMode();
    void examMode();
    void addCourse();
    void uploadHomework();
    void uploadData();
};

#endif  // SRC_UI_MANAGEWIDGET_H_
