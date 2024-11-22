/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

Ledger DeviceLogging;   //device to cloud ledger for the remote logs
Ledger DeviceConfig;    //cloud to device ledger for configuration

retained uint8_t remoteLogs[2048];

// setup() runs once, when the device is first turned on
void setup() {
  // Put initialization like pinMode and begin functions here
  
  waitFor(Serial.isConnected, 10000);   //waits for serial port for specified time, handy for seeing early log messages

  // Start cloud to device ledger synchronization
  deviceConfig = Particle.ledger("device-config");
  deviceConfig.onSync(syncCallback);

  // set device to cloud ledger
  DeviceLogging = Particle.ledger("device-logging");

  //insert ledger??

  /*
  DeviceLoggingLedger::instance()

        .withLocalConfig(localConfig)   //need to figure this out since I'm not showing localconfig....
        .withRetainedBuffer(remoteLogs, sizeof(remoteLogs))
        .setup(); 
  */


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

  DeviceLoggingLedger::instance().loop();
}
