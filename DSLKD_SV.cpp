
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <mylib.h>
#include <iostream>


using namespace std;

struct sinhvien
{
   int mssv;
   char ho[30];
   char ten[10];
   float dtb;
   int hang;
   
};

struct node
{
   sinhvien sv;
   struct node *next;
};
typedef node *NODEPTR;

NODEPTR search_info(NODEPTR First, int x);


char menu ()
{  int chucnang;
   do
   {  system("cls");
      printf("\n\n\t\tCHUONG TRINH QUAN LY DANH SACH SINH VIEN");
      printf("\n\nCac chuc nang cua chuong trinh:\n");
      printf("   1: Tao danh sach sinh vien\n");
      printf("   2: Them sinh vien vao danh sach\n");
      printf("   3: Xem danh sach sinh vien\n");
      printf("   4: Hieu chinh sinh vien\n");
      printf("   5: Xoa sinh vien trong danh sach theo mssv\n");
      printf("   6: Tim kiem sinh vien theo MSSV\n");
      printf("   7: Sap xep danh sach theo MSSV\n");
      printf("   8: Loc danh sach\n");
      printf("   9: Dao nguoc danh sach\n");
      printf("   10: Xoa tat ca sinh vien theo ten \n");
      printf("   11: Ghi vao file \n");
      printf("   12: Mo danh sach \n");
      printf("   13: Xep hang sinh vien \n");
      printf("   0: Ket thuc chuong trinh\n");
      printf("Chuc nang ban chon: ");
      cin>>chucnang;
      } while(chucnang < 0 || chucnang >13) ;
      return chucnang;
}
// Phep toan New_node: cap phat mot nut cho danh sach lien ket
NODEPTR New_node(void)
{
   NODEPTR p;
   p = new node;
   return(p);
}

// Phep toan clearlist: xoa tat ca cac nut trong danh sach lien ket
void clearlist(NODEPTR &First)
{
   NODEPTR p;   
   p = First;
   while(First != NULL)
   {
      p = First;
      First = First->next;
      delete p;
   }
}

void Create_list(NODEPTR &First)
{ NODEPTR Last,p, temp;
  sinhvien sv;

    char maso [5],c;
	clearlist(First);   
	
    
  do
  {
  		printf("Ma so sinh vien: ");
		gets(maso);
		sv.mssv = atoi(maso);
		if(sv.mssv<=0) return;
		temp=search_info(First,sv.mssv);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: ");
		gets(sv.ho);
		printf("Ten sinh vien: ");
		gets(sv.ten);
		cout<<"Diem trung binh: ";
		cin>>sv.dtb;
		fflush(stdin);
		p= new node; //New_node();
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

// tim kiem theo ma so
NODEPTR search_info(NODEPTR First, int x){
	NODEPTR p;
	for(p=First; p!= NULL; p=p->next){
		if(p->sv.mssv==x)
		return p;
	}
	return NULL;
}

void NhapChuoi (char *tieude, char *S) {
	cout << tieude ;  fflush(stdin);
    do
	  gets(S);
    while (strcmp(S,"")==0)  ;	
}

int XacNhan (char *S){
	cout<<S;
	char kt;
	do{
		kt=toupper(getch());
	}while(kt!='Y'&&kt!='N');
	cout<<kt;
	return kt=='Y';
}

// dem tong so nut
int Reccount(NODEPTR First){
	NODEPTR p;
	int tong = 0;
	for(p=First; p!=NULL; p=p->next){
		++tong;
	}
	return tong;
}

// ham them vao dau
void Insert_first(NODEPTR &First, sinhvien x){
	NODEPTR p;
	p = new node;
	p->sv = x;
	p->next = First;
	First = p;		
}

// ham them vao cuoi
void Insert_last(NODEPTR &First, sinhvien x){
	NODEPTR tmp = new node;
	tmp->sv = x;
	
	if(First==NULL) 
		Insert_first(First,x);
	else 
	{
	  NODEPTR p = First;
	  while(p->next!=NULL)
			p = p->next;
	
	   p->next = tmp;
	   tmp->next=NULL;
}
    
}

void Insert_after(NODEPTR p, sinhvien sv)
{
   NODEPTR q;
   if(p == NULL)
		printf("khong them phan tu vao danh sach duoc");
   else
   { q =new node;
      q->sv = sv;
      q->next = p->next;
      p->next = q;
   }
}

//Them vao danh sach co thu tu
void Insert_Order(NODEPTR &First, sinhvien sv){
   NODEPTR p, t, s;  // t la nut truoc, s la nut sau
   p=new node;
   p->sv.mssv=sv.mssv;
   for(s = First; s != NULL && s->sv.mssv < sv.mssv ; t=s, s = s->next)   ;
	if(s == First)  // them nut vao dau danh sach lien ket
   {
      p->next = First;
      First = p;
   }
   else           // them nut p vao truoc nut s
   {
      p->next= s;
      t->next= p;
   }
}

//them sinh vien
void addSV(NODEPTR &First, int ms){
	NODEPTR temp;
	sinhvien sv;
	ms=sv.mssv;
	temp=search_info(First,ms);
	while(temp!=NULL || ms==0 ){
		cout<<"\nDa ton tai sinh vien co ma so: "<<ms;
		cout<<"\nNhap lai mssv: ";
		cin>>sv.mssv;
		ms=sv.mssv;
		temp=search_info(First,ms);
	}	
	NhapChuoi("Nhap Ho: ", sv.ho);
	NhapChuoi("Nhap Ten: ", sv.ten);
	cout<<"Nhap diem trung binh: ";
	cin>>sv.dtb;
	fflush(stdin);
	if(Reccount == 0 )
		Insert_first(First,sv);
	else		
		Insert_last(First,sv);
	cout<<"\nThem thanh cong";
	getche();
}

// Phep toan traverse: duyet danh sach lien ket
void traverse(NODEPTR First)
{
   NODEPTR p;
   int stt = 0;
   p = First; 
   if(p == NULL){
   	printf("\n   (Khong co sinh vien trong danh sach)");
   	getche();
   	return;
   }
      
   printf("\n       Danh sach sinh vien: ");
   printf("\n   STT  MSSV               HO TEN \t\t               DTB\t    HANG");
   //setprecision(2);
   
   while(p != NULL)
   {
      printf("\n   %-5d %-8d  %-30s %-10s %-8.2f %10d"  , ++stt, p->sv.mssv, p->sv.ho,p->sv.ten,p->sv.dtb,p->sv.hang);
      p = p->next;
   }
   getche();
}


// xoa node dau tien
void Delete_first(NODEPTR &First){
	NODEPTR p;
	p=First;
	First=p->next;
	delete p;
}

//xoa node sau p
void Delete_after(NODEPTR p){
	NODEPTR q;
	// neu p la NULL hoac p chi nut cuoi
	if((p == NULL) || (p->next == NULL))
      printf("khong xoa sinh vien nay duoc");
    else{
    	q=p->next;
    	p->next=q->next;
    	delete q;
	}
}

// Xoa theo ma so
int Delete(NODEPTR &First, int maso){
	NODEPTR p,temp;
	p = search_info(First,maso);
	if(p==NULL){
	    cout<<"\nKhong ton tai";
	    getche();
	}
	else{
		cout<<"\n\tHo\tTen";
	 	cout<<"\n\t"<<p->sv.ho<<"\t"<<p->sv.ten;
	 	int yn = XacNhan("\nBan co muon xoa khong? (Y/N): ");
		if(yn==1){
			if(p==First){
				Delete_first(First);
			}
			else{
				temp = First;
				while(temp->next != p){
					temp=temp->next;
				}
				Delete_after(temp);
			}
			cout<<"\nXoa thanh cong";
			getch();
		}
	}
}

//tim ten
NODEPTR search_name(NODEPTR First, char *x){
	NODEPTR p;
	for(p=First; p!= NULL; p=p->next){
		if(strcmp(p->sv.ten,x)==0)
		return p;
	}
	return NULL;
}

//Xoa tat ca cac sv co ten x
void DeleteName(NODEPTR &First){
	NODEPTR p,temp;
	char name[10];
	do{
		NhapChuoi("Ten sinh vien muon xoa: ", name);
		p=search_name(First,name);
	}while(p==NULL);		
		
	while(p!=NULL){	
		if(First==NULL) return;		
		if(p==First){				
			Delete_first(First);
		}										p
		else{  						5	6	7	8	2	4
			temp = First;					t
			while(temp->next != p){
				temp=temp->next;
			}
			Delete_after(temp);
		}
		p=search_name(First,name);
	}
	cout<<"\nXoa thanh cong";	
	getche();
}

//Loc
void Loctrungtheotensv(NODEPTR &First){
	if (First == NULL|| First->next==NULL) return;
	NODEPTR p,q;
	for(p=First; p->next!=NULL; p=p->next)
		for(q=p;q->next!=NULL;){
			if(stricmp(q->next->sv.ten,p->sv.ten)==0)
				Delete_after(q);
			else q=q->next;
		}
}

// Loc while
void Filter(NODEPTR First){
	if (First == NULL|| First->next==NULL) return;
	NODEPTR p=First,q;
	while(p->next!=NULL){				
		q=p;							
		while(q->next!=NULL){
			if(stricmp(q->next->sv.ten,p->sv.ten)==0){
				Delete_after(q);
			}
			else	q=q->next;
		}
		p=p->next;
	}
}

//Sap xep tang dan
void selectionsort(NODEPTR &First){
	NODEPTR p,q,pmin;
	sinhvien temp;
	int min;
	if(First==NULL){
		cout<<"Danh sach rong";
	}
	else{
		for(p=First; p->next!=NULL ; p=p->next){
			min = p->sv.mssv;
			pmin = p;
			for(q=p->next; q!=NULL; q=q->next){
				if(q->sv.mssv<min){
					min = q->sv.mssv;
					pmin=q;
				}
			}
			//hoan doi truong sv (info) cua p va min
			temp=pmin->sv;
			pmin->sv=p->sv;
			p->sv=temp;
		}
		cout<<"Sap xep thanh cong";
	}
	
}

//Dao nguoc
int Reverse(NODEPTR &First){
	NODEPTR cur = First;
	NODEPTR prev=NULL,next=NULL;
	while(cur!=NULL){
		next=cur->next;
		
		cur->next=prev;
		
		prev=cur;
		cur= next;
	}
	First = prev;
	return 1;
}

//In ds nguoc
void DSReverse(NODEPTR &First){
	Reverse(First);
	traverse(First);
	Reverse(First);
}

//Sap xep diem
void SapXepGiamTheoDiem(NODEPTR &First){
	NODEPTR p,q,pmax;
	sinhvien temp;
	float max;
	if(First==NULL){
		cout<<"Danh sach rong";
	}
	else{
		for(p=First; p->next!=NULL ; p=p->next){
			max = p->sv.dtb;
			pmax = p;
			for(q=p->next; q!=NULL; q=q->next){
				if(q->sv.dtb>max){
					max = q->sv.dtb;
					pmax=q;
				}
			}
			//hoan doi truong sv (info) cua p va min
			temp=pmax->sv;
			pmax->sv=p->sv;
			p->sv=temp;
		}
		cout<<"Sap xep thanh cong";
	}
	
}

//Xep hang
void XepHang(NODEPTR First){
	if(First==NULL) return;
	SapXepGiamTheoDiem(First);
	
	float mdtb;
	int mhang=1;
	NODEPTR p;
	
	p=First;
	mdtb=p->sv.dtb;
	for( ;p!=NULL;p=p->next){
		if(mdtb==p->sv.dtb)
			p->sv.hang=mhang;
		else{
			mdtb=p->sv.dtb;
			mhang++;
			p->sv.hang=mhang;
		}
	}
}

//luu file
int SaveFile (NODEPTR First, char *tenfile) {
	FILE *f = fopen (tenfile, "wb");
	if (f==NULL) return 0;
	for (NODEPTR p=First ; p!=NULL ; p=p->next)
	  fwrite (&p->sv, sizeof (sinhvien), 1, f);
	fclose (f);
	cout<<"Da luu file";
	getche();
	return 1;  
}

//mo file
int OpenFile (NODEPTR &First, char *tenfile) {
	NODEPTR p;  sinhvien sv ;
	FILE *f = fopen (tenfile, "rb");
	if (f==NULL) 
	  return 0; // mo file khong duoc
	clearlist(First);
	while  (fread (&sv, sizeof (sinhvien), 1, f)== 1 ){
		Insert_last (First , sv);
	} 
	fclose (f);
	cout<<"Mo file thanh cong";
	getche();
	return 1;  
}



// chuong trinh chinh

int main()
{
   int vitri, x, ms, chucnang;  sinhvien sv;
   char c, maso [5], c_vitri[5] ;
   NODEPTR p;
   char filename[40] = "F:/ct/dssv.txt";
   // khoi dong danh sach lien ket
   NODEPTR First=NULL;
   do
   {  system("cls");
      chucnang = menu();
      system("cls");
      fflush(stdin);
      switch(chucnang)
      {
	      case 1:
	      {
		    Create_list(First);
	     	break;
	      }
	      case 2:
	      {	
	      	NODEPTR temp;
			cout<<"Nhap thong tin sinh vien can them:";
			cout<<"\nMa so sinh vien: ";
			cin>>sv.mssv;
			ms=sv.mssv;
			temp=search_info(First,ms);
			while(temp!=NULL || ms==0 ){
				cout<<"\nDa ton tai sinh vien co ma so: "<<ms;
				cout<<"\nNhap lai mssv: ";
				cin>>sv.mssv;
				ms=sv.mssv;
				temp=search_info(First,ms);
			}	
			NhapChuoi("Nhap Ho: ", sv.ho);
			NhapChuoi("Nhap Ten: ", sv.ten);
			if(Reccount(First) == 0 ){
				Insert_first(First,sv);
			}
			else{
				Insert_last(First,sv);
			}		
			cout<<"\nThem thanh cong";
			getche();
			traverse(First);
            break;
	      }
	      case 3:
	      {
		     traverse(First);
		     break;
	      }
	      case 5:
	      	{
	      		cout<<"\nNhap ma so sinh vien can xoa: ";
				cin>>ms;
	      		Delete(First,ms);
	      		traverse(First);
	      		break;	
			}
	      case '6':
	      	{
	      		NODEPTR p;
	      		cout<<"Nhap ma so sinh vien can tim: ";
	      		cin>>ms;
	      		p = search_info(First, ms);
	      		if(p==NULL)
	      			cout<<"\n Khong ton tai";
	      		else{
	      			cout<<"Ho"<<"\t"<<"Ten"<<endl;
					cout<<p->sv.ho<<"\t"<<p->sv.ten<<endl;
					getche();
				}
				break;
			}
			case 7:
			{
				selectionsort(First);
				getche();
				traverse(First);
				break;
			}
			case 8:
			{
				Filter(First);
				traverse(First);
				break;
			}
			case 9 :
			{
				DSReverse(First);
				break;
			}
			case 10:
			{
				DeleteName(First);
				traverse(First);
				break;
			}
			case 11:
			{
				SaveFile(First, filename);
				break;
			}
			case 12:
			{
				OpenFile(First,filename);
				break;
			}
			case 13:
				{
					XepHang(First);
					traverse(First);
					break;
				}
	  }	
   } while(chucnang != 0);

   // xoa tat ca cac nut tren danh sach lien ket
	clearlist(First);
}
