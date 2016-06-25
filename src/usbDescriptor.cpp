#include "usbDescriptor.h"

#include "usb.h"

usbDescriptor::usbDescriptor(u_int8_t descriptorType, u_int8_t* pDataStruct, u_int16_t uiDataStructSize)	:	m_iHostDevHandle(-1),
																												m_iDevAddr(0),
																												m_uiDescriptorType(descriptorType),
																												m_pDataStruct(pDataStruct),
																												m_uiDataStructSize(uiDataStructSize) {
	memset(m_pDataStruct, 0, m_uiDataStructSize);
}

usbDescriptor::~usbDescriptor() {
}

int usbDescriptor::load(int hostDevHandle, int devAddr, u_int8_t descriptorIndex, u_int16_t descriptorLangIndex) {
	int rv = -1;
	
	m_iHostDevHandle = hostDevHandle;
	m_iDevAddr = devAddr;
	
	if (m_pDataStruct && m_uiDataStructSize > 0) {
		if (usbRequest(m_iHostDevHandle, devAddr, USB_REQTYPE_READ, USB_REQCODE_GET_DESCRIPTOR, m_uiDescriptorType, descriptorIndex, descriptorLangIndex, m_uiDataStructSize, m_pDataStruct) != -1) {
			if (validate()) {
				rv = 0;
			} else {
				USB_DEBUG_ERROR("usbDescriptor::load() Validation of descriptor structure failed.");
			}
		} else {
			USB_DEBUG_ERROR("usbDescriptor::load() usbRequest() failed.");
		}
	} else {
		USB_DEBUG_ERROR("usbDescriptor::load() Invalid destination pointer or size.");
	}
	
	return rv;
}

u_int8_t usbDescriptor::getType() {
	return m_uiDescriptorType;
}

bool usbDescriptor::validate() {
	return getType() == m_uiDescriptorType;
}
