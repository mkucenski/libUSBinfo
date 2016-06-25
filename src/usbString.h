#ifndef USBSTRING_H_
#define USBSTRING_H_

#include <string>

#include "usb.h"
#include "usbDescriptor.h"

using namespace std;

class usbString : private usbDescriptor { 
	public:
		usbString();
		~usbString();
		
		int load(int hostDevHandle, int devAddr, u_int8_t stringIndex, u_int16_t langIndex = 0x0409);

		wstring getString();
		u_int8_t getType();
};

#endif /*USBSTRING_H_*/
