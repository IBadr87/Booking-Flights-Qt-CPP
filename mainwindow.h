#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customers.h"
#include "bookingflights.h"
#include "SeatWidget.h"
#include "flightstatus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void PBCustomersClicked();
    void PBBookingClicked();
    void PBFlightStatusClicked ();
    void PBFAboutClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
