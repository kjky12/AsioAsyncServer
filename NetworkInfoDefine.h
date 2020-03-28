
#ifndef _NETWORKINFODEFINE_H_
#define _NETWORKINFODEFINE_H_


// Packet ID --------------------------------------------------------------------------------------------------------------------


// 공통 메시지 정의

#define	dfMSG_NETWORK_ID_INFO			0x0000		// 네트워크 ID 정보(S -> C ,S -> D)
#define	dfMSG_NETWORK_1					0x0002		// 
#define	dfMSG_NETWORK_2					0x0003		// 





#pragma  pack(push,1)

/////////////////////////////////////////////////////////////////////////////
//	Packet Header
/////////////////////////////////////////////////////////////////////////////
typedef struct P_HEADER
{
	int			PacketSize;
	int			PacketID;
	short		sSenderID;
}P_HEADER;

//////////////////////////////////////////////////////////////////////////
//	통신 기본 구조체
/////////////////////////////////////////////////////////////////////////////
typedef struct P_PACKET_DEFAULT
{
	P_HEADER	pHeader;

	PBYTE		pData;
}P_PACKET_DEFAULT;


#pragma  pack(pop)

#endif