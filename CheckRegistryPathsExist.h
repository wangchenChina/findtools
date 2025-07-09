#pragma once

#include <afxtempl.h> // CStringArray 支持

// 函数声明
void CheckRegistryPathsExist(
    HKEY hRootKey,
    const CStringArray& subKeys,
    CEdit& editCtrl);
