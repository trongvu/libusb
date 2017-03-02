# Expose Serial interface via USB of Samsung Android
For license, original usage ..., please refer [libusb](https://github.com/libusb/libusb)  

## Why Samsung Android?
Since my device is Samsung one, so I just do the test with this type only :)  

## And Serial Interface is?
The way to talk with Modem chipset directly via USB.
We can send some AT command via this communication channel and get result back from Modem side.  

## Bierf Information
###1. Windows  
This connection already opened in Windows PCs.  
We just need to install [official driver](http://developer.samsung.com/galaxy/others/android-usb-driver-for-windows) from Samsung. After plugging in, check Modem section in Device Manager.  
We can find out the correct COM port, use Putty to open serial connection to this port, send some AT commands, no sweat.  
###2. Other OSes  
We need to enable USB debugging options.  
If there is no USB debugging, device will be connected to HOST under MTP/PTP protocol, no way to talk with Modem side.  
So, problem here, if we dont want to enable USB debugging or even we could not enabled it (locked devices), how we can talk with Modem?  
That is what I'm going to explain later.  
