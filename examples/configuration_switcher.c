#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"
#define SAMSUNG_VENDOR_ID  0x04e8
#define APPLE_VENDOR_ID  0x05ac

static void switcher(libusb_device **devs, int config)
{
    libusb_device_handle *device = NULL;
    libusb_device *dev;
    int i = 0; 

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor\n");
            return;
        }
        printf("idVendor = %04x\n", desc.idVendor);
        if((desc.idVendor == SAMSUNG_VENDOR_ID || desc.idVendor == APPLE_VENDOR_ID) && desc.bNumConfigurations >= 2){
            //samsung device, change to configuration #2
            //dev - > current device
            int count = 0;
            while(count < 2){
                printf("Found samsung/apple device, try to change configuration \n");
                int status = libusb_open(dev, &device);
                if(status){
                    printf("Open device failed, status = %d \n", status);
                    break;
                }
                int currentConfig = 0;
                libusb_get_configuration(device, &currentConfig);
                /*if((desc.idVendor == SAMSUNG_VENDOR_ID && currentConfig == 2) || (desc.idVendor == APPLE_VENDOR_ID && currentConfig == 4)){
                    printf("Current config = 2 (samsung) or 4 (apple), status = %d \n", status);
                    break;
                }*/
		if(currentConfig == config){
			printf("Request same config = %d \n", currentConfig);
                    	break;
		}
                status = libusb_reset_device(device);
                if(status){
                    printf("Reset device failed, status = %d \n", status);
                    break;
                }
                /*if(desc.idVendor == SAMSUNG_VENDOR_ID)
                    status = libusb_set_configuration(device, 2);
                if(desc.idVendor == APPLE_VENDOR_ID)
                   status = libusb_set_configuration(device, 4);*/ 
		status = libusb_set_configuration(device, config);
                libusb_close(device);
                device = NULL;
                if(!status){
                    printf("Config changed, new config = %d \n", config);
                   break;
                }else{
                    printf("Config NOT changed, status = %d \n", status);
                   count++;
                }
            }
        }
    }
}
int main(int argc, char **argv)
{
	libusb_device **devs;
	int r, config;
	ssize_t cnt;
	if(argc == 2){
		config = atoi(argv[1]);
	}else{
		config = -1;
	}
	r = libusb_init(NULL);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int) cnt;

	switcher(devs, config);
	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);
	return 0;
}
