#pragma once



class CTCP_Server;
class CSession : public boost::enable_shared_from_this<CSession>
{
private:
	tcp::socket m_Socket;
	int m_nID;


	std::string m_sMsg;
	boost::array<BYTE, eBufSize> m_RecvBuf;

	//! 콜백 함수의 동기화를 보장
	boost::asio::io_service::strand m_strand;


	CSession(boost::asio::io_service& io, CTCP_Server* pServer);

	bool IsErrorProcess(const boost::system::error_code error);

	// 날짜시간 메세지를 만든다.
	std::string make_daytime_string();

	void handle_Accept(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

	void handle_Write(const boost::system::error_code& error, size_t /*bytes_transferred*/);

	void handle_Read(const boost::system::error_code& error, size_t /*bytes_transferred*/);

public:
	//! Recv 패킷을 처리한다!!
	void ProcessRecvPacket(PBYTE pData);
	//! 해당 세션에 메세지를 전송한다
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
