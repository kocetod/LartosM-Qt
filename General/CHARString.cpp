//#include "stdafx.h"
#include "General/CHARString.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <wchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <clocale>
#include <cwctype>
#ifdef LINUX_VER
#include <unicode/ustdio.h>
#endif


using namespace std;

#define LETTER_COUNT	30

//char g_arrLower[] = {'à','á','â','ã','ä','å','æ','ç','è','é','ê','ë','ì','í','î','ï','ð','ñ','ò','ó','ô','õ','ö','÷','ø','ù','ü','ú','þ','ÿ'};
//char g_arrUpper[] = {'À','Á','Â','Ã','Ä','Å','Æ','Ç','È','É','Ê','Ë','Ì','Í','Î','Ï','Ð','Ñ','Ò','Ó','Ô','Õ','Ö','×','Ø','Ù','Ü','Ú','Þ','ß'};

///////////////////////////////////////////////////////////////////////////////////////////
// friend global functions
CCHARStringA operator + (const char* pChar, CCHARStringA & strString)
{
    CCHARStringA strResult = strString;
    if(pChar != 0)
    {
        int i;
        int nLength = strlen(pChar);
        int nOldLength = strResult.GetLength();
        int nNewLength = nLength + nOldLength;
        strResult.m_pData = (char*)realloc(strResult.m_pData, nNewLength + 1);
        for(i = nOldLength - 1; i >= 0; i--)
            strResult.m_pData[nNewLength - (nOldLength - i)] = strResult.m_pData[i];
        for(i = 0; i < nLength; i++)
            strResult.m_pData[i] = pChar[i];
        strResult.m_pData[nNewLength] = '\0';
        strResult.m_nLength = nNewLength;
    }
    return strResult;
}

CCHARStringA operator + (char pChar, CCHARStringA & strString)
{
    CCHARStringA strResult = strString;
    if (pChar != 0)
    {
        int i;
        int nLength = 1;
        int nOldLength = strResult.GetLength();
        int nNewLength = nLength + nOldLength;
        strResult.m_pData = (char*)realloc(strResult.m_pData, nNewLength + 1);
        for (i = nOldLength - 1; i >= 0; i--)
            strResult.m_pData[nNewLength - (nOldLength - i)] = strResult.m_pData[i];
        strResult.m_pData[0] = pChar;
        strResult.m_pData[nNewLength] = '\0';
        strResult.m_nLength = nNewLength;
    }
    return strResult;
}

CCHARStringA::CCHARStringA(void)
{
    m_pData = 0;
    m_nLength = 0;
}

CCHARStringA::CCHARStringA(const CCHARStringA & objString)
{
    m_nLength = 0;
    m_pData = 0;
    char* pString = objString.GetCHAR();
    if(pString != 0)
    {
        //int nLen = strlen(pString);
        m_nLength = objString.GetLength();
        m_pData = (char*)malloc((m_nLength + 1) * sizeof(char));
        if(m_pData != NULL)
        {
            //strcpy(m_pData, pString);
            memcpy(m_pData, pString, m_nLength);
            m_pData[m_nLength] = '\0';
        }
    }
}

CCHARStringA::CCHARStringA(const char* pString)
{
    if(pString != 0)
    {
        m_nLength = strlen(pString);
        m_pData = (char*)malloc((m_nLength + 1) * sizeof(char));
        if(m_pData != NULL)
        {
            //strcpy(m_pData, pString);
            memcpy(m_pData, pString, m_nLength);
            m_pData[m_nLength] = '\0';
        }
    }
    else
    {
        m_pData = 0;
        m_nLength = 0;
    }
}

CCHARStringA::CCHARStringA(const char* pString, int nCount)
{
    if(pString != 0)
    {
        m_nLength = strlen(pString);
        if(nCount > m_nLength)
            nCount = m_nLength;
        m_pData = (char*)malloc((nCount + 1) * sizeof(char));
        memcpy(m_pData, pString, nCount * sizeof(char));
        m_pData[nCount] = '\0';
        //Marian add
        m_nLength = strlen(m_pData);
    }
    else
    {
        m_pData = 0;
        m_nLength = 0;
    }
}
/*
#ifndef _EXCLUDE_BSTR_
CCHARStringA::CCHARStringA(BSTR bstr)
{
    m_nLength = WideCharToMultiByte(1251, NULL, bstr, -1, NULL, 0, NULL, NULL) - 1;
    m_pData = (char*)malloc(m_nLength + 1);
    WideCharToMultiByte(1251, NULL, bstr, -1, m_pData, m_nLength, NULL, NULL);
    m_pData[m_nLength] = '\0';

    //m_nLength = wcslen((wchar_t*)bstr);
    //m_pData = (char*)malloc(m_nLength + 1);
    //wcstombs(m_pData, bstr, m_nLength);
    //m_pData[m_nLength] = '\0';
}
#endif*/

CCHARStringA::~CCHARStringA(void)
{
    if(m_pData != NULL)
        free(m_pData);
}

CCHARStringA & CCHARStringA::operator = (const CCHARStringA & objString)
{
    if(m_pData != 0)
        free(m_pData);
    m_pData = 0;
    m_nLength = 0;

    char* pString = objString.GetCHAR();
    if(pString != 0)
    {
        m_nLength = objString.GetLength();
        m_pData = (char*)malloc((m_nLength + 1) * sizeof(char));
        if(m_pData != 0)
        {
            if (m_nLength > 0)
                memcpy(m_pData, pString, m_nLength);
            m_pData[m_nLength] = '\0';
        }
        else m_nLength = 0;
    }
    return (CCHARStringA&)(*this);
}

CCHARStringA & CCHARStringA::operator = (const char* pString)
{
    if(m_pData != 0)
        free(m_pData);
    m_pData = 0;
    m_nLength = 0;

    if(pString != 0)
    {
        m_nLength = strlen(pString);
        m_pData = (char*)malloc((m_nLength + 1) * sizeof(char));
        if(m_pData != NULL)
        {
            if(m_nLength > 0)
                memcpy(m_pData, pString, m_nLength);
            m_pData[m_nLength] = '\0';
        }
    }
    return (CCHARStringA&)(*this);
}
/*
#ifndef _EXCLUDE_BSTR_
CCHARStringA & CCHARStringA::operator = (BSTR bstr)
{
    if(m_pData != 0)
    {
        free(m_pData);
        m_nLength = 0;
    }

    //m_nLength = wcslen((wchar_t*)bstr);
    m_nLength = WideCharToMultiByte(1251, NULL, bstr, -1, NULL, 0, NULL, NULL) - 1;
    m_pData = (char*)malloc(m_nLength + 1);
    //wcstombs(m_pData, bstr, m_nLength);
    WideCharToMultiByte(1251, NULL, bstr, -1, m_pData, m_nLength, NULL, NULL);
    m_pData[m_nLength] = '\0';
    return (CCHARStringA&)(*this);
}
#endif*/

CCHARStringA CCHARStringA::operator + (CCHARStringA & objString)
{
    CCHARStringA string;
    char *pString = objString.GetCHAR();
    if(m_pData != NULL || pString != NULL)
    {
        int nLen1 = strlen(m_pData);
        int nLen2 = strlen(pString);
        char *pData = (char*)malloc((nLen1 + nLen2 + 1) * sizeof(char));
        if(m_pData != NULL)
            strcpy(pData, m_pData);
        if(pString != NULL)
            strcpy(pData + nLen1, pString);
        pData[nLen1 + nLen2] = '\0';
        string.SetValue(pData, nLen1 + nLen2);
        free(pData);
    }
    return string;
}

CCHARStringA CCHARStringA::operator + (const char* pString)
{
    CCHARStringA string;
    if(m_pData != NULL || pString != NULL)
    {
        int nLen1 = strlen(m_pData);
        int nLen2 = strlen(pString);
        char *pData = (char*)malloc((nLen1 + nLen2 + 1) * sizeof(char));
        if(m_pData != NULL)
            strcpy(pData, m_pData);
        if(pString != NULL)
            strcpy(pData + nLen1, pString);
        pData[nLen1 + nLen2] = '\0';
        string.SetValue(pData, nLen1 + nLen2);
        free(pData);
    }
    return string;
}

void CCHARStringA::operator += (CCHARStringA & objString)
{
    char *pString = objString.GetCHAR();
    if(pString == NULL) return;
    int nLen = m_nLength;
    m_pData = (char*)realloc(m_pData, (nLen + strlen(pString) + 1) * sizeof(char));
    memcpy(m_pData + nLen, pString, objString.GetLength());
    m_pData[nLen + objString.GetLength()] = '\0';
    m_nLength += objString.GetLength();
}

void CCHARStringA::operator += (const char* pString)
{
    if(pString == 0) return;

    m_pData = (char*)realloc(m_pData, (m_nLength + strlen(pString) + 1) * sizeof(char));

    strcpy(m_pData + m_nLength, pString);
    m_pData[m_nLength + strlen(pString)] = '\0';
    m_nLength += strlen(pString);
}

void CCHARStringA::operator += (char ch)
{
    m_pData = (char*)realloc(m_pData, (m_nLength + 2) * sizeof(char));
    m_pData[m_nLength] = ch;
    m_pData[m_nLength + 1] = '\0';
    m_nLength++;
}

/*#ifndef _EXCLUDE_BSTR_
void CCHARStringA::operator += (BSTR bstrString)
{
    int nLen = WideCharToMultiByte(1251, NULL, bstrString, -1, NULL, 0, NULL, NULL) - 1;
    char *pString = (char*)malloc(nLen + 1);
    WideCharToMultiByte(1251, NULL, bstrString, -1, pString, nLen, NULL, NULL);
    pString[nLen] = '\0';

    //int nLen = wcslen(bstrString);
    //char *pString = (char*)malloc(nLen + 1);
    //wcstombs(pString, bstrString, nLen);
    //pString[nLen] = '\0';
    (*this) += pString;
    free(pString);
}
#endif*/

bool CCHARStringA::operator == (const CCHARStringA & objString)
{
    char* pString = objString.GetCHAR();
    if(m_pData == 0)
    {
        if(pString != 0 && !strcmp(pString, ""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !strcmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringA::operator == (const CCHARStringA & objString) const
{
    char* pString = objString.GetCHAR();
    if(m_pData == 0)
    {
        if(pString != 0 && !strcmp(pString, ""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !strcmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringA::operator == (const char* pString)
{
    if(m_pData == 0)
    {
        if(pString != 0 && !strcmp(pString, ""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !strcmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringA::operator == (const char* pString) const
{
    if (m_pData == 0)
    {
        if (pString != 0 && !strcmp(pString, ""))
            return true;
        else if (pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !strcmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringA::operator != (CCHARStringA & objString)
{
    char *pString = objString.GetCHAR();
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !strcmp(pString, ""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !strcmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringA::operator != (CCHARStringA & objString) const
{
    char *pString = objString.GetCHAR();
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !strcmp(pString, ""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !strcmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringA::operator != (const char* pString)
{
    if(m_pData == 0)
    {
        if(pString == 0)
            return false;
        else if(pString != 0 && !strcmp(pString, ""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !strcmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringA::operator != (const char* pString) const
{
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !strcmp(pString, ""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !strcmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringA::operator < (const CCHARStringA & objString)
{
    return (strcmp(m_pData, objString) < 0);
}

bool CCHARStringA::operator < (const CCHARStringA & objString) const
{
    return (strcmp(m_pData, objString) < 0);
}

bool CCHARStringA::operator > (const CCHARStringA & objString)
{
    return (strcmp(m_pData, objString) > 0);
}

bool CCHARStringA::operator > (const CCHARStringA & objString) const
{
    return (strcmp(m_pData, objString) > 0);
}

CCHARStringA::operator const char* () const
{
    return (const char*)m_pData;
}

CCHARStringA::operator const char* ()
{
    return (const char*)m_pData;
}

char CCHARStringA::operator [] (int nIndex)
{
    if(m_pData == NULL) return 0;
    int nLength = strlen(m_pData);
    if(nIndex < 0 || nIndex > nLength - 1) return 0;
    return m_pData[nIndex];
}

void CCHARStringA::SetValue(const char* pText, int nLength)
{
    if(m_pData != 0)
    {
        free(m_pData);
        m_pData = 0;
        m_nLength = 0;
    }
    m_pData = (char*)malloc((nLength + 1) * sizeof(char));
    if(m_pData != 0)
    {
        memcpy(m_pData, pText, nLength);
        m_nLength = nLength;
        m_pData[m_nLength] = '\0';
    }
}

int CCHARStringA::GetLength() const
{
    return m_nLength;
}

char* CCHARStringA::GetCHAR() const
{
    return m_pData;
}

CCHARStringA CCHARStringA::Left(int nCount)
{
    CCHARStringA string(m_pData, nCount);
    return string;
}

CCHARStringA CCHARStringA::Mid(int nPos, int nCount)
{
    if(nCount == -1)
    {
        nCount = m_nLength - nPos;
    }
    CCHARStringA string(m_pData + nPos, nCount);
    return string;
}

CCHARStringA CCHARStringA::Right(int nCount)
{
    int nPos = m_nLength - nCount;
    CCHARStringA string(m_pData + nPos, nCount);
    return string;
}

int CCHARStringA::ReverseFind(char ch)
{
    if(m_pData == NULL) return -1;
    for(int i = m_nLength - 1; i >= 0; --i)
    {
        if(m_pData[i] == ch)
            return i;
    }
    return -1;
}

int CCHARStringA::Find(char ch, int nStartIndex)
{
    if(m_pData == NULL) return -1;
    for(int i = nStartIndex; i < m_nLength; ++i)
    {
        if(m_pData[i] == ch)
            return i;
    }
    return -1;
}

int CCHARStringA::Find(const char* str, int nStartIndex)
{
    if(nStartIndex > m_nLength - 1)
        return -1;
    char* pFound = strstr(m_pData + nStartIndex, str);
    if(pFound)
        return (pFound - m_pData);
    return -1;
}

void CCHARStringA::Trim(const char* pCharSet)
{
    TrimLeft(pCharSet);
    TrimRight(pCharSet);
}

void CCHARStringA::TrimLeft(const char* pCharSet)
{
    if(m_pData == NULL) return;
    int nLength = m_nLength, j;
    int nCharSetLength = strlen(pCharSet);
    for(int i = 0; i < nLength; i++)
    {
        bool bFound = false;
        for(j = 0; j < nCharSetLength; j++)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(!bFound)
        {
            if(i > 0)
            {
                for(j = i; j < nLength; j++)
                    m_pData[j - i] = m_pData[j];
                m_pData = (char*)realloc(m_pData, nLength - i + 1);
                m_pData[nLength - i] = '\0';
            }
            break;
        }
    }
    if(m_pData != 0)
        m_nLength = strlen(m_pData);
    else
        m_nLength = 0;
}

void CCHARStringA::TrimRight(const char* pCharSet)
{
    if(m_pData == NULL) return;
    int nLength = m_nLength;
    int nCharSetLength = strlen(pCharSet);
    int i, j;
    bool bFound = false;
    for(i = nLength - 1; i >= 0; --i)
    {
        bFound = false;
        for(j = 0; j < nCharSetLength; ++j)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(!bFound)
        {
            if(i < nLength - 1)
            {
                m_pData = (char*)realloc(m_pData, i + 2);
                m_pData[i + 1] = '\0';
            }
            break;
        }
    }
    if(i < 0)
    {
        if (m_pData != 0)
        {
            free(m_pData);
            m_pData = 0;
        }
        //m_pData = (char*)realloc(m_pData, i + 2);
        //m_pData[i + 1] = '\0';
    }
    if(m_pData != 0)
        m_nLength = strlen(m_pData);
    else
        m_nLength = 0;
}

CCHARStringA CCHARStringA::SpanExcluding(const char* pCharSet)
{
    CCHARStringA strRet;
    size_t nLength = m_nLength;
    if(nLength <= 0) return strRet;
    size_t nCharSetLength = strlen(pCharSet);
    for(size_t i = 0; i < nLength; i++)
    {
        bool bFound = false;
        for(size_t j = 0; j < nCharSetLength; j++)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound= true;
                break;
            }
        }
        if(bFound)
        {
            strRet = this->Left(i);
            break;
        }
        else if(i == nLength - 1)
        {
            strRet = this->Left(i + 1);
            break;
        }
    }
    return strRet;
}

CCHARStringA CCHARStringA::SpanIncluding(const char* pCharSet)
{
    CCHARStringA strRet;
    strRet = "";
    size_t nLength = m_nLength;
    if(nLength <= 0) return strRet;
    int nFirstPos = -1, nLastPos = -1;
    size_t nCharSetLength = strlen(pCharSet);
    for(long i = 0; i < nLength; i++)
    {
        bool bFound = false;
        for(long j = 0; j < nCharSetLength; j++)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(bFound)
        {
            if(nFirstPos == -1) nFirstPos = i;
            else nLastPos = i;
        }
    }
    if(nFirstPos > -1)
    {
        if(nLastPos > 0)
        {
            strRet = this->Mid(nFirstPos, nLastPos - nFirstPos + 1);
        }
        else
        {
            strRet = this->Mid(nFirstPos);
        }
    }
    else
    {
        strRet = "";
    }

    return strRet;
}

void CCHARStringA::Format(const char* pFormat, ...)
{
    if(pFormat == 0) return;

    va_list argList;
    va_start(argList, pFormat);
#ifdef WINDOWS_VER
    m_nLength = _vscprintf(pFormat, argList);
#endif
#ifdef LINUX_VER
    m_nLength = vsnprintf(0, 0, pFormat, argList);
    va_end(argList);
    va_start(argList, pFormat);
#endif
    if (m_pData != 0) free(m_pData);
    m_pData = (char*)malloc(m_nLength + 1);
    m_nLength = vsprintf(m_pData, pFormat, argList);
    va_end(argList);
}

//#ifndef _EXCLUDE_BSTR_
//CCHARString & CCHARString::operator = (BSTR bstr)
//{
//	if(m_pData != 0)
//	{
//		free(m_pData);
//		m_nLength = 0;
//	}
//
//	m_nLength = wcslen((wchar_t*)bstr);
//	m_pData = (char*)malloc(m_nLength + 1);
//	wcstombs(m_pData, bstr, m_nLength);
//	m_pData[m_nLength] = '\0';
//	return (CCHARString&)(*this);
//}
//#endif

void CCHARStringA::SetAt(int nIndex, char ch)
{
    m_pData[nIndex] = ch;
}

/*#ifndef _EXCLUDE_BSTR_
BSTR CCHARStringA::AllocSysString()
{
    if(m_pData == NULL) return NULL;
    size_t nLen = m_nLength;
    wchar_t* pWC = (wchar_t*)malloc(nLen * sizeof(wchar_t));
    mbstowcs(pWC, m_pData, nLen);
    BSTR bstr = ::SysAllocStringLen(pWC, nLen);
    free(pWC);
    return bstr;
}
#endif*/

int CCHARStringA::CompareNoCase(const char* pChar)
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
#ifdef LINUX_VER
    return strcasecmp(m_pData, pChar);
#else // WINDOWS_VER
    //return _stricmp(m_pData, pChar);
#endif
}

int CCHARStringA::CompareNoCase(const char* pChar) const
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
#ifdef LINUX_VER
    return strcasecmp(m_pData, pChar);
#else // WINDOWS_VER
    //return _stricmp(m_pData, pChar);
#endif
}

int CCHARStringA::Compare(const char* pChar)
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
    return strcmp(m_pData, pChar);
}

int CCHARStringA::Compare(const char* pChar) const
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
    return strcmp(m_pData, pChar);
}

void CCHARStringA::Add(const char* pString, int nCount)
{
    if(pString == NULL) return;

    m_pData = (char*)realloc(m_pData, (m_nLength + nCount + 1) * sizeof(char));

    memcpy(m_pData + m_nLength, pString, nCount);
    m_pData[m_nLength + nCount] = '\0';
    m_nLength += nCount;
}

void CCHARStringA::Empty()
{
    if(m_pData != 0)
    {
        free(m_pData);
        m_pData = 0;
        m_nLength = 0;
    }
}

void CCHARStringA::Replace(const char* pOld, const char* pNew)
{
    if (!strcmp(pOld, pNew)) return;
    CCHARStringA strTemp;
    int nPos = Find(pOld);
    while(nPos != -1)
    {
        strTemp = this->Left(nPos) + pNew;
        strTemp += this->Mid(nPos + strlen(pOld));
        (*this) = strTemp;
        nPos = Find(pOld);
    }
}

void CCHARStringA::Insert(int nIndex, char ch)
{
    if(nIndex >= 0 && nIndex < m_nLength)
    {
        if(m_nLength > 0)
        {
            if(nIndex == 0)
            {
                CCHARStringA strTemp;
                strTemp += ch;
                strTemp += (*this);
                (*this) = strTemp;
            }
            else
            {
                CCHARStringA strTemp;
                strTemp = this->Left(nIndex);
                strTemp += ch;
                strTemp += this->Mid(nIndex);
                (*this) = strTemp;
            }
        }
        else
        {
            (*this) += ch;
        }
    }
}

void CCHARStringA::Insert(int nIndex, const char* pText)
{
    if(nIndex >= 0 && nIndex < m_nLength && pText != 0)
    {
        if(m_nLength > 0)
        {
            if(nIndex == 0)
            {
                CCHARStringA strTemp;
                strTemp += pText;
                strTemp += (*this);
                (*this) = strTemp;
            }
            else
            {
                CCHARStringA strTemp;
                strTemp = this->Left(nIndex);
                strTemp += pText;
                strTemp += this->Mid(nIndex);
                (*this) = strTemp;
            }
        }
        else
        {
            (*this) += pText;
        }
    }
}

CCHARStringA CCHARStringA::UpperCase(const CCHARStringA & strString)
{
    setlocale(LC_ALL, "");
    CCHARStringA strNew;
    int i, nLen = strString.GetLength();
    for (i = 0; i < nLen; i++)
        strNew += toupper(strString[i]);
    return strNew;

    /*CCHARStringA strNew;
    bool bFound;
    int i, j;
    int nLen = strString.GetLength();
    for(i = 0; i < nLen; i++)
    {
        bFound = false;
        for(j = 0; j < LETTER_COUNT; j++)
        {
            if(strString[i] == g_arrLower[j])
            {
                strNew += g_arrUpper[j];
                bFound = true;
                break;
            }
        }
        if(!bFound)
            strNew += strString[i];
    }
    return strNew;*/
}

CCHARStringA CCHARStringA::UpperCase(const char* strString)
{
    setlocale(LC_ALL, "");
    CCHARStringA strNew;
    int i, nLen = strlen(strString);
    for (i = 0; i < nLen; i++)
        strNew += toupper(strString[i]);
    return strNew;

    /*CCHARStringA strNew;
    bool bFound;
    int i, j;
    int nLen = strlen(strString);
    for (i = 0; i < nLen; i++)
    {
        bFound = false;
        for (j = 0; j < LETTER_COUNT; j++)
        {
            if (strString[i] == g_arrLower[j])
            {
                strNew += g_arrUpper[j];
                bFound = true;
                break;
            }
        }
        if (!bFound)
            strNew += strString[i];
    }
    return strNew;*/
}

CCHARStringA CCHARStringA::LowerCase(const CCHARStringA & strString)
{
    setlocale(LC_ALL, "");
    CCHARStringA strNew;
    int i, nLen = strString.GetLength();
    for (i = 0; i < nLen; i++)
        strNew += tolower(strString[i]);
    return strNew;

    /*CCHARStringA strNew;
    bool bFound;
    int i, j;
    int nLen = strString.GetLength();
    for(i = 0; i < nLen; i++)
    {
        bFound = false;
        for(j = 0; j < LETTER_COUNT; j++)
        {
            if(strString[i] == g_arrUpper[j])
            {
                strNew += g_arrLower[j];
                bFound = true;
                break;
            }
        }
        if(!bFound)
            strNew += (char)tolower(strString[i]);
    }
    return strNew;*/
}

CCHARStringA CCHARStringA::LowerCase(const char* strString)
{
    setlocale(LC_ALL, "");
    CCHARStringA strNew;
    int i, nLen = strlen(strString);
    for (i = 0; i < nLen; i++)
        strNew += tolower(strString[i]);
    return strNew;

    /*CCHARStringA strNew;
    bool bFound;
    int i, j;
    int nLen = strlen(strString);
    for (i = 0; i < nLen; i++)
    {
        bFound = false;
        for (j = 0; j < LETTER_COUNT; j++)
        {
            if (strString[i] == g_arrUpper[j])
            {
                strNew += g_arrLower[j];
                bFound = true;
                break;
            }
        }
        if (!bFound)
            strNew += (char)tolower(strString[i]);
    }
    return strNew;*/
}

long CCHARStringA::ToLong()
{
    if (!m_pData || m_nLength == 0)
        return 0;
    return atol(m_pData);
}

/* Old code
int CCHARStringA::FindOneOf(const char* str) const
{
    char * pFound = strpbrk(m_pData, str);
    if (pFound)
        return (int)(pFound - m_pData);
    return -1;

    //return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);

}
*/
int CCHARStringA::FindOneOf(const char* str) const
{
    char cMask = -1;
    char cPattern = *str;
    int nPos;
    int nSPos;
    int nRet = -1;

    for (nPos = 1; str[nPos]; ++nPos)
    {
        cMask &= ~(str[nPos - 1] ^ str[nPos]);
        cPattern |= str[nPos];
    }
    // cMask now contains '1's in bits that have the same value for every char in pSearch string

    // Check each char in pString
    for (nPos = 0; m_pData[nPos]; ++nPos)
    {
        // Find out which bits have the same values by '~(pString[nPos] ^ cPattern)'
        // Mask the bits of interest and compare with the mask
        if ((~(m_pData[nPos] ^ cPattern) & cMask) == cMask)
        {
            // We have a possible match, now walk through the search string
            for (nSPos = 0; str[nSPos]; ++nSPos)
            {
                if (m_pData[nPos] == str[nSPos])
                {
                    // A match was found, update return value and get out
                    nRet = nPos;
                    break;
                }
            }
            if (nRet != -1)
            {
                break;
            }
        }
    }

    return nRet;
}
/*
#ifndef _EXCLUDE_BSTR_
CCHARString CCHARStringA::UnicodeToANSI(const wchar_t* strString)
{
    CCHARString ansistr;
    //int lenW = SysStringLen(strString);
    int lenW = wcslen(strString);
    int lenA = WideCharToMultiByte(CP_ACP, 0, strString, lenW, 0, 0, NULL, NULL);
    if (lenA > 0)
    {
        //ansistr = new char[lenA + 1]; // allocate a final null terminator as well
        char* pString = (char*)malloc(lenA + 1);
        WideCharToMultiByte(CP_ACP, 0, strString, lenW, pString, lenA, NULL, NULL);
        pString[lenA] = '\0'; // Set the null terminator yourself
        ansistr = pString;
        free(pString);
    }
    else
    {
        // handle the error
    }

    //...use the strings, then free their memory:
    //delete[] ansistr;
    //SysFreeString(unicodestr);

    return ansistr;
}
#endif *///_EXCLUDE_BSTR_

// end of class CCHARStringA implementation
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
// friend global functions
CCHARStringW operator + (wchar_t pChar, const CCHARStringW & strString)
{
    CCHARStringW strResult = strString;
    if (pChar != 0)
    {
        int i;
        int nLength = 1;
        int nOldLength = strResult.GetLength();
        int nNewLength = nLength + nOldLength;
        strResult.m_pData = (wchar_t*)realloc(strResult.m_pData, (nNewLength + 1) * sizeof(wchar_t));
        for (i = nOldLength - 1; i >= 0; i--)
            strResult.m_pData[nNewLength - (nOldLength - i)] = strResult.m_pData[i];
        strResult.m_pData[0] = pChar;
        strResult.m_pData[nNewLength] = 0;
        strResult.m_nLength = nNewLength;
    }
    return strResult;
}

CCHARStringW operator + (const wchar_t* pChar, const CCHARStringW & strString)
{
    CCHARStringW strResult = strString;
    if (pChar != 0)
    {
        int i;
        int nLength = wcslen(pChar);
        int nOldLength = strResult.GetLength();
        int nNewLength = nLength + nOldLength;
        strResult.m_pData = (wchar_t*)realloc(strResult.m_pData, (nNewLength + 1) * sizeof(wchar_t));
        for (i = nOldLength - 1; i >= 0; i--)
            strResult.m_pData[nNewLength - (nOldLength - i)] = strResult.m_pData[i];
        for (i = 0; i < nLength; i++)
            strResult.m_pData[i] = pChar[i];
        strResult.m_pData[nNewLength] = 0;
        strResult.m_nLength = nNewLength;
    }
    return strResult;
}

///////////////////////////////////////////////////////////////////////////////////////////
// class CCHARStringW implementation

CCHARStringW::CCHARStringW(void)
{
    m_pData = 0;
    m_nLength = 0;
}

CCHARStringW::CCHARStringW(const CCHARStringW & objString)
{
    m_nLength = 0;
    m_pData = 0;
    wchar_t* pString = objString.GetCHAR();
    if(pString != 0)
    {
        m_nLength = objString.GetLength();
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        if(m_pData != NULL)
        {
            if(m_nLength > 0)
                memcpy(m_pData, pString, m_nLength * sizeof(wchar_t));
            m_pData[m_nLength] = L'\0';
        }
    }
}

CCHARStringW::CCHARStringW(const wchar_t* pString)
{
    m_pData = 0;
    m_nLength = 0;
    if(pString != 0)
    {
        m_nLength = wcslen(pString);
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        if(m_pData != 0)
        {
            if(m_nLength > 0)
                memcpy(m_pData, pString, m_nLength * sizeof(wchar_t));
            m_pData[m_nLength] = L'\0';
        }
    }
}

CCHARStringW::CCHARStringW(const wchar_t* pString, int nCount)
{
    m_pData = 0;
    m_nLength = 0;
    if(pString != 0)
    {
        m_nLength = wcslen(pString);
        if(nCount > m_nLength)
            nCount = m_nLength;
        m_pData = (wchar_t*)malloc((nCount + 1) * sizeof(wchar_t));
        memcpy(m_pData, pString, nCount * sizeof(wchar_t));
        m_pData[nCount] = L'\0';
        m_nLength = wcslen(m_pData);
    }
}

CCHARStringW::~CCHARStringW(void)
{
    if(m_pData != NULL)
        free(m_pData);
}

CCHARStringW & CCHARStringW::operator = (const CCHARStringW & objString)
{
    if(m_pData != 0)
        free(m_pData);
    m_pData = 0;
    m_nLength = 0;

    wchar_t* pString = objString.GetCHAR();
    if(pString != 0)
    {
        m_nLength = objString.GetLength();
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        if(m_pData != 0)
        {
            if(m_nLength > 0)
                memcpy(m_pData, pString, m_nLength * sizeof(wchar_t));
            m_pData[m_nLength] = L'\0';
        }
        else m_nLength = 0;
    }
    return (CCHARStringW&)(*this);
}

CCHARStringW & CCHARStringW::operator = (const wchar_t* pString)
{
    if (m_pData != 0)
        free(m_pData);
    m_pData = 0;
    m_nLength = 0;

    if (pString != 0)
    {
        m_nLength = wcslen(pString);
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        if(m_pData != 0)
        {
            if(m_nLength > 0)
                memcpy(m_pData, pString, m_nLength * sizeof(wchar_t));
            m_pData[m_nLength] = L'\0';
        }
    }
    return (CCHARStringW&)(*this);
}

CCHARStringW & CCHARStringW::operator = (const char* pString)
{
    if (m_pData != 0)
        free(m_pData);
    m_pData = 0;
    m_nLength = 0;
    if (pString != 0)
    {
        m_nLength = strlen(pString);
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        if (m_pData != 0)
        {
            if(m_nLength > 0)
                mbstowcs(m_pData, pString, m_nLength);
            m_pData[m_nLength] = L'\0';
        }
    }
    return (CCHARStringW&)(*this);
}

CCHARStringW CCHARStringW::operator + (const CCHARStringW & objString)
{
    CCHARStringW string;
    wchar_t* pString = objString.GetCHAR();
    if(m_pData != NULL || pString != NULL)
    {
        int nLen1 = wcslen(m_pData);
        int nLen2 = wcslen(pString);
        wchar_t* pData = (wchar_t*)malloc((nLen1 + nLen2 + 1) * sizeof(wchar_t));
        if(m_pData != NULL)
            wcscpy(pData, m_pData);
        if(pString != NULL)
            wcscpy(pData + nLen1, pString);
        pData[nLen1 + nLen2] = L'\0';
        string.SetValue(pData, nLen1 + nLen2);
        free(pData);
    }
    return string;
}

CCHARStringW CCHARStringW::operator + (const wchar_t* pString)
{
    CCHARStringW string;
    if(m_pData != NULL || pString != NULL)
    {
        int nLen1 = wcslen(m_pData);
        int nLen2 = wcslen(pString);
        wchar_t *pData = (wchar_t*)malloc((nLen1 + nLen2 + 1) * sizeof(wchar_t));
        if(m_pData != NULL)
            wcscpy(pData, m_pData);
        if(pString != NULL)
            wcscpy(pData + nLen1, pString);
        pData[nLen1 + nLen2] = L'\0';
        string.SetValue(pData, nLen1 + nLen2);
        free(pData);
    }
    return string;
}

void CCHARStringW::operator += (CCHARStringW & objString)
{
    wchar_t *pString = objString.GetCHAR();
    if(pString == NULL) return;
    int nLen = m_nLength;

    m_pData = (wchar_t*)realloc(m_pData, (nLen + wcslen(pString) + 1) * sizeof(wchar_t));

    memcpy(m_pData + nLen, pString, objString.GetLength() * sizeof(wchar_t));
    m_pData[nLen + objString.GetLength()] = L'\0';
    m_nLength += objString.GetLength();
}

void CCHARStringW::operator += (const wchar_t* pString)
{
    if(pString == 0) return;

    m_pData = (wchar_t*)realloc(m_pData, (m_nLength + wcslen(pString) + 1) * sizeof(wchar_t));

    //wcscpy(m_pData + m_nLength, pString);
    memcpy(m_pData + m_nLength, pString, wcslen(pString) * sizeof(wchar_t));
    m_pData[m_nLength + wcslen(pString)] = L'\0';
    m_nLength += wcslen(pString);
}

void CCHARStringW::operator += (wchar_t ch)
{
    m_pData = (wchar_t*)realloc(m_pData, (m_nLength + 2) * sizeof(wchar_t));
    m_pData[m_nLength] = ch;
    m_pData[m_nLength + 1] = L'\0';
    m_nLength++;
}

bool CCHARStringW::operator == (const CCHARStringW & objString)
{
    wchar_t* pString = objString.GetCHAR();
    if(m_pData == 0)
    {
        if(pString != 0 && !wcscmp(pString, L""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !wcscmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringW::operator == (const CCHARStringW & objString) const
{
    wchar_t* pString = objString.GetCHAR();
    if(m_pData == 0)
    {
        if(pString != 0 && !wcscmp(pString, L""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !wcscmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringW::operator == (const wchar_t* pString) const
{
    if(m_pData == 0)
    {
        if(pString != 0 && !wcscmp(pString, L""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !wcscmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringW::operator == (const wchar_t* pString)
{
    if(m_pData == 0)
    {
        if(pString != 0 && !wcscmp(pString, L""))
            return true;
        else if(pString == 0)
            return true;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !wcscmp(m_pData, pString))
            return true;
    }
    return false;
}

bool CCHARStringW::operator != (CCHARStringW & objString)
{
    wchar_t* pString = objString.GetCHAR();
    //if(!m_pData && !pString)
    //	return FALSE;
    //else if(!m_pData && pString)
    //	return TRUE;
    //else if(m_pData && !pString)
    //	return TRUE;
    //else
    //{
    //	if(!wcscmp(m_pData, pString))
    //		return FALSE;
    //}
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !wcscmp(pString, L""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !wcscmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringW::operator != (CCHARStringW & objString) const
{
    wchar_t* pString = objString.GetCHAR();
    //if (!m_pData && !pString)
    //	return FALSE;
    //else if (!m_pData && pString)
    //	return TRUE;
    //else if (m_pData && !pString)
    //	return TRUE;
    //else
    //{
    //	if (!wcscmp(m_pData, pString))
    //		return FALSE;
    //}
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !wcscmp(pString, L""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !wcscmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringW::operator != (const wchar_t* pString)
{
    if(m_pData == 0)
    {
        if(pString == 0)
            return false;
        else if(pString != 0 && !wcscmp(pString, L""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if(pString != 0 && !wcscmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringW::operator != (const wchar_t* pString) const
{
    if (m_pData == 0)
    {
        if (pString == 0)
            return false;
        else if (pString != 0 && !wcscmp(pString, L""))
            return false;
    }
    else // if(m_pData != 0)
    {
        if (pString != 0 && !wcscmp(m_pData, pString))
            return false;
    }
    return true;
}

bool CCHARStringW::operator < (const CCHARStringW & objString)
{
    return (wcscmp(m_pData, objString) < 0);
}

bool CCHARStringW::operator < (const CCHARStringW & objString) const
{
    return (wcscmp(m_pData, objString) < 0);
}

bool CCHARStringW::operator > (const CCHARStringW & objString)
{
    return (wcscmp(m_pData, objString) > 0);
}

bool CCHARStringW::operator > (const CCHARStringW & objString) const
{
    return (wcscmp(m_pData, objString) > 0);
}

CCHARStringW::operator const wchar_t* () const
{
    return (const wchar_t*)m_pData;
}

CCHARStringW::operator const wchar_t* ()
{
    return (const wchar_t*)m_pData;
}

wchar_t CCHARStringW::operator [] (int nIndex)
{
    if(m_pData == NULL) return 0;
    int nLength = wcslen(m_pData);
    if(nIndex < 0 || nIndex > nLength - 1) return 0;
    return m_pData[nIndex];
}

void CCHARStringW::SetValue(const wchar_t* pText, int nLength)
{
    if(m_pData != 0)
    {
        free(m_pData);
        m_pData = 0;
        m_nLength = 0;
    }
    m_pData = (wchar_t*)malloc((nLength + 1) * sizeof(wchar_t));
    if(m_pData != 0)
    {
        memcpy(m_pData, pText, nLength * sizeof(wchar_t));
        m_nLength = nLength;
        m_pData[m_nLength] = L'\0';
    }
}

int CCHARStringW::GetLength() const
{
    //if(!m_pData)
    //	return 0;
    //return strlen(m_pData);
    return m_nLength;
}

wchar_t* CCHARStringW::GetCHAR() const
{
    return m_pData;
}

CCHARStringW CCHARStringW::Left(int nCount)
{
    CCHARStringW string(m_pData, nCount);
    return string;
}

CCHARStringW CCHARStringW::Mid(int nPos, int nCount)
{
    if(nCount == -1)
    {
        //int nLen = strlen(m_pData);
        //nCount = nLen - nPos;
        nCount = m_nLength - nPos;
    }
    CCHARStringW string(m_pData + nPos, nCount);
    return string;
}

CCHARStringW CCHARStringW::Right(int nCount)
{
    //int nLen = strlen(m_pData);
    //int nPos = nLen - nCount;
    int nPos = m_nLength - nCount;
    CCHARStringW string(m_pData + nPos, nCount);
    return string;
}

int CCHARStringW::ReverseFind(wchar_t ch)
{
    if(m_pData == NULL) return -1;
    //int nCount = strlen(m_pData);
    //for(int i = nCount - 1; i >= 0; i--)
    for(int i = m_nLength - 1; i >= 0; --i)
    {
        if(m_pData[i] == ch)
            return i;
    }
    return -1;
}

int CCHARStringW::Find(wchar_t ch, int nStartIndex)
{
    if(m_pData == NULL) return -1;
    //int nCount = strlen(m_pData);
    //for(int i = nStartIndex; i < nCount; i++)
    for(int i = nStartIndex; i < m_nLength; ++i)
    {
        if(m_pData[i] == ch)
            return i;
    }
    return -1;
}

int CCHARStringW::Find(const wchar_t* str, int nStartIndex)
{
    if(nStartIndex > m_nLength - 1)
        return -1;
    wchar_t* pFound = wcsstr(m_pData + nStartIndex, str);
    if(pFound)
        return (pFound - m_pData);
    return -1;
}

void CCHARStringW::Trim(const wchar_t* pCharSet)
{
    TrimLeft(pCharSet);
    TrimRight(pCharSet);
}

void CCHARStringW::TrimLeft(const wchar_t* pCharSet)
{
    if(m_pData == NULL) return;
    int nLength = m_nLength, j;
    int nCharSetLength = wcslen(pCharSet);
    for(int i = 0; i < nLength; ++i)
    {
        bool bFound = false;
        for(j = 0; j < nCharSetLength; ++j)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(!bFound)
        {
            if(i > 0)
            {
                for(j = i; j < nLength; ++j)
                    m_pData[j - i] = m_pData[j];
                m_pData = (wchar_t*)realloc(m_pData, (nLength - i + 1) * sizeof(wchar_t));
                m_pData[nLength - i] = 0;
            }
            break;
        }
    }
    if(m_pData != 0)
        m_nLength = wcslen(m_pData);
    else
        m_nLength = 0;
}

void CCHARStringW::TrimRight(const wchar_t* pCharSet)
{
    if(m_pData == NULL) return;
    int nLength = m_nLength;
    int nCharSetLength = wcslen(pCharSet);
    int i;
    for(i = nLength - 1; i >= 0; --i)
    {
        bool bFound = false;
        for(int j = 0; j < nCharSetLength; ++j)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(!bFound)
        {
            if(i < nLength - 1)
            {
                m_pData = (wchar_t*)realloc(m_pData, (i + 2) * sizeof(wchar_t));
                m_pData[i + 1] = 0;
            }
            break;
        }
    }
    if(i < 0)
    {
        if (m_pData != 0)
        {
            free(m_pData);
            m_pData = 0;
        }
    }
    if(m_pData != 0)
        m_nLength = wcslen(m_pData);
    else
        m_nLength = 0;
}

CCHARStringW CCHARStringW::SpanExcluding(const wchar_t* pCharSet)
{
    CCHARStringW strRet;
    size_t nLength = m_nLength;
    if(nLength <= 0) return strRet;
    bool bFound = false;
    size_t nCharSetLength = wcslen(pCharSet);
    size_t i, j;
    for(i = 0; i < nLength; ++i)
    {
        bFound = false;
        for(j = 0; j < nCharSetLength; ++j)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound= true;
                break;
            }
        }
        if(bFound)
        {
            strRet = this->Left(i);
            break;
        }
        else if(i == nLength - 1)
        {
            strRet = this->Left(i + 1);
            break;
        }
    }
    return strRet;
}

CCHARStringW CCHARStringW::SpanIncluding(const wchar_t* pCharSet)
{
    CCHARStringW strRet;
    strRet = "";
    size_t nLength = m_nLength;
    if(nLength <= 0) return strRet;
    int nFirstPos = -1, nLastPos = -1;
    size_t nCharSetLength = wcslen(pCharSet);
    for(long i = 0; i < nLength; i++)
    {
        bool bFound = false;
        for(long j = 0; j < nCharSetLength; j++)
        {
            if(pCharSet[j] == m_pData[i])
            {
                bFound = true;
                break;
            }
        }
        if(bFound)
        {
            if(nFirstPos == -1) nFirstPos = i;
            else nLastPos = i;
        }
    }
    if(nFirstPos > -1)
    {
        if(nLastPos > 0)
        {
            strRet = this->Mid(nFirstPos, nLastPos - nFirstPos + 1);
        }
        else
        {
            strRet = this->Mid(nFirstPos);
        }
    }
    else
    {
        strRet = "";
    }

    return strRet;
}

int CCHARStringW::CalculateStringLength(const wchar_t* pFormat, va_list argList, size_t* pLength)
{
    int nRet = CS_LENGTH_CALCULATED;
    *pLength = -1;
    bool bFound, bFlagAddSign, bFlagAddBlankSpace, bGetWidthFromParameter, bGetPrecisionFromParameter, bPrecision, bFlag;
    wchar_t ch, chSpecifier;
    size_t nLen = 0, i, j, nWidthStart = -1, nWidthLength = 0, nDotPos, nSpecifierPos, nDataTypeLengthPos, nPrecisionStart, nPrecisionLength, nPrecision, nLargest, nFlagsStart, nFlagsLength, nFlagsTestEnd, nWidthTestStart, nWidthTestEnd, nWidth, nDataTypeLength, nDotCount;
    size_t nFormatLength = wcslen(pFormat);
    for(i = 0; i < nFormatLength; ++i)
    {
        ch = pFormat[i];
        if(ch == L'%')
        {
            if(i < nFormatLength - 1)
            {
                bFound = false;
                for(j = i + 1; j < nFormatLength; ++j)
                {
                    if(pFormat[j] == L'd' || pFormat[j] == L'i' || pFormat[j] == L'u' || pFormat[j] == L'o' || pFormat[j] == L'x' || pFormat[j] == L'X' || pFormat[j] == L'f' || pFormat[j] == L'F' || pFormat[j] == L'e' || pFormat[j] == L'E' || pFormat[j] == L'g' || pFormat[j] == L'G' || pFormat[j] == L'a' || pFormat[j] == L'A' || pFormat[j] == L'c' || pFormat[j] == L's' || pFormat[j] == L'p' || pFormat[j] == L'n' || pFormat[j] == L'%')
                    {
                        nSpecifierPos = j;
                        chSpecifier = pFormat[j];
                        bFound = true;
                        break;
                    }
                }

                if(bFound)
                {
                    if(chSpecifier == L'%')
                    {
                        if(nSpecifierPos == i + 1)
                        {
                            ++nLen;
                            ++i;
                        }
                        else // invalid specifier
                        {
                            nRet = CS_INVALID_SPECIFIER;
                            break;
                        }
                    }
                    else
                    {
                        //bFlagLeftJustify = false;
                        bFlagAddSign = false;
                        bFlagAddBlankSpace = false;
                        //bFlagHashTag = false;
                        //bFlagLeftPadWithZeros = false;
                        bGetWidthFromParameter = false;
                        bGetPrecisionFromParameter = false;
                        bPrecision = false;
                        nWidth = 0;
                        nWidthLength = 0;
                        nDataTypeLength = DTL_NONE;
                        nDataTypeLengthPos = nSpecifierPos;
                        nDotCount = 0;
                        nPrecision = 0;
                        nPrecisionLength = 0;
                        nFlagsLength = 0;
                        bFlag = false;

                        if(nSpecifierPos > i + 1)
                        {
                            if(nSpecifierPos - 1 > i)
                            {
                                ch = pFormat[nSpecifierPos - 1];
                                switch(ch)
                                {
                                case L'h':
                                    nDataTypeLength = DTL_h;
                                    nDataTypeLengthPos = nSpecifierPos - 1;
#ifdef C_PLUS_PLUS_11
                                    if(nSpecifierPos - 2 > i)
                                    {
                                        if(pFormat[nSpecifierPos - 2] == L'h')
                                        {
                                            nDataTypeLength = DTL_hh;
                                            nDataTypeLengthPos = nSpecifierPos - 2;
                                        }
                                    }
#endif // C_PLUS_PLUS_11
                                    break;
                                case L'l':
                                    nDataTypeLength = DTL_l;
                                    nDataTypeLengthPos = nSpecifierPos - 1;
#ifdef C_PLUS_PLUS_11
                                    if(nSpecifierPos - 2 > i)
                                    {
                                        if(pFormat[nSpecifierPos - 2] == L'l')
                                        {
                                            nDataTypeLength = DTL_ll;
                                            nDataTypeLengthPos = nSpecifierPos - 2;
                                        }
                                    }
#endif // C_PLUS_PLUS_11
                                    break;
#ifdef C_PLUS_PLUS_11
                                case L'j':
                                    break;
                                case L'z':
                                    break;
                                case L't':
                                    break;
#endif // C_PLUS_PLUS_11
                                case L'L':
                                    nDataTypeLength = DTL_L;
                                    break;
                                }
                            }

                            for(j = i + 1; j < nDataTypeLengthPos; ++j)
                            {
                                if(pFormat[j] == L'.')
                                {
                                    nDotPos = j;
                                    ++nDotCount;
                                }
                            }
                            if(nDotCount == 1)
                                bPrecision = true;

                            if(bPrecision)
                            {
                                if(nDotPos + 1 < nDataTypeLengthPos)
                                {
                                    for(j = nDotPos + 1; j < nDataTypeLengthPos; ++j)
                                    {
                                        if(iswdigit(pFormat[j]))
                                        {
                                            if(j == nDotPos + 1)
                                            {
                                                nPrecisionStart = j;
                                                nPrecisionLength = 1;
                                            }
                                            else
                                                ++nPrecisionLength;
                                        }
                                        else
                                        {
                                            if(pFormat[j] == L'*')
                                                bGetPrecisionFromParameter = true;
                                            break;
                                        }
                                    }
                                    if(nPrecisionLength > 0)
                                    {
                                        wstringstream s;
                                        for(j = nPrecisionStart; j < nPrecisionStart + nPrecisionLength; ++j)
                                            s << pFormat[j];
                                        s >> nPrecision;
                                    }
                                }
                                nFlagsTestEnd = nDotPos;
                            }
                            else
                                nFlagsTestEnd = nDataTypeLengthPos;

                            for(j = i + 1; j < nFlagsTestEnd; ++j)
                            {
                                if(pFormat[j] == L'-' || pFormat[j] == L'+' || pFormat[j] == L' ' || pFormat[j] == L'#' || pFormat[j] == L'0')
                                {
                                    if(j == i + 1)
                                    {
                                        nFlagsStart = j;
                                        nFlagsLength = 1;
                                    }
                                    else
                                        ++nFlagsLength;

                                    switch(pFormat[j])
                                    {
                                    case L'-':
                                        //bFlagLeftJustify = true;
                                        bFlag = true;
                                        break;
                                    case L'+':
                                        bFlagAddSign = true;
                                        bFlag = true;
                                        break;
                                    case L' ':
                                        bFlagAddBlankSpace = true;
                                        bFlag = true;
                                        break;
                                    case L'#':
                                        //bFlagHashTag = true;
                                        bFlag = true;
                                        break;
                                    case L'0':
                                        //bFlagLeftPadWithZeros = true;
                                        bFlag = true;
                                        break;
                                    }
                                }
                                else
                                    break;
                            }

                            if(bFlag)
                                nWidthTestStart = nFlagsStart + nFlagsLength;
                            else
                                nWidthTestStart = i + 1;
                            if(bPrecision)
                                nWidthTestEnd = nDotPos;
                            else
                                nWidthTestEnd = nDataTypeLengthPos;

                            for(j = nWidthTestStart; j < nWidthTestEnd; ++j)
                            {
                                if(iswdigit(pFormat[j]))
                                {
                                    if(j == nWidthTestStart)
                                    {
                                        nWidthStart = j;
                                        nWidthLength = 1;
                                    }
                                    else
                                        ++nWidthLength;
                                }
                                else
                                {
                                    if(pFormat[j] == L'*')
                                        bGetWidthFromParameter = true;
                                    break;
                                }
                            }

                            if(nWidthLength > 0)
                            {
                                wstringstream s;
                                for(j = nWidthStart; j < nWidthStart + nWidthLength; ++j)
                                    s << pFormat[j];
                                s >> nWidth;
                            }
                        }

                        switch(chSpecifier)
                        {
                        case L'd': case L'i':
                            {
                                if(nWidthLength == 0)
                                {
                                    if(bGetWidthFromParameter)
                                        nWidth = va_arg(argList, int);
                                }
                                if(nPrecisionLength == 0)
                                {
                                    if(bGetPrecisionFromParameter)
                                        nPrecision = va_arg(argList, int);
                                }
                                wstringstream s;
                                size_t nValLength = 0;
                                if(nDataTypeLength == DTL_NONE)
                                {
                                    int nVal = va_arg(argList, int);
                                    s << nVal;
                                    wstring str = s.str();
                                    nValLength = str.length();
                                }
                                else if(nDataTypeLength == DTL_l)
                                {
                                    long nVal = va_arg(argList, long);
                                    s << nVal;
                                    wstring str = s.str();
                                    nValLength = str.length();
                                }
                                else if(nDataTypeLength == DTL_h)
                                {
                                    short nVal = (short)va_arg(argList, int);
                                    s << nVal;
                                    wstring str = s.str();
                                    nValLength = str.length();
                                }
                                if(nPrecision > nValLength)
                                    nLargest = nPrecision;
                                else
                                    nLargest = nValLength;
                                if(nWidth > nLargest)
                                    nLargest = nWidth;
                                else
                                {
                                    if(bFlagAddSign || bFlagAddBlankSpace)
                                        ++nLargest;
                                }
                                nLen += nLargest;
                                i = nSpecifierPos;
                            }
                            break;
                        case L'u':
                            break;
                        case L'o':
                            break;
                        case L'x':
                            break;
                        case L'X':
                            break;
                        case L'f': case L'F':
                            {
                                if(nWidthLength == 0)
                                {
                                    if(bGetWidthFromParameter)
                                        nWidth = va_arg(argList, int);
                                }
                                if(nPrecisionLength == 0)
                                {
                                    if(bGetPrecisionFromParameter)
                                        nPrecision = va_arg(argList, int);
                                }
                                wstringstream s;
                                double dblVal = va_arg(argList, double);
                                s << dblVal;
                                wstring str = s.str();
                                size_t nPos = str.find(L'.');
                                if(nPrecision == 0)
                                    nLargest = nPos + 1 + 6;
                                else
                                    nLargest = nPos + 1 + nPrecision;
                                if(nWidth > nLargest)
                                    nLargest = nWidth;
                                else
                                {
                                    if(bFlagAddSign || bFlagAddBlankSpace)
                                        ++nLargest;
                                }
                                nLen += nLargest;
                                i = nSpecifierPos;
                            }
                            break;
                        case L'e':
                            break;
                        case L'E':
                            break;
                        case L'g':
                            break;
                        case L'G':
                            break;
                        case L'a':
                            break;
                        case L'A':
                            break;
                        case L'c':
                            {
                                if(nDataTypeLength == DTL_l)
                                {
                                    //wint_t nVal = va_arg(argList, wint_t);
                                    ++nLen;
                                    i = nSpecifierPos;
                                }
                                else
                                {
                                    nRet = CS_INVALID_SPECIFIER;
                                    break;
                                }
                            }
                            break;
                        case L's':
                            {
                                if(nDataTypeLength == DTL_l)
                                {
                                    if(nWidthLength == 0)
                                    {
                                        if(bGetWidthFromParameter)
                                            nWidth = va_arg(argList, int);
                                    }
                                    if(nPrecisionLength == 0)
                                    {
                                        if(bGetPrecisionFromParameter)
                                            nPrecision = va_arg(argList, int);
                                    }
                                    size_t nValLength = 0;
                                    wchar_t* pVal = va_arg(argList, wchar_t*);
                                    nValLength = wcslen(pVal);
                                    if(bPrecision)
                                    {
                                        if(nPrecision < nValLength)
                                            nLargest = nPrecision;
                                        else
                                            nLargest = nValLength;
                                        if(nWidth > nLargest)
                                            nLargest = nWidth;
                                    }
                                    else
                                    {
                                        if(nWidth > nValLength)
                                            nLargest = nWidth;
                                        else
                                            nLargest = nValLength;
                                    }
                                    nLen += nLargest;
                                    i = nSpecifierPos;
                                }
                                else
                                {
                                    nRet = CS_INVALID_SPECIFIER;
                                    break;
                                }
                            }
                            break;
                        case L'p':
                            break;
                        case L'n':
                            break;
                        }
                    }
                }
                else // invalid specifier
                {
                    nRet = CS_INVALID_SPECIFIER;
                    break;
                }
            }
            else // if(i == nFormatLength - 1)
            {
                nRet = CS_INVALID_SPECIFIER;
                break;
            }
        }
        else
        {
            ++nLen;
        }
    }
    *pLength = nLen;
    return nRet;
}

void CCHARStringW::Format(const wchar_t* pFormat, ...)
{
    if(pFormat == 0) return;

    va_list argList;
    va_start(argList, pFormat);
#ifdef WINDOWS_VER

    //size_t nL;
    //CalculateStringLength(pFormat, argList, &nL);

    m_nLength = _vscwprintf(pFormat, argList);
    if(m_pData != 0) free(m_pData);
    m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
    vswprintf(m_pData, m_nLength + 1, pFormat, argList);
    va_end(argList);
#endif
#ifdef LINUX_VER
    size_t nL;
    if(CalculateStringLength(pFormat, argList, &nL) == CS_LENGTH_CALCULATED)
    {
        va_end(argList);
        m_nLength = nL;
        if(m_pData != 0) free(m_pData);
        m_pData = (wchar_t*)malloc((m_nLength + 1) * sizeof(wchar_t));
        va_start(argList, pFormat);
        vswprintf(m_pData, m_nLength + 1, pFormat, argList);
    }
    va_end(argList);
#endif
}

void CCHARStringW::SetAt(int nIndex, wchar_t ch)
{
    m_pData[nIndex] = ch;
}

int CCHARStringW::CompareNoCase(const wchar_t* pChar)
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
#ifdef LINUX_VER
    return wcscasecmp(m_pData, pChar);
#else // WINDOWS_VER
    //return _wcsicmp(m_pData, pChar);
#endif
    return -1;
}

int CCHARStringW::CompareNoCase(const wchar_t* pChar) const
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
#ifdef LINUX_VER
    return wcscasecmp(m_pData, pChar);
#else // WINDOWS_VER
    //return _wcsicmp(m_pData, pChar);
#endif
}

int CCHARStringW::Compare(const wchar_t* pChar)
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
    return wcscmp(m_pData, pChar);
}

int CCHARStringW::Compare(const wchar_t* pChar) const
{
    if (m_pData == 0)
    {
        if (pChar == 0)
            return 0;
        else
            return -1;
    }
    else // if(m_pData != 0)
    {
        if (pChar == 0)
            return 1;
    }
    return wcscmp(m_pData, pChar);
}

void CCHARStringW::Add(const wchar_t* pString, int nCount)
{
    if(pString == NULL) return;

    m_pData = (wchar_t*)realloc(m_pData, (m_nLength + nCount + 1) * sizeof(wchar_t));

    memcpy(m_pData + m_nLength, pString, nCount * sizeof(wchar_t));
    m_pData[m_nLength + nCount] = 0;
    m_nLength += nCount;
}

void CCHARStringW::Empty()
{
    if(m_pData != 0)
    {
        free(m_pData);
        m_pData = 0;
        m_nLength = 0;
    }
}

void CCHARStringW::Replace(const wchar_t* pOld, const wchar_t* pNew)
{
#ifdef LINUX_VER
    if (!wcscasecmp(pOld, pNew))
        return;
#else // WINDOWS_VER
    //if (!_wcsicmp(pOld, pNew))
    //    return;
#endif
    CCHARStringW strTemp;
    int nPos = Find(pOld);
    while(nPos != -1)
    {
        strTemp = this->Left(nPos) + pNew;
        strTemp += this->Mid(nPos + wcslen(pOld));
        (*this) = strTemp;
        nPos = Find(pOld);
    }
}

void CCHARStringW::Insert(int nIndex, wchar_t ch)
{
    if(nIndex >= 0 && nIndex < m_nLength)
    {
        if(m_nLength > 0)
        {
            if(nIndex == 0)
            {
                CCHARStringW strTemp;
                strTemp += ch;
                strTemp += (*this);
                (*this) = strTemp;
            }
            else
            {
                CCHARStringW strTemp;
                strTemp = this->Left(nIndex);
                strTemp += ch;
                strTemp += this->Mid(nIndex);
                (*this) = strTemp;
            }
        }
        else
        {
            (*this) += ch;
        }
    }
}

void CCHARStringW::Insert(int nIndex, const wchar_t* pText)
{
    if(nIndex >= 0 && nIndex < m_nLength && pText != 0)
    {
        if(m_nLength > 0)
        {
            if(nIndex == 0)
            {
                CCHARStringW strTemp;
                strTemp += pText;
                strTemp += (*this);
                (*this) = strTemp;
            }
            else
            {
                CCHARStringW strTemp;
                strTemp = this->Left(nIndex);
                strTemp += pText;
                strTemp += this->Mid(nIndex);
                (*this) = strTemp;
            }
        }
        else
        {
            (*this) += pText;
        }
    }
}

CCHARStringW CCHARStringW::UpperCase(const CCHARStringW & strString)
{
    std::setlocale(LC_ALL, "");
    CCHARStringW strNew;
    int i, nLen = strString.GetLength();
    for(i = 0; i < nLen; i++)
        strNew += std::towupper(strString[i]);
    return strNew;
}

CCHARStringW CCHARStringW::UpperCase(const wchar_t* strString)
{
    std::setlocale(LC_ALL, "");
    CCHARStringW strNew;
    int i, nLen = wcslen(strString);
    for(i = 0; i < nLen; i++)
        strNew += std::towupper(strString[i]);
    return strNew;
}

CCHARStringW CCHARStringW::LowerCase(const CCHARStringW & strString)
{
    std::setlocale(LC_ALL, "");
    CCHARStringW strNew;
    int i, nLen = strString.GetLength();
    for(i = 0; i < nLen; i++)
        strNew += std::towlower(strString[i]);
    return strNew;
}

CCHARStringW CCHARStringW::LowerCase(const wchar_t* strString)
{
    std::setlocale(LC_ALL, "");
    CCHARStringW strNew;
    int i, nLen = wcslen(strString);
    for(i = 0; i < nLen; i++)
        strNew += std::towlower(strString[i]);
    return strNew;
}

long CCHARStringW::ToLong()
{
    if(!m_pData || m_nLength == 0)
        return 0;
    return wcstol(m_pData, 0, 10);
}

int CCHARStringW::FindOneOf(const wchar_t* str) const
{
    wchar_t * pFound = wcspbrk(m_pData, str);
    if (pFound)
        return (int)(pFound - m_pData);
    return -1;

    //return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

unsigned short* CCHARStringW::GetUSHORT(const CCHARStringW & strString, int* pLength)
{
    *pLength = strString.GetLength();
    unsigned short* str = new unsigned short[(*pLength) + 1];
    for (int i = 0; i < (*pLength); ++i)
        str[i] = (unsigned short)strString[i];
    str[*pLength] = 0;
    return str;
}

unsigned short* CCHARStringW::GetUSHORT(const wchar_t* strString, int* pLength)
{
    *pLength = wcslen(strString);
    unsigned short* str = new unsigned short[(*pLength) + 1];
    for (int i = 0; i < (*pLength); ++i)
        str[i] = (unsigned short)strString[i];
    str[*pLength] = 0;
    return str;
}

wchar_t* CCHARStringW::GetWCHAR(const unsigned short* strString, int nLength)
{
    wchar_t* str = new wchar_t[nLength + 1];
    for (int i = 0; i < nLength; ++i)
        str[i] = (wchar_t)strString[i];
    str[nLength] = L'\0';
    return str;
}

char* CCHARStringW::GetCHARA(const CCHARStringW & strString)
{
    wchar_t* pText = strString.GetCHAR();
    size_t nLength = strString.GetLength();
    char* str = new char[nLength + 1];
    for (size_t i = 0; i < nLength; ++i)
        str[i] = (char)pText[i];
    str[nLength] = '\0';
    return str;
}

char* CCHARStringW::GetCHARA(const wchar_t* strString)
{
    size_t nLength = wcslen(strString);
    char* str = new char[nLength + 1];
    for (size_t i = 0; i < nLength; ++i)
        str[i] = (char)strString[i];
    str[nLength] = '\0';
    return str;
}

#ifdef HANDLE_SQL_TYPES
wchar_t* CCHARStringW::GetWCHAR(SQLWCHAR* strString, int nLength)
{
    wchar_t* str = new wchar_t[nLength + 1];
    for (int i = 0; i < nLength; ++i)
        str[i] = (wchar_t)strString[i];
    str[nLength] = L'\0';
    return str;
}
#endif
