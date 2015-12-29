#include <MJ.h>

MJ::MJ() {
  m_9LBD = false;
  m_GSWS = false;
  m_4AK = false;
  m_AKnum = 0;
  m_MKnum = 0;
}

MJ::~MJ() {

}

// initialize
void MJ::init() {
  m_9LBD = false;
  m_GSWS = false;
  m_4AK = false;
  m_AKnum = 0;
  m_MKnum = 0;
}

// 加入新牌
bool MJ::AddPai(int p_type, int p_value) {
  int iSize = m_MyPAIVec[p_type].size();
  bool t_Find = false;
  vector<int>::iterator Iter;

  for(Iter = m_MyPAIVec[p_type].begin();Iter !=m_MyPAIVec[p_type].end(); Iter++) {
    if((*Iter)>p_value) {
      m_MyPAIVec[p_type].insert(Iter,p_value);
      t_Find = true;
      break;
    }
  }
  if(t_Find==false) {
    m_MyPAIVec[p_type].push_back(p_value);
  }
  m_lastPAI.m_type = p_type;
  m_lastPAI.m_value = p_value;

  return true;
}

int MJ::GetPaiIndex(int p_type, int p_value) {
  int count = 0;
  for (UINT i = 0; i < 6; i++) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[i].begin(); Iter != m_MyPAIVec[i].end(); Iter++) {
      if (i == p_type && (*Iter) == p_value) {
        return count;
      }
      count++;
    }
  }
  return -1;
}

bool MJ::delPai(int PaiIndex) {
  int count = 0;
  for (UINT i =0; i < 6; i++) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[i].begin(); Iter != m_MyPAIVec[i].end(); Iter++) {
      if(count == PaiIndex) {
        m_MyPAIVec[i].erase(Iter);
        return true;
      }
      count++;
    }
  }
  return false;
}

bool MJ::delPai(int p_type, int p_value) {
  vector<int>::iterator Iter;
  for(Iter = m_MyPAIVec[p_type].begin(); Iter != m_MyPAIVec[p_type].end(); Iter++) {
    if((*Iter) == p_value) {
      m_MyPAIVec[p_type].erase(Iter);
      return true;
    }
  }
  return false;
}

void MJ::CleanUp() {
  for(UINT i = 0; i < 6; i++) {
    m_MyPAIVec[i].clear();
    m_ChiPAIVec[i].clear();
    m_PengPAIVec[i].clear();
    m_GangPAIVec[i].clear();
  }
}

stGoodInfo *GetInfo() {
  return &m_GoodInfo;
}

void MJ::printAllPai() {
  cout << " ";
  for (UINT i = 0; i < 13; i++) {
    cout<< "  - ";
  }
  cout<<endl;

  int icount = 0;

  // 字牌
  if (m_MyPAIVec[0].empty() == false) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[0].begin(); Iter != m_MyPAIVec[0].end(); Iter++) {
      switch (*Iter) {
        case 0:
          cout<<"[中]";
          break;
        case 1:
          cout<<"[发]";
          break;
        case 2:
          cout<<"[白]";
          break;
      }
      icount++;
    }
  }

  // 风牌
  if (m_MyPAIVec[1].empty() == false) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[1].begin(); Iter != m_MyPAIVec[1].end(); Iter++) {
      switch (*Iter) {
        case 0:
          cout<<"[东]";
          break;
        case 1:
          cout<<"[南]";
          break;
        case 2:
          cout<<"[西]";
          break;
        case 3:
          cout<<"[北]";
          break;
      }
      icount++;
    }
  }

  // 万
  if (m_MyPAIVec[2].empty() == false) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[2].begin(); Iter != m_MyPAIVec[2].end(); Iter++) {
      cout<<"["<<Iter<<"万]";
      icount++;
    }
  }

  // 条
  if (m_MyPAIVec[3].empty() == false) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[3].begin(); Iter != m_MyPAIVec[3].end(); Iter++) {
      cout<<"["<<Iter<<"条]";
      icount++;
    }
  }
  // 饼
  if (m_MyPAIVec[4].empty() == false) {
    vector<int>::iterator Iter;
    for (Iter = m_MyPAIVec[4].begin(); Iter != m_MyPAIVec[4].end(); Iter++) {
      cout<<"["<<Iter<<"饼]";
      icount++;
    }
  }
}

void MJ::printPai(int p_type, int p_value) {
  if(p_type == 0) {
    switch (p_value) {
      case 0:
        cout<<"[中]";
        break;
      case 1:
        cout<<"[发]";
        break;
      case 2:
        cout<<"[白]";
        break;
    }
  } else if (p_type == 1) {
    switch (p_value) {
      case 0:
        cout<<"[东]";
        break;
      case 1:
        cout<<"[南]";
        break;
      case 2:
        cout<<"[西]";
        break;
      case 3:
        cout<<"[北]";
        break;
    }
  } else if (p_type == 2) {
    cout<<"["<<p_value<<"万]";
  } else if (p_type == 3) {
    cout<<"["<<p_value<<"条]";
  } else if (p_type == 4) {
    cout<<"["<<p_value<<"饼]";
  }
}

bool MJ::checkChiPai(int p_type, int p_value) {
  m_tempChiPAIVec.clear();
  // 饼
  if (m_MyPAIVec[p_type].empty() == false) {
    int iSize = m_MyPAIVec[p_type].size();
    if (iSize >= 2) {
      for (UINT i = 0; i < iSize-1; i++) {
        // 已有AB吃C
        if ((m_MyPAIVec[p_type][i]==(p_value-2)) && (m_MyPAIVec[p_type][i+1]==(p_value-1))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value-2;
          t_Chi.m_value2 = p_value-1;
          t_Chi.m_value3 = p_value;
          m_tempChiPAIVec.push_back(t_Chi);
        }
        // 已有AC吃B
        if ((m_MyPAIVec[p_type][i]==(p_value-1)) && (m_MyPAIVec[p_type][i+1]==(p_value+1))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value-1;
          t_Chi.m_value2 = p_value;
          t_Chi.m_value3 = p_value+1;
          m_tempChiPAIVec.push_back(t_Chi);
        }
        // 已有BC吃A
        if ((m_MyPAIVec[p_type][i]==(p_value+1)) && (m_MyPAIVec[p_type][i+1]==(p_value+2))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value;
          t_Chi.m_value2 = p_value+1;
          t_Chi.m_value3 = p_value+2;
          m_tempChiPAIVec.push_back(t_Chi);
        }
      }
    }
    // 已有ABC吃B
    if (iSize >= 3) {
      for (UINT i = 1; i < iSize-1; i++) {
        if ((m_MyPAIVec[p_type][i-1]==(p_value-1)) && (m_MyPAIVec[p_type][i]==(p_value)) && (m_MyPAIVec[p_type][i+1]==(p_value+1))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value-1;
          t_Chi.m_value2 = p_value;
          t_Chi.m_value3 = p_value+1;
          m_tempChiPAIVec.push_back(t_Chi);
        }
      }
    }
    // 已有ABBC吃B
    if (iSize >= 4) {
      for (UINT i = 1; i < iSize-2; i++) {
        if ((m_MyPAIVec[p_type][i-1]==(p_value-1)) && (m_MyPAIVec[p_type][i]==p_value) && (m_MyPAIVec[p_type][i+2]==(p_value+1))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value-1;
          t_Chi.m_value2 = p_value;
          t_Chi.m_value3 = p_value+1;
          m_tempChiPAIVec.push_back(t_Chi);
        }
      }
    }
    // 已有ABBBC吃B
    if (iSize >= 5) {
      for (UINT i = 1; i < iSize-3; i++) {
        if ((m_MyPAIVec[p_type][i-1]==(p_value-1)) && (m_MyPAIVec[p_type][i]==p_value) && (m_MyPAIVec[p_type][i+3]==(p_value+1))) {
          stCHI t_Chi;
          t_Chi.m_type = p_type;
          t_Chi.m_value1 = p_value-1;
          t_Chi.m_value2 = p_value;
          t_Chi.m_value3 = p_value+1;
          m_tempChiPAIVec.push_back(t_Chi);
        }
      }
    }
    if (m_tempChiPAIVec.size() > 0) {
       return true;
    }
  }
  return false;
}


bool MJ::DoChiPai(int p_index, int p_type, int p_value) {
  AddPai(p_type, p_value);
  vector<int>::iterator Iter;
  int icount = 0;
  for (Iter = m_tempChiPAIVec.begin(); Iter != m_tempChiPAIVec.end(); Iter++) {
    if (icount == p_index) {
      delPai((*Iter).m_type, (*Iter).m_value1);
      delPai((*Iter).m_type, (*Iter).m_value2);
      delPai((*Iter).m_type, (*Iter).m_value3);

      m_ChiPAIVec[(*Iter).m_type].push_back((*Iter).m_value1);
      m_ChiPAIVec[(*Iter).m_type].push_back((*Iter).m_value2);
      m_ChiPAIVec[(*Iter).m_type].push_back((*Iter).m_value3);

      return true;
    }
    icount++;
  }
  return false;
}

void MJ::printChiChosePai() {
  cout<<"================吃牌组合======================="<<endl;
  vector<int>::iterator Iter;
  for (Iter = m_tempChiPAIVec.begin(); Iter != m_tempChiPAIVec.end(); Iter++) {
    // 万
    if ((*Iter).m_type == 2) {
      cout<<"["<<(*Iter).m_value1<<"万";
      cout<<""<<(*Iter).m_value2<<"万";
      cout<<""<<(*Iter).m_value3<<"万]";
    }
    // 条
    if ((*Iter).m_type == 3) {
      cout<<"["<<(*Iter).m_value1<<"条";
      cout<<""<<(*Iter).m_value2<<"条";
      cout<<""<<(*Iter).m_value3<<"条]";
    }
    // 饼
    if ((*Iter).m_type == 4) {
      cout<<"["<<(*Iter).m_value1<<"饼";
      cout<<""<<(*Iter).m_value2<<"饼";
      cout<<""<<(*Iter).m_value3<<"饼]";
    }
  }
  cout<<endl<<"========================================="<<endl;
}

void MJ::printPengChosePai() {
  cout<<"================碰牌组合======================="<<endl;
  vector<int>::iterator Iter;
  for (Iter = m_tempPengPAIVec.begin(); Iter != m_tempPengPAIVec.end(); Iter++) {
    // 万
    if ((*Iter).m_type == 2) {
      cout<<"["<<(*Iter).m_value1<<"万";
      cout<<""<<(*Iter).m_value2<<"万";
      cout<<""<<(*Iter).m_value3<<"万]";
    }
    // 条
    if ((*Iter).m_type == 3) {
      cout<<"["<<(*Iter).m_value1<<"条";
      cout<<""<<(*Iter).m_value2<<"条";
      cout<<""<<(*Iter).m_value3<<"条]";
    }
    // 饼
    if ((*Iter).m_type == 4) {
      cout<<"["<<(*Iter).m_value1<<"饼";
      cout<<""<<(*Iter).m_value2<<"饼";
      cout<<""<<(*Iter).m_value3<<"饼]";
    }
  }
  cout<<endl<<"========================================="<<endl;
}

void MJ::printGangChosePai() {
  cout<<"================碰牌组合======================="<<endl;
  vector<int>::iterator Iter;
  for (Iter = m_tempGangPAIVec.begin(); Iter != m_tempGangPAIVec.end(); Iter++) {
    // 万
    if ((*Iter).m_type == 2) {
      cout<<"["<<(*Iter).m_value1<<"万";
      cout<<""<<(*Iter).m_value2<<"万";
      cout<<""<<(*Iter).m_value3<<"万";
      cout<<""<<(*Iter).m_value4<<"万]";
    }
    // 条
    if ((*Iter).m_type == 3) {
      cout<<"["<<(*Iter).m_value1<<"条";
      cout<<""<<(*Iter).m_value2<<"条";
      cout<<""<<(*Iter).m_value3<<"条";
      cout<<""<<(*Iter).m_value4<<"条]";
    }
    // 饼
    if ((*Iter).m_type == 4) {
      cout<<"["<<(*Iter).m_value1<<"饼";
      cout<<""<<(*Iter).m_value2<<"饼";
      cout<<""<<(*Iter).m_value3<<"饼";
      cout<<""<<(*Iter).m_value4<<"饼]";
    }
  }
}

UINT MJ::GetChiChoseNum() {
  return m_tempChiPAIVec.size();
}

// 碰牌
bool MJ::checkPengPai(int p_type, int p_value) {
  m_tempPengPAIVec.clear();
  // 饼
  if (m_MyPAIVec[p_type].empty() == false) {
    int iSize = m_MyPAIVec[p_type].size();
    if (iSize >= 2) {
      for (UINT i = 0; i < iSize-1; i++) {
        if (m_MyPAIVec[p_type][i]==p_value && m_MyPAIVec[p_type][i+1]==p_value) {
          stPAI t_peng;
          t_peng.m_type = p_type;
          t_peng.m_value = p_value;
          m_tempPengPAIVec.push_back(t_peng);
          break;
        }
      }
    }
    if (m_tempChiPAIVec.size() > 0) {
      return true;
    }
  }
  return false;
}

// 碰牌
bool MJ::DoPengPai(int p_type, int p_value) {
  AddPai(p_type, p_value);
  vector<stPAI>::iterator Iter;
  for (Iter=m_tempPengPAIVec.begin(); Iter != m_tempPengPAIVec.end(); Iter++) {
    delPai((*Iter).m_type, (*Iter).m_value);
    delPai((*Iter).m_type, (*Iter).m_value);
    delPai((*Iter).m_type, (*Iter).m_value);

    m_PengPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
    m_PengPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
    m_PengPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
    return true;
  }
  return false;
}

// 杠牌
bool MJ::checkGangPai(int p_type, int p_value) {
  m_tempGangPAIVec.clear();

  if (m_MyPAIVec[p_type].empty() == false) {
    int iSize = m_MyPAIVec[p_type].size();
    if (iSize >= 3) {
      for (UINT i = 0; i < size-2; i++) {
        if ((m_MyPAIVec[p_type][i]==p_value) && (m_MyPAIVec[p_type][i+1]==p_value) && (m_MyPAIVec[p_type][i+2]==p_value)) {
          stPAI t_gang;
          t_gang.m_type = p_type;
          t_gang.m_value = p_value;
          m_tempGangPAIVec.push_back(t_gang);
          break;
        }
      }
    }
    if (m_tempGangPAIVec.size() > 0) {
      return true;
    }
  }
  return false;
}

// 杠
bool DoGangPai(int p_type, int p_value) {
  AddPai(p_type, p_value);
  vector<stPAI>::iterator Iter;
  for (Iter=m_tempGangPAIVec.begin(); Iter != m_tempGangPAIVec.end(); Iter++) {
    delPai((*Iter).m_type, (*Iter).m_value);
    delPai((*Iter).m_type, (*Iter).m_value);
    delPai((*Iter).m_type, (*Iter).m_value);
    delPai((*Iter).m_type, (*Iter).m_value);

    //
    if (m_GangPAIVec[(*Iter).m_type].empty()) {
      m_GangPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
      m_GangPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
      m_GangPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
      m_GangPAIVec[(*Iter).m_type].push_back((*Iter).m_value);
    } else {
      vector<int>::iterator Iter2;
      for (Iter2=m_GangPAIVec[(*Iter).m_type].begin(); Iter2 != m_GangPAIVec[(*Iter).m_type].end(); Iter2++) {
        if ((*Iter2) > (*Iter).m_value) {
          m_GangPAIVec[(*Iter).m_type].insert(Iter2, (*Iter).m_value);
          m_GangPAIVec[(*Iter).m_type].insert(Iter2, (*Iter).m_value);
          m_GangPAIVec[(*Iter).m_type].insert(Iter2, (*Iter).m_value);
          m_GangPAIVec[(*Iter).m_type].insert(Iter2, (*Iter).m_value);
          break;
        }
      }
    }
    return true;
  }
  return false;
}
