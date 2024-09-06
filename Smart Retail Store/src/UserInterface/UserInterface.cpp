#include "UserInterface.h"
#include "fonts/roboto_bold_8.h"
#include "fonts/roboto_bold_10.h"
#include "images/qr_code.h"

UserInterface::UIPage currentUIPage = UserInterface::UIPage::PAGE_ENABLED; // Current UI page state
const uint8_t *UserInterface::qr_code = qr_code_image; // Initialize the pointer with the QR code image data

void UserInterface::setup()
{
    Serial.println("UI setup: Initializing OLED...");
    Display.init(); // Initialize OLED
    Serial.println("UI setup: OLED has initialized.");
    Display.clear();
    Display.setBrightness(5);
    Display.invertDisplay();
    Display.setFont(Roboto_Bold_10);
    Display.drawString(50, 20, "Please Wait");
    Display.display();
    Serial.println("UI setup: Display setup complete."); 
}

void UserInterface::renderUI()
{
    Serial.println("Rendering UI...");
    if (GlobalVariables::trolleyEnabled)
    {
        Serial.println("Trolley is enabled. Displaying enabled page...");
        currentUIPage = UIPage::PAGE_ENABLED;
        displayEnabledPage();
    }
    else
    {
        Serial.println("Trolley is disabled. Displaying disabled page...");
        currentUIPage = UIPage::PAGE_DISABLED;
        displayDisabledPage();
    }
    Serial.println("UI rendering complete.");
}

// OLED dimensions:  (128 x 64), (width x height)
void UserInterface::displayEnabledPage()
{
    Serial.println("Displaying enabled page...");
    Display.clear();
    Display.setFont(Roboto_Bold_10);
    
    // Display "Welcome to INNO Store"
    Display.setTextAlignment(TEXT_ALIGN_CENTER);
    Display.drawString(64, 0, "Welcome to INNO Store");

    // Wi-Fi status
    Display.drawString(64, 20, WiFi.status() == WL_CONNECTED ? "Online" : "Offline");
    Display.drawString(64, 35, String(GlobalVariables::bleClients) + String(" users connected."));
    Display.display();
    Serial.println("Enabled page displayed.");
}

void UserInterface::displayDisabledPage()
{
    Serial.println("Displaying disabled page...");
    Display.clear();
    Display.setFont(Roboto_Bold_10);
    Display.setTextAlignment(TEXT_ALIGN_CENTER);
    Display.drawStringMaxWidth(64, 10, 78, GlobalVariables::trolleyName);
    Display.drawString(60, 40, "This trolley is disabled");
    Display.display();
    Serial.println("Disabled page displayed.");
}
