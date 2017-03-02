# Expose Serial interface via USB of Samsung Android
For license, original usage ..., please refer [libusb](https://github.com/libusb/libusb)  

## Why Samsung Android?
Since my device is Samsung one, so I just do the test with this type only :)  

## And Serial Interface is?
The way to talk with Modem chipset directly via USB.
We can send some AT command via this communication channel and get result back from Modem side.  

## Bierf Information
### 1. Windows  
This connection already opened in Windows PCs.  
We just need to install [official driver](http://developer.samsung.com/galaxy/others/android-usb-driver-for-windows) from Samsung. After plugging in, check Modem section in Device Manager.  
We can find out the correct COM port, use Putty to open serial connection to this port, send some AT commands, no sweat.  
### 2. Other OSes  
We need to enable USB debugging options.  
If there is no USB debugging, device will be connected to HOST under MTP/PTP protocol, no way to talk with Modem side.  
So, problem here, if we dont want to enable USB debugging or even we could not enabled it (locked devices), how we can talk with Modem?  
That is what I'm going to explain later.  

## USB configuration under Linux   
Since there is nothing to do in Windows, so I'm going to show you what happens on Linux (Ubuntu 14.04). Android has same behaviour.
I dont have Mac, but I guess, it should be similar :D.  
### 1. With USB debugging ON  
Run "lsusb -v -d 04e8", refer [output](configuration_changer/debug_on.txt)
```
bFunctionClass          2 Communications
bFunctionSubClass       2 Abstract (modem)
bFunctionProtocol       1 AT-commands (v.25ter)
iFunction               8 CDC Serial
```
CDC Serial was here, so we can try to issue some AT command.
```
trongvu@trongvu-PC:~$ sudo socat - /dev/ttyACM0,crnl
ATZ

OK
AT+GMM
AT+GMM
SM-N900K
OK
AT+GSN
AT+GSN
357557055xxxxx2 ===> IMEI
OK
```
### 2. With USB debugging OFF  
There is no "/dev/ttyACM0", so we could not issue AT command any more.  
In this case, how we can enable it without unlock the device nor enable USB debugging by ourself.  
Let's try deeper look into result of "lsusb".  
In case of USB debug ON, there is only one configuration:  
```
bNumConfigurations      1  
```
But in case of USB debugging OFF, we have two:  
``` 
bNumConfigurations      2  
```
And we still can see CDC Serial Interface under Configuration #2 (not activated one).  
So, main problem now is how to active configuration #2 

## How to change default configuration  
For this purpose, please refer to [f9c2971](https://github.com/trongvu/libusb/commit/f9c2971d8ca35f255b11f37998329b0c323f5d83)

