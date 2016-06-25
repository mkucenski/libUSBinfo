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

#ifndef USBENDPOINT_H_
#define USBENDPOINT_H_

#include <string>
#include <vector>

#include "usb.h"
#include "usbDescriptor.h"
#include "usbEndpoint.h"

using namespace std;

class usbEndpoint : private usbDescriptor { 
	public:
		usbEndpoint();
		~usbEndpoint();

		int load(USB_ENDPOINT_DESCRIPTOR endpointStruct);

		u_int8_t getEndpointNumber();
		u_int8_t getEndpointDirection();
		wstring getEndpointDirectionString();
		u_int8_t getTransferType();
		wstring getTransferTypeString();
		u_int8_t getSyncType();
		wstring getSyncTypeString();
		u_int8_t getUsageType();
		wstring getUsageTypeString();
		u_int16_t getMaxPacketSize();
		u_int8_t getDataTransferInterval();
		u_int8_t getType();
};

#endif /*USBENDPOINT_H_*/
