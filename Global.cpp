#include "Global.h"




/*!
	\brief 실행파일의 위치리턴
	\remarks 실행파일의 폴더 위치를 리턴합니다.
	\param
	\return	CString
	\warning
*/
std::wstring	gf_GetModulePathW()
{

	wchar_t szPath[MAX_PATH] = { NULL };
	::GetModuleFileName(NULL, szPath, MAX_PATH);


	std::wstring strPath = szPath;


	int iPos = strPath.rfind('\\');

	

	std::wstring sModulePath = strPath.substr(0, iPos);
	sModulePath += L"\\";


	return sModulePath;
}


std::string gf_GetModulePathA()
{
	char buffer[MAX_PATH];

	::GetModuleFileNameA(NULL, buffer, MAX_PATH);

	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos) + "\\";
}



void MakeFullDirectoryA(char* full_path)
{
	char temp[256], * sp;
	strcpy(temp, full_path); // 경로문자열을 복사
	sp = temp; // 포인터를 문자열 처음으로

	while ((sp = strchr(sp, '\\')))
	{ // 디렉토리 구분자를 찾았으면
		if (sp > temp&&* (sp - 1) != ':')
		{ // 루트디렉토리가 아니면
			*sp = '\0'; // 잠시 문자열 끝으로 설정
			//mkdir(temp, S_IFDIR);
			CreateDirectoryA(temp, NULL);
			// 디렉토리를 만들고 (존재하지 않을 때)
			*sp = '\\'; // 문자열을 원래대로 복귀
		}
		sp++; // 포인터를 다음 문자로 이동
	}

}

//! 파일 유무 판단.
bool gf_IsExistsFile(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}


//! 경로가 없을 경우 하단 모든 디렉토리 생성
void gf_MakeFullDirectoryA(std::string strPath)
{
	char chTmp[MAX_PATH] = { NULL , };
	strcpy(chTmp, strPath.c_str());

	//! 디렉토리가 없는경우 디렉토리를 전체 생성!
	if (GetFileAttributesA(chTmp) == -1)
		MakeFullDirectoryA(chTmp);

}


std::string format_string(const std::string fmt, ...) 
{
	int size = ((int)fmt.size()) * 2;
	std::string buffer;
	va_list ap;
	while (1) 
	{
		buffer.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char*)buffer.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) 
		{
			buffer.resize(n);
			return buffer;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return buffer;
}


