#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;

/*Matrix class not completed
class Matrix{
	public:
	double ** matrix;
	int xLength;
	int yLength;
	Matrix(int n, int m){
		xLength=n;
		yLength=m;
		matrix=new double *[n];
		for(int i=0;i<n;i++){
			matrix[i]=new double[m];
			for(int j=0;j<m;j++){
				matrix[i][j]=0;
			}
		}
	}
	Matrix * addData(double data,int xPosition,int yPosition){
		if(xPosition>=xLength||xPosition<0||yPosition>=yLength||yPosition<0){
			cout<<"Could not add Data, outside of bounds"<<endl;
			return this;
		}
		matrix[xPosition][yPosition]=data;
		return this;
	}
	Matrix * addData(double * data,int xPosition){
		if(xPosition>=xLength||xPosition<0){
			cout<<"Could not add Data, outside of bounds"<<endl;
			return this;
		}
		for(int i=0;i<sizeof(data);i++){
			matrix[xPosition][i]=data[i];
		}
		return this;
	}
	Matrix * transpose(){
		Matrix * transposedMatrix=new Matrix(yLength,xLength);
		for(int i=0;i<xLength;i++){
			for(int j=0;j<yLength;j++){
				transposedMatrix->matrix[j][i]=matrix[i][j];
			}
		}
		return transposedMatrix;
	}
	Matrix * multiply(Matrix * matrixB){
		if(yLength!=matrixB->xLength){
			cout<<"INVALID DIMENSIONS FOR MULTIPLICATION"<<endl;
			return this;
		}
		Matrix * multipliedMatrix= new Matrix(xLength,matrixB->yLength);
	for(int k=0;k<matrixB->yLength;k++){
		for(int i=0;i<xLength;i++){
			int rowValue=0;
			for(int j=0;j<yLength;j++){
				rowValue+=matrix[i][j]*matrixB->matrix[j][k];
			}
			multipliedMatrix->addData(rowValue,i,k);
		}
	}
		return multipliedMatrix;
	}
	//TODO: MAKE AN INVERSE FUNCTION FOR A MATRIX
	Matrix * inverse(){
		
	}
	
	void print(){
		for(int i=0;i<xLength;i++){
			for(int j=0;j<yLength;j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<"\n";
		}
		
	}

};*/



class Annuity{
	public:
	bool annuityDue; 
	int nPer; //Number Of Periods For An Annuity
	double discountRate; // 
	double growthRate; //
	double pV;
	double payment;
	double fV;
	Annuity(){
		annuityDue=false;
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
	Annuity * isAnnuityDue(){
		this->annuityDue=true;
		return this;
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
	void setCashFlow(double cashInflow,int timePeriod){
		if(timePeriod>=cashFlow.size()){
			cout<<"Could Not Add CashFlow"<<endl;
			return;
		}
		cashFlow[timePeriod]=cashInflow;
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
	void printCashFlows(){
		for(int i=0;i<cashFlow.size();i++){
			cout<<i+1<<". "<<cashFlow[i]<<endl;
		}
	}
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

int main(){
	Bond * b=new Bond();
	b->setNPer(10)->setCouponRate(20)->setDiscountRate(30)->setCouponValue(100)->setPaymentsPerYear('q')->setBondAnnuity();
	cout<<b->getCurrentValue()<<endl;
	};