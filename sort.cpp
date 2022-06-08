#define FALSE 0
#define TRUE  1
void Bubble_Sort_Ad(int A[], int n){
  int i,temp;
  char flag=TRUE;
  while (flag){
  	flag = FALSE ;
	for (i=0; i<n-1; i++)
    	if (A[i] > A[i+1]){
		 	temp = A[i];
			A[i] = A[i+1];
			A[i+1] = temp;
			flag=TRUE;
		}
  	}
}

void Insertion_sort(int A[], int n){  
  int x;
  int i,j;
  for (i=1; i< n; i++)
  {
    x = A[i];
    for (j=i-1; j>=0 && x<A[j]; j--) 
		A[j+1] = A[j];
    A[j+1]=x;
  }
}

void Selection_Sort(int A[], int n){
  int min, vitrimin;
  int i,j;
  for (i=0; i< n-1; i++){
    min = A[i];    vitrimin=i;
    for (j=i+1; j<n; j++)
      if (A[j] < min){
	  	min = A[j];	vitrimin=j;
      }
    // Doi cho 2 phan tu A[i] va A[vitrimin]
    min = A[vitrimin] ;    A[vitrimin] = A[i];    A[i] = min;
  }
}
//quick_sort
void Sort(int A[], int q,int r)
  { int temp;
    int i=q;
    int j=r;
    int x = A[(q+r) / 2]; //Lay phan tu giua cua day con sap thu tu lam chot
    do
    {  // Phan doan day con a[q],..., a[r]
      while (A[i] < x)  i++; //Tim phan tu dau tien co tri lon hon hay bang x
      while (A[j] > x)  j--; //Tìm phan tu dau tien có tri nho hon hay bang x
      if (i<=j)   // Doi cho A[i] voi A[j]
     { temp = A[i];
       A[i] =A[j];
       A[j] = temp;
	     i++ ;  j--;
   }
} while (i<=j);
  if (q<j) 	// phan thu nhat co tu 2 phan tu tro len
	Sort(A,q,j);
  if (i<r)   	// phan thu ba co tu 2 phan tu tro len
	Sort (A,i,r);
}

void Quick_Sort(int A[], int n)
{ Sort( A,0,n-1);	// Goi ham Sort voi phan tu dau có chi so 0 den phan tu cuoi cung co chi so n-1
  }


//Tron 2 danh sach co thu tu thanh danh sach thu 3 co thu tu
PTR Merge_Order(PTR &First1, PTR &First2)
{ PTR p1, p2, p3;
  PTR First3= new node ;
  p1=First1; p2 = First2; p3=First3;
  while (p1 !=NULL && p2 !=NULL)
    if (p1->info < p2->info)
    { p3->next = p1;
      p3=p1;
      p1=p1->next ;
    }
    else
    { p3->next = p2;
      p3=p2;
      p2=p2->next ;
    }

    if (p1 == NULL)
      p3->next=p2;
    else
p3->next=p1;

    p3 = First3;
    First3=p3->next;
    delete p3; 
    First1=First2=NULL;
    return First3;
}



bài s?a Nhân da th?c:
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <mylib.h>
using namespace std;
struct node
{  int heso ; int somu;
node *next ;
};
typedef node *PTR;
void NhapDaThuc (PTR &First){
int somu;
int heso;
while (1){
printf("Nhap he so (Nhap 0 de dung) = ");
scanf("%d",&heso);
if (heso==0) break;

printf("Nhap so mu = ");
scanf("%d",&somu);
Insert_Last(First, heso, somu);
}
}

void CongHeSo(PTR DaThuc) {
PTR p1; PTR p2,tr_p2;
if (DaThuc==NULL) return;
for (p1= DaThuc; p1->next !=NULL; p1=p1->next) {
for (tr_p2=p1, p2=p1->next; p2 !=NULL ; )
if (p2->somu == p1->somu){
p1->heso = p1->heso + p2->heso;
tr_p2->next=p2->next; delete p2; p2=tr_p2->next ;
}
else { tr_p2=p2; p2=p2->next;	}

}
}

PTR NhanDaThuc (PTR DaThuc1, PTR DaThuc2) {
PTR p1,p2, DaThucTich=NULL;
int heso, somu;
for (p1=DaThuc1; p1 != NULL; p1 = p1->next)
for (p2=DaThuc2; p2 != NULL; p2 = p2->next)  {
heso = p1->heso * p2->heso; //Nhan he so
somu = p1->somu + p2->somu; //cong so mu
Insert_Last (DaThucTich, heso, somu);

}

CongHeSo(DaThucTich);
Delete_All_Info (DaThucTich, 0);
return DaThucTich;
}

