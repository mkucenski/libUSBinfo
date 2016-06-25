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
