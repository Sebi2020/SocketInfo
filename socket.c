#ifndef UNICODE
#define UNICODE 1
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <objbase.h>
#include <tchar.h>
#include <wchar.h>
int main(int argc, char *argv[]) {
WSADATA data;
//WCHAR Guid[40] = {0};
	if(WSAStartup(MAKEWORD(1,1), &data) != 0) {
		fprintf(stderr, "WSAStartup failed!\r\n");
		exit(1);
	}
	LPWSAPROTOCOL_INFO buffer = malloc(16384);
	DWORD lngt =0;
	lngt = 32000;
	int ret = 0;
	int retI = 0;
	ret = WSAEnumProtocols(NULL,buffer,&lngt);
	if(ret != SOCKET_ERROR) {
		wprintf(L"Enum suceeded with %d protocols!\n",ret);
		int i;
		for(i=0; i<ret;i++) {
			if(buffer[i].szProtocol == 0) {
				wprintf(L"Entry %d: UNKOWN ",i+1);
			} else {
				wprintf(L"Entry %d: %ws ",i+1,buffer[i].szProtocol);
			}
			if (buffer[i].ProtocolChain.ChainLen==1) {
				wprintf(L"(Base Service Provider)\n");
			} else if(buffer[i].ProtocolChain.ChainLen==0) {
				wprintf(L"(Layered Protocol Entry\n");
			} else {
				wprintf(L"(Layered Chain Entry)\n");
			}
			wprintf(L"-----------------------------------------------------------------\n");
			
			// Socket Type
			wprintf(L"Socket Type:\t\t\t");
			switch(buffer[i].iSocketType) {
				case SOCK_STREAM:
				wprintf(L"Stream Socket (SOCK_STREAM)\n");
				break;
				case SOCK_DGRAM:
				wprintf(L"Datagram Socket (SOCK_DGRAM)\n");
				break;
				case SOCK_RAW:
				wprintf(L"Raw Socket (SOCK_RAW)\n");
				break;
				case SOCK_RDM:
				wprintf(L"Relieable Message Datagram Socket (SOCK_RDM)\n");
				break;
				case SOCK_SEQPACKET:
				wprintf(L"Pseudo-Stream Packet Datagram Socket (SOCK_SEQPACKET)\n");
				break;
			}
			// Address Family
			wprintf(L"Address Family:\t\t\t");
			switch(buffer[i].iAddressFamily) {
			case AF_INET:
			wprintf(L"IPv4 (AF_INET)\n");
			break;
			case AF_IPX:
			wprintf(L"IPX (AF_IPX)\n");
			break;
			case AF_APPLETALK:
			wprintf(L"AppleTalk (AF_APPLETALK)\n");
			break;
			case AF_NETBIOS:
			wprintf(L"Netbios (AF_NETBIOS)\n");
			case AF_INET6:
			wprintf(L"IPv6 (AF_INET6)\n");
			break;
			case AF_IRDA:
			wprintf(L"Infrared Data Association (AF_IRDA)\n");
			break;
			case 32:
			wprintf(L"Bluetooth (AF_BTH)\n");
			break;
			}
			// Message Size
			wprintf(L"Maximum Message Size:\t\t");
			switch(buffer[i].dwMessageSize) {
			case 0x0:
			case 0xFFFFFFFF:
			wprintf(L"Infinite\n");
			break;
			case 0x1:
			default:
			wprintf(L"Depends on MTU setting\n");
			break;
			}
			wprintf(L"Byte-Order:\t\t\t");
			wprintf(buffer[i].iNetworkByteOrder ? L"Little-Endian (0x%X)\n" : L"Big-Endian (0x%X)\n",buffer[i].iNetworkByteOrder);
			
			// Provider reserved
			wprintf(L"Reserved:\t\t\t");
			wprintf(buffer[i].dwProviderReserved ? L"True\n" : L"False\n");
			printf("\n\n");
		}
		WSACleanup();
		free(buffer);
		exit(0);
	} else {
	WSACleanup();
	free(buffer);
	exit(1);
	}
}