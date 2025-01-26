#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QJsonObject>
#include <spdlog/spdlog.h>
#include <fstream>

// Include your header files
#include "config_manager.hxx"
#include "hyprland_controller.hxx"
#include "waybar_controller.hxx"
#include "wallpaper_controller.hxx"
#include "wofi_controller.hxx"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize the main window and layout
    QWidget window;
    QHBoxLayout *layout = new QHBoxLayout(&window);
    
    // Define the path for your themes directory
    fs::path themesDir("/home/wzqrxzd/projects/tpzq/themes/");
    
    // Create a ConfigManager object
    ConfigManager cfgManager(themesDir);
    auto themesSet = cfgManager.getThemesSet();

    // Set the background color of the main window
    window.setStyleSheet("background-color: #0F0F17;"); // Dark background color (e.g., dark blue/gray)

    // Create buttons for each theme dynamically
    for (const auto& theme : themesSet) {
        // Create button for the theme
        QPushButton *button = new QPushButton(QString::fromStdString(theme.filename().string()));
        
        // Set the fixed size of the button
        button->setFixedSize(100, 100);
        
        // Set a fixed margin (spacing between buttons)
        layout->setSpacing(30);  // Set the space between buttons to 30 pixels

        // Apply custom styles (rounded corners, color, etc.) to the button
        button->setStyleSheet(
            "QPushButton {"
            "    border-radius: 30px;" // Rounded corners with a radius of 30px
            "    background-color: #A0302B;" // Button background color (blue)
            "    color: white;" // Text color (white)
            "    font-size: 14px;" // Font size
            "    border: none;" // Remove border
            "    padding: 10px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #2980b9;" // Darker blue when hovering
            "}"
        );
        
        // Connect button click signal to the slot for applying the theme
        QObject::connect(button, &QPushButton::clicked, [&cfgManager, theme](){
            // Load the theme's configuration
            json config = cfgManager.getTheme(theme);
            
            // Here, apply the controllers for the theme as needed
            std::vector<std::unique_ptr<Controller>> controllers;
            controllers.push_back(std::make_unique<WaybarController>(&config));
            controllers.push_back(std::make_unique<HyprlandController>(&config));
            controllers.push_back(std::make_unique<WofiController>(&config));
            controllers.push_back(std::make_unique<WallpaperController>(&config));

            // Apply the theme using each controller
            for (const auto& controller : controllers)
                controller->apply();

            // Optional: show a message box for successful application
            QMessageBox::information(nullptr, "Success", "Theme applied: " + QString::fromStdString(theme.filename().string()));
        });

        // Add the button to the layout
        layout->addWidget(button);
    }

    // Adjust the window's width dynamically based on the number of buttons
    int windowWidth = 100 + 30 * (themesSet.size() - 1) + 100 * themesSet.size();  // Fixed size + spacing + button widths
    window.setFixedWidth(windowWidth);  // Set the width of the window to fit the buttons
    window.setFixedHeight(150);  // Fixed height of 150

    // Set the window title
    window.setWindowTitle("Theme Selector");

    // Show the window
    window.show();

    // Run the Qt event loop
    return app.exec();
}

