#include "usbEndpoint.h"

usbEndpoint::usbEndpoint()	:	usbDescriptor(USB_DESCTYPE_ENDPOINT, (u_int8_t*)new USB_ENDPOINT_DESCRIPTOR, USB_ENDPOINT_DESCRIPTOR_LENGTH) {
}

usbEndpoint::~usbEndpoint() {
	if (m_pDataStruct) {
		delete ((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct);
		m_pDataStruct = NULL;
	}
}

int usbEndpoint::load(USB_ENDPOINT_DESCRIPTOR endpointStruct) {
	int rv = -1;
	
	if (m_pDataStruct) {
		*(USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct = endpointStruct;
		rv = 0;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::load() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbEndpoint::getEndpointNumber() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bEndpointAddress & 0xf;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getEndpointNumber() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbEndpoint::getEndpointDirection() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = (((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bEndpointAddress & 0x80) > 0;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getEndpointDirection() Invalid descriptor pointer.");
	}

	return rv;
}

wstring usbEndpoint::getEndpointDirectionString() {
	u_int8_t direction = getEndpointDirection();
	return (direction == 0 ? L"OUT" : L"IN");
}

u_int8_t usbEndpoint::getTransferType() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bmAttributes & 0x3;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getTransferType() Invalid descriptor pointer.");
	}

	return rv;
}

wstring usbEndpoint::getTransferTypeString() {
	wstring rv;
	
	u_int8_t transferType = getTransferType();
	switch (transferType) {
		case 0:
			rv = L"CONTROL";
			break;
		case 1:
			rv = L"ISOCHRONOUS";
			break;
		case 2:
			rv = L"BULK";
			break;
		case 3:
			rv = L"INTERRUPT";
			break;
		default:
			rv = L"UNKNOWN";
			break;
	}
	
	return rv;
}	

u_int8_t usbEndpoint::getSyncType() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = (((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bmAttributes >> 2) & 0x3;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getSyncType() Invalid descriptor pointer.");
	}

	return rv;
}

wstring usbEndpoint::getSyncTypeString() {
	wstring rv;
	
	u_int8_t syncType = getSyncType();
	switch (syncType) {
		case 0:
			rv = L"NONE";
			break;
		case 1:
			rv = L"ASYNCHRONOUS";
			break;
		case 2:
			rv = L"ADAPTIVE";
			break;
		case 3:
			rv = L"SYNCHRONOUS";
			break;
		default:
			rv = L"UNKNOWN";
			break;
	}
	
	return rv;
}

u_int8_t usbEndpoint::getUsageType() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = (((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bmAttributes >> 4) & 0x3;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getUsageType() Invalid descriptor pointer.");
	}

	return rv;
}

wstring usbEndpoint::getUsageTypeString() {
	wstring rv;
	
	u_int8_t usageType = getUsageType();
	switch (usageType) {
		case 0:
			rv = L"DATA";
			break;
		case 1:
			rv = L"FEEDBACK";
			break;
		case 2:
			rv = L"EXPLICIT FEEDBACK DATA";
			break;
		default:
			rv = L"UNKNOWN";
			break;
	}
	
	return rv;
}

u_int16_t usbEndpoint::getMaxPacketSize() {
	u_int16_t rv = 0;

	if (m_pDataStruct) {
		rv = USB_GET_WORD(((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->wMaxPacketSize);
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getMaxPacketSize() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbEndpoint::getDataTransferInterval() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bInterval;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getDataTransferInterval() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbEndpoint::getType() {
	u_int8_t rv = 0;

	if (m_pDataStruct) {
		rv = ((USB_ENDPOINT_DESCRIPTOR*)m_pDataStruct)->bDescriptorType;
	} else {
		USB_DEBUG_ERROR("usbEndpoint::getType() Invalid descriptor pointer.");
	}

	return rv;
}
