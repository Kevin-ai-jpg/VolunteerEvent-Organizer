# VolunteerEvent-Organizer
# Volunteer Event Organizer - OOP Project (C++/Qt)

A simple C++ application using the Qt framework, developed for an Object-Oriented Programming exam. This project demonstrates core OOP principles for managing volunteer events.

## Core Functionality

* **Event Management:** Define event details (name, date, location).
* **Volunteer Tracking:** Add and manage volunteers for events.
* **Event Registration:** Allow volunteers to sign up for events.

The application uses a layered approach: Presentation (Qt UI), Application Logic, Domain Model, and Data Persistence (e.g., in-memory or file-based).

## Technologies Used

* **Language:** C++
* **UI Framework:** Qt
* **Compiler:** [e.g., GCC, Clang, MSVC - Specify what you used or what's required]
* **Build System:** [e.g., qmake, CMake - Specify what you used]
* **IDE:** [e.g., Qt Creator, Visual Studio, CLion, VS Code]

## Getting Started

### Prerequisites

* C++ Compiler (supporting C++11 or newer, e.g., GCC 7+)
* Qt Framework (e.g., Qt 5.12 or newer) installed. Make sure Qt tools (like `qmake` or `cmake` with Qt support, and `moc`) are in your system PATH.

### Running the Application

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/Kevin-ai-jpg/VolunteerEvent-Organizer.git](https://github.com/Kevin-ai-jpg/VolunteerEvent-Organizer.git)
    ```
2.  **Navigate to the project directory:**
    ```sh
    cd VolunteerEvent-Organizer
    ```
3.  **Build the project:**
    * **Using qmake (typical for Qt Creator projects):**
        ```sh
        qmake # Generates Makefile
        make  # Or mingw32-make on Windows with MinGW
        ```
    * **Using CMake (if you set it up that way):**
        ```sh
        mkdir build && cd build
        cmake ..
        make
        ```
    * *(Alternatively, open the .pro file or CMakeLists.txt in Qt Creator and click the "Build" button.)*
4.  **Run the application:**
    * The executable will typically be found in a `debug` or `release` subfolder, or in the `build` directory if using CMake.
    * (e.g., `./debug/VolunteerEventOrganizer` or `.\debug\VolunteerEventOrganizer.exe` on Windows)
    * (e.g., `./build/VolunteerEventOrganizer`)

---

**Author:** Kevin-ai-jpg
**Course:** Object-Oriented Programming Exam
