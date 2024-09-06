#ifndef FIREBASE_UTILS_H
#define FIREBASE_UTILS_H

#include "Arduino.h"
#include "../Utilities.h"
#include <FirebaseESP32.h>
#include "../GlobalVariables/GlobalVariables.h"

// Firebase Login Credentials
#define USER_EMAIL "hanxi1999@gmail.com"
#define USER_PASSWORD "w6ynbK8hCTFbjgD"
#define API_KEY "AIzaSyAVwstNrTq2uhc7oPbZryfG3AkoEQXKLWc"
#define DATABASE_URL "https://esp32-18june-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Intervals
#define GET_CONFIG_INTERVAL 3500
#define UPLOAD_LOG_INTERVAL 2000

class FirebaseUtils
{
public:
    static String configPath;
    static String logPath;
    static String pastLogsPath;
    static FirebaseAuth auth;     // The user UID can be obtained from auth.token.uid
    static FirebaseConfig config; // Firebase Config data
    static FirebaseData configReceiveFirebaseData;
    static FirebaseData loggingFirebaseData;

    static Utilities::RepeatingTask getConfigTask;
    static Utilities::RepeatingTask uploadLogTask;

    static void setup();
    static void run();
    static void getConfigFromFirebase();
    static void uploadLogToFirebase(String coordinates);
    // static void configStreamCallback(StreamData data);
    // static void configStreamTimeoutCallback(bool timeout);
};

#endif