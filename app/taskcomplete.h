#ifndef TASKCOMPLETE_H
#define TASKCOMPLETE_H

#include <QDialog>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <math.h>
#include <iomanip>
#include <sstream>
//#include <iostream>


namespace Ui
{
    class Taskcomplete;
}


class Taskcomplete : public QDialog
{
    Q_OBJECT

public:

    explicit Taskcomplete(QWidget *parent = nullptr);

    ~Taskcomplete();

    void setMessage(const QString &_message, const bool &_timer_mode);

private slots:

    void on_closeWindow_clicked();

    void on_buttonCancel_clicked();

    void repeatHandler();

    bool eventFilter(QObject *watched, QEvent *event);

private:

    Ui::Taskcomplete *ui_taskcomplete;

    QTimer *timer;

    QString _message;

    int elps_t;

    bool clickPressedFlag = false;

    QPoint mouseClickCoordinate;

    void show_message(QString _message);
};

#endif // TASKCOMPLETE_H
