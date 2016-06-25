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
