#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MJ_ZFB    0
#define MJ_FENG   1
#define MJ_WAN    2
#define MJ_TIAO   3
#define MJ_BING   4

#define MJPAI_GETPAI     TRUE
#define MJPAI_PUTPAI     FALSE

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
  bool checkAllPai(bool GetOrPut);
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

  // 带雀头检测
  // 检测是否胡牌（张）
  bool check5Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5);
  // 检测是否胡牌（张）
  bool check8Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8);
  // 检测是否胡牌（张）
  bool check11Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9, int iValue10, int iValue11);
  // 检测是否胡牌（张）
  bool check14Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9, int iValue10, int iValue11, int iValue12, int iValue13, int iValue14);

  // 不带雀头检测
  // 检测是否胡牌（张）
  bool check3Pai(int iValue1, int iValue2, int iValue3);
  // 检测是否胡牌（张）
  bool check6Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6);
  // 检测是否胡牌（张）
  bool check9Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9);
  // 检测是否胡牌（张）
  bool check12Pai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7, int iValue8, int iValue9, int iValue10, int iValue11, int iValue12);


private:
  // 役种判断

  // 1.役牌
  bool CheckYP_HU();
  // 2.立直
  bool CheckLZ_HU();
  // 3.断幺
  bool CheckDY_HU();
  // 4.平和
  bool CheckHU();
  // 5.一发
  bool Check1F_HU();
  // 6.一杯口
  bool Check1BK_HU();
  // 7.抢杠
  bool CheckQG_HU();
  // 8.检测岭上开花
  bool CheckLSKH_HU();
  // 9.检测河底捞鱼
  bool CheckHDLY_HU();
  // 10.检测海底摸月
  bool CheckHDMY_HU();
  // 11.双立直
  bool CheckSLZ_HU();
  // 12.一气贯通
  bool Check1QGT_HU();
  // 13.小三元
  bool CheckX3Y_HU();
  // 14.三色同顺
  bool Check3STS_HU();
  // 15.三色同刻
  bool Check3STK_HU();
  // 16.三暗刻
  bool Check3AK_HU();
  // 17.三杠子
  bool Check3GZ_HU();
  // 18.全带幺九
  bool CheckQDYJ_HU();
  // 19.检测是否七对子
  bool Check7D_HU();
  // 20.对对和
  bool CheckDDH_HU();
  // 21.两杯口
  bool CheckLBK_HU();
  // 22.混一色
  bool CheckH1S_HU();
  // 23.混老头
  bool CheckHLT_HU();
  // 24.纯全带幺
  bool CheckCQDY_HU();
  // 25.流局满贯
  bool CheckLJMG_HU();
  // 26.清一色
  bool CheckQ1S_HU();
  // 27.小四喜
  bool CheckX4X_HU();
  // 28.天和
  bool CheckTH_HU();
  // 29.地和
  bool CheckDH_HU();
  // 30.人和
  bool CheckRH_HU();
  // 31.四杠子
  bool Check4Gang_HU();
  // 32.四暗刻
  bool Check4AK_HU();
  // 33.清老头
  bool CheckQLT_HU();
  // 34.绿一色
  bool CheckL1S_HU();
  // 35.九莲宝灯
  bool Check9LBD_HU();
  // 36.国士无双
  bool CheckGSWS_HU();
  // 37.大三元
  bool CheckD3Y_HU();
  // 38.大车轮
  bool CheckDCL_HU();
  // 39.大四喜
  bool CheckD4X_HU();

private:
  // 听牌判断

  // 听九莲宝灯
  bool Check9LBD_TING();
  // 听国士无双
  bool CheckGSWS_TING();
  // 听四暗刻
  bool Check4AK_TING();
  // 听牌
  bool CheckTING();
};
