#include "stdafx.h"
#include "printfex.h"

// OutputDebugString��printf�Ɠ����g������ɂ���
void printf_ex(LPCTSTR pszFormat, ...)
{
    va_list	argp;
    TCHAR pszBuf[256];
    va_start(argp, pszFormat);
    // ��2�����ɒ��� �ςȖ��O�ł����Avsprintf�ł��B
    _vstprintf(pszBuf, sizeof(pszBuf), pszFormat, argp);
    va_end(argp);
    OutputDebugString(pszBuf);
}
