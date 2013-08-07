#include "stdafx.h"
#include "string.h"
#include "iostream"

#include "TraderProxy.h"
using namespace std;

CThostFtdcTraderApi* traderApi; 
TraderSpi* traderSpi;
char* traderbrokerId;
char* traderuserId;
char* traderpasswd;

OnTraderProxyCreated traderCreatedInvoke;//����
OnTraderHeartBeatWarning traderHeartBeatInvoke;//����
OnTraderRspAuthenticate traderRspAuthenicateInvoke;//�ͻ�����֤
OnTraderRspUserLogin traderRspUserLoginInvoke;//��¼
OnTraderRspUserLogout traderRspUserLogoutInvoke;//�ǳ�
OnTraderRspUserPasswordUpdate traderRspUserPwdUpdateInvoke;//�û��������
OnTraderRspTradingAccountPasswordUpdate traderRspTradingAccoutPwdUpdateInvoke;//�ʽ��˺ſ������

void TraderSpi::OnFrontConnected(){
	CThostFtdcReqUserLoginField f;
	memset(&f, 0, sizeof(f));
	strcpy_s(f.BrokerID, traderbrokerId);
	strcpy_s(f.UserID, traderuserId);
	strcpy_s(f.Password, traderpasswd);
	traderApi->ReqUserLogin(&f, ++nReq);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse){
	if(traderHeartBeatInvoke != NULL){
		traderHeartBeatInvoke(nTimeLapse);
	}
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserLoginInvoke!=NULL){
		traderRspUserLoginInvoke(pRspUserLogin,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserLogoutInvoke!=NULL){
		traderRspUserLogoutInvoke(pUserLogout,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserPwdUpdateInvoke!=NULL){
		traderRspUserPwdUpdateInvoke(pUserPasswordUpdate,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspTradingAccoutPwdUpdateInvoke != NULL){
		traderRspTradingAccoutPwdUpdateInvoke(pTradingAccountPasswordUpdate,pRspInfo,nRequestID,bIsLast);
	}
}

//ע�ᴴ����ɺ���¼�
ExportAPI void __stdcall RegOnTraderProxyCreated(OnTraderProxyCreated e){
	traderCreatedInvoke=e;
}

///ע�������¼�
ExportAPI void __stdcall RegOnTraderHeartBeatWarning(OnTraderHeartBeatWarning e){
	traderHeartBeatInvoke=e;
}
///ע��ͻ�����֤��Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspAuthenticate(OnTraderRspAuthenticate e){
	traderRspAuthenicateInvoke=e;
}
///ע���¼������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserLogin(OnTraderRspUserLogin e){
	traderRspUserLoginInvoke=e;
}
///ע��ǳ�������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserLogout(OnTraderRspUserLogout e){
	traderRspUserLogoutInvoke=e;
}
///ע���û����������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspUserPasswordUpdate(OnTraderRspUserPasswordUpdate e){
	traderRspUserPwdUpdateInvoke=e;
}
///ע���ʽ��˻��������������Ӧ�¼�
ExportAPI void __stdcall RegOnTraderRspTradingAccountPasswordUpdate(OnTraderRspTradingAccountPasswordUpdate e){
	traderRspTradingAccoutPwdUpdateInvoke=e;
}

//����ʵ��
ExportAPI void CreateTraderProxy(char* brokerid,char* userid,char* pwd){
	traderbrokerId=brokerid;
	traderuserId=userid;
	traderpasswd=pwd;
	traderSpi= new TraderSpi();
	traderApi=CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	traderApi->RegisterSpi((CThostFtdcTraderSpi*)traderSpi);
	if(traderCreatedInvoke!=NULL){
		traderCreatedInvoke();
	}
}
//ע�ύ��ǰ��
ExportAPI void RegisterTraderFront(char* fontaddr){
	traderApi->RegisterFront(fontaddr);
}
//ע�ύ��
ExportAPI void RegisterTraderNameServer(char* fontaddr){
	traderApi->RegisterNameServer(fontaddr);
}
//��ʼ��
ExportAPI void TraderInit(){
	traderApi->Init();
}