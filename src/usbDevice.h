#ifndef USBDEVICE_H_
#define USBDEVICE_H_

#include <string>

#include "usb.h"
#include "usbDescriptor.h"
#include "usbConfiguration.h"
#include "usbOtherConfiguration.h"

using namespace std;

class usbDevice : private usbDescriptor { 
	public:
		usbDevice();
		~usbDevice();

		int load(int hostDevHandle, int devAddr);

		int getConfiguration(u_int8_t index, usbConfiguration* config);
		usbConfiguration getConfiguration(u_int8_t index);

		int getOtherConfiguration(u_int8_t index, usbOtherConfiguration* otherConfig);
		usbOtherConfiguration getOtherConfiguration(u_int8_t index);

		u_int8_t getType();
		u_int8_t getClass();
		u_int8_t getSubClass();
		u_int8_t getProtocol();
		u_int8_t getConfigCount();
		u_int8_t getMaxPacketSize();
		u_int16_t getVendorID();
		u_int16_t getProductID();

		wstring getUSBSpec();
		wstring getRevision();
		wstring getVendor(u_int16_t langIndex = 0x0409);
		wstring getProduct(u_int16_t langIndex = 0x0409);
		wstring getSerialNumber(u_int16_t langIndex = 0x0409);
};

#endif /*USBDEVICE_H_*/
