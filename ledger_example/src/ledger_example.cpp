
// Include Particle Device OS APIs
#include "Particle.h"

// inlcude library APIs
#include "DeviceInfoLedger.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);   //not required for OS >=6.2.x

// Set the firmware version
PRODUCT_VERSION(3);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// Used for retaining the last log
retained uint8_t retainedLogs[2048];

// setup() runs once, when the device is first turned on
void setup() {
  // Put initialization like pinMode and begin functions here
  
  waitFor(Serial.isConnected, 10000);   //waits for serial port for specified time, handy for seeing early log messages

    // This sets up remote configuration
    DeviceConfigLedger::instance()
        .withConfigDefaultLedgerName("device-config")
        .setup();
    
    // This sets up the device information in ledger
    DeviceInfoLedger::instance()
        .withInfoLedgerName("device-logging")
        .withRetainedBuffer(retainedLogs, sizeof(retainedLogs))
        .setup(); 


    // Using SYSTEM_MODE(SEMI_AUTOMATIC) and calling Particle.connect() after calling setup() for DeviceInfoLedger
    // is recommended to avoid getting new connection information in the last run log.
    Particle.connect();

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

  // This captures the various messages and sets the values in retainedLogs
  DeviceInfoLedger::instance().loop();
}