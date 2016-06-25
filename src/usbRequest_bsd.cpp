// Copyright 2007 Matthew A. Kucenski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
