#include "stdafx.h"
#include "printfex.h"

// OutputDebugStringをprintfと同じ使い勝手にする
void printf_ex(LPCTSTR pszFormat, ...)
{
    va_list	argp;
    TCHAR pszBuf[256];
    va_start(argp, pszFormat);
    // 第2引数に注意 変な名前ですが、vsprintfです。
    _vstprintf(pszBuf, sizeof(pszBuf), pszFormat, argp);
    va_end(argp);
    OutputDebugString(pszBuf);
}
