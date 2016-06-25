#include "usb.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <dev/usb/usb.h>

int usbOpenHost(const char* hostDeviceName) {
	int rv = -1;
	if ((rv = open(hostDeviceName, O_RDONLY)) == -1) {
		USB_DEBUG_ERROR("usbOpenHost() Failure opening: " << hostDeviceName);
	}
	return rv;
}

int usbCloseHost(int hostDevHandle) {
	int rv = -1;
	if ((rv = close(hostDevHandle)) == -1) {
		USB_DEBUG_ERROR("usbCloseHandle() Failure closing file handle.");
	}
	return rv;
}

int usbRequest(int hostDevHandle, int deviceAddr, u_int8_t bmRequestType, u_int8_t bRequest, u_int8_t wValueHigh, u_int8_t wValueLow, u_int16_t wIndex, u_int16_t wLength, void* pData) {
	int rv = -1;
	
	if (hostDevHandle > 0) {
		if (pData && wLength > 0) {
			struct usb_ctl_request devRequest;
			memset(&devRequest, 0, sizeof(devRequest));
			
			devRequest.ucr_addr = deviceAddr;
			devRequest.ucr_flags = USBD_SHORT_XFER_OK;
			devRequest.ucr_data = pData;
			devRequest.ucr_request.bmRequestType = bmRequestType;
			devRequest.ucr_request.bRequest = bRequest;
			USETW2(devRequest.ucr_request.wValue, wValueHigh, wValueLow);
			USETW(devRequest.ucr_request.wIndex, wIndex);
			USETW(devRequest.ucr_request.wLength, wLength);
			if (ioctl(hostDevHandle, USB_REQUEST, &devRequest) != -1) {
				rv = 0;
			} else {
				USB_DEBUG_ERROR("usbRequest() ioctl: " << strerror(errno));
			}
		} else {
			USB_DEBUG_ERROR("usbRequest() Invalid function arguments.");
		}
	} else {
		USB_DEBUG_ERROR("usbRequest() Invalid host device handle.");
	}
	
	return rv;
}
