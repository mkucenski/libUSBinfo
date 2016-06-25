#include "usbString.h"

usbString::usbString()	:	usbDescriptor(USB_DESCTYPE_STRING, (u_int8_t*)new USB_STRING_DESCRIPTOR, USB_STRING_DESCRIPTOR_LENGTH) {
}

usbString::~usbString() {
	if (m_pDataStruct) {
		delete ((USB_STRING_DESCRIPTOR*)m_pDataStruct);
		m_pDataStruct = NULL;
	}
}

int usbString::load(int hostDevHandle, int devAddr, u_int8_t stringIndex, u_int16_t langIndex) {
	int rv = -1;
	
	if (stringIndex > 0 && langIndex > 0) {
		if (usbDescriptor::load(hostDevHandle, devAddr, stringIndex, langIndex) != -1) {
			rv = 0;
		} else {
			USB_DEBUG_ERROR("usbString::load() usbDescriptor::load() failed.");
		}
	} else {
		USB_DEBUG_ERROR("usbString::load() Invalid string or language index.");
	}

	return rv;
}

wstring usbString::getString() {
	wstring rv;
	
	if (m_pDataStruct) {
		for (int i=0; i<(((USB_STRING_DESCRIPTOR*)m_pDataStruct)->bLength-2)/2; i++) {
			rv += ((USB_STRING_DESCRIPTOR*)m_pDataStruct)->bString[i];
		}
	} else {
		USB_DEBUG_ERROR("usbString::getString() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int8_t usbString::getType() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_STRING_DESCRIPTOR*)m_pDataStruct)->bDescriptorType;
	} else {
		USB_DEBUG_ERROR("usbString::getType() Invalid descriptor pointer.");
	}
	
	return rv;
}
