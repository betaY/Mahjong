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

bool MJ::checkAllPai(bool GetOrPut) {
  if (GetOrPut == MJPAI_GETPAI) {
    // 1.役牌
    if (CheckYP_HU()) {
      strcpy(m_GoodInfo.m_goodName,"役牌");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 2.立直
    if (CheckLZ_HU()) {
      strcpy(m_GoodInfo.m_goodName,"立直");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 3.断幺
    if (CheckDY_HU()) {
      strcpy(m_GoodInfo.m_goodName,"断幺");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 4.平和
    if (CheckHU()) {
      strcpy(m_GoodInfo.m_goodName,"平和");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 5.一发
    if (Check1F_HU()) {
      strcpy(m_GoodInfo.m_goodName,"一发");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 6.一杯口
    if (Check1BK_HU()) {
      strcpy(m_GoodInfo.m_goodName,"一杯口");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 7.抢杠
    if (CheckQG_HU()) {
      strcpy(m_GoodInfo.m_goodName,"抢杠");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 8.岭上开花
    if (CheckLSKH_HU()) {
      strcpy(m_GoodInfo.m_goodName,"岭上开花");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 9.河底捞鱼
    if (CheckHDLY_HU()) {
      strcpy(m_GoodInfo.m_goodName,"河底捞鱼");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 10.海底摸月
    if (CheckHDMY_HU()) {
      strcpy(m_GoodInfo.m_goodName,"海底摸月");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 11.双立直
    if (CheckSLZ_HU()) {
      strcpy(m_GoodInfo.m_goodName,"双立直");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 12.一气贯通
    if (Check1QGT_HU()) {
      strcpy(m_GoodInfo.m_goodName,"一气贯通");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 13.小三元
    if (CheckX3Y_HU()) {
      strcpy(m_GoodInfo.m_goodName,"小三元");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 14.三色同顺
    if (Check3STS_HU()) {
      strcpy(m_GoodInfo.m_goodName,"三色同顺");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 15.三色同刻
    if (Check3STK_HU()) {
      strcpy(m_GoodInfo.m_goodName,"三色同刻");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 16.三暗刻
    if (Check3AK_HU()) {
      strcpy(m_GoodInfo.m_goodName,"三暗刻");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 17.三杠子
    if (Check3GZ_HU()) {
      strcpy(m_GoodInfo.m_goodName,"三杠子");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 18.全带幺九
    if (CheckQDYJ_HU()) {
      strcpy(m_GoodInfo.m_goodName,"全带幺九");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 19.七对子
    if (Check7D_HU()) {
      strcpy(m_GoodInfo.m_goodName,"七对子");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 20.对对和
    if (CheckDDH_HU()) {
      strcpy(m_GoodInfo.m_goodName,"对对和");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 21.两杯口
    if (CheckLBK_HU()) {
      strcpy(m_GoodInfo.m_goodName,"两杯口");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 22.混一色
    if (CheckH1S_HU()) {
      strcpy(m_GoodInfo.m_goodName,"混一色");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 23.混老头
    if (CheckHLT_HU()) {
      strcpy(m_GoodInfo.m_goodName,"混老头");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 24.纯全带幺
    if (CheckCQDY_HU()) {
      strcpy(m_GoodInfo.m_goodName,"纯全带幺");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 25.流局满贯
    if (CheckLJMG_HU()) {
      strcpy(m_GoodInfo.m_goodName,"流局满贯");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 26.清一色
    if (CheckQ1S_HU()) {
      strcpy(m_GoodInfo.m_goodName,"清一色");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 27.小四喜
    if (CheckX4X_HU()) {
      strcpy(m_GoodInfo.m_goodName,"小四喜");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 28.天和
    if (CheckTH_HU()) {
      strcpy(m_GoodInfo.m_goodName,"天和");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 29.地和
    if (CheckDH_HU()) {
      strcpy(m_GoodInfo.m_goodName,"地和");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 30.人和
    if (CheckRH_HU()) {
      strcpy(m_GoodInfo.m_goodName,"人和");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 31.四杠子
    if (Check4Gang_HU()) {
      strcpy(m_GoodInfo.m_goodName,"四杠子");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 32.四暗刻
    if (Check4AK_HU()) {
      strcpy(m_GoodInfo.m_goodName,"四暗刻");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 33.清老头
    if (CheckQLT_HU()) {
      strcpy(m_GoodInfo.m_goodName,"清老头");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 34.绿一色
    if (CheckL1S_HU()) {
      strcpy(m_GoodInfo.m_goodName,"绿一色");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 35.九莲宝灯
    if (Check9LBD_HU()) {
      strcpy(m_GoodInfo.m_goodName,"九莲宝灯");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 36.国士无双
    if (CheckGSWS_HU()) {
      strcpy(m_GoodInfo.m_goodName,"国士无双");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 37.大三元
    if (CheckD3Y_HU()) {
      strcpy(m_GoodInfo.m_goodName,"大三元");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 38.大车轮
    if (CheckDCL_HU()) {
      strcpy(m_GoodInfo.m_goodName,"大车轮");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
    // 39.大四喜
    if (CheckD4X_HU()) {
      strcpy(m_GoodInfo.m_goodName,"大四喜");
      m_GoodInfo.m_goodValue = 1;
      return true;
    }
  } else {
    m_9LBD = Check9LBD_TING();
    if (m_9LBD) {
      return true;
    }
    m_GSWS = CheckGSWS_TING();
    if (m_GSWS) {
      return true;
    }
    return CheckTING();
  }
}

inline bool MJ::checkAAPai(int iValue1, int iValue2) {
  if (iValue1 == iValue2) return true;
  return false;
}

inline bool MJ::checkABCPai(int iValue1, int iValue2, int iValue3) {
  if (iValue1==(iValue2-1) && iValue2==(iValue3-1)) return true;
  return false;
}

inline bool MJ::checkAAAPai(int iValue1, int iValue2, int iValue3) {
  if (iValue1==iValue2 && iValue2==iValue3) return true;
  return false;
}

inline bool MJ::checkAAAAPai(int iValue1, int iValue2, int iValue3, int iValue4) {
  if (iValue1==iValue2 && iValue2==iValue3 && iValue3==iValue4) return true;
  return false;
}

inline bool MJ::checkAABBCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6) {
  if (iValue1==iValue2 && iValue3==iValue4 && iValue5==iValue6) {
    if (iValue1==(iValue3-1) && iValue3==(iValue5-1)) {
        return true;
    }
  }
  return false;
}
