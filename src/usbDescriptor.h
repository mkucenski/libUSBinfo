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

#ifndef USBDESCRIPTOR_H_
#define USBDESCRIPTOR_H_

#include <string>
#include <sys/types.h>

using namespace std;

class usbDescriptor {
	public:
		usbDescriptor(u_int8_t descriptorType, u_int8_t* pDataStruct, u_int16_t uiDataStructSize);
		virtual ~usbDescriptor();
		
		int load(int hostDevHandle, int devAddr, u_int8_t descriptorIndex = 0, u_int16_t descriptorLangIndex = 0);
		virtual u_int8_t getType();
		bool validate();
		
	protected:
		int m_iHostDevHandle;
		int m_iDevAddr;
		u_int8_t m_uiDescriptorType;
		u_int8_t* m_pDataStruct;
		u_int16_t m_uiDataStructSize;
};

#endif /*USBDESCRIPTOR_H_*/
