#pragma once

#include <afxtempl.h> // CStringArray 支持
#include <afxwin.h>   // CEdit 支持

// 函数声明
void FindFiles(const CStringArray& filePaths, CEdit& editCtrl);