#pragma once

#ifdef LINUX_VER
#include <stdarg.h>
#include <stdlib.h>
#endif

#ifdef HANDLE_SQL_TYPES
#include <sql.h>
#include <sqlext.h>
#endif

#include <stdio.h>
#ifdef WINDOWS_VER
#ifndef _EXCLUDE_BSTR_
#include <WTypes.h>
//#include <Windows.h>
#endif //_EXCLUDE_BSTR_
#endif // WINDOWS_VER
#define CS_LENGTH_CALCULATED				0
#define CS_INVALID_SPECIFIER				1

#define DTL_NONE							0
#define DTL_hh								1
#define DTL_h								2
#define DTL_l								3
#define DTL_ll								4
#define DTL_j								5
#define DTL_z								6
#define DTL_t								7
#define DTL_L								8

class CCHARStringA;
class CCHARStringW;

#ifdef CHARSTRING_UNICODE
typedef wchar_t AACHARTYPE;
#define AATEXT(t) (L##t)
#define AACHAR(c) (L##c)
#define STRLEN wcslen
#define ISDIGIT iswdigit
#else
typedef char AACHARTYPE;
#define AATEXT(t) t
#define AACHAR(c) c
#define STRLEN strlen
#define ISDIGIT isdigit
#endif

#ifdef CHARSTRING_UNICODE
typedef CCHARStringW CCHARString;
#else
typedef CCHARStringA CCHARString;
#endif

CCHARStringA operator + (char pChar, CCHARStringA & strString);
CCHARStringA operator + (const char* pChar, CCHARStringA & strString);

///////////////////////////////////////////////////////////////////////////////////////////
// class CCHARStringA

class CCHARStringA
{
protected:
    char* m_pData;
    size_t m_nLength;

public:
    CCHARStringA(void);
    CCHARStringA(const CCHARStringA & objString);
    CCHARStringA(const char* pString);
    CCHARStringA(const char* pString, int nCount);
//#ifndef _EXCLUDE_BSTR_
//    CCHARStringA(BSTR bstr);
//#endif
    ~CCHARStringA(void);
    CCHARStringA & operator = (const CCHARStringA & objString);
    CCHARStringA & operator = (const char* pString);
//#ifndef _EXCLUDE_BSTR_
//    CCHARStringA & operator = (BSTR bstr);
//#endif
    CCHARStringA operator + (CCHARStringA & objString);
    CCHARStringA operator + (const char* pString);
    void operator += (CCHARStringA & objString);
    void operator += (const char* pString);
    void operator += (char ch);
//#ifndef _EXCLUDE_BSTR_
//    void operator += (BSTR bstrString);
//#endif
    bool operator == (const CCHARStringA & objString);
    bool operator == (const CCHARStringA & objString) const;
    bool operator == (const char* pString);
    bool operator == (const char* pString) const;
    bool operator != (CCHARStringA & objString);
    bool operator != (CCHARStringA & objString) const;
    bool operator != (const char* pString);
    bool operator != (const char* pString) const;
    bool operator < (const CCHARStringA & objString);
    bool operator < (const CCHARStringA & objString) const;
    bool operator > (const CCHARStringA & objString);
    bool operator > (const CCHARStringA & objString) const;
//#ifndef _EXCLUDE_BSTR_
//    BSTR AllocSysString();
//#endif
    operator const char* () const;
    operator const char* ();
    char operator [] (int nIndex);
    void SetValue(const char* pText, int nLength);
    int GetLength() const;
    char* GetCHAR() const;
    CCHARStringA Left(int nCount);
    CCHARStringA Mid(int nPos, int nCount = -1);
    CCHARStringA Right(int nCount);
    int ReverseFind(char ch);
    int Find(char ch, int nStartIndex = 0);
    int Find(const char* str, int nStartIndex = 0);
    void Trim(const char* pCharSet = " \t");
    void TrimLeft(const char* pCharSet = " \t");
    void TrimRight(const char* pCharSet = " \t");
    CCHARStringA SpanExcluding(const char* pCharSet);
    CCHARStringA SpanIncluding(const char* pCharSet);
    void Format(const char* pFormat, ...);
    int CompareNoCase(const char* pChar);
    int CompareNoCase(const char* pChar) const;
    int Compare(const char* pChar);
    int Compare(const char* pChar) const;
    void Add(const char* pString, int nCount);
    void SetAt(int nIndex, char ch);
    void Empty();
    void Replace(const char* pOld, const char* pNew);
    void Insert(int nIndex, char ch);
    void Insert(int nIndex, const char* pText);
    long ToLong();
    int FindOneOf(const char* str) const;
    static CCHARStringA UpperCase(const CCHARStringA & strString);
    static CCHARStringA UpperCase(const char* strString);
    static CCHARStringA LowerCase(const CCHARStringA & strString);
    static CCHARStringA LowerCase(const char* strString);
#ifndef _EXCLUDE_BSTR_
    CCHARString UnicodeToANSI(const wchar_t* strString);
#endif //_EXCLUDE_BSTR_

    friend CCHARStringA operator + (char pChar, CCHARStringA &strString);
    friend CCHARStringA operator + (const char* pChar, CCHARStringA &strString);
};

CCHARStringW operator + (wchar_t pChar, const CCHARStringW & strString);
CCHARStringW operator + (const wchar_t* pChar, const CCHARStringW & strString);

///////////////////////////////////////////////////////////////////////////////////////////
// class CCHARStringW

class CCHARStringW
{
protected:
    wchar_t* m_pData;
    int m_nLength;

protected:
    int CalculateStringLength(const wchar_t* pFormat, va_list argList, size_t* pLength);

public:
    CCHARStringW(void);
    CCHARStringW(const CCHARStringW & objString);
    CCHARStringW(const wchar_t* pString);
    CCHARStringW(const wchar_t* pString, int nCount);
    ~CCHARStringW(void);
    CCHARStringW & operator = (const CCHARStringW & objString);
    CCHARStringW & operator = (const wchar_t* pString);
    CCHARStringW & operator = (const char* pString);
    CCHARStringW operator + (const CCHARStringW & objString);
    CCHARStringW operator + (const wchar_t* pString);
    void operator += (CCHARStringW & objString);
    void operator += (const wchar_t* pString);
    void operator += (wchar_t ch);
    bool operator == (const CCHARStringW & objString);
    bool operator == (const CCHARStringW & objString) const;
    bool operator == (const wchar_t* pString);
    bool operator == (const wchar_t* pString) const;
    bool operator != (CCHARStringW & objString);
    bool operator != (CCHARStringW & objString) const;
    bool operator != (const wchar_t* pString);
    bool operator != (const wchar_t* pString) const;
    bool operator < (const CCHARStringW & objString);
    bool operator < (const CCHARStringW & objString) const;
    bool operator > (const CCHARStringW & objString);
    bool operator > (const CCHARStringW & objString) const;
    operator const wchar_t* () const;
    operator const wchar_t* ();
    wchar_t operator [] (int nIndex);
    void SetValue(const wchar_t* pText, int nLength);
    int GetLength() const;
    wchar_t* GetCHAR() const;
    CCHARStringW Left(int nCount);
    CCHARStringW Mid(int nPos, int nCount = -1);
    CCHARStringW Right(int nCount);
    int ReverseFind(wchar_t ch);
    int Find(wchar_t ch, int nStartIndex = 0);
    int Find(const wchar_t* str, int nStartIndex = 0);
    void Trim(const wchar_t* pCharSet = L" \t");
    void TrimLeft(const wchar_t* pCharSet = L" \t");
    void TrimRight(const wchar_t* pCharSet = L" \t");
    CCHARStringW SpanExcluding(const wchar_t* pCharSet);
    CCHARStringW SpanIncluding(const wchar_t* pCharSet);
    void Format(const wchar_t* pFormat, ...);
    int CompareNoCase(const wchar_t* pChar);
    int CompareNoCase(const wchar_t* pChar) const;
    int Compare(const wchar_t* pChar);
    int Compare(const wchar_t* pChar) const;
    void Add(const wchar_t* pString, int nCount);
    void SetAt(int nIndex, wchar_t ch);
    void Empty();
    void Replace(const wchar_t* pOld, const wchar_t* pNew);
    void Insert(int nIndex, wchar_t ch);
    void Insert(int nIndex, const wchar_t* pText);
    long ToLong();
    int FindOneOf(const wchar_t* str) const;
    static CCHARStringW UpperCase(const CCHARStringW & strString);
    static CCHARStringW UpperCase(const wchar_t* strString);
    static CCHARStringW LowerCase(const CCHARStringW & strString);
    static CCHARStringW LowerCase(const wchar_t* strString);
    static unsigned short* GetUSHORT(const CCHARStringW & strString, int* pLength);
    static unsigned short* GetUSHORT(const wchar_t* strString, int* pLength);
    static wchar_t* GetWCHAR(const unsigned short* strString, int nLength);
    static char* GetCHARA(const CCHARStringW & strString);
    static char* GetCHARA(const wchar_t* strString);
#ifdef HANDLE_SQL_TYPES
    static wchar_t* GetWCHAR(SQLWCHAR* strString, int nLength);
#endif

    friend CCHARStringW operator + (wchar_t pChar, const CCHARStringW & strString);
    friend CCHARStringW operator + (const wchar_t* pChar, const CCHARStringW & strString);
};
