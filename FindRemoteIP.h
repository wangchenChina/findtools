#pragma once

#include <vector>
#include <string>
#include <afx.h> // CString ֧��

// ��������
std::vector<std::string> GetActiveRemoteIPs();
void FindRemoteIP(const CStringArray& expectedIPs,CEdit& editCtrl);
