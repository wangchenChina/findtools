#pragma once

#include <afxtempl.h> // CStringArray ֧��

// ��������
void CheckRegistryPathsExist(
    HKEY hRootKey,
    const CStringArray& subKeys,
    CEdit& editCtrl);
