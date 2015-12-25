#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MJ_ZFB    0
#define MJ_FENG   1
#define MJ_WAN    2
#define MJ_TIAO   3
#define MJ_BING   4

#define MJ_MO     TRUE
#define MJ_DA     FALSE

struct stPAI {
  int m_type;       // 牌类型
  int m_value;      // 牌字
};

struct stCHI {
  int m_type;
  int m_value1;
  int m_value2;
  int m_value3;
};

struct stGoodInfo {
  char m_goodName[100];     // 胡牌役种
  int m_goodValue;          // 和牌番数
};

class MJ {
  vector<int> m_MyPAIVec[6];
  vector<int> m_ChiPAIVec[6];
  vector<int> m_PengPAIVec[6];
  vector<int> m_GangPAIVec[6];

  stPAI m_lastPAI;
  stGoodInfo m_GoodInfo;

  bool m_GSWS;        // 是否国士无双
  bool m_9LBD;        // 是否九莲宝灯
  int m_MKnum;        // 明刻数
  int m_AKnum;        // 暗刻数
  bool m_4AK;         // 是否四暗刻

  vector<stCHI> m_tempChiPAIVec;      // 吃牌选择
  vector<stPAI> m_tempPengPAIVec;     // 碰牌选择
  vector<stPAI> m_tempGangPAIVec;     // 杠牌选择

public:
  // Constructor
  MJ();
  //
  ~MJ();
  // initialize
  void init();
  //
  bool AddPai(int p_type, int p_value);
  // get pai index
  int GetPaiIndex(int p_type, int p_value);
  //
  bool delPai(int PaiIndex);
  //
  bool delPai(int p_type, int p_value);
  //
  void CleanUp();
  //
  stGoodInfo *GetInfo();
  // 检查和牌
  bool checkAllPai();
  //
  void printAllPai();
  //
  void printPai(int p_type, int p_value);
  // 检查吃牌
  bool checkChiPai(int p_type, int p_value);
  // 吃牌
  bool DoChiPai(int p_index, int p_type, int p_value);
  // 检查碰牌
  bool checkPengPai(int p_type, int p_value);
  // 碰牌
  bool DoPengPai(int p_type, int p_value);
  // 检查杠牌
  bool checkGangPai(int p_type, int p_value);
  // 杠牌
  bool DoGangPai(int p_type, int p_value);
  // 输出吃牌组合
  void printChiChosePai();
  // 输出碰牌组合
  void printPengChosePai();
  // 输出杠牌组合
  void printGangChosePai();
  // 取得吃牌组合数
  UINT GetChiChoseNum();

private:
  // 检测是否和牌
  bool checkAAPai(int iValue1, int iValue2);
  // 检测是否三连
  bool checkABCPai(int iValue1, int iValue2, int iValue3);
  // 检测是否三重张
  bool checkAAAPai(int iValue1, int iValue2, int iValue3);
  // 检测是否四重张
  bool checkAAAAPai(int iValue1, int iValue2, int iValue3, int iValue4);
  // 检测是否三连对
  bool checkAABBCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6);
  // 检测是否AAABBBCCC
  bool checkAAABBBCCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9);
  // 检测是否三连刻
  bool checkAAAABBBBCCCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9, int iValue10, int iValue11, int iValue12);
  // 检测是否六连对
  bool checkAABBCCDDEEFFPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9, int iValue10, int iValue11, int iValue12);
  
}
