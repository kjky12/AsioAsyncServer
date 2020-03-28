#pragma once


#include "pch.h"





extern std::wstring	gf_GetModulePathW();
extern std::string	gf_GetModulePathA();

//! 파일 유무 판단.
extern bool gf_IsExistsFile(const std::string& name);

extern void gf_MakeFullDirectoryA(std::string strPath);



extern std::string format_string(const std::string fmt, ...);
