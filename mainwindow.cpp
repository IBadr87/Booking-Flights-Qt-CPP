#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->PB_Customers,SIGNAL(clicked(bool)),SLOT(PBCustomersClicked()));
    connect(ui->PB_Booking,SIGNAL(clicked(bool)),SLOT(PBBookingClicked()));
    connect(ui->PB_Flights,SIGNAL(clicked(bool)),SLOT(PBFlightStatusClicked()));
    connect(ui->PB_About,SIGNAL(clicked(bool)),SLOT(PBFAboutClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// click on button Customer, open a new window to manage the customers information Window
void MainWindow::PBCustomersClicked()
{
    Customers c(this);
    c.exec();
}

// click on button Booking Flights, open a new window to manage the Reservation information Window
void MainWindow::PBBookingClicked()
{
    BookingFlights b(this);
    b.exec();
}

void MainWindow::PBFlightStatusClicked()
{
    FlightStatus f(this);
    f.exec();
}

void MainWindow::PBFAboutClicked()
{
    QString about_text;
    about_text = "Auther : GROUP3 (Badr, Manyo, Ekhizi, Djophant)\n";
    about_text = "Date : 08/07/2022\n";
    about_text = "Version : BMED1.1 (R)\n";
    QMessageBox::about(this, "About Mission Impossible", about_text);
}
