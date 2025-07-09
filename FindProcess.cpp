#include "pch.h" 
#include "FindProcess.h"
#include <tlhelp32.h>

void FindProcesses(const CStringArray& processNames, CEdit& editControl)
{
    CStringArray foundProcesses;
    foundProcesses.RemoveAll();

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        editControl.SetWindowText(_T("�������̿���ʧ��"));
        return;
    }

    PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
    BOOL bMore = Process32First(hSnapshot, &pe);

    while (bMore)
    {
        CString currentName(pe.szExeFile);

        for (int i = 0; i < processNames.GetSize(); ++i)
        {
            if (currentName.CompareNoCase(processNames[i]) == 0)
            {
                // ����Ƿ�����ӹ�
                BOOL bExists = FALSE;
                for (int j = 0; j < foundProcesses.GetSize(); ++j)
                {
                    if (foundProcesses[j] == processNames[i])
                    {
                        bExists = TRUE;
                        break;
                    }
                }

                if (!bExists)
                {
                    foundProcesses.Add(processNames[i]);
                }
            }
        }

        bMore = Process32Next(hSnapshot, &pe);
    }

    CloseHandle(hSnapshot);

    // ��ʾ������༭��
    CString output;
    if (!foundProcesses.IsEmpty())
    {
        output = _T("���ֿ��ɽ����������У�\r\n");
        for (int i = 0; i < foundProcesses.GetSize(); ++i)
        {
            output += _T(" - ") + foundProcesses[i] + _T("\r\n");
        }
    }
    else
    {
        output = _T("δ����ָ���Ŀ��ɽ��̡�\r\n");
    }

    editControl.SetWindowText(output);
}