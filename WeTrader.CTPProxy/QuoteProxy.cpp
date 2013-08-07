// This is the main DLL file.

#include "stdafx.h"
#include "string.h"
#include "iostream"

#include "QuoteProxy.h"
using namespace std;

CThostFtdcMdApi* md;
QuoteMdSpi* mdSpi;
char* brokerId;
char* userId;
char* passwd;
//�ص��¼�
OnQuoteProxyCreated createdInvoke;
OnQuoteHeartBeatWarning heartBeatInvoke;
OnQuoteRspUserLogin rspUserLoginInvoke;
OnQuoteRspUserLogout rspUserLogoutInvoke;
OnQuoteRspError rspErrorInvoke;
OnQuoteRspSubMarketData rspSubMarketDataInvoke;
OnQuoteRspUnSubMarketData rspUnSubMarketDataInvoke;
OnQuoteRtnDepthMarketData  rtnDepthMarketDataInvoke;

void QuoteMdSpi::OnFrontConnected(){
	CThostFtdcReqUserLoginField f;
	memset(&f, 0, sizeof(f));
	strcpy_s(f.BrokerID, brokerId);
	strcpy_s(f.UserID, userId);
	strcpy_s(f.Password, passwd);
	md->ReqUserLogin(&f, ++nReq);
}
//����
void QuoteMdSpi::OnHeartBeatWarning(int nTimeLapse){
	if(heartBeatInvoke != NULL){
		heartBeatInvoke(nTimeLapse);
	}
}
///��¼������Ӧ
void QuoteMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspUserLoginInvoke!=NULL){
		rspUserLoginInvoke(pRspUserLogin,pRspInfo,nRequestID,bIsLast);
	}
}
///�ǳ�������Ӧ
void QuoteMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspUserLogoutInvoke != NULL){
		rspUserLogoutInvoke(pUserLogout,pRspInfo,nRequestID,bIsLast);
	}
}
///����Ӧ��
void QuoteMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspErrorInvoke != NULL){
		rspErrorInvoke(pRspInfo,nRequestID,bIsLast);
	}
}
///��������Ӧ��
void QuoteMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspSubMarketDataInvoke != NULL){
		rspSubMarketDataInvoke(pSpecificInstrument,pRspInfo,nRequestID,bIsLast);
	}
}
///ȡ����������Ӧ��
void QuoteMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if(rspUnSubMarketDataInvoke != NULL){
		rspUnSubMarketDataInvoke(pSpecificInstrument,pRspInfo,nRequestID,bIsLast);
	}
}
//����������Ӧ
void QuoteMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData){
	if(rtnDepthMarketDataInvoke != NULL){
		rtnDepthMarketDataInvoke(pDepthMarketData);
	}
}

//ע�ᴴ����ɺ���¼�
ExportAPI void __stdcall RegOnQuoteProxyCreated(OnQuoteProxyCreated e){
	createdInvoke=e;
}

//ע�������¼�
ExportAPI void __stdcall RegOnQuoteHeartBeatWarning(OnQuoteHeartBeatWarning e){ heartBeatInvoke = e;}

//ע���û���¼֮���¼�
ExportAPI void __stdcall RegOnQuoteRspUserLogin(OnQuoteRspUserLogin e){ rspUserLoginInvoke = e;}

//ע���û��ǳ�֮���¼�
ExportAPI void __stdcall RegOnQuoteRspUserLogout(OnQuoteRspUserLogout e){ rspUserLogoutInvoke = e;}

//ע�������Ӧ���¼�
ExportAPI void __stdcall RegOnQuoteRspError(OnQuoteRspError e){ rspErrorInvoke = e;}

//ע�ᶩ������֮����¼�
ExportAPI void __stdcall RegOnQuoteRspSubMarketData(OnQuoteRspSubMarketData e){ rspSubMarketDataInvoke = e;}

//ע���˶�����֮����¼�
ExportAPI void __stdcall RegOnQuoteRspUnSubMarketData(OnQuoteRspUnSubMarketData e){rspUnSubMarketDataInvoke = e;}

//ע���յ��������ݺ���¼�
ExportAPI void __stdcall RegOnQuoteRtnDepthMarketData(OnQuoteRtnDepthMarketData e){rtnDepthMarketDataInvoke = e;}

//ʵ����
ExportAPI void CreateQuoteProxy(char* brokerid,char* userid,char* pwd){
	brokerId=brokerid;
	userId=userid;
	passwd=pwd;
	mdSpi = new QuoteMdSpi();
	md=CThostFtdcMdApi::CreateFtdcMdApi("./qlog");
	md->RegisterSpi((CThostFtdcMdSpi*)mdSpi);
	if(createdInvoke != NULL){
		createdInvoke();
	}
}

//ע��ǰ�û�
ExportAPI void RegisterQuoteFront(char* fontaddr){
	md->RegisterFront(fontaddr);
}

//���Ʒ����������ַ
ExportAPI void RegisterQuoteNameServer(char* nsaddr){
	md->RegisterNameServer(nsaddr);
}

//��ʼ��
ExportAPI void QuoteInit(){
	md->Init();
}

//��������
ExportAPI void SubscribeMarketData(char* instrumentId){
	char*ppInst[1];
	ppInst[0]=instrumentId;
	md->SubscribeMarketData(ppInst,1);
}