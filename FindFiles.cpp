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
                output += _T("发现可疑目录：") + path + _T("\r\n");
            }
            else
            {
                output += _T("发现可疑文件：") + path + _T("\r\n");
            }
        }
        else
        {
            //output += _T("[不存在] 路径无效：") + path + _T("\r\n");
        }
    }

    // 获取原有文本并追加新内容
    CString oldText;
    editCtrl.GetWindowText(oldText);
    editCtrl.SetWindowText(oldText + output); // 追加内容
}