#include "usbInterface.h"

#include "usbString.h"

usbInterface::usbInterface()	:	usbDescriptor(USB_DESCTYPE_INTERFACE, (u_int8_t*)new USB_INTERFACE_DESCRIPTOR, USB_INTERFACE_DESCRIPTOR_LENGTH) {
}

usbInterface::~usbInterface() {
	for (vector<usbEndpoint*>::iterator it = m_vEndpoints.begin(); it != m_vEndpoints.end(); it++) {
		delete *it;
	}
	
	if (m_pDataStruct) {
		delete ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct);
		m_pDataStruct = NULL;
	}
}

int usbInterface::load(int hostDevHandle, int devAddr, USB_INTERFACE_DESCRIPTOR interfaceStruct) {
	int rv = -1;
	
	m_iHostDevHandle = hostDevHandle;
	m_iDevAddr = devAddr;

	if (m_pDataStruct) {
		*(USB_INTERFACE_DESCRIPTOR*)m_pDataStruct = interfaceStruct;
		rv = 0;
	} else {
		USB_DEBUG_ERROR("usbInterface::load() Invalid descriptor pointer.");
	}

	return rv;
}

int usbInterface::getEndpoint(u_int8_t index, usbEndpoint** ppEndpoint) {
	int rv = -1;
	
	if (ppEndpoint) {
		if (m_vEndpoints.size() >= index+1) {
			*ppEndpoint = m_vEndpoints[index];
			rv = 0;
		} else {
			USB_DEBUG_ERROR("usbInterface::getEndpoint() Invalid index.");
		}
	} else {
		USB_DEBUG_ERROR("usbInterface::getEndpoint() Invalid destination pointer.");
	}
	
	return rv;
}

usbEndpoint* usbInterface::getEndpoint(u_int8_t index) {
	usbEndpoint* pEndpoint = NULL;
	getEndpoint(index, &pEndpoint);
	return pEndpoint;
}
		
u_int8_t usbInterface::getEndpointCount() {
	USB_DEBUG_INFO("usbInterface::getEndpointCount() " << this);
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->bNumEndpoints;
		USB_DEBUG_INFO("usbInterface::getEndpointCount() " << rv);
	} else {
		USB_DEBUG_ERROR("usbInterface::getEndpointCount() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbInterface::getClass() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->bInterfaceClass;
	} else {
		USB_DEBUG_ERROR("usbInterface::getClass() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbInterface::getSubClass() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->bInterfaceSubClass;
	} else {
		USB_DEBUG_ERROR("usbInterface::getSubClass() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbInterface::getProtocol() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->bInterfaceProtocol;
	} else {
		USB_DEBUG_ERROR("usbInterface::getProtocol() Invalid descriptor pointer.");
	}

	return rv;
}

wstring usbInterface::getDescription(u_int16_t langIndex) {
	wstring rv;
	
	if (m_pDataStruct) {
		usbString stringDescriptor;
		if (stringDescriptor.load(m_iHostDevHandle, m_iDevAddr, ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->iInterface, langIndex) != -1) {
			rv = stringDescriptor.getString();
		} else {
			USB_DEBUG_ERROR("usbInterface::getDescription() Failure loading string descriptor.");
		}
	} else {
		USB_DEBUG_ERROR("usbInterface::getDescription() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int8_t usbInterface::getType() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_INTERFACE_DESCRIPTOR*)m_pDataStruct)->bDescriptorType;
	} else {
		USB_DEBUG_ERROR("usbInterface::getType() Invalid descriptor pointer.");
	}

	return rv;
}
