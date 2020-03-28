#pragma once

#include "IncludeBoost.h"

//[ example_sinks_async_init
enum severity_level
{
	normal,
	warning,
	error
};

// Complete sink type
typedef sinks::asynchronous_sink< sinks::text_ostream_backend > sink_t;



class CBoostLog
{
public:




public:
	CBoostLog();

	~CBoostLog();


	bool SetLogDirectoryPath(std::string strDirectory);

	//! �α� ��ΰ� ��Ʈ���� ���ں��� �ڵ����� �������Ѵ�.
	bool SetAutoDateRefreshDirectory(bool bAutoRefreshDirectory);

	bool DumpLog(std::string strLog, bool bFlush = true);

	

private:

	std::string m_strLogRootDirectory;
	//! �α� �Է½� ���ڿ� ���� �ڵ����� �α����� ������Ʈ ���� -> 0: ��Ȱ��ȭ, 1:�ڵ�������Ʈ!
	bool		m_bAutoRefreshDirectory;

	//! �α� ��ũ �ʱ�ȭ!
	boost::shared_ptr< sink_t > init_logging();

	boost::shared_ptr<std::ofstream> open_file(const std::string file_name, uint8_t presition);

	//! �Էµ� �����͸� ������Ʈ!
	void stop_logging(boost::shared_ptr< sink_t >& sink);

	//! ��ũ�� �����ع�����.
	void Finsh_logging(boost::shared_ptr< sink_t >& sink);

	boost::shared_ptr< sink_t > m_sinkSingleTone;
	


// 	{
// 		init();
// 		logging::add_common_attributes();
// 
// 		src::severity_logger< severity_level > lg;
// 
// 
// 		BOOST_LOG_SEV(lg, trace) << "A trace severity message";
// 		BOOST_LOG_SEV(lg, debug) << "A debug severity message";
// 		BOOST_LOG_SEV(lg, info) << "An informational severity message";
// 		BOOST_LOG_SEV(lg, warning) << "A warning severity message";
// 		BOOST_LOG_SEV(lg, error) << "An error severity message";
// 		BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
// 
// 		//BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
// 		//BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
// 		//BOOST_LOG_TRIVIAL(info) << "An informational severity message";
// 		//BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
// 		//BOOST_LOG_TRIVIAL(error) << "An error severity message";
// 		//BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
// 
// 
// 	}





// 	void init()
// 	{
// 
// 		logging::add_file_log(
// // 			logging::keywords::file_name = "sample_%N.log",
// // 			logging::keywords::rotation_size = 10 * 1024 * 1024, //10mb���� rotate 
// // 			logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), //12�ø��� rotate 
// // 			logging::keywords::format = "[%TimeStamp%]: %Message%"
// 
// 			logging::keywords::file_name = "sample_%N.log", // ������ �̸� ���� 
// 			logging::keywords::rotation_size = 10 * 1024 * 1024, // ������ �ִ� ũ��, �� "������ �����̼Ǹ� 10MB���� �ض�" ��� �ǹ� 
// 			logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), // ������ �����̼� �ð�, "��������" 
// 			logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%" // �α� ���ڵ��� ��� ����
// 			//[%TimeStamp%] : �ð�(�Ҽ�������)
// 			//[% ThreadID%] : ������ ID
// 			//[% Severity%] : �α� ����
// 			//[% ProcessID%] : ���μ��� ID? -> �����ε�?
// 			//[% LineID%] : ���μ����� ��ġ?? -> �Ƹ� �ٸ� �Լ��� ��� �ٸ� ���� ��µǴµ�..
// 		
// 		); // text ���Ϸ� ���� �ϴ� sink
// 
// 
// // 		logging::add_file_log
// // 		(
// // 			keywords::file_name = "sample_%N.log",
// // 			keywords::rotation_size = 10 * 1024 * 1024,
// // 			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
// // 			keywords::format = "[%TimeStamp%]: %Message%"
// // 		);
//  
// 		logging::core::get()->set_filter
// 		(
// 			logging::trivial::severity >= logging::trivial::info
// 		);
// 	}





};

