#pragma once



class CTCP_Server;
class CSession : public boost::enable_shared_from_this<CSession>
{
private:
	tcp::socket m_Socket;
	int m_nID;


	std::string m_sMsg;
	boost::array<BYTE, eBufSize> m_RecvBuf;

	//! �ݹ� �Լ��� ����ȭ�� ����
	boost::asio::io_service::strand m_strand;


	CSession(boost::asio::io_service& io, CTCP_Server* pServer);

	bool IsErrorProcess(const boost::system::error_code error);

	// ��¥�ð� �޼����� �����.
	std::string make_daytime_string();

	void handle_Accept(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

	void handle_Write(const boost::system::error_code& error, size_t /*bytes_transferred*/);

	void handle_Read(const boost::system::error_code& error, size_t /*bytes_transferred*/);

public:
	//! Recv ��Ŷ�� ó���Ѵ�!!
	void ProcessRecvPacket(PBYTE pData);
	//! �ش� ���ǿ� �޼����� �����Ѵ�
	void SendToSocket(PBYTE pData);
	

	typedef boost::shared_ptr<CSession> pointer;

	static pointer create(boost::asio::io_service& io, CTCP_Server* pServer)
 	{
 		return pointer(new CSession(io, pServer));
 	}

	tcp::socket& socket();

	void start(int nID);


	CTCP_Server* m_pServer;

};
