#include "pch.h"
#include "CheckRegistryPathsExist.h"
#include <windows.h>
#include <afxwin.h> // CEdit 支持


LPCTSTR GetRootKeyName(HKEY hRootKey)
{
    if (hRootKey == HKEY_CLASSES_ROOT)     return _T("HKEY_CLASSES_ROOT");
    if (hRootKey == HKEY_CURRENT_USER)     return _T("HKEY_CURRENT_USER");
    if (hRootKey == HKEY_LOCAL_MACHINE)    return _T("HKEY_LOCAL_MACHINE");
    if (hRootKey == HKEY_USERS)            return _T("HKEY_USERS");
    if (hRootKey == HKEY_CURRENT_CONFIG)   return _T("HKEY_CURRENT_CONFIG");

    return _T("未知根键");
}


void CheckRegistryPathsExist(
    HKEY hRootKey,
    const CStringArray& subKeys,
    CEdit& editCtrl)
{
    CString output;

    for (int i = 0; i < subKeys.GetSize(); ++i)
    {
        HKEY hKey;
        LONG lResult = RegOpenKeyEx(hRootKey, subKeys[i], 0, KEY_READ, &hKey);

        if (lResult == ERROR_SUCCESS)
        {
            output.AppendFormat(_T("发现可疑注册表路径 %s\\%s\r\n"), GetRootKeyName(hRootKey), (LPCTSTR)subKeys[i]);
            RegCloseKey(hKey);
        }
    }

    CString oldText;
    editCtrl.GetWindowText(oldText);
    editCtrl.SetWindowText(oldText + output); // 追加内容
}