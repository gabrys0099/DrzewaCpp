#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

using namespace std;


//Struktura kopca
typedef struct DrzewoRB

{
	int key;
	char bf;
	DrzewoRB * poprzednik;
	DrzewoRB * L;
	DrzewoRB * P;
}node;
//Funkcja wypisujaca drzewo metoda VLR rekurencyjnie
void VLRwzdluzne (node *head)
{
	if(head!=NULL)
	{
		cout<<head->key<<", ";//wypisanie na ekranie glowy
		VLRwzdluzne(head->L);//przejscie na lewa glowe
		VLRwzdluzne(head->P);//przejscia na prawa glowe
	}
}
//wypisanie drzewa metoda LVR rekurencyjnie
void LVRpoprzeczne(node*head)
{
	if(head!=NULL)
	{
		LVRpoprzeczne(head->L);////przejscie na lewa glowe
		cout<<head->key<<", ";//wypisanie na ekranie glowy
		LVRpoprzeczne(head->P);//przejscia na prawa glowe
	}
}
//wypisanie drzewa metoda LRV rekurencyjnie
void LRVwsteczne(node * head)
{
	if(head!=NULL)
	{
		LRVwsteczne(head->L);//przejscie na lewa glowe
		LRVwsteczne(head->P);//przejscia na prawa glowe
		cout<<head->key<<", ";//wypisanie na ekranie glowy
	}
}
//Funkcja usuwajaca cale drzewo
void usuniecieDrzewa(node ** head)
{
	if(*head!=NULL)
	{
		usuniecieDrzewa(&(*head)->L);//Wywo³anie funkcji usuniecia z lewa glowa
		usuniecieDrzewa(&(*head)->P);//wywolanie funkcji usuniecia z prawa glowa
		free(*head);//usuniecie glowy
		*head=NULL;
	}
}
//Funkcja rysujaca drzewo na ekranie
void wykresDrzewaBST( string sp, string sn, node * head )
{
  string s;
  string b, c, a; 
  a=b=c="  ";
  a[0]=218;
  a[1]=196;
  b[0]=192;
  b[1]=196;
  c[0]=179;
  if(head!=NULL)
  {
    s=sp;
    if(sn==a)s[s.length()-2]=' ';
    wykresDrzewaBST(s+c,a,head->P);

    s=s.substr(0,sp.length()-2);
    cout<<s<<sn<<head->key<<endl;

    s=sp;
    if(sn==b)s[s.length()-2]=' ';
    wykresDrzewaBST(s+c, b, head->L );
  }
}
//Funkcja wykonujaca rotacje w Prawo
void RR(node **head, node *A){
// rotacaj RR
    node *B=A->P, *p=A->poprzednik;

    A->P = B->L;
    if(A->P) A->P->poprzednik = A;

    B->L=A;
    B->poprzednik=p;
    A->poprzednik=B;

    // gdy p == NULL to element A by³ naszym korzeniem
    if(p!=NULL){
          if(p->L == A) p->L=B;
          else p->P=B;
     }
     else *head=B;
}
//Funkcja wykonujaca rotacje w Lewo
void LL(node ** head, node *A){
// rotacja LL
   node *B=A->L, *p=A->poprzednik;

      A->L=B->P;
      if(A->L) A->L->poprzednik=A;

     B->P=A;
     B->poprzednik=p;
     A->poprzednik=B;

    // gdy p == NULL to element A by³ naszym korzeniem
    if(p!=NULL){
          if(p->L==A) p->L=B;
          else p->P = B;
    }
    else *head = B;
}
//Funkcja sprawdzajaca jaka jest wysokosc drzewa aktualnie
void wysokoscDrzewa(node *head,int poziom,int *h){
// funkcja w zmiennej h bêdzie dawa³a nam wysokoœæ poddrzewa
   if(head!=NULL){
            if(head->P){
                  poziom++;
                  wysokoscDrzewa(head->P,poziom,h);
                  poziom--;
            }
            if(poziom>*h) *h=poziom;

            if(head->L){
                  poziom++;
                  wysokoscDrzewa(head->L,poziom,h);
                  poziom--;
            }
      }
}

void BF(node *r){
// funkcja liczy wspó³czynnik po dokonani rotacji
// argumentem jest element dla którego liczymy bf

    int a=0;
    int b=0;
    node *x=r, *y=x->L, *z=x->P;

    if(y) wysokoscDrzewa(y,1,&a);
    if(z) wysokoscDrzewa(z,1,&b);
    x->bf=a-b;

}
//Funkcja dodawania do drzewa nowego elementu
node *DodanieDoDrzewa(node *head, int key)
{ 
    node *newNode,*p,*r, *d;
    int t;
    //zdefiniowanie nowego elementu
    newNode = (node *)malloc(sizeof(node));
	newNode->L = newNode->P = newNode->poprzednik = NULL;
    newNode->key = key;
    newNode->bf = 0;  
    d=head;
    if(head==NULL)//jezeli glowa jest pusta ustaw element za glowe
	{
        newNode->poprzednik=NULL;
        head=newNode;
    }
    else
	{
	    while(d!=NULL)//przejscie do elementu w ktory trzeba wstawic nowy node
		{
        if(d->key > key)//jezeli nowy element jest mniejszy przejdz w lewo
		{
            p=d;
            d=d->L;
        }
		else if(d->key < key)//jezeli nowy element jest wiekszy przejdz w prawo
		{
            p=d;
            d=d->P;
        }
		else break;
        }
        if(d==NULL)//jezeli miejsce jest puste ustaw tam nowy element 
		{
            if(p->key>key)
			{
				p->L=newNode;	
			}
			else 
			{
				p->P=newNode;
			}
            newNode->poprzednik=p;
         }
        //przywrocenie stabilnosci drzewa
        r=newNode;
        while(p!=NULL)
		{ 
            if(p->L==r)
			{
				 p->bf+=1;
			}
            else if (p->P==r)
			{
				p->bf-=1;
			}
            if(p->bf==2 || p->bf==-2) 
			{
				break;
			}
            r=p;
            p=p->poprzednik;
        }
        if(p!=NULL)
		{ 
            if(p->bf == 2)
			{
                if(p->P != r)
				{
                    if(r->bf == -1)
					{ 
                        RR(&head,p->L);
                        LL(&head,p);
                    }
					else LL(&head,p);
                }
            }
            else
			{
                if(p->L != r)
				{
                    if(r->bf == 1)
					{ 
					    LL(&head,p->P);
                        RR(&head,p);
                    }
                    else RR(&head,p);
                }
            }
        p=p->poprzednik; 
        if(p->P)
		{
			BF(p->P);
		}
        if(p->L)
		{
			BF(p->L);
		}
        BF(p);
        }
    }
    return head;
}

node * UsuwanieElementuDrzewaAVL(node **head, int key){
 
   if(*head!= NULL)
   {
        if((*head)->key > key)
		{
			return UsuwanieElementuDrzewaAVL(&(*head)->L,key);
		}
        else
		{
            if ((*head)->key < key)
			{
				return UsuwanieElementuDrzewaAVL(&(*head)->P, key);
			}
            else
			{
                node *z=*head, *p=z, *r=z,*y;
                if(z->L==NULL)
				{
                    if(z->P!=NULL)
					{
						 z->P->poprzednik=(*head)->poprzednik;
					}
                    *head=z->P;
                    y=z->poprzednik;
                    free(z);
                    z=NULL;
                    return y;
				}
				else
				{
                    if (z->P==NULL)
					{
                        z->L->poprzednik=(*head)->poprzednik;
                        *head=z->L;
                        y=z->poprzednik;
                        free(z);
                        z=NULL;
                        return y;
                    }
					else
					{
                        p=z->L;
                        r=z;
                        while(p->P!=NULL)
						{
                            r=p;
							p=p->P;
                        }
                        int temp = p->key;
                        p->key=z->key;
						z->key=temp;
                        if(r->key!=z->key)
						{
                            r->P=p->L;
                            if(r->P!=NULL)
							{
								r->P->poprzednik=p->poprzednik;
							}
                        }
                        else
						{
                            r->L=p->L;
                            if(r->L!=NULL)
							{
								r->L->poprzednik=p->poprzednik;
							}
                        }
                        y=p->poprzednik;
                        free(p);
                        p=NULL;
                        return y;
                    }
                }
            }
        }
    }
}

void removeAVL (node **head, int x){

    if(*head!=NULL)
	{
	    node *p=NULL,*r=NULL;
		p=UsuwanieElementuDrzewaAVL(head,x); 
        r=p;
        if(*head!=NULL && p!=NULL)
		{
            while(p!=NULL)
			{
			    BF(p);
				if(p->bf==2 || p->bf==-2)
				{
					break; 
				}
                r=p;
                p=p->poprzednik;
            }
            if(r==p)
			{
                if(p->P==NULL)
				{
					r=p->L;
				}
				else if(p->L==NULL)
				{
					r=p->P;
				}
            }
            if(p!=NULL)
			{
                if(p->bf == 2)
				{
                    if(p->P != r)
					{
                        if(r->bf == -1)
						{ 
                            RR(head,p->L);
                            LL(head,p);
                        }
                        else 
						{
							LL(head,p);
						}
                    }
                }
				else
				{
					if(p->L != r)
					{
                        if(r->bf == 1)
						{ 
                            LL(head,p->P);
                            RR(head,p);
                        }
                        else 
						{
							RR(head,p);
						}
                    }
                }
                if(p->poprzednik!=NULL)
				{
					p=p->poprzednik;
				} 
                if(p->P!=NULL)
				{
					BF(p->P);
				}
                if(p->L!=NULL)
				{
					BF(p->L);
				}
                BF(p);
            }
        }
    }
}

void SzukanieElementu(node **head, int key)
{
	
	if(*head!=NULL)
	{
		if((*head)->key==key)
		{
			cout<<"Szukany element to korzen "<<endl;
			return;
		}
	node *tmp=*head;
	cout<<(*head)->key;

	do
	{
		if(key>tmp->key)
		{
			
			tmp=tmp->P;
			if(tmp==NULL)
			{
				cout<<"nie ma takiej wartosci";
				return;
			}
			cout<<"->"<<tmp->key;

		}
		else if(key<tmp->key)
		{
			tmp=tmp->L;
			if(tmp==NULL)
			{
				cout<<"nie ma takiej wartosci";
				return;
			}
			cout<<"->"<<tmp->key;
		}
		if(tmp->key==key)
		{
			return;
		}
	}while(tmp->key!=key);
	}
	
}


int main()
{
	int wybor;
	node *head=NULL;
	cout<<"Jezeli chcesz wprowadzic dane z pliku wcisnij 2, jezeli z klawiatury wybierz 1: ";
	cin>>wybor;
	switch(wybor)
	{
		case 1:
			{
				int n;
				cout<<"Ile elementow chcesz wprowadzic: ";
				cin>>n;
				for(int i=0;i<n;i++)
				{
					int a;
					cout<<"Podaj wartosc elementu: ";
					cin>>a;
					head=DodanieDoDrzewa(head, a);
				}
				break;
			}
		case 2:
			{
				ifstream plik("we.txt");
				while(!plik.eof())
				{
					
					int a;
					plik>>a;
					head=DodanieDoDrzewa(head, a);
				}
				plik.close();
				break;
			}
	}
	
	cout<<endl<<"wykres drzewa: "<<endl<<endl;
	wykresDrzewaBST( "", "", head );
	
	int usuwana;
	cout<<endl<<"Jaki wezel chcesz usunac: ";
	cin>>usuwana;
	removeAVL(&head, usuwana);
	cout<<"wykres po usunieciu wezla: "<<endl<<endl;
	wykresDrzewaBST( "", "", head );
	
	int szukana;
	cout<<endl<<"Jaki element chcesz znalezc: ";
	cin>>szukana;
	cout<<"sciezka elementu "<<szukana<<": "<<endl;
	SzukanieElementu(&head, szukana);
	
	cout<<endl<<"Wypisanie VLR wzdluzne: "<<endl;

	VLRwzdluzne(head);
	

	cout<<endl<<"Wypisanie LVR poprzeczene: "<<endl;

	LVRpoprzeczne(head);
	
	cout<<endl<<"Wypisanie LRV wsteczne: "<<endl;

	LRVwsteczne(head);
	
	
	return 0;
}
