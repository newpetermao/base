// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#include <string>
#include <map>

class Config {
 public:
  Config() {m_bInit = false;}
  ~Config() {}

  /*
   * @func open sFileName and init
   * @ret  0   success
   *       -1  param invalid
   *       -2  file not exist
   *       -3  line is too long(max is 1024)
   */
  int Init(const std::string sFileName);

  /*
   * @func get the val to sVal from sSection.sKey
   * @ret  0   success
   *       -1  param invalid
   *       -2  init fail
   *       -3  bad section
   *       -4  bad key
   */
  int Get(const std::string sSection,
          const std::string sKey,
          std::string* sVal);

 private:
  bool m_bInit;
  std::map<std::string, std::map<std::string, std::string> > m_mapConfig;
  void Trim(std::string* str);
};

#endif  // SRC_CONFIG_H_
