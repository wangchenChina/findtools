#pragma once

#include <vector>
#include <string>
#include <afx.h> // CString 支持

// 函数声明
std::vector<std::string> GetActiveRemoteIPs();
void FindRemoteIP(const CStringArray& expectedIPs,CEdit& editCtrl);
