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

	//! 로그 경로가 루트에서 일자별로 자동으로 나뉘게한다.
	bool SetAutoDateRefreshDirectory(bool bAutoRefreshDirectory);

	bool DumpLog(std::string strLog, bool bFlush = true);

	

private:

	std::string m_strLogRootDirectory;
	//! 로그 입력시 일자에 따라 자동으로 로그파일 업데이트 변수 -> 0: 비활성화, 1:자동업데이트!
	bool		m_bAutoRefreshDirectory;

	//! 로깅 링크 초기화!
	boost::shared_ptr< sink_t > init_logging();

	boost::shared_ptr<std::ofstream> open_file(const std::string file_name, uint8_t presition);

	//! 입력된 데이터를 업데이트!
	void stop_logging(boost::shared_ptr< sink_t >& sink);

	//! 링크를 종료해버린다.
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
// // 			logging::keywords::rotation_size = 10 * 1024 * 1024, //10mb마다 rotate 
// // 			logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), //12시마다 rotate 
// // 			logging::keywords::format = "[%TimeStamp%]: %Message%"
// 
// 			logging::keywords::file_name = "sample_%N.log", // 파일의 이름 패턴 
// 			logging::keywords::rotation_size = 10 * 1024 * 1024, // 파일의 최대 크기, 즉 "파일의 로테이션를 10MB마다 해라" 라는 의미 
// 			logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), // 파일의 로테이션 시간, "자정마다" 
// 			logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%" // 로그 레코드의 출력 형식
// 			//[%TimeStamp%] : 시간(소수점까지)
// 			//[% ThreadID%] : 스레드 ID
// 			//[% Severity%] : 로그 종류
// 			//[% ProcessID%] : 프로세스 ID? -> 순서인듯?
// 			//[% LineID%] : 프로세스의 위치?? -> 아마 다른 함수의 경우 다른 값이 출력되는듯..
// 		
// 		); // text 파일로 저장 하는 sink
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

