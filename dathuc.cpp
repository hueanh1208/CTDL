#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct DonThuc{
	float heso;
	int somu;
};
struct node{
	DonThuc donthuc;
	struct node *next;
};
typedef node *PTR;


void Add(PTR &First, DonThuc dt){
	PTR tmp = new node;
	tmp->donthuc = dt;
	if(First==NULL||First->donthuc.somu<dt.somu){
		tmp->next=First;
		First = tmp;
	}
	else{
		PTR p=First;
		while(p->next!=NULL&&p->next->donthuc.somu>=dt.somu){
			p=p->next;
		}
		if(p->donthuc.somu==dt.somu)
			p->donthuc.heso+=dt.heso;
		else{
			tmp->next=p->next;
			p->next=tmp;
		}
	}
	
}

void NhapDaThuc(PTR &First){
	DonThuc dt;
	do{
		cout<<"He so: ";
		cin>>dt.heso;
		cout<<"So mu: ";
		cin>>dt.somu;
		if(dt.somu<0) return;
		Add(First,dt);
	}while(1);
}

void XuatDaThuc(PTR First){
	PTR p=First;
	if(First==NULL) cout<<"\nDa Thuc rong";
	else{
		cout<<p->donthuc.heso<<"X^"<<p->donthuc.somu;
		p=p->next;
	}
	while(p!=NULL){
		if(p->donthuc.heso!=0){
			if(p->donthuc.heso>0)	cout<<"+";
			cout<<p->donthuc.heso;
			if(p->donthuc.somu)	cout<<"X^"<<p->donthuc.somu;
		}
		p=p->next;
	}
}

PTR Nhan2DaThuc(PTR fdt1, PTR fdt2){
	PTR temp;
	DonThuc dt;	
	PTR p1,p2;
	p1 = fdt1;
	while(p1!=NULL){
		p2 = fdt2;
		while(p2!=NULL){
			dt.heso = fdt1->donthuc.heso * fdt2->donthuc.heso;
			dt.somu = fdt1->donthuc.somu + fdt2->donthuc.somu;
			Add(temp,dt);
		}
		p1=p1->next;
	}
	return temp;
}



int main(){
	PTR First = NULL;
	PTR dt1 = NULL;
	PTR dt2 = NULL;
	PTR dt3 = NULL;
	cout<<"Nhap da thuc thu 1: ";
	NhapDaThuc(dt1);
	cout<<"Nhap da thuc thu 2: ";
	NhapDaThuc(dt2);
	cout<<"DT1: "<<endl;
	XuatDaThuc(dt1);
	cout<<"DT2: ";
	XuatDaThuc(dt1);
	
	cout<<"Nhan 2 da thuc: ";
	dt3 = Nhan2DaThuc(dt1,dt2);
	cout<<"ket qua: "<<dt3;
	
}
