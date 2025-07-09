#pragma once

#include <afxtempl.h> // CStringArray 支持
#include <afxwin.h>   // CEdit 支持

// 函数声明：查找多个进程，并更新编辑框
void FindProcesses(const CStringArray& processNames, CEdit& editControl);
