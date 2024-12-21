/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// inlcude library APIs
#include "DeviceInfoLedger.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);   //not required for OS >=6.2.0

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

retained uint8_t retainedLogs[2048];


// setup() runs once, when the device is first turned on
void setup() {
  // Put initialization like pinMode and begin functions here
  
  waitFor(Serial.isConnected, 10000);   //waits for serial port for specified time, handy for seeing early log messages

    // This sets up remote configuration
    DeviceConfigLedger::instance()
        .withConfigDefaultLedgerName("device-config")
        //.withConfigDeviceLedgerName("device-info-config")
        .setup();

    // This sets up the device information in ledger
    DeviceInfoLedger::instance()
        .withInfoLedgerName("device-logging")
        .withRetainedBuffer(retainedLogs, sizeof(retainedLogs))
        .setup(); 


    // Using SYSTEM_MODE(SEMI_AUTOMATIC) and calling Particle.connect() after calling setup() for DeviceInfoLedger
    // is recommended to avoid getting new connection information in the last run log.
    Particle.connect();


/*
  // Start cloud to device ledger synchronization
  DeviceConfig = Particle.ledger("device-config");
  //DeviceConfig.onSync(OnSyncCallback);    //EAF need to do this to set the config values for logging
  //https://docs.particle.io/reference/device-os/api/ledger/onsync-onsynccallback-ledger-class/

  // set device to cloud ledger
  DeviceLogging = Particle.ledger("device-logging");
  */


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

  //insert the portion to set the data to the D->C ledger

  DeviceInfoLedger::instance().loop();
}