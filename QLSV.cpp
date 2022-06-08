#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <mylib.h>
#include <string>
#include <iostream>
#include <fstream>

#define MAXLOPTINCHI 100000

using namespace std;

//=============================== DS MON HOC CAY NHI PHAN TIM KIEM =====================
struct MONHOC{
	char MAMH[10];
	char TENMN[35];
	int STCLT;
	int STCTH; 
};

struct nodeMH{
	MONHOC mh;
	nodeMH *left;
	nodeMH *right;
};

typedef nodeMH *PTRMH;


//=============================== SINH VIEN DS LIEN KET DON ============================

struct SinhVien{
	char MASV[15];
	char HO[30];
	char TEN[10];
	char SDT[12];
	char PHAI[4];
	char MALOP[15];
};

struct nodeSV {
	SinhVien sv;
	nodeSV* next;
};

typedef nodeSV* PTRSV;
        
//============================ DANG KY DS LIEN KET DON =======================
struct DangKy {
	char MASV[15];
	float DIEM;
	boolean HUYDANGKY = false;	
};

struct nodeDangKy {
	DangKy dangky;
	nodeDangKy* next;
};

typedef nodeDangKy* PTRDK;


// LOP TIN CHI DS TUYEN TINH MANG CON TRO

struct LopTinChi{
	int MALOPTC;
	char MAMH[10];
	char NIENKHOA[10];
	int HOCKY;
	int NHOM;
	int SOSVMIN;
	int SOSVMAX;
	
	boolean HUYLOP = false;
	PTRDK First_DSSVDK = NULL;
};

struct LIST_LTC {
	int soluong = 0;
	LopTinChi *nodesltc[MAXLOPTINCHI];
};

// =========================== END KHAI BAO ========================

int XacNhan (char *S){
	cout<<S;
	char kt;
	do{
		kt=toupper(getch());
	}while(kt!='Y'&&kt!='N');
	cout<<kt;
	return kt=='Y';
}

int DK_Reccount(PTRDK &FirstDK);
void DK_Insert_last(PTRDK &FirstDK, DangKy dk);

//==========================MON HOC=================

// tim kiem mon hoc 
PTRMH Search_MonHoc(PTRMH root, char *x)
{
   PTRMH p;
   p = root;
   while(p != NULL && stricmp(p->mh.MAMH,x)!=0)
     if(stricmp(p->mh.MAMH,x)<0)
         p = p->left;
      else
         p = p->right;
return(p); 
}

// them node mon hoc vao cay nhi phan
void Insert_MonHoc(PTRMH &p, MONHOC mh)
{ 
   if(p == NULL)    // nut p hien tai se la nut la
   {
     p = new nodeMH;
     p->mh = mh;
     p->left = NULL;     p->right = NULL;  
   }
   else
    if(stricmp(p->mh.MAMH,mh.MAMH)<0)
    	Insert_MonHoc(p->left, mh);
    else if(stricmp(p->mh.MAMH,mh.MAMH)>0)
		Insert_MonHoc(p->right, mh);
}

// Tao cay mon hoc 
void Create_MONHOC(PTRMH &root)
{ MONHOC mh;
	PTRMH temp;
  	while(1){
	 
  	fflush(stdin);
  	cout<<"Nhap ma mon hoc: ";
  	gets(mh.MAMH);
  	if(strcmp(mh.MAMH,"0")==0) break;
  	temp=Search_MonHoc(root,mh.MAMH);
  	if(temp!=NULL) {
  		cout<<"Ma bi trung\n";
  		continue;
	  }
  	cout<<"Nhap ten mon hoc: ";
  	gets(mh.TENMN);
  	cout<<"Nhap so tin chi ly thuyet: ";
    cin >> mh.STCLT;
    cout<<"Nhap so tin chi thuc hanh: ";
    cin >> mh.STCTH;
        
    Insert_MonHoc(root,mh);
     
    }
}


//Show NLR
void Show_MonHoc(PTRMH root)
{

   if (root != NULL) 
   {
      printf("\n   %10s  %-15s %-8d %8d"   , root->mh.MAMH, root->mh.TENMN,root->mh.STCLT,root->mh.STCTH);
      Show_MonHoc(root->left);
      Show_MonHoc(root->right);
   }
}

// dem tong so nut cua cay mon hoc
void SoNut_MonHoc(PTRMH &root, int &sl)
{

   if (root != NULL) 
   {
      sl++;
      SoNut_MonHoc(root->left,sl);
      SoNut_MonHoc(root->right,sl);
   }
}

// duyet cay ghi vao file 
void traverseWriteToFile(PTRMH root,ofstream &outfile){
	MONHOC mh;
	if(root != NULL){
		outfile<<root->mh.MAMH<<endl;
		outfile<<root->mh.TENMN<<endl;
		outfile<<root->mh.STCLT<<endl;
		outfile<<root->mh.STCTH<<endl;
		traverseWriteToFile(root->left, outfile);
		traverseWriteToFile(root->right, outfile);
	}
}

// ghi file mon hoc
void ghiFileMonHoc(PTRMH &root){
	ofstream outfile;
	outfile.open("MonHoc.txt");
	int slmh =0;
	SoNut_MonHoc(root,slmh);
	outfile<<slmh<<endl;
	traverseWriteToFile(root,outfile);
	outfile.close();
}

// doc file mon hoc 
void docFileMonHoc(PTRMH &root){
	MONHOC mh;
	ifstream filein;
	root = NULL;
	filein.open("MonHoc.txt",ios::in);
	int slmh;
	filein>>slmh;
	filein.ignore();
	for(int i =0; i<slmh; i++){
		filein.getline(mh.MAMH , 10);
		filein.getline(mh.TENMN,35);
		filein>>mh.STCLT;
		filein.ignore();
		filein>>mh.STCTH;
		filein.ignore();
		cout<<"Doc file thanh cong"<<mh.MAMH;
		getch(); 
		Insert_MonHoc(root, mh);	
	}
	filein.close();
	
}

//==========================LOP TIN CHI========================


// ma LTC tu dong tang 
int maTuDongTang(LIST_LTC &list_ltc){
	if(list_ltc.soluong==0) return 1; 
	return list_ltc.nodesltc[list_ltc.soluong-1]->MALOPTC+1;
}

// search ltc theo ma
int LTC_Search_theoma(LIST_LTC list_ltc, int x)
{
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	     if (list_ltc.nodesltc[i]->MALOPTC == x) return i;
	return -1;
}


// tao lop tin chi
int Create_LTC(LIST_LTC &list_ltc, LopTinChi &ltc){	
	cout<<"Nhap thong tin lop tin chi\n";
	ltc.MALOPTC=maTuDongTang(list_ltc); fflush(stdin);
	cout<<"Nhap Ma mon hoc: ";
	gets(ltc.MAMH);
	if(stricmp(ltc.MAMH,"0")==0) return 0;
	cout<<"Nhap Nien khoa: "; fflush(stdin);
	gets(ltc.NIENKHOA);
	cout<<"Nhap Hoc ki: ";
	cin>>ltc.HOCKY;
	cout<<"Nhap Nhom: ";
	cin>>ltc.NHOM;
	cout<<"Nhap so sinh vien min: ";
	cin>>ltc.SOSVMIN;
	cout<<"Nhap so sinh vien max: ";
	cin>>ltc.SOSVMAX;
	ltc.HUYLOP = false;
	ltc.First_DSSVDK=NULL;
	fflush(stdin);
	return 1;
}

// tao danh sach lop tin chi
// them lop tin chi
void Create_List_LTC(LIST_LTC &list_ltc){
	LopTinChi ltc;
	
	while(list_ltc.soluong<MAXLOPTINCHI){
		if (Create_LTC(list_ltc, ltc)==0)    
		   return;
		list_ltc.nodesltc[list_ltc.soluong] = new LopTinChi;
		//gan gia tri lop tin chi them vao vao con tro lop tin chi cuoi mang
		*list_ltc.nodesltc[list_ltc.soluong] = ltc;
		list_ltc.soluong +=1;
	}
}

void LTC_Insert(LIST_LTC &list_ltc, LopTinChi ltc){
	list_ltc.nodesltc[list_ltc.soluong]=new LopTinChi;
	*list_ltc.nodesltc[list_ltc.soluong]=ltc;
	list_ltc.soluong +=1;
}

// duyet danh sach lop tin chi 
void duyetDS_LTC(LIST_LTC &list_ltc){
	printf ("                     DANH SACH LOP TIN CHI \n");
 	printf ("  Stt   Ma lop   Ma mon   Nhom   Nien khoa     Hoc Ky    So sv max     So sv min   \n");
	for (int i =0 ; i < list_ltc.soluong ; i++)
  		printf ("%8d %5d  %-10s  %-8d  %10s  %5d  %5d   %5d    \n", 
		  i+1,
		  list_ltc.nodesltc[i]->MALOPTC,
		  list_ltc.nodesltc[i]->MAMH,
		  list_ltc.nodesltc[i]->NHOM,
		  list_ltc.nodesltc[i]->NIENKHOA,
		  list_ltc.nodesltc[i]->HOCKY,
		  list_ltc.nodesltc[i]->SOSVMAX,
		  list_ltc.nodesltc[i]->SOSVMIN);
 	getch();
}

int LTC_Empty(LIST_LTC &list_ltc)
{     return(list_ltc.soluong == 0 ? 1 : 0);
}

// xoa LTC theo ma
void LTC_Delete_theoma (LIST_LTC &list_ltc)
{	int i;
	cout<<"Nhap ma lop tin chi muon xoa: ";
	cin>>i;
	int j;
	int temp;
	if(i <= 0 || i > list_ltc.soluong)
		printf("Vi tri xoa khong phu hop.");
	else
		if(LTC_Empty(list_ltc))
			printf("Danh sach khong co phan tu.");
		else
		{
			for(j = i;  j< list_ltc.soluong ; j++)
				list_ltc.nodesltc[j-1] = list_ltc.nodesltc[j];
			list_ltc.soluong--;
		}
}

//
int LTC_Sua_theoma(LIST_LTC &list_ltc){
	char x[10];
	int temp;
	int maltc;
	cout<<"Nhap ma lop tin chi muon sua: ";
	cin>>maltc;
	int vitri=LTC_Search_theoma(list_ltc,maltc);
	if(vitri==-1) cout<<"Khong tim thay.";
	else{
		printf ("   Ma lop   Ma mon   Nhom   Nien khoa     Hoc Ky    So sv max     So sv min   \n");
  		printf (" %5d  %-10s  %-8d  %10s  %5d  %5d   %5d    \n", 
	  		list_ltc.nodesltc[vitri]->MALOPTC,
	  		list_ltc.nodesltc[vitri]->MAMH,
	  		list_ltc.nodesltc[vitri]->NHOM,
	  		list_ltc.nodesltc[vitri]->NIENKHOA,
	  		list_ltc.nodesltc[vitri]->HOCKY,
	  		list_ltc.nodesltc[vitri]->SOSVMAX,
	  		list_ltc.nodesltc[vitri]->SOSVMIN);
	  	cout<<"Nhap Ma mon hoc: ";	fflush(stdin);
		gets(list_ltc.nodesltc[vitri]->MAMH);
		//if(stricmp(x,"0")!=0) list_ltc.nodesltc[vitri]->MAMH=x;
		//=============can bat loi nhap ma mon hoc =========//
	  	cout<<"Nhap Nien khoa: "; fflush(stdin);
		gets(list_ltc.nodesltc[vitri]->NIENKHOA);
		//if(stricmp(x,"0")==0)	list_ltc.nodesltc[vitri]->NIENKHOA=x;
		cout<<"Nhap Hoc ki: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->HOCKY=temp;
		cout<<"Nhap Nhom: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->NHOM=temp;
		cout<<"Nhap so sinh vien min: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->SOSVMIN=temp;
		cout<<"Nhap so sinh vien max: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->SOSVMAX=temp;
	}
	
 	getch();
}




// ghi file lop tin chi
void LTC_ghiFile(LIST_LTC &list_ltc){
	PTRDK p;
	ofstream outfile;
	outfile.open("LopTinChi.txt");
	outfile<<list_ltc.soluong<<endl;	//ghi so luong lop
	for(int i=0; i<list_ltc.soluong;i++){
		outfile<<list_ltc.nodesltc[i]->MALOPTC<<endl;
		outfile<<list_ltc.nodesltc[i]->MAMH<<endl;
		outfile<<list_ltc.nodesltc[i]->NHOM<<endl;
		outfile<<list_ltc.nodesltc[i]->HOCKY<<endl;
		outfile<<list_ltc.nodesltc[i]->NIENKHOA<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMIN<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMAX<<endl;
		if(list_ltc.nodesltc[i]->HUYLOP==true)
		outfile<<1<<endl;
		else outfile<<0<<endl;
		int slsv=DK_Reccount(list_ltc.nodesltc[i]->First_DSSVDK);	//ghi so luong sinh vien cua lop
		outfile<<slsv<<endl;
		p=list_ltc.nodesltc[i]->First_DSSVDK;
		while(p!=NULL){
			outfile<<p->dangky.MASV<<endl;
			outfile<<p->dangky.DIEM<<endl;
			if(p->dangky.HUYDANGKY==true)
			outfile<<1<<endl;
			else outfile<<0<<endl;
			
			p=p->next;	
		}
	}
	outfile.close();
}



void LTC_docFile(LIST_LTC &list_ltc){
	LopTinChi ltc;
	DangKy dk;
	ifstream filein;
	int slsv,slltc;
	list_ltc.soluong=0;
	filein.open("LopTinChi.txt",ios::in);
	filein>>slltc;
	filein.ignore();
	for(int i =0; i<slltc; i++){
		filein>>ltc.MALOPTC;
		filein.ignore();
		filein.getline(ltc.MAMH, 10);
		filein>>ltc.NHOM;
		filein.ignore();
		filein>>ltc.HOCKY;
		filein.ignore();
		filein.getline(ltc.NIENKHOA,10);
		filein>>ltc.SOSVMIN;
		filein.ignore();
		filein>>ltc.SOSVMAX;
		filein.ignore();
		int kt;
		filein>>kt;
		filein.ignore();
		if(kt==1)	ltc.HUYLOP=true;
		else	ltc.HUYLOP=false;
		filein>>slsv;
		filein.ignore();
		ltc.First_DSSVDK=NULL;
		for(int j=0; j<slsv;j++){
			filein.getline(dk.MASV,15);
			filein>>dk.DIEM;
			filein.ignore();
			filein>>kt;
			filein.ignore();
			if(kt==1)	dk.HUYDANGKY=true;
			else	dk.HUYDANGKY=false;
			DK_Insert_last(ltc.First_DSSVDK,dk);
		}
		LTC_Insert(list_ltc, ltc);
		
		getch(); 	
	}
	cout<<"\nDoc file thanh cong";
	filein.close();
	
}


// =============================== SINH VIEN ======================================
// CLEAR DANH SACH SINH VIEN
void SV_clearlist(PTRSV &First)
{
   PTRSV p;   
   p = First;
   while(First != NULL)
   {
      p = First;
      First = First->next;
      delete p;
   }
}

//TIM SV THEO ....
PTRSV SV_search_infosv(PTRSV First, char *x){
	PTRSV p;
	for(p=First; p!= NULL; p=p->next){
		if(stricmp(p->sv.MASV,x)==0)
		return p;
	}
	return NULL;
}

//KHOI TAO DANH SACH SINH VIEN
void SV_Create_DSSV(PTRSV &First)
{ 
	PTRSV Last,p, temp;
    SinhVien sv;

    char maso[15],c;
	  	
    
  do
  {
  		printf("Ma so sinh vien: ");
		gets(sv.MASV);
		if(stricmp(sv.MASV,"0")==0) return;
		temp=SV_search_infosv(First,sv.MASV);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: ");
		gets(sv.HO);
		printf("Ten sinh vien: ");
		gets(sv.TEN);
		cout<<"Ma lop: ";
		gets(sv.MALOP);
		cout<<"Phai: ";
		gets(sv.PHAI);
		cout<<"So dien thoai: ";
		gets(sv.SDT);
		fflush(stdin);
		
		p = new nodeSV; //New_node();
		p->sv=sv;
		
		if (First==NULL)
		  First=p;
		else 
		 {
		  for (Last = First ; Last->next !=NULL;Last=Last->next);
		  Last->next = p;
		 }
		
		p->next=NULL;
	}while(1);
}

// duyet DS SINH VIEN
void SV_traverse(PTRSV First)
{
   PTRSV p;
   int stt = 0;
   p = First; 
   if(p == NULL){
   	printf("\n   (Khong co sinh vien trong danh sach)");
   	getche();
   	return;
   }
      
   printf("\n       Danh sach sinh vien: ");
   printf("\n     STT       MSSV       HO           TEN            MA LOP          PHAI            SDT");
   while(p != NULL)
   {
      printf("\n   %5d %10s  %-15s %-10s %15s %5s %15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.MALOP, p->sv.PHAI, p->sv.SDT);
      p = p->next;
   }
   getche();
}



void SV_Insert_last(PTRSV &FirstSV, SinhVien x){
	PTRSV tmp = new nodeSV;
	tmp->sv = x;
	
	if(FirstSV==NULL){
		tmp->next = FirstSV;
		FirstSV = tmp;
	} 
		
	else 
	{
	  PTRSV p = FirstSV;
	  while(p->next!=NULL)
			p = p->next;
	
	   p->next = tmp;
	   tmp->next=NULL;
}
    
}

//luu file SV
int SV_SaveFile (PTRSV &FirstSV) {
	FILE *f = fopen ("SinhVien.txt", "wb");
	if (f==NULL) return 0;
	for (PTRSV p=FirstSV ; p!=NULL ; p=p->next)
	  fwrite (&p->sv, sizeof (SinhVien), 1, f);
	fclose (f);
	cout<<"Da luu file";
	getche();
	return 1;  
}

//mo file SV 
int SV_OpenFile (PTRSV &FirstSV) {
	PTRSV p;  SinhVien sv ;
	FILE *f = fopen ("SinhVien.txt", "rb");
	if (f==NULL) 
	  return 0; // mo file khong duoc
	SV_clearlist(FirstSV);
	while  (fread (&sv, sizeof (SinhVien), 1, f)== 1 ){
		SV_Insert_last (FirstSV , sv);
	} 
	fclose (f);
	cout<<"Mo file thanh cong";
	getche();
	return 1;  
}





//===============DS DANG KY================//

int DK_Reccount(PTRDK &FirstDK){
	PTRDK p;
	int tong = 0;
	for(p=FirstDK; p!=NULL; p=p->next){
		++tong;
	}
	return tong;
}

void DK_Insert_last(PTRDK &FirstDK,DangKy dk){
	PTRDK tmp = new nodeDangKy;
	tmp->dangky= dk;
	
	if(FirstDK==NULL){
		tmp->next = FirstDK;
		FirstDK = tmp;
	} 	
	else 
	{
	  PTRDK p = FirstDK;
	  while(p->next!=NULL)
			p = p->next;
	
	   p->next = tmp;
	   tmp->next=NULL;
	}
    
}

PTRDK DK_search_info_masv(PTRDK First, char *x){
	PTRDK p;
	for(p=First; p!= NULL; p=p->next){
		if(stricmp(p->dangky.MASV,x)==0)
		return p;
	}
	return NULL;
}

void DK_Nhap_SV(LIST_LTC &list_ltc, PTRSV &FirstSV){
	PTRDK Last,p, tempdk;
	PTRSV tempsv;
  	DangKy dk; 
  	int malop;
  	cout<<"Nhap ma lop muon nhap sinh vien: ";
  	cin>>malop;
  	int vitri = LTC_Search_theoma(list_ltc,malop);
  	cout<<"\tNhap sinh vien";
  do
  {
  		printf("Ma so sinh vien: "); fflush(stdin);
		gets(dk.MASV);
		if(stricmp(dk.MASV,"0")==0) return;
		tempsv=SV_search_infosv(FirstSV,dk.MASV);
		if(tempsv==NULL)	{
			cout<<"\nKhong ton tai sinh vien nay\n";
			continue;	
		}
		tempdk=DK_search_info_masv(list_ltc.nodesltc[vitri]->First_DSSVDK,dk.MASV);
		if(tempdk!=NULL){
			cout<<"\nSinh vien da dang ky.";
			continue;
		}
		dk.DIEM = 0;
		p= new nodeDangKy; //New_node();
		p->dangky=dk;
		if (list_ltc.nodesltc[vitri]->First_DSSVDK==NULL)
		  list_ltc.nodesltc[vitri]->First_DSSVDK=p;
		else 
		 {
		  for (Last = list_ltc.nodesltc[vitri]->First_DSSVDK ; Last->next !=NULL;Last=Last->next);
		  Last->next = p;
		 }
		
		p->next=NULL;
	}while(1);
}

int DK_traverse(LIST_LTC &list_ltc, PTRSV &FirstSV)
{
	int malop;
  	cout<<"Nhap ma lop muon xem: ";
  	cin>>malop;
  	int vitri = LTC_Search_theoma(list_ltc,malop);
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->First_DSSVDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return -1;
   }
      
   	printf("\n       Danh sach lop: ");
   	printf("\n     STT       MSSV       HO           TEN            DIEM");
   	while(p != NULL)
   	{
   		
   		PTRSV tempsv = SV_search_infosv(FirstSV,p->dangky.MASV);
   		
      printf("\n   %5d %10s  %-15s %-10s %15d"   , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,p->dangky.DIEM);
      p = p->next;
   	}
   getche();
   return vitri;
}

PTRDK DK_Search_SV_thuocDSLTC(LIST_LTC &list_ltc, int vitri, char * x){
	PTRDK p;
	for(p=list_ltc.nodesltc[vitri]->First_DSSVDK; p!= NULL; p=p->next){
		if(stricmp(p->dangky.MASV,x)==0)
		return p;
	}
	return NULL;
}

void DK_Delete_First(PTRDK &FirstDK){
	PTRDK p;
	p=FirstDK;
	FirstDK=p->next;
	delete p;
}
void DK_Delete_After(PTRDK p){
	PTRDK q;
	// neu p la NULL hoac p chi nut cuoi
	if((p == NULL) || (p->next == NULL))
      printf("khong xoa sinh vien nay duoc");
    else{
    	q=p->next;
    	p->next=q->next;
    	delete q;
	}
}

void DK_Xoa_SVtheoma(LIST_LTC &list_ltc, PTRSV &FirstSV){
	int vitri=DK_traverse(list_ltc, FirstSV);
	if(vitri=-1) return;
	char maso[10];
	PTRDK tempdk,p;
	do{
		cout<<"\nNhap ma sinh vien muon xoa";	fflush(stdin);
		gets(maso);
		tempdk=DK_Search_SV_thuocDSLTC(list_ltc, vitri,maso);
		if(tempdk==NULL) cout<<"Sinh vien khong co trong lop tin chi.";
	}while(tempdk==NULL);
	PTRSV tempsv = SV_search_infosv(FirstSV,tempdk->dangky.MASV);
	printf("\n   %10s  %-15s %-10s %15d"  , tempdk->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,tempdk->dangky.DIEM);
	int yn = XacNhan("\nBan co muon xoa khong? (Y/N): ");
	if(yn==1){
		if(tempdk==list_ltc.nodesltc[vitri]->First_DSSVDK){
			DK_Delete_First(list_ltc.nodesltc[vitri]->First_DSSVDK);
		}
		else{
			PTRDK temp = list_ltc.nodesltc[vitri]->First_DSSVDK;
			while(temp->next != tempdk){
				temp=temp->next;
			}
			DK_Delete_After(temp);
		}
		cout<<"\nXoa thanh cong";
		getch();
	}
}


// menu 
char menu(){
	int chucnang;
	do {
		printf("\n\n\t\tQUAN LY SINH VIEN THEO HE TIN CHI");
		printf("\n\Cac chuc nang cua chuong trinh\n");
		printf("   1. Tao danh sach sinh vien\n");
		printf("   2: Xem danh sach sinh vien\n");
		printf("   3: Nhap mon hocn\n");
		printf("   4: Xem danh sach mon hoc\n");
		printf("   5: Tao lop tin chi\n");
		printf("   6: Xem lop tin chi\n");
		printf("   7: Xoa lop tin chi\n");
		printf("   8: Sua lop tin chi\n");
		printf("   9: Them lop tin chi\n");
		printf("   10: Them SV vao lop\n");
		printf("   11: Show DSSV LTC\n");
		printf("   12: Xoa SV trong LTC\n");
		printf("   20: Ghi vao file \n");
      	printf("   21: Mo danh sach \n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
		
	}while(chucnang < 0) ;
      return chucnang;
}

int main(){
	PTRMH treeMH = NULL;
	LIST_LTC list_ltc;
	list_ltc.soluong =0;
	PTRSV FirstSV = NULL;
		
	do {
		system("cls");
      	int chucnang = menu();
      	system("cls");
      	fflush(stdin);
      	switch(chucnang){
      		case 1:
      			{
      			SV_Create_DSSV(FirstSV);
      			break;
			}
			case 2:{
				SV_traverse(FirstSV);
				break;
			}
			case 3:{
				Create_MONHOC(treeMH);
				break;
			}
			case 4:{
				printf("\n       Danh sach mon hoc: ");
   				printf("\n     Ma mon       Ten mon    STCLT	STCTH"); 
				Show_MonHoc(treeMH);	
				getch();
				break;
			}
			case 5:{
				Create_List_LTC(list_ltc);
				break;
			}
			case 6:{
				duyetDS_LTC(list_ltc);
				break;
			}
			case 7 :{
				LTC_Delete_theoma(list_ltc);
				break;
			}
			case 8:{
				LTC_Sua_theoma(list_ltc);
				break;
			}
			case 9:{
				Create_List_LTC(list_ltc);
				break;
			}
			case 10:{
				DK_Nhap_SV(list_ltc,FirstSV);
				break;
			}
			case 11:{
				DK_traverse(list_ltc,FirstSV);
				break;
			}
			case 12:{
				DK_Xoa_SVtheoma(list_ltc,FirstSV);
				break;
			}
			case 20:{
				//ghiFileMonHoc(treeMH);
				//SV_SaveFile(FirstSV);
				LTC_ghiFile(list_ltc);
				break;
			}
			case 21: {
				docFileMonHoc(treeMH);
				SV_OpenFile(FirstSV);
				LTC_docFile(list_ltc);
				break;
			}
			
		}
	}
	while(1);
	
}









