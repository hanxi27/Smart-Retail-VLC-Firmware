#include "src/Utilities.h"
#include "src/GlobalVariables/GlobalVariables.h"
#include "src/Pins/Pins.h"
#include "src/WifiUtils/WifiUtils.h"
#include "src/FirebaseUtils/FirebaseUtils.h"
#include "src/BluetoothUtils/BluetoothUtils.h"
#include "src/UserInterface/UserInterface.h"
#include "src/Vlc/Vlc.h"
#include "src/Pins/SSD1306Wire.h"  // Include your SSD1306Wire library

// Tasks
Utilities::RepeatingTask wifiReconnectTask(WIFI_RECONNECT_INTERVAL);
Utilities::RepeatingTask uiRefreshTask(UI_REFRESH_INTERVAL);

int runCounter = 0;  // Initialize the counter

void setup() {
    Serial.begin(115200);
    Serial.println("Starting setup...");

    Serial.println("Setting up Pins...");
    Pins::setup();
    Serial.println("Pins setup complete.");

    Serial.println("Setting up WiFi...");
    WifiUtils::setup();
    Serial.println("WiFi setup complete.");

    Serial.println("Setting up VLC...");
    Vlc::setup();
    Serial.println("VLC setup complete.");

    Serial.println("Setting up Firebase...");
    FirebaseUtils::setup();
    Serial.println("Firebase setup complete.");

    Serial.println("Setting up Bluetooth...");
    BluetoothUtils::setup();
    Serial.println("Bluetooth setup complete.");

    Serial.println("Setting up User Interface...");
    UserInterface::setup();
    Serial.println("User Interface setup complete.");
}

void loop() {
    Serial.print("Iteration ");
    Serial.print(runCounter + 1);  // Iteration number starts from 1
    Serial.println("...");

    // Reconnect WiFi if not connected and the reconnect task is ready
    if ((WiFi.status() != WL_CONNECTED) && wifiReconnectTask.isReady()) {
        Serial.println("WiFi not connected, attempting to reconnect...");
        WifiUtils::reconnect();
    }

    // Run VLC if the trolley is enabled
    if (GlobalVariables::trolleyEnabled) {
        Serial.println("Trolley is enabled, running VLC...");
        Vlc::run();
    }

    // Run Firebase utilities
    Serial.println("Running Firebase utilities...");
    FirebaseUtils::run();

    // Run Bluetooth utilities
    Serial.println("Running Bluetooth utilities...");
    BluetoothUtils::run();

    // Refresh UI if the task is ready
    if (uiRefreshTask.isReady()) {
        Serial.println("Refreshing UI...");
        UserInterface::renderUI(); // Display user interface
    }

    runCounter++;
    Serial.print("Run counter incremented to: ");
    Serial.println(runCounter);

    Serial.println("Loop iteration complete.");
    delay(1); // Add a delay to avoid rapid looping (optional)
}
