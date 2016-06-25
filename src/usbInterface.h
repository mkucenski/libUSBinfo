#ifndef USBINTERFACE_H_
#define USBINTERFACE_H_

#include <string>
#include <vector>

#include "usb.h"
#include "usbDescriptor.h"
#include "usbEndpoint.h"

using namespace std;

class usbInterface : private usbDescriptor { 
	friend class usbConfiguration;
	
	public:
		usbInterface();
		~usbInterface();

		int load(int hostDevHandle, int devAddr, USB_INTERFACE_DESCRIPTOR interfaceStruct);
		int getEndpoint(u_int8_t index, usbEndpoint** ppEndpoint);
		usbEndpoint* getEndpoint(u_int8_t index);
		
		u_int8_t getEndpointCount();
		u_int8_t getClass();
		u_int8_t getSubClass();
		u_int8_t getProtocol();
		wstring getDescription(u_int16_t langIndex = 0x0409);
		u_int8_t getType();
		
	private:
		vector<usbEndpoint*> m_vEndpoints;
};

#endif /*USBINTERFACE_H_*/
