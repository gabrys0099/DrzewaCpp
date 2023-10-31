#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//Struktura Drzewa BST
typedef struct DrzewoBST
{
	int key;
	DrzewoBST * poprzednik;
	DrzewoBST * L;
	DrzewoBST * P;
}node;

//dodanie elementu do drzewa wg schematu
node * DodanieDoDrzewa (node * head, int key)
{
	node *newNode =(node *)malloc(sizeof(node));
	newNode->key=key;
	newNode->L=NULL;
	newNode->P=NULL;
	newNode->poprzednik=NULL;
	if(head==NULL)
	{
		head=newNode;//jezeli drzewo jest puste dodaj korzen jako nowy element
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
					return head;
				}
				tmp=tmp->L;
			}
			else//jezeli wartosc nowego elementu jest wieksza niz element obecny przejdz w prawo 
			{
				if(tmp->P==NULL)//jezeli nie ma nic w prawo ustaw tam nowy element
				{
					tmp->P=newNode;
					newNode->poprzednik=tmp;
					return head;
				}
				tmp=tmp->P;
			}
		}
	}
}
//Wypisanie drzaewa metoda VLR rekurencyjnie
void VLRwzdluzne (node *head)
{
	ofstream plik("wy.txt", ios::app);
	if(head!=NULL)
	{
		cout<<head->key<<", ";
		plik<<head->key<<", ";
		VLRwzdluzne(head->L);
		VLRwzdluzne(head->P);
	}
	plik.close();
}
//wypisanie drzewa metoda LVR rekurencyjnie
void LVRpoprzeczne(node*head)
{
	ofstream plik("wy.txt", ios::app);
	if(head!=NULL)
	{
		LVRpoprzeczne(head->L);
		cout<<head->key<<", ";
		plik<<head->key<<", ";
		LVRpoprzeczne(head->P);
	}
	plik.close();
}
//wypisanie drzewa metoda LRV rekurencyjnie
void LRVwsteczne(node * head)
{
	ofstream plik("wy.txt", ios::app);
	if(head!=NULL)
	{
		LRVwsteczne(head->L);
		LRVwsteczne(head->P);
		cout<<head->key<<", ";
		plik<<head->key<<", ";
	}
	plik.close();
}
//usuniecie calego drzewa lub poddrzewa
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
//usuniecie wybranego wezla
void KasowanieElemntu(node ** head, int key)
{
	node *tmp=*head, *tmp2=*head;
	if((*head)->key==key)//jezeli element jest glowa usun cale drzewo
	{
		usuniecieDrzewa(&(*head));
		return;
	}
	do
	{
		if(key>tmp->key)//jezeli wartosc jest wieksza niz obecny element przejdz w prawo
		{
			tmp2=tmp;
			tmp=tmp->P;
			if(tmp==NULL)
			{
				cout<<"nie ma takiej wartosci";
				return;
			}
		}
		else if(key<tmp->key)//jezeli wartosc jest mniejsza niz obecny element przejdx w lewo
		{
			tmp2=tmp;
			tmp=tmp->L;
			if(tmp==NULL)
			{
				cout<<"nie ma takiej wartosci";
				return;
			}
		}
		if(tmp->key==key)//jezeli wartosc jest rowna obecnemu elementowi usun cale poddrzewo
		{
			if(tmp2->P==tmp)
			{
				tmp2->P=NULL;
			}
			else
			{
				tmp2->L=NULL;
			}
			tmp->poprzednik=NULL;
			usuniecieDrzewa(&tmp);
			return;
		}
	}while(tmp->key!=key);

}

//Funkcja rysujace ca³e drzewo
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


//szukanie danego elementu w drzewie z wypisaniem sciezki dostepu do niego
void SzukanieElementu(node **head, int key)
{
	ofstream plik("wy.txt", ios::app);
	if(*head!=NULL)
	{
		if((*head)->key==key)
		{
			cout<<"Szukany element to korzen "<<endl;
			return;
		}
	node *tmp=*head;
	cout<<(*head)->key;
	plik<<(*head)->key;
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
			plik<<"->"<<tmp->key;
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
			plik<<"->"<<tmp->key;
		}
		if(tmp->key==key)
		{
			return;
		}
	}while(tmp->key!=key);
	}
	plik.close();
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
	ofstream plik("wy.txt", ios::app);
	plik<<"-----------------------Drzewo BST---------------------"<<endl;
	cout<<"Wypisanie VLR wzdluzne: "<<endl;
	plik<<"Wypisanie VLR wzdluzne: "<<endl;
	VLRwzdluzne(head);
	

	cout<<endl<<"Wypisanie LVR poprzeczene: "<<endl;
	plik<<endl<<"Wypisanie LVR poprzeczene: "<<endl;
	LVRpoprzeczne(head);
	
	cout<<endl<<"Wypisanie LRV wsteczne: "<<endl;
	plik<<endl<<"Wypisanie LRV wsteczne: "<<endl;
	LRVwsteczne(head);
	
	cout<<endl<<"wykres drzewa: "<<endl<<endl;
	wykresDrzewaBST( "", "", head );
	
	int szukana;
	cout<<endl<<"Jaki element chcesz znalezc: ";
	cin>>szukana;
	cout<<"sciezka elementu "<<szukana<<": "<<endl;
	plik<<endl<<"sciezka elementu "<<szukana<<": "<<endl;
	SzukanieElementu(&head, szukana);
	
	int usuwana;
	cout<<endl<<"Jaki wezel chcesz usunac: ";
	cin>>usuwana;
	KasowanieElemntu(&head, usuwana);
	cout<<"wykres po usunieciu wezla: "<<endl<<endl;
	
	wykresDrzewaBST( "", "", head );
	
	
	usuniecieDrzewa(&head);
	cout<<endl<<endl;
	if(head==NULL)
	{
		cout<<"drzewo usuniete";
	}
	plik<<endl<<"-----------------------Nastepne wywolanie---------------------"<<endl;
	plik.close();
	
	return 0;
	
}
