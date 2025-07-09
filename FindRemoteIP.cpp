#include "pch.h"
#include "FindRemoteIP.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

std::vector<std::string> GetActiveRemoteIPs()
{
    std::vector<std::string> remoteIPs;

    DWORD dwSize = 0;
    PMIB_TCPTABLE_OWNER_PID pTcpTable = NULL;

    // ��ȡ TCP ���С
    if (GetExtendedTcpTable(NULL, &dwSize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == ERROR_INSUFFICIENT_BUFFER)
    {
        pTcpTable = (PMIB_TCPTABLE_OWNER_PID)malloc(dwSize);
        if (pTcpTable == NULL)
        {
            return remoteIPs;
        }

        if (GetExtendedTcpTable(pTcpTable, &dwSize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR)
        {
            for (DWORD i = 0; i < pTcpTable->dwNumEntries; ++i)
            {
                MIB_TCPROW_OWNER_PID row = pTcpTable->table[i];
                sockaddr_in addr;
                addr.sin_family = AF_INET;
                addr.sin_addr.S_un.S_addr = row.dwRemoteAddr;
                addr.sin_port = row.dwRemotePort;

                char ipStr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &addr.sin_addr, ipStr, sizeof(ipStr));

                if (strcmp(ipStr, "0.0.0.0") != 0)
                {
                    remoteIPs.push_back(std::string(ipStr));
                }
            }
        }

        free(pTcpTable);
    }

    return remoteIPs;
}

// ����Ƿ���Զ�� IP ��Ԥ���б���
void FindRemoteIP(const CStringArray& expectedIPs, CEdit& editCtrl)
{
    std::vector<std::string> activeIPs = GetActiveRemoteIPs();
    CString output;

    for (const auto& ip : activeIPs)
    {
        for (int i = 0; i < expectedIPs.GetSize(); ++i)
        {
            CString strExpected = expectedIPs[i];
            std::string expected = CT2CA(strExpected); // ת�� CString -> std::string

            if (ip == expected)
            {
                output.AppendFormat(_T("���ֿ���ͨ��IP��%s\r\n"), strExpected);
            }
        }
    }

    if (output.IsEmpty())
    {
        output = _T("δ����ƥ��Ŀ���IP\r\n");
    }

    CString oldText;
    editCtrl.GetWindowText(oldText);
    editCtrl.SetWindowText(oldText + output); // ׷������
}