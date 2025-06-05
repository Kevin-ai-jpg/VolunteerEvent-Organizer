#include <QApplication> // Changed from QCoreApplication for GUI
#include <QDebug>
#include <memory> // For std::make_unique
#include <QDate>  // For QDate

// Project specific headers
#include "../Controller/Controller.h"
#include "../Repository/CSV/CSVVolunteerRepository.h"
#include "../Repository/CSV/CSVEventRepository.h"
#include "../Repository/JSON/JSONVolunteerRepository.h"
#include "../Repository/JSON/JSONEventRepository.h"
#include "mainwindow.h"
#include <QDir>

int main(int argc, char *argv[]) {
    // Initialize QApplication for GUI applications
    QApplication a(argc, argv);

    qDebug() << "Starting Volunteer Management Application (GUI)...";

    // Define filenames for the CSV repositories and create instances of the CSV repositories
    // QString volunteerCsvFile = "volunteers.csv";
    // QString eventCsvFile = "events.csv";
    // auto volunteerRepo = std::make_unique<CSVVolunteerRepository>(volunteerCsvFile);
    // auto eventRepo = std::make_unique<CSVEventRepository>(eventCsvFile);

    QString volunteerJsonFile = "volunteers.json";
    QString eventJsonFile = "events.json";
    auto volunteerRepo = std::make_unique<JSONVolunteerRepository>(volunteerJsonFile);
    auto eventRepo = std::make_unique<JSONEventRepository>(eventJsonFile);


    // Create the Controller, passing in the repositories
    // The Controller takes ownership of the repository unique_ptr's
    // We'll keep the controller on the stack here, or you could manage it with a smart pointer
    // if MainWindow takes ownership or a shared pointer.
    // For simplicity, assuming MainWindow takes a reference or a raw pointer to a stack-allocated controller.
    Controller controller(std::move(volunteerRepo), std::move(eventRepo));

    // Add this after initializing the Controller and before creating MainWindow

    // Add 10 volunteers
    controller.addVolunteer(Volunteer(1, "Alice Smith", "alice@example.com"));
    controller.addVolunteer(Volunteer(2, "Bob Johnson", "bob@example.com"));
    controller.addVolunteer(Volunteer(3, "Charlie Lee", "charlie@example.com"));
    controller.addVolunteer(Volunteer(4, "Diana King", "diana@example.com"));
    controller.addVolunteer(Volunteer(5, "Ethan Brown", "ethan@example.com"));
    controller.addVolunteer(Volunteer(6, "Fiona White", "fiona@example.com"));
    controller.addVolunteer(Volunteer(7, "George Black", "george@example.com"));
    controller.addVolunteer(Volunteer(8, "Hannah Green", "hannah@example.com"));
    controller.addVolunteer(Volunteer(9, "Ian Gray", "ian@example.com"));
    controller.addVolunteer(Volunteer(10, "Julia Blue", "julia@example.com"));

    // Add 3 events
    controller.addEvent(Event(1, "Community Cleanup", QDate(2024, 6, 15), "Central Park"));
    controller.addEvent(Event(2, "Food Drive", QDate(2024, 7, 20), "Community Center"));
    controller.addEvent(Event(3, "Charity Run", QDate(2024, 8, 10), "Riverside Park"));

    qDebug() << "Controller and repositories initialized.";

    // Create and show the MainWindow
    // This assumes your MainWindow constructor can take a Controller reference or pointer.
    // Adjust if your MainWindow constructor is different.
    // Example: MainWindow mainWindow(&controller); or MainWindow mainWindow(controller);
    MainWindow mainWindow(&controller); // Pass controller by pointer
    mainWindow.setWindowTitle("Volunteer and Event Management"); // Optional: Set a window title
    mainWindow.show();

    qDebug() << "MainWindow shown. Starting event loop...";



    // Start the Qt event loop. This is essential for GUI applications.
    return a.exec();
}