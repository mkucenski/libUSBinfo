#include "usbDevice.h"

#include "utils.h"
#include "usbString.h"

usbDevice::usbDevice()	:	usbDescriptor(USB_DESCTYPE_DEVICE, (u_int8_t*)new USB_DEVICE_DESCRIPTOR, USB_DEVICE_DESCRIPTOR_LENGTH) {
}

usbDevice::~usbDevice() {
	if (m_pDataStruct) {
		delete ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct);
		m_pDataStruct = NULL;
	}
}

int usbDevice::load(int hostDevHandle, int devAddr) {
	int rv = -1;
	
	if (usbDescriptor::load(hostDevHandle, devAddr, 0, 0) != -1) {
		rv = 0;
	} else {
		USB_DEBUG_ERROR("usbDevice::load() usbDescriptor::load() failed.");
	}

	return rv;
}

int usbDevice::getConfiguration(u_int8_t index, usbConfiguration* config) {
	int rv = -1;
	
	if (m_pDataStruct) {
		if (config) {
			rv = config->load(m_iHostDevHandle, m_iDevAddr, index);
		} else {
			USB_DEBUG_ERROR("usbDevice::getConfiguration() Invalid destination pointer.");
		}
	} else {
		USB_DEBUG_ERROR("usbDevice::getConfiguration() Invalid descriptor pointer.");
	}
	
	return rv;
}

int usbDevice::getOtherConfiguration(u_int8_t index, usbOtherConfiguration* otherConfig) {
	return getConfiguration(index, otherConfig);
}

usbConfiguration usbDevice::getConfiguration(u_int8_t index) {
	usbConfiguration config;
	getConfiguration(index, &config);
	return config;
}

usbOtherConfiguration usbDevice::getOtherConfiguration(u_int8_t index) {
	usbOtherConfiguration otherConfig;
	getConfiguration(index, &otherConfig);
	return otherConfig;
}

wstring usbDevice::getUSBSpec() {
	string rv;
	
	if (m_pDataStruct) {
		char buf[12];
		u_int16_t bcdVal = USB_GET_WORD(((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bcdUSB);
		if (BCD3(bcdVal) != 0) {
			snprintf(buf, sizeof(buf)-1, "%d.%d.%d.%d", BCD3(bcdVal), BCD2(bcdVal), BCD1(bcdVal), BCD0(bcdVal));
		} else {
			snprintf(buf, sizeof(buf)-1, "%d.%d.%d", BCD2(bcdVal), BCD1(bcdVal), BCD0(bcdVal));
		}
		rv = buf;
	} else {
		USB_DEBUG_ERROR("usbDevice::getUSBSpec() Invalid descriptor pointer.");
	}
	
	return to_wstring(rv);
}

u_int8_t usbDevice::getClass() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bDeviceClass;
	} else {
		USB_DEBUG_ERROR("usbDevice::getClass() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbDevice::getSubClass() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bDeviceSubClass;
	} else {
		USB_DEBUG_ERROR("usbDevice::getSubClass() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbDevice::getProtocol() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bDeviceProtocol;
	} else {
		USB_DEBUG_ERROR("usbDevice::getProtocol() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbDevice::getMaxPacketSize() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bMaxPacketSize;
	} else {
		USB_DEBUG_ERROR("usbDevice::getMaxPacketSize() Invalid descriptor pointer.");
	}

	return rv;
}

u_int16_t usbDevice::getVendorID() {
	u_int16_t rv = 0;
	
	if (m_pDataStruct) {
		rv = USB_GET_WORD(((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->idVendor);
	} else {
		USB_DEBUG_ERROR("usbDevice::getVendorID() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int16_t usbDevice::getProductID() {
	u_int16_t rv = 0;
	
	if (m_pDataStruct) {
		rv = USB_GET_WORD(((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->idProduct);
	} else {
		USB_DEBUG_ERROR("usbDevice::getProductID() Invalid descriptor pointer.");
	}
	
	return rv;
}

wstring usbDevice::getRevision() {
	string rv;
	
	if (m_pDataStruct) {
		char buf[12];
		u_int16_t bcdVal = USB_GET_WORD(((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bcdDevice);
		if (BCD3(bcdVal) != 0) {
			snprintf(buf, sizeof(buf)-1, "%d.%d.%d.%d", BCD3(bcdVal), BCD2(bcdVal), BCD1(bcdVal), BCD0(bcdVal));
		} else {
			snprintf(buf, sizeof(buf)-1, "%d.%d.%d", BCD2(bcdVal), BCD1(bcdVal), BCD0(bcdVal));
		}
		rv = buf;
	} else {
		USB_DEBUG_ERROR("usbDevice::getRevision() Invalid descriptor pointer.");
	}
	
	return to_wstring(rv);
}

wstring usbDevice::getVendor(u_int16_t langIndex) {
	wstring rv;
	
	if (m_pDataStruct) {
		usbString stringDescriptor;
		if (stringDescriptor.load(m_iHostDevHandle, m_iDevAddr, ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->iManufacturer, langIndex) != -1) {
			rv = stringDescriptor.getString();
		} else {
			USB_DEBUG_ERROR("usbDevice::getVendor() usbString::load() failed.");
		}
	} else {
		USB_DEBUG_ERROR("usbDevice::getVendor() Invalid descriptor pointer.");
	}
	
	return rv;
}

wstring usbDevice::getProduct(u_int16_t langIndex) {
	wstring rv;
	
	if (m_pDataStruct) {
		usbString stringDescriptor;
		if (stringDescriptor.load(m_iHostDevHandle, m_iDevAddr, ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->iProduct, langIndex) != -1) {
			rv = stringDescriptor.getString();
		} else {
			USB_DEBUG_ERROR("usbDevice::getProduct() usbString::load() failed.");
		}
	} else {
		USB_DEBUG_ERROR("usbDevice::getProduct() Invalid descriptor pointer.");
	}
	
	return rv;
}

wstring usbDevice::getSerialNumber(u_int16_t langIndex) {
	wstring rv;
	
	if (m_pDataStruct) {
		usbString stringDescriptor;
		if (stringDescriptor.load(m_iHostDevHandle, m_iDevAddr, ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->iSerialNumber, langIndex) != -1) {
			rv = stringDescriptor.getString();
		} else {
			USB_DEBUG_ERROR("usbDevice::getSerialNumber() usbString::load() failed.");
		}
	} else {
		USB_DEBUG_ERROR("usbDevice::getSerialNumber() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int8_t usbDevice::getConfigCount() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bNumConfigurations;
	} else {
		USB_DEBUG_ERROR("usbDevice::getConfigCount() Invalid descriptor pointer.");
	}

	return rv;
}

u_int8_t usbDevice::getType() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_DEVICE_DESCRIPTOR*)m_pDataStruct)->bDescriptorType;
	} else {
		USB_DEBUG_ERROR("usbDevice::getType() Invalid descriptor pointer.");
	}
	
	return rv;
}
