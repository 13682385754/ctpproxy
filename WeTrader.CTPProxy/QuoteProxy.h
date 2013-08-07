// WeTrader.CTPProxy.h

#pragma once
#include "QuoteMdSpi.h"

#define ExportAPI  extern "C" _declspec(dllexport)

//��ʼ����ɺ��ί��
typedef void (__stdcall *OnQuoteProxyCreated)(void);

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
typedef void (__stdcall *OnQuoteHeartBeatWarning)(int nTimeLapse);

//��ɵ�¼֮���ί��
typedef void (__stdcall *OnQuoteRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//�˳���¼֮���ί��
typedef void (__stdcall *OnQuoteRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//����Ӧ��
typedef void (__stdcall *OnQuoteRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//��������Ӧ��
typedef void (__stdcall *OnQuoteRspSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//�˶�����Ӧ��
typedef void (__stdcall *OnQuoteRspUnSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//�յ����ݺ��ί��
typedef void (__stdcall *OnQuoteRtnDepthMarketData)(CThostFtdcDepthMarketDataField *p);

//ע���ʼ����ɺ���¼�
ExportAPI void __stdcall RegOnQuoteProxyCreated(OnQuoteProxyCreated e);

//ע�������¼�
ExportAPI void __stdcall RegOnQuoteHeartBeatWarning(OnQuoteHeartBeatWarning e);

//ע���û���¼֮���¼�
ExportAPI void __stdcall RegOnQuoteRspUserLogin(OnQuoteRspUserLogin e);

//ע���û��ǳ�֮���¼�
ExportAPI void __stdcall RegOnQuoteRspUserLogout(OnQuoteRspUserLogout e);

//ע�������Ӧ���¼�
ExportAPI void __stdcall RegOnQuoteRspError(OnQuoteRspError e);

//ע�ᶩ������֮����¼�
ExportAPI void __stdcall RegOnQuoteRspSubMarketData(OnQuoteRspSubMarketData e);

//ע���˶�����֮����¼�
ExportAPI void __stdcall RegOnQuoteRspUnSubMarketData(OnQuoteRspUnSubMarketData e);

//ע���յ��������ݺ���¼�
ExportAPI void __stdcall RegOnQuoteRtnDepthMarketData(OnQuoteRtnDepthMarketData e);


//ʵ����
ExportAPI void CreateQuoteProxy(char* brokerid,char* userid,char* pwd);

///<summary>
/// ע��ǰ�û���ַ
///</summary>
///<param name="fontaddr">
/// ǰ�û������ַ
/// �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001����
/// ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
///</param>
ExportAPI void RegisterQuoteFront(char* fontaddr);

///<summary>
/// ע�����Ʒ����������ַ
///</summary>
///<param name="nsaddr">
/// �����������ַ
/// @remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
/// @remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
/// @remark RegisterNameServer������RegisterFront
///</param>
ExportAPI void RegisterQuoteNameServer(char* nsaddr);

//API��ʼ��
ExportAPI void QuoteInit();

//��������
ExportAPI void SubscribeMarketData(char* instrumentId);