// Copyright 2007 Matthew A. Kucenski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
