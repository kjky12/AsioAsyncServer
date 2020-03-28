#include "Global.h"




/*!
	\brief ���������� ��ġ����
	\remarks ���������� ���� ��ġ�� �����մϴ�.
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
	strcpy(temp, full_path); // ��ι��ڿ��� ����
	sp = temp; // �����͸� ���ڿ� ó������

	while ((sp = strchr(sp, '\\')))
	{ // ���丮 �����ڸ� ã������
		if (sp > temp&&* (sp - 1) != ':')
		{ // ��Ʈ���丮�� �ƴϸ�
			*sp = '\0'; // ��� ���ڿ� ������ ����
			//mkdir(temp, S_IFDIR);
			CreateDirectoryA(temp, NULL);
			// ���丮�� ����� (�������� ���� ��)
			*sp = '\\'; // ���ڿ��� ������� ����
		}
		sp++; // �����͸� ���� ���ڷ� �̵�
	}

}

//! ���� ���� �Ǵ�.
bool gf_IsExistsFile(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}


//! ��ΰ� ���� ��� �ϴ� ��� ���丮 ����
void gf_MakeFullDirectoryA(std::string strPath)
{
	char chTmp[MAX_PATH] = { NULL , };
	strcpy(chTmp, strPath.c_str());

	//! ���丮�� ���°�� ���丮�� ��ü ����!
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


