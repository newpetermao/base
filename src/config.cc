// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include <stdio.h>
#include "./config.h"

int Config::Init(const std::string sFileName) {
  FILE* fp = NULL;
  char acBuf[1024];
  bool bLast = false;
  std::string sKey = "";
  std::string sValue = "";
  std::string sLine = "";
  std::string sSectionName;
  std::string::size_type pos;
  std::map<std::string, std::string> mapSectionInfo;

  bLast = false;
  m_bInit = false;
  if ("" == sFileName)
    return -1;

  fp = fopen(sFileName.c_str(), "rb");
  if (NULL == fp)
    return -2;

  m_mapConfig.clear();
  while (fgets(acBuf, sizeof(acBuf), fp)) {
    if (bLast)
      return -3;

    sLine = std::string(acBuf);
    // line exceed sizeof(acBuf) - 1
    if (sLine.length() > 0 && sLine[sLine.length() -1] != '\n')
      bLast = true;

    if (sLine.length() > 0 && sLine[sLine.length() -1] == '\n') {
      if (sLine.length() > 1 && sLine[sLine.length() - 2] == '\r') {
        sLine.erase(sLine.length() - 2, 2);
      } else {
        sLine.erase(sLine.length() - 1, 1);
      }
    }

    this->Trim(&sLine);
    if (sLine == "" || sLine[0] == '#' || sLine[0] == '/')
      continue;

    if (sLine[0] == '[' && sLine[sLine.length() - 1] == ']') {
      if (sSectionName != "") {
        this->m_mapConfig[sSectionName] = mapSectionInfo;
        mapSectionInfo.clear();
      }

      sSectionName = sLine.substr(1, sLine.length() - 2);
      Trim(&sSectionName);
    } else {
      pos = sLine.find('=');
      if (std::string::npos != pos) {
        if (pos < sLine.length() - 1) {
          sKey.assign(sLine, 0, pos);
          sValue.assign(sLine, pos + 1, sLine.length() - pos - 1);
          this->Trim(&sKey);
          this->Trim(&sValue);
          mapSectionInfo[sKey] = sValue;
        } else if (sLine.length() - 1 == pos) {
          sLine.erase(sLine.length() - 1, 1);
          this->Trim(&sLine);
          mapSectionInfo[sLine] = "";
        }
      }
    }
  }

  if (sSectionName != "")
    this->m_mapConfig[sSectionName] = mapSectionInfo;

  m_bInit = true;
  return 0;
}

int Config::Get(const std::string sSection,
                    const std::string sKey,
                    std::string* sVal) {
  std::map<std::string, std::string>::const_iterator iterKey;
  typedef std::map<std::string, std::string> sec_map;
  std::map<std::string, sec_map>::const_iterator iterSec;

  if ("" == sSection || "" == sKey || NULL == sVal)
    return -1;

  if (false == m_bInit)
    return -2;

  iterSec = m_mapConfig.find(sSection);
  if (m_mapConfig.end() == iterSec)
    return -3;

  iterKey = iterSec->second.find(sKey);
  if (iterSec->second.end() == iterKey)
    return -4;

  *sVal = iterKey->second;
  return 0;
}

void Config::Trim(std::string* str) {
  std::string::size_type pos = 0;

  if (NULL == str || 0 == str->length())
    return;

  while (pos < str->length()) {
    if (!isspace((*str)[pos]))
      break;
    pos++;
  }

  if (pos > 0)
    str->erase(0, pos);

  pos = str->length() - 1;
  while (pos >= 0) {
    if (!isspace((*str)[pos]))
      break;
    pos--;
  }

  if (pos < str->length() - 1)
    str->erase(pos + 1, str->length() - pos - 1);

  return;
}
