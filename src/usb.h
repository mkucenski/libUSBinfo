#ifndef USB_H_
#define USB_H_

#include <sys/types.h>

#ifdef _DEBUG_
#include <iostream>
#define USB_DEBUG_ERROR(msg)	(std::cerr << "DEBUG ERROR: " << msg << "\n")
#define USB_DEBUG_WARNING(msg)	(std::cerr << "DEBUG WARNING: " << msg << "\n")
#define USB_DEBUG_INFO(msg)		(std::cerr << "DEBUG INFO: " << msg << "\n")
#else
#define USB_DEBUG_ERROR(msg)
#define USB_DEBUG_WARNING(msg)
#define USB_DEBUG_INFO(msg)
#endif

#define USB_REQTYPE_WRITE						0x00
#define USB_REQTYPE_READ						0x80
#define USB_REQTYPE_STANDARD					0x00
#define USB_REQTYPE_CLASS						0x20
#define USB_REQTYPE_VENDOR						0x40
#define USB_REQTYPE_DEVICE						0x00
#define USB_REQTYPE_INTERFACE					0x01
#define USB_REQTYPE_ENDPOINT					0x02
#define USB_REQTYPE_OTHER						0x03

#define USB_REQCODE_GET_STATUS					0x00
#define USB_REQCODE_CLEAR_FEATURE				0x01
#define USB_REQCODE_SET_FEATURE					0x03
#define USB_REQCODE_SET_ADDRESS					0x05
#define USB_REQCODE_GET_DESCRIPTOR				0x06
#define USB_REQCODE_SET_DESCRIPTOR				0x07
#define USB_REQCODE_GET_CONFIGURATION			0x08
#define USB_REQCODE_SET_CONFIGURATION			0x09
#define USB_REQCODE_GET_INTERFACE				0x0a
#define USB_REQCODE_SET_INTERFACE				0x0b
#define USB_REQCODE_SYNCH_FRAME					0x0c

#define USB_DESCTYPE_DEVICE						0x01
#define USB_DESCTYPE_CONFIGURATION				0x02
#define USB_DESCTYPE_STRING						0x03
#define USB_DESCTYPE_INTERFACE					0x04
#define USB_DESCTYPE_ENDPOINT					0x05
#define USB_DESCTYPE_DEVICE_QUALIFIER			0x06
#define USB_DESCTYPE_OTHER_SPEED_CONFIGURATION	0x07
#define USB_DESCTYPE_INTERFACE_POWER			0x08

typedef struct _USB_STRING_DESCRIPTOR {
	u_int8_t	bLength;
	u_int8_t	bDescriptorType;
	u_int16_t	bString[127];
} USB_STRING_DESCRIPTOR;
#define USB_STRING_DESCRIPTOR_LENGTH 256

typedef struct _USB_ENDPOINT_DESCRIPTOR {
	u_int8_t bLength;
	u_int8_t bDescriptorType;
	u_int8_t bEndpointAddress;
	u_int8_t bmAttributes;
	u_int8_t wMaxPacketSize[2];
	u_int8_t bInterval;
} USB_ENDPOINT_DESCRIPTOR;
#define USB_ENDPOINT_DESCRIPTOR_LENGTH 7

typedef struct _USB_INTERFACE_DESCRIPTOR {
	u_int8_t bLength;
	u_int8_t bDescriptorType;
	u_int8_t bInterfaceNumber;
	u_int8_t bAlternateSetting;
	u_int8_t bNumEndpoints;
	u_int8_t bInterfaceClass;
	u_int8_t bInterfaceSubClass;
	u_int8_t bInterfaceProtocol;
	u_int8_t iInterface;
} USB_INTERFACE_DESCRIPTOR;
#define USB_INTERFACE_DESCRIPTOR_LENGTH 9

typedef struct _USB_CONFIG_DESCRIPTOR {
	u_int8_t bLength;
	u_int8_t bDescriptorType;
	u_int8_t wTotalLength[2];		
	u_int8_t bNumInterfaces;
	u_int8_t bConfigurationValue;
	u_int8_t iConfiguration;
	u_int8_t bmAttributes;
	u_int8_t bMaxPower;
} USB_CONFIG_DESCRIPTOR;
#define USB_CONFIG_DESCRIPTOR_LENGTH 9

typedef struct _USB_DEVICE_DESCRIPTOR {
	u_int8_t bLength;
	u_int8_t bDescriptorType;
	u_int8_t bcdUSB[2];
	u_int8_t bDeviceClass;
	u_int8_t bDeviceSubClass;
	u_int8_t bDeviceProtocol;
	u_int8_t bMaxPacketSize;
	u_int8_t idVendor[2];
	u_int8_t idProduct[2];
	u_int8_t bcdDevice[2];
	u_int8_t iManufacturer;
	u_int8_t iProduct;
	u_int8_t iSerialNumber;
	u_int8_t bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;
#define USB_DEVICE_DESCRIPTOR_LENGTH 18

#define USB_GET_WORD(word) (word[0] | (word[1] << 8))
#define USB_SET_WORD(word, value) (word[0] = (u_int8_t)value, word[1] = (u_int8_t)(value >> 8))
#define USB_SET_WORD2(word,  highbyte, lowbyte) (word[0] = (u_int8_t)lowbyte, word[1] = (u_int8_t)highbyte)

#define BCD0(word) (word & 0xf)
#define BCD1(word) ((word >> 4) & 0xf)
#define BCD2(word) ((word >> 8) & 0xf)
#define BCD3(word) ((word >> 12) & 0xf)

int usbOpenHost(const char* hostDeviceName);
int usbCloseHost(int hostDevHandle);
int usbRequest(int hostDevHandle, int deviceAddr, u_int8_t bmRequestType, u_int8_t bRequest, u_int8_t wValueHigh, u_int8_t wValueLow, u_int16_t wIndex, u_int16_t wLength, void* pData);

#endif /*USB_H_*/
