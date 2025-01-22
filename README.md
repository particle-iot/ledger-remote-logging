# Particle Ledger

Imagine that your company has deployed thousands of connected devices, and a critical issue arises with a key customer. Resolving it requires sending a technician to manually retrieve logs and metadata—a costly, time-consuming process that unfortunately grows with your fleet.

Previously, debugging and troubleshooting started with the use of Particle’s built-in [SerialLogHandler](https://docs.particle.io/reference/device-os/api/logging/log-handlers/). The SerialLogHandler captures essential data about your application using serial over USB interface. This data can include comprehensive connectivity logs, detailed low-level Device OS trace data, and even application specific information. While powerful, this approach still required an on-site technician to access the data.

Enter Particle’s **Device [Ledger](https://docs.particle.io/getting-started/logic-ledger/ledger/)**. This solution transforms remote device diagnostics by securely streaming SerialLogHandler data directly to the Particle Cloud. With this cloud-based access, your team can rapidly diagnose and resolve issues without sending someone on-site. The result? Reduced operational costs, faster troubleshooting, and a seamless, scalable approach to maintaining device performance across your entire fleet.

## Ledger Setup

In this post we’ll use two different Ledgers, one for saving the remote log from a device and one for configuring the logging level. Technically only the one Ledger for the remote log is required, but it is useful to use Ledger to remotely change the behavior of devices you are troubleshooting. If you choose to only use the Ledger for the remote log, you will need to hardcode the configuration values in your firmware.

To start, we need to create a Device to Cloud Ledger in the Cloud. This is where the actual logs from the device will be stored. In the Particle Console, navigate to Ledger under Cloud Services, create a new Ledger, and select *Device to Cloud Ledger*. Press *Start now*. Then you want to name your Ledger. For the sake of this post I named the Ledger *device-logging*. Press *Save*.

Next, you will also want to create a Cloud to Device Ledger and this can be used to change parameters on the device, like log level, frequency, filters, etc. This is extremely useful as the goal is to not have to interact with the device locally. . For the sake of this post I named the Ledger *device-config* and I set the scope to be at the product level. Press *Save*.

If you are dealing with multiple devices, it is best practice to create two Cloud to Device Ledgers, one for the product default configuration, scoped at the product level, and one scoped at the device level. The device level Ledger can then be used to adjust just the device you are troubleshooting without affecting the rest of your devices under that product.

Under the device-config Ledger, we then want to create a new instance and set the configuration for the device. Navigate to the *Instances* tab and *Create a new instance* using the button. Navigate to the *Advanced* tab and paste the following configuration into the box and press *Create Instance*.

```jsx
{
    "lastRunLog": 1024,
    "connectionLog": 2048,
    "logAllConnections": true,
    "includeGeneral": true,
    "includeDiag": true,
    "includeTower": true,
    "logLevel": "TRACE",
    "logFilters": []
}
```

## The Firmware

This example uses simple firmware to capture a low-level log that prior to Ledger would require  human intervention to capture the log over Serial. The firmware is the same firmware as found in [this document](https://docs.particle.io/getting-started/logic-ledger/device-info-ledger/), but with minor tweaks to the Ledger names. Also this firmware leverages the [DeviceInfoLedger library](https://github.com/particle-iot/DeviceInfoLedger) which handles the complexities of capturing a remote log.  In order to have access to the Ledger firmware API, you must be running on Device OS greater than or equal to 6.1.0. 

This firmware was built running on OS 6.2.1


## Capturing a Log

Back in the Particle Console, navigate to Ledger and then select the *device-logging* Ledger. Select the latest instance and you will see the log output by the device. The instance will continue to be updated, giving you relevant information about how that particular device is performing.

## Conclusion

By utilizing Particle’s Device Ledger, your company can gains remote access to detailed logging and device metadata, enabling faster troubleshooting and resolution when field issues arise. This scalable solution enhances business operations by reducing costs and saving time, ensuring you deliver an exceptional user experience to your customers.