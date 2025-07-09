#include "pch.h"
#include "FindFiles.h"
#include <afx.h>

void FindFiles(const CStringArray& filePaths, CEdit& editCtrl)
{
    CString output;

    for (int i = 0; i < filePaths.GetSize(); ++i)
    {
        const CString& path = filePaths[i];
        CFileStatus status;

        if (CFile::GetStatus(path, status))
        {
            if (status.m_attribute & FILE_ATTRIBUTE_DIRECTORY)
            {
                output += _T("���ֿ���Ŀ¼��") + path + _T("\r\n");
            }
            else
            {
                output += _T("���ֿ����ļ���") + path + _T("\r\n");
            }
        }
        else
        {
            //output += _T("[������] ·����Ч��") + path + _T("\r\n");
        }
    }

    // ��ȡԭ���ı���׷��������
    CString oldText;
    editCtrl.GetWindowText(oldText);
    editCtrl.SetWindowText(oldText + output); // ׷������
}