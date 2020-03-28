
#include "pch.h"

#include "Session.h"
#include "TCP_Server.h"


CSession::CSession(boost::asio::io_service& io, CTCP_Server* pServer)
	: m_Socket(io), m_nID(-1), m_pServer(pServer), m_strand(io)
{
	
}



// ��¥�ð� �޼����� �����.
std::string CSession::make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now); // ctime_s ����. �����ϱ� �׳� ���� �Ѿ����
}

void CSession::handle_Accept(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/)
{

	m_Socket.async_read_some(boost::asio::buffer(m_RecvBuf),
		m_strand.wrap(
			boost::bind(&CSession::handle_Read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
		)
	);


}

bool CSession::IsErrorProcess(const boost::system::error_code error)
{
	bool bReturn = true;


	if (error)
	{
		bReturn = false;

		if (error == boost::asio::error::eof)
		{
			std::ostringstream stream;
			stream << m_nID << "Ŭ���̾�Ʈ�� ������ ���������ϴ�" << std::endl;
			g_BoostLog.DumpLog(stream.str());

			//! ��Ŀ �����忡�� �����ش�.
			g_Worker.DeleteAdr(m_nID);

			//! ������ �ݴ´�.
			m_Socket.close();
			
			//! �ӽÿ�������... �������� �����ϴ� shared_ptr�� �����ش�.
			m_pServer->DisconnectSoket(m_nID);
		}
		else if (error.value() == 10054)
		{
			std::ostringstream stream;
			stream << "Ŭ���̾�Ʈ�� ������ �������ϴ�." << std::endl;
			g_BoostLog.DumpLog(stream.str());

		}
		else
		{
			std::ostringstream stream;
			stream << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
			g_BoostLog.DumpLog(stream.str());

		}

	}



	return bReturn;
}

void CSession::handle_Write(const boost::system::error_code& error, size_t /*bytes_transferred*/)
{
	if (IsErrorProcess(error))
	{
		//! �ʿ� ó���� ������ ���⼭ ó��
	}

}

void CSession::handle_Read(const boost::system::error_code& error, size_t /*bytes_transferred*/)
{
	if (IsErrorProcess(error))
	{
		// ������ ó��
		if (m_RecvBuf.size() > 0)
		{
			std::ostringstream stream;
			stream << "Thread No : " << GetCurrentThreadId() << "\t" << "Session_Enqueue " << m_nID << "'s : " /*<< (*(char*)(m_RecvBuf.data()))*/ << std::endl;
			g_BoostLog.DumpLog(stream.str());

			g_Worker.AddWork(m_nID, m_RecvBuf.size(), m_RecvBuf.data());

			m_RecvBuf.assign(NULL); // ���� �ʱ�ȭ 
		}

		//m_Socket.async_wait(50);

		// Recv ���
		m_Socket.async_read_some(boost::asio::buffer(m_RecvBuf),

			m_strand.wrap(

				boost::bind(&CSession::handle_Read, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)

			)
		);




	}
}

void CSession::ProcessRecvPacket(PBYTE pData)
{
	std::ostringstream stream;
	stream << "Thread No : " << GetCurrentThreadId() << "\t" << m_nID << " ProcessRecvPacket" << std::endl;
	g_BoostLog.DumpLog(stream.str());

	SendToSocket(pData);

}





void CSession::SendToSocket(PBYTE pData)
{
	P_HEADER* pHeader = (P_HEADER*)pData;
	if (pHeader->PacketSize > 0)
	{
		m_Socket.async_write_some(boost::asio::buffer(pData, pHeader->PacketSize),
			m_strand.wrap(
				boost::bind(&CSession::handle_Write, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
			)
		);
	}

}




	tcp::socket& CSession::socket()
	{
		return m_Socket;
	}

	void CSession::start(int nID)
	{
		std::ostringstream stream;
		stream << "new connect id : " << nID << " ::: Welcome !" << std::endl;
		g_BoostLog.DumpLog(stream.str());

		m_nID = nID;

		//! ���⼭ ��Ŀ�� ID�� �ο����ش�.
		g_Worker.InsertAdr(m_nID, std::bind1st(std::mem_fun(&CSession::ProcessRecvPacket), this));

		// Recv ��� ����!
		m_Socket.async_read_some(boost::asio::buffer(m_RecvBuf),
			m_strand.wrap(
				boost::bind(&CSession::handle_Read, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
			)
		);

	}