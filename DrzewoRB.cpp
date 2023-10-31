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
	char kolor;
	DrzewoRB * poprzednik;
	DrzewoRB * L;
	DrzewoRB * P;
}node;

//Funkcja wykonujaca rotacje w prawo
void  RR(node **head, node *A)
{
    node *B=A->L, *p;
    if(B!=NULL)
    {
    	p=A->poprzednik;
    	A->L = B->P;
		if(A->L!=NULL)
		{
			A->L->poprzednik = A;
		}
		B->P=A;
		B->poprzednik=p;
		A->poprzednik=B;
		if(p!=NULL)
		{
			if(p->L == A) p->L=B;
			else p->P=B;
		}
		else *head=B;
	}

}

//funkcja wykonujaca rotacjew w lewo
void  LL(node ** head, node * A)
{
    node *B=A->P, *p;
    if(B!=NULL)
    {
    	p=A->poprzednik;
    	A->P = B->L;
		if(A->P!=NULL)
		{
			A->P->poprzednik = A;
		}
		B->L=A;
		B->poprzednik=p;
		A->poprzednik=B;
		if(p!=NULL)
		{
			if(p->L == A) p->L=B;
			else p->P=B;
		}
		else *head=B;
	}
}



node * DodanieDoDrzewa (node * head, int key)
{
	
	node *newNode =(node *)malloc(sizeof(node));
	newNode->key=key;
	newNode->kolor='R';
	newNode->L=NULL;
	newNode->P=NULL;
	newNode->poprzednik=NULL;
	if(head==NULL)
	{
		
		head=newNode;//jezeli drzewo jest puste dodaj korzen jako nowy element
		head->kolor='B';
	}
	else
	{
		node *tmp=head;
		while(true)
		{
			if(tmp->key>key)//jezeli wartosc nowego elementu jest mniejsza niz element obecny przejdz w lewo
			{
				if(tmp->L==NULL)//jezeli w lewo nic nie ma ustaw tam nowy element
				{
					tmp->L=newNode;
					newNode->poprzednik=tmp;
					break;
				}
				tmp=tmp->L;
			}
			else//jezeli wartosc nowego elementu jest wieksza niz element obecny przejdz w prawo 
			{
				if(tmp->P==NULL)//jezeli nie ma nic w prawo ustaw tam nowy element
				{
					tmp->P=newNode;
					newNode->poprzednik=tmp;
					break;
				}
				tmp=tmp->P;
			}
		}
	}
		while((newNode!=head) && ((newNode->poprzednik)->kolor=='R'))
		{
			if(newNode->poprzednik==newNode->poprzednik->poprzednik->L)
			{
				node *tmp=newNode->poprzednik->poprzednik->P;
				if(tmp->kolor=='R')
				{
					newNode->poprzednik->kolor='B';
					tmp->kolor='B';
					newNode->poprzednik->poprzednik->kolor='R';
					newNode=newNode->poprzednik->poprzednik;
					continue;
				}
				if(newNode==newNode->poprzednik->P)
				{
					newNode=newNode->poprzednik;
					LL(&head, newNode);
					
				}
				newNode->poprzednik->kolor='B';
				newNode->poprzednik->poprzednik->kolor='R';
				RR(&head, newNode->poprzednik->poprzednik);
				break;
	
			}
			else
			{
				node *tmp=newNode->poprzednik->poprzednik->L;
				if(tmp->kolor=='R')
				{
					newNode->poprzednik->kolor='B';
					tmp->kolor='B';
					newNode->poprzednik->poprzednik->kolor='R';
					newNode=newNode->poprzednik->poprzednik;
					continue;
				}
				if(newNode==newNode->poprzednik->L)
				{
					newNode=newNode->poprzednik;
					RR(&head, newNode);
					
				}
				newNode->poprzednik->kolor='B';
				newNode->poprzednik->poprzednik->kolor='R';
				LL(&head, newNode->poprzednik->poprzednik);
				break;
			}
		}
		
	
	head->kolor='B';
	return head;
}


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
    cout<<s<<sn<<head->kolor<<":"<<head->key<<endl;

    s=sp;
    if(sn==b)s[s.length()-2]=' ';
    wykresDrzewaBST(s+c, b, head->L );
  }
}
//Wypisanie drzewa metoda LVR rekurencyjnie
void VLRwzdluzne (node *head)
{
	if(head!=NULL)
	{
		cout<<head->key<<", ";
		VLRwzdluzne(head->L);
		VLRwzdluzne(head->P);
	}
}
//wypisanie drzewa metoda LVR rekurencyjnie
void LVRpoprzeczne(node*head)
{
	if(head!=NULL)
	{
		LVRpoprzeczne(head->L);
		cout<<head->key<<", ";
		LVRpoprzeczne(head->P);
	}
}
//wypisanie drzewa metoda LRV rekurencyjnie
void LRVwsteczne(node * head)
{
	if(head!=NULL)
	{
		LRVwsteczne(head->L);
		LRVwsteczne(head->P);
		cout<<head->key<<", ";
	}
}

//Funkcja usuwajaca cale drzewo
void usuniecieDrzewa(node ** head)
{
	if(*head!=NULL)
	{
		usuniecieDrzewa(&(*head)->L);
		usuniecieDrzewa(&(*head)->P);
		free(*head);
		*head=NULL;
	}
}

//Funkcja usuwajaca wybrany element z drzewa
node *UsuwanieKlucza(node ** head, int key)
{
   if(*head!= NULL)
   {
        if((*head)->key > key) 
		{
			return UsuwanieKlucza(&(*head)->L,key);
		}
        else
		{
            if ((*head)->key < key)
			{
				return UsuwanieKlucza(&(*head)->P, key);
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

//funkcja naprawiajaca drzewo po usunieciu elementu
void UsuwanieElementuDrzewaRB(node ** head, int key){

    if(*head!=NULL)
	{
		node *q=NULL,*x=NULL,*p=NULL,*y=NULL;
        q=UsuwanieKlucza(head,key); //Wywo³anie funkcji usuniecia elementu
		if(*head!=NULL && q!=NULL)
		{
            if(q->kolor=='R' && q->L && q->L->kolor=='R')
			{
				q=q->L;
			}
            else if (q->kolor=='R' && q->P && q->P->kolor=='R') 
            {
            	q=q->P;
			}
            x=q;
            p=x->poprzednik;
            if(p!=NULL && p->kolor=='R')
			{
				while(x)
				{
					p=x->poprzednik;
                    if(p->poprzednik)
					{
                        if(p->poprzednik->L==p)
						{
							y=p->poprzednik->P;
						}
                        else if(p->poprzednik->P==p)
						{
							y=p->poprzednik->L;
						}
                    }
					else y=NULL;
                    if(y && y->kolor=='R' && p->kolor=='R')
					{
					    p->kolor=y->kolor='B';
                        if(p->poprzednik==*head)
						{
							break;
						}
                        p->poprzednik->kolor='R';
                        if(p!=NULL)
						{
							x=p->poprzednik;
						}
                    }
					else
					{
                        if(p->poprzednik && y==p->poprzednik->P)
						{
						    if(p->kolor=='R')
							{
                                if(p->P==x)   
								{
									RR(head,p);
								}
								LL(head,p->poprzednik);
                                x->poprzednik->kolor='B';
                                x->poprzednik->P->kolor='R';
                            }
                        }
						else if(p->poprzednik && y==p->poprzednik->L)
						{
						    if(p->kolor=='R')
							{
                                if(p->L==x)    
                                {
                                	LL(head,p);
								}
                                RR(head,p->poprzednik);
                                x->poprzednik->kolor='B';
                                x->poprzednik->L->kolor='R';
                            }
                        }
                        break;
                    }
               }
           }
		}
    }
}

//Funkcja Szukania elementu o kluczu key
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
			;
		}
		if(tmp->key==key)
		{
			return;
		}
	}while(tmp->key!=key);
	}
	
}


int main ()
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
	UsuwanieElementuDrzewaRB(&head, usuwana);
	cout<<"wykres po usunieciu wezla: "<<endl<<endl;
	wykresDrzewaBST( "", "", head );
	
	int szukana;
	cout<<endl<<"Jaki element chcesz znalezc: ";
	cin>>szukana;//Pobranie od uzytkownika elementu do znalezienia
	cout<<"sciezka elementu "<<szukana<<": "<<endl;
	SzukanieElementu(&head, szukana);//Wywolanie funkcji szukania elementu
	
	cout<<endl<<"Wypisanie VLR wzdluzne: "<<endl;
	VLRwzdluzne(head);
	

	cout<<endl<<"Wypisanie LVR poprzeczene: "<<endl;
	LVRpoprzeczne(head);
	
	cout<<endl<<"Wypisanie LRV wsteczne: "<<endl;
	LRVwsteczne(head);

	return 0;
}
