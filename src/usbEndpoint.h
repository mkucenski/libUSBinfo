#ifndef USBENDPOINT_H_
#define USBENDPOINT_H_

#include <string>
#include <vector>

#include "usb.h"
#include "usbDescriptor.h"
#include "usbEndpoint.h"

using namespace std;

class usbEndpoint : private usbDescriptor { 
	public:
		usbEndpoint();
		~usbEndpoint();

		int load(USB_ENDPOINT_DESCRIPTOR endpointStruct);

		u_int8_t getEndpointNumber();
		u_int8_t getEndpointDirection();
		wstring getEndpointDirectionString();
		u_int8_t getTransferType();
		wstring getTransferTypeString();
		u_int8_t getSyncType();
		wstring getSyncTypeString();
		u_int8_t getUsageType();
		wstring getUsageTypeString();
		u_int16_t getMaxPacketSize();
		u_int8_t getDataTransferInterval();
		u_int8_t getType();
};

#endif /*USBENDPOINT_H_*/
