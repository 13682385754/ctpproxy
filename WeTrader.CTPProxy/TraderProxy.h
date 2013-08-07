#pragma once
#include "TraderSpi.h"

#define ExportAPI  extern "C" _declspec(dllexport)

///��ʼ����ɺ��ί��
typedef void (__stdcall *OnTraderProxyCreated)(void);
///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
typedef void (__stdcall *OnTraderHeartBeatWarning)(int nTimeLapse);
///�ͻ�����֤��Ӧ
typedef void (__stdcall *OnTraderRspAuthenticate)(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��¼������Ӧ
typedef void (__stdcall *OnTraderRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//�ǳ�������Ӧ
typedef void (__stdcall *OnTraderRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//�û��������������Ӧ
typedef void (__stdcall *OnTraderRspUserPasswordUpdate)(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//�ʽ��˻��������������Ӧ
typedef void (__stdcall *OnTraderRspTradingAccountPasswordUpdate)(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


///ע���ʼ����ɺ���¼�
ExportAPI void __stdcall RegOnTraderProxyCreated(OnTraderProxyCreated e);
///ע�������¼�
ExportAPI void __stdcall RegOnTraderHeartBeatWarning(OnTraderHeartBeatWarning e);
///ע��ͻ�����֤��Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspAuthenticate(OnTraderRspAuthenticate e);
///ע���¼������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserLogin(OnTraderRspUserLogin e);
///ע��ǳ�������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserLogout(OnTraderRspUserLogout e);
///ע���û����������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserPasswordUpdate(OnTraderRspUserPasswordUpdate e);
///ע���ʽ��˻��������������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspTradingAccountPasswordUpdate(OnTraderRspTradingAccountPasswordUpdate e);

//����ʵ��
ExportAPI void CreateTraderProxy(char* brokerid,char* userid,char* pwd);
//ע�ύ��ǰ��
ExportAPI void RegisterTraderFront(char* fontaddr);
//ע�ύ��
ExportAPI void RegisterTraderNameServer(char* fontaddr);
//��ʼ��
ExportAPI void TraderInit();