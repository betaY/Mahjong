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
  m_lastPAI.m_Type = p_type;
  m_lastPAI.m_Value = p_value;

  return true;
}

int MJ::GetPaiIndex(int p_type, int p_value) {
  int count = 0;
  
}
