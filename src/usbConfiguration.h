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

#ifndef USBCONFIGURATION_H_
#define USBCONFIGURATION_H_

#include <string>
#include <vector>

#include "usb.h"
#include "usbDescriptor.h"
#include "usbInterface.h"
#include "usbEndpoint.h"

using namespace std;

class usbConfiguration : private usbDescriptor {
	public:
		usbConfiguration(u_int8_t descriptorType = USB_DESCTYPE_CONFIGURATION);
		~usbConfiguration();

		int load(int hostDevHandle, int devAddr, u_int8_t configIndex);
		int getInterface(u_int8_t index, usbInterface** ppInterface);
		usbInterface* getInterface(u_int8_t index);
		
		u_int8_t getInterfaceCount();
		bool getBusPowered();
		bool getSelfPowered();
		bool getRemoteWakeup();
		u_int8_t getMaxPower();			//Expressed in mA units
		wstring getDescription(u_int16_t langIndex = 0x0409);
		u_int16_t getTotalLength();
		u_int8_t getType();
		
	private:
		vector<usbInterface*> m_vInterfaces;
};

#endif /*USBCONFIGURATION_H_*/
