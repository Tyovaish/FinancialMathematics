#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;
class Annuity{
	private:
	bool annuityDue; 
	int nPer; //Number Of Periods For An Annuity
	int startDate;
	double discountRate; // 
	double growthRate; //
	double pV;
	double payment;
	double fV;
	public:
	Annuity(){
		annuityDue=false;
		startDate=0;
		nPer=0;
		discountRate=0;
		growthRate=0;
		pV=0;
		payment=0;
		fV=0;
	}
	Annuity * setNPer(int nPer){
		this->nPer=nPer;
		return this;
	}
	Annuity * setDiscountRate(double discountRate){
		this->discountRate=discountRate;
		return this;
	}
	Annuity * setGrowthRate(double growthRate){
		this->growthRate=growthRate;
		return this;
	}
	Annuity * setPV(double pV){
		this->pV=pV;
		return this;
	}
	Annuity * setPayment(double payment){
		this->payment=payment;
		return this;
	}
	Annuity * setFV(double fV){
		this->fV=fV;
		return this;
	}
	Annuity * setStartDate(int startDate){
		this->startDate=startDate;
		return this;
	}
	Annuity * isAnnuityDue(){
		this->annuityDue=true;
		return this;
	}
	int getNPer(){
			return nPer;
	}
	double getDiscountRate(){
		return discountRate;
	}
	double getGrowthRate(){
		return growthRate;
	}
	double getStartValue(){
		return pV;
	}
	double getEndValue(){
		return fV;
	}
	double getPayment(){
		return payment;
	}
	int getStartDate(){
			return startDate;
	}
	double getPV(){
		double presentValueOfAnnuity=pV+payment*((1+growthRate)-pow(1/(1+discountRate/100.0),nPer))/((discountRate-growthRate)/100.0)+fV*pow((1/(1+discountRate/100.0)),nPer);
		if(annuityDue){
			double rate;
			if(growthRate>0||growthRate<0){
				rate=growthRate;
			}else {
			rate=discountRate;
			}
			presentValueOfAnnuity=presentValueOfAnnuity*(1+rate/100.0);
		}
		return presentValueOfAnnuity;
	}
	double getPV(int periodEnding){
		double rate;
		if(growthRate>0||growthRate<0){
			rate=growthRate;
		}else {
			rate=discountRate;
		}
		return getPV()*pow((1+rate/100.0),periodEnding);
		
	}
	double getFV(){
		double rate;
		if(growthRate>0||growthRate<0){
			rate=growthRate;
		}else {
			rate=discountRate;
		}
		return getPV()*pow((1+rate/100.0),nPer);
	}
	double getPaymentAmount(){
		return -1*(fV*pow((1/(1+discountRate/100.0)),nPer)+pV)/(((1+growthRate)-pow(1/(1+discountRate/100.0),nPer))/((discountRate-growthRate)/100.0));
	}
	void clear()
	{
		annuityDue=false;
		nPer=0;
		discountRate=0;
		pV=0;
		payment=0;
		growthRate=0;
		fV=0;
	}	
};

class CashFlow{
	public:
	int currentTime;
	double discountRate;
	double growthRate;
	vector<double> cashFlow;
	CashFlow(){
		currentTime=0;
		discountRate=0;
		growthRate=0;
	}
	CashFlow * setDiscountRate(double discountRate){
		this->discountRate=discountRate;
		return this;
	}
	CashFlow * setGrowthRate(double growthRate){
		this->growthRate=growthRate;
		return this;
	}
	CashFlow * addCashFlow(double cashInflow,int freq){
		for(int i=0;i<freq;i++){
			cashFlow.push_back(cashInflow);
		}
		return this;
	}
	CashFlow * addCashFlow(double cashInflow,int freq,int increment){
		for(int i=0;i<freq;i++){
			cashFlow.push_back(cashInflow+increment*i);
		}
		return this;
	}
	void setCashFlowAt(double cashInflow,int timePeriod){
		if(timePeriod>=cashFlow.size()){
			for(int i=cashFlow.size();i<=timePeriod;i++){
				cashFlow.push_back(0);
			}
		}
		cashFlow[timePeriod]=cashInflow;
	}
	int getCashFlowLength(){
		return cashFlow.size()-1;
	}
	double getCashFlowAt(int timePeriod){
		if(timePeriod>=cashFlow.size()){
			return 0;
		}
		return cashFlow[timePeriod];
	}
	double getNPV(){
		double npV=0;
		for(int i=0;i<cashFlow.size();i++){
			npV+=cashFlow[i]*pow(1/(1+discountRate/100.0),i);
		}
		return npV;
	}
	double getNFV(){
			double rate=0;
		if(growthRate>0||growthRate<0){
			rate=growthRate;
		}else {
			rate=discountRate;
		}
		return getNPV()*pow((1+rate/100.0),cashFlow.size());
	}
	double getMIRR(){
		double positiveNFV=0;
		double negativeNPV=0;
		for(int i=0;i<cashFlow.size();i++){
			if(cashFlow[i]<0){
				negativeNPV+=cashFlow[i]*pow(1/(1+discountRate/100.0),i);
			} else {
				positiveNFV+=cashFlow[i]*pow(1+growthRate/100.0,cashFlow.size()-i);
			}
		}
		double nPV;
			for(double i=0.01;i<1000;i+=.01){
				nPV=negativeNPV+positiveNFV*pow(1/(1+i/100.0),cashFlow.size());
				if(nPV<0){
					return i;
				}
			}
		return -1;
	}
	double getIRR(){
		double savedDiscountRate=discountRate;
		double nPV;
			for(double i=0.01;i<1000;i+=.01){
				discountRate=i;
				nPV=getNPV();
				if(nPV<0){
					return i;
				}
			}
			discountRate=savedDiscountRate;
		return -1;
		
	}
	double getPI(){
		return -1*getNPV()/cashFlow[0];
	}
	void print(){
		for(int i=0;i<cashFlow.size();i++){
			cout<<i<<". "<<cashFlow[i]<<endl;
		}
	}
	//TODO ADD a clearing function
};
class Bond{
	public:
	int nPer;
	int paymentsPerYear;
	double couponRate;
	double couponValue;
	double purchasePrice;
	double discountRate;
	Annuity * bondAnnuity;
	Bond(){
		nPer=-1;
		paymentsPerYear=-1;
		couponRate=-1;
		couponValue=-1;
		discountRate=-1;
		bondAnnuity=NULL;
	}
	Bond * setNPer(int nPer ){
		this->nPer=nPer;
		return this;
	}
	Bond * setPaymentsPerYear(char typeOfBond){
		switch(typeOfBond){
			case 'z': paymentsPerYear=0;
					break;
			case 'm': paymentsPerYear=12;
					break;
			case 'q': paymentsPerYear=4;
					break;
			case 's': paymentsPerYear=2;
					break;
			default: paymentsPerYear=1;
					break;
		}
	}
	Bond * setCouponRate(double couponRate){
		this->couponRate=couponRate;
		return this;
	}
	Bond * setDiscountRate(double discountRate){
		this->discountRate=discountRate;
		return this;
	}
	Bond * setCouponValue(double couponValue){
		this->couponValue=couponValue;
		return this;
	}
	Bond * setPurchasePrice(double purchasePrice){
		this->purchasePrice=purchasePrice;
		return this;
	}
	Bond * setBondAnnuity(){
		if(nPer==-1||paymentsPerYear==-1||couponValue==-1||discountRate==-1){
			cout<<"Could not create bond"<<endl;
			return this;
		}
		bondAnnuity=new Annuity();
		bondAnnuity->setNPer(nPer*paymentsPerYear)->setDiscountRate(discountRate/paymentsPerYear)->setPayment(couponValue*(couponRate)/100/paymentsPerYear)->setPV(0)->setFV(couponValue);
	}
double getCurrentValue(){
		return bondAnnuity->getPV();
	}
};

class Asset{
	CashFlow * cashFlow;
	double discountRate;
	public:
	Asset(){
		cashFlow=new CashFlow();
	}
	Asset * setCashInFlow(double amount,int periodEnding){
		cashFlow->setCashFlowAt(amount,periodEnding);
		return this;
	}
	Asset * setDiscountRate(double discountRate){
		this->discountRate=discountRate;
		cashFlow->setDiscountRate(discountRate);
		return this;
	}
	double getCashInFlowAt(int timePeriod){
			return cashFlow->getCashFlowAt(timePeriod);
	}
	int getCashFlowLength(){
		return cashFlow->getCashFlowLength();
	}
	double getPV(){
		return cashFlow->getNPV();
	}
	void print(){
		cashFlow->print();
	}
};
class Liability{
	private:
	CashFlow * cashFlow;
	double discountRate;
	public:
	Liability(){
		cashFlow=new CashFlow();
		discountRate=0;
	}
	Liability * setCashOutFlow(double amount,int periodEnding){
		cashFlow->setCashFlowAt(-1*amount,periodEnding);
		return this;
	}
	Liability * setDiscountRate(double discountRate){
		this->discountRate=discountRate;
		cashFlow->setDiscountRate(discountRate);
		return this;
	}
	double getCashOutFlowAt(int timePeriod){
			return cashFlow->getCashFlowAt(timePeriod);
	}
	int getCashFlowLength(){
		return cashFlow->getCashFlowLength();
	}
	double getPV(){
		return cashFlow->getNPV();
	}
	void print(){
		cashFlow->print();
	}
};
//TODO: ADD a Bond Portfolio Class
class BondPortfolio{};
//TODO: ADD a Stock Portfolio Class
class StockPortfolio{};
//TODO: ADD a Mortgage Class()
//TODO: ADD A Portfolio Class
class Portfolio{
	StockPortfolio * stockPortfolio;
	BondPortfolio * bondPortfolio;
	vector<Asset *> assets;
	vector<Liability *> liabilities;
	public:
	Portfolio(){};
	Portfolio * addAsset(Asset * currentAsset){
		assets.push_back(currentAsset);
		return this;
	}
	Portfolio * addLiability(Liability * currentLiability){
		liabilities.push_back(currentLiability);
		return this;
	}
	void printData(){
		int maxLength;
		if(!assets.empty()){
		maxLength=assets[0]->getCashFlowLength();
		} else if(!liabilities.empty()){
		maxLength=liabilities[0]->getCashFlowLength();
		} else {
			maxLength=0;
		}
		for(int i=0;i<assets.size();i++){
			int currentCashFlowLength=assets[i]->getCashFlowLength();
			if(maxLength<currentCashFlowLength){
				maxLength=currentCashFlowLength;
			}
		}
		for(int i=0;i<liabilities.size();i++){
			int currentCashFlowLength=liabilities[i]->getCashFlowLength();
			if(maxLength<currentCashFlowLength){
				maxLength=currentCashFlowLength;
			}
		}
		cout<<"Cash Flow Time Table"<<endl;
		cout<<"Time Period"<<endl;
		for(int i=0;i<=maxLength;i++){
			cout<<"\t\t"<<i;
		}
		cout<<"\n";
		cout<<"Assets"<<endl;
		for(int i=0;i<assets.size();i++){
			for(int j=0;j<=maxLength;j++){
				cout<<"\t\t"<<assets[i]->getCashInFlowAt(j);
			}
			cout<<"\n\n";
		}
		cout<<"Liabilities";
		cout<<"\n";
		for(int i=0;i<liabilities.size();i++){
			for(int j=0;j<=maxLength;j++){
				cout<<"\t\t"<<liabilities[i]->getCashOutFlowAt(j);
			}
			cout<<"\n\n";
		}
		cout<<"Totals\n";
		for(int i=0;i<=maxLength;i++){
			double assetInFlowSum=0;
			double liabilityOutFlowSum=0;
			for(int j=0;j<assets.size();j++){
				assetInFlowSum+=assets[j]->getCashInFlowAt(i);
			}
			for(int j=0;j<liabilities.size();j++){
				liabilityOutFlowSum+=liabilities[j]->getCashOutFlowAt(i);
			}
			cout<<"\t\t"<<assetInFlowSum+liabilityOutFlowSum;
		}
		cout<<"\n\n";
		
		cout<<"Present Value Of Portfolio";
		cout<<"\n";
		double totalPresentValueAssets=0;
		double totalPresentValueLiabilities=0;
			for(int j=0;j<assets.size();j++){
				totalPresentValueAssets+=assets[j]->getPV();
			}
			for(int j=0;j<liabilities.size();j++){
				totalPresentValueLiabilities+=liabilities[j]->getPV();
			}
		cout<<totalPresentValueAssets+totalPresentValueLiabilities<<endl;
	}
};
