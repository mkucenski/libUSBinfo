#include "usbConfiguration.h"

#include "usbString.h"

usbConfiguration::usbConfiguration(u_int8_t descriptorType)	:	usbDescriptor(descriptorType, (u_int8_t*)new USB_CONFIG_DESCRIPTOR, USB_CONFIG_DESCRIPTOR_LENGTH) {
}

usbConfiguration::~usbConfiguration() {
	for (vector<usbInterface*>::iterator it = m_vInterfaces.begin(); it != m_vInterfaces.end(); it++) {
		delete *it;
	}
	
	if (m_pDataStruct) {
		delete ((USB_CONFIG_DESCRIPTOR*)m_pDataStruct);
		m_pDataStruct = NULL;
	}
}

int usbConfiguration::load(int hostDevHandle, int devAddr, u_int8_t configIndex) {
	int rv = -1;
	
	if (usbDescriptor::load(hostDevHandle, devAddr, configIndex, 0) != -1) {
		if (getInterfaceCount() > 0) {
			u_int16_t uiDataSize = getTotalLength();
			u_int8_t* pData = (u_int8_t*)malloc(uiDataSize);
			if (pData) {
				usbDescriptor genericDescriptor(m_uiDescriptorType, pData, uiDataSize);
				if (genericDescriptor.load(hostDevHandle, devAddr, configIndex, 0) != -1) {
					u_int8_t* marker = &(pData[USB_CONFIG_DESCRIPTOR_LENGTH]);
					for (unsigned int i=0; i<getInterfaceCount(); i++) {
						USB_DEBUG_INFO("usbConfiguration::load() Found interface " << i);
						
						USB_INTERFACE_DESCRIPTOR interfaceStruct;
						memcpy(&interfaceStruct, marker, USB_INTERFACE_DESCRIPTOR_LENGTH);
						
						usbInterface* pInterface = new usbInterface;
						pInterface->load(hostDevHandle, devAddr, interfaceStruct);
						m_vInterfaces.push_back(pInterface);
						
						marker+=USB_INTERFACE_DESCRIPTOR_LENGTH;
						for (unsigned int j=0; j<interfaceStruct.bNumEndpoints; j++) {
							USB_DEBUG_INFO("usbConfiguration::load() Found endpoint " << j);
							
							USB_ENDPOINT_DESCRIPTOR endpointStruct;
							memcpy(&endpointStruct, marker, USB_ENDPOINT_DESCRIPTOR_LENGTH);

							usbEndpoint* pEndpoint = new usbEndpoint;
							pEndpoint->load(endpointStruct);
							pInterface->m_vEndpoints.push_back(pEndpoint);

							marker+=USB_ENDPOINT_DESCRIPTOR_LENGTH;
						}
					}
					rv = 0;
				} else {
					USB_DEBUG_ERROR("usbConfiguration::load() usbDescriptor::load() complete request error.");
				}
				free(pData);
			} else {
				USB_DEBUG_ERROR("usbConfiguration::load() malloc() failed.");
			}
		}
	} else {
		USB_DEBUG_ERROR("usbConfiguration::load() usbDescriptor::load() intial request error.");
	}

	return rv;
}

int usbConfiguration::getInterface(u_int8_t index, usbInterface** ppInterface) {
	int rv = -1;
	
	if (ppInterface) {
		if (m_vInterfaces.size() >= index+1) {
			*ppInterface = m_vInterfaces[index];
			rv = 0;
		} else {
			USB_DEBUG_ERROR("usbConfiguration::getInterface() Invalid index value.");
		}
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getInterface() Invalid destination pointer.");
	}
	
	return rv;
}

usbInterface* usbConfiguration::getInterface(u_int8_t index) {
	usbInterface* pInterface = NULL;
	getInterface(index, &pInterface);
	return pInterface;
}

u_int8_t usbConfiguration::getInterfaceCount() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bNumInterfaces;
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getInterfaceCount() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int8_t usbConfiguration::getMaxPower() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bMaxPower * 2;
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getMaxPower() Invalid descriptor pointer.");
	}
	
	return rv;
}

wstring usbConfiguration::getDescription(u_int16_t langIndex) {
	wstring rv;
	
	if (m_pDataStruct) {
		usbString stringDescriptor;
		if (stringDescriptor.load(m_iHostDevHandle, m_iDevAddr, ((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->iConfiguration, langIndex) != -1) {
			rv = stringDescriptor.getString();
		} else {
			USB_DEBUG_ERROR("usbConfiguration::getDescription() stringDescriptor::load() error");
		}
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getDescription() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int16_t usbConfiguration::getTotalLength() {
	u_int16_t rv = 0;
	
	if (m_pDataStruct) {
		rv = USB_GET_WORD(((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->wTotalLength);
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getTotalLength() Invalid descriptor pointer.");
	}
		
	return rv;
}

bool usbConfiguration::getBusPowered() {
	bool rv = false;
	
	if (m_pDataStruct) {
		rv = ((((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bmAttributes & 0x80) > 0);
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getBusPowered() Invalid descriptor pointer.");
	}
	
	return rv;
}

bool usbConfiguration::getSelfPowered() {
	bool rv = false;
	
	if (m_pDataStruct) {
		rv = ((((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bmAttributes & 0x40) > 0);
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getSelfPowered() Invalid descriptor pointer.");
	}
	
	return rv;
}

bool usbConfiguration::getRemoteWakeup() {
	bool rv = false;
	
	if (m_pDataStruct) {
		rv = ((((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bmAttributes & 0x20) > 0);
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getRemoteWakeup() Invalid descriptor pointer.");
	}
	
	return rv;
}

u_int8_t usbConfiguration::getType() {
	u_int8_t rv = 0;
	
	if (m_pDataStruct) {
		rv = ((USB_CONFIG_DESCRIPTOR*)m_pDataStruct)->bDescriptorType;
	} else {
		USB_DEBUG_ERROR("usbConfiguration::getType() Invalid descriptor pointer.");
	}
	
	return rv;
}
