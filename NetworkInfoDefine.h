
#ifndef _NETWORKINFODEFINE_H_
#define _NETWORKINFODEFINE_H_


// Packet ID --------------------------------------------------------------------------------------------------------------------


// ���� �޽��� ����

#define	dfMSG_NETWORK_ID_INFO			0x0000		// ��Ʈ��ũ ID ����(S -> C ,S -> D)
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
//	��� �⺻ ����ü
/////////////////////////////////////////////////////////////////////////////
typedef struct P_PACKET_DEFAULT
{
	P_HEADER	pHeader;

	PBYTE		pData;
}P_PACKET_DEFAULT;


#pragma  pack(pop)

#endif