#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

using namespace std;


//Struktura kopca
typedef struct Kopiec

{
	int key;
	Kopiec * poprzednik;
	Kopiec * L;
	Kopiec * P;
}node;

//funkcja dodajaca do kopca
node * DodanieDoKopca (node * head, int key, int h, int licznik)
{
	node *newNode =(node *)malloc(sizeof(node));
	newNode->key=key;
	newNode->L=NULL;
	newNode->P=NULL;
	newNode->poprzednik=NULL;
	if(head==NULL)//jezeli glowa jest pusta ustaw element jako glowe
	{
		head=newNode;
	}
	
	else
	{
		node *tmp=head, *tmp2=head;
		do
		{
			//sprawdzenie czy element bedzie ustawiony w lewym czy prawym poddrzewie
			if(((pow(2,h))+1)/2>licznik)//jezeli wartosc ilosci elementow na wysokosci h jest wieksza niz licznik przejdz w lewo
			{
				
				tmp2=tmp;
				tmp=tmp->L;
				
			}
			else if(((pow(2,h))+1)/2<licznik)//jezeli wartosc ilosci elementow na wysokosci h jest mniejsza niz licznik przejdz w prawo
			{
				tmp2=tmp;
				tmp=tmp->P;
			}
			else
			{
				cout<<"bledna cyfra";
			}
			h=h-1;//zmniejszenie wysokosci o 1 gdy przejde do poddrzewa
		}while(h!=0);//zakonczenie gdy znajduyjemy sie na lisciu
		newNode->poprzednik=tmp2;
		if(licznik%2==1)//sprawdzenie czy element bedzie w lewym czy prawym lisciu swojego poprzednika
		{
			tmp2->L=newNode;
		}
		else if(licznik%2==0)
		{	
			tmp2->P=newNode;
		}
	}
	if(newNode!=head)
	{
		node * tmp4=newNode;
		while(true)
		{
		if(tmp4->poprzednik==head)//jezeli element jest wiekszy niz glowa ustaw go jako glowe i zakoncz
		{
			if(tmp4->key>head->key)
			{
				int tmp3=tmp4->key;
				tmp4->key=head->key;
				head->key=tmp3;
			}
			break;		
		}
		else
		{
			
			node * tmp5=tmp4;
			tmp5=tmp5->poprzednik;
			if((tmp4->key)>(tmp5->key))//jezeli element jest wiekszy niz swoj rodzic zamien go
			{
				int tmp3=tmp4->key;
				tmp4->key=tmp5->key;
				tmp5->key=tmp3;
				tmp4=tmp4->poprzednik;
			}
			else//w przeciwnym razie zakoncz while
			{

				break;
			}
			
		}
	}
	}

	return head;
}


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

void usuniecieKopca(node ** head)
{
	if(*head!=NULL)
	{
		usuniecieKopca(&(*head)->L);
		usuniecieKopca(&(*head)->P);
		free(*head);
		*head=NULL;
	}
}

//narysowanie kopca na ekranie
void wykresKopca( string sp, string sn, node * head )
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
    wykresKopca(s+c,a,head->P);

    s=s.substr(0,sp.length()-2);
    cout<<s<<sn<<head->key<<endl;

    s=sp;
    if(sn==b)s[s.length()-2]=' ';
    wykresKopca(s+c, b, head->L );
  }
}


//Usuniecie wybranego wezla kopca
void usuniecieWybranegoWezlaKopca(node **head, int key)
{
	if(*head!=NULL)
	{
		if((*head)->key>key)//jezeli wartosc obecnego elementu jest wieksza niz element do usuniecie
		{
			usuniecieWybranegoWezlaKopca(&(*head)->L, key);//przejdz rekurencyjnie do lewego poddrzewa
			usuniecieWybranegoWezlaKopca(&(*head)->P, key);//przejdz rekurencyjnie do prawego poddrzewa 
			
		}
		else if((*head)->key<key)//jezeli element obecny jest mniejszy niz element szukany zakoncz funkcje wroc do poprzedniego wywolania
		{
			return;
		}
		else if((*head)->key==key)//jezeli zostal znaleziony element do usuniecia przejdz do usuniecia poddrzewa
		{
			usuniecieKopca(&(*head));
		}
	}
}


int main()
{
	node * head=NULL;
	int wybor;
	cout<<"Jezeli chcesz wczytac dane z pliku wpisz 1, gdy z klawiatury wpisz 2: ";
	cin>>wybor;
	switch(wybor)
	{
		case 1:
			{
				ifstream plik("we.txt");
				int h=0, licznik=1;
				while(!plik.eof())
				{
					int a;
					plik>>a;
					head=DodanieDoKopca(head, a, h, licznik);
					if((pow(2, h))==licznik)
					{
						h++;
						licznik=1;
					}
					else
					{
						licznik++;
					}
				}
				plik.close();
				break;
			}
		case 2:
			{
				int n;
				cout<<"Ile elementow chcesz wprowadzic: ";
				cin>>n;
				int h=0, licznik=1;//ustawienie drzewa na wysokosc 0 i licznik elementow 1
				for(int i=0;i<n;i++)
				{
					
					int a;
					cout<<"Podaj wartosc elementu: ";
					cin>>a;
					head=DodanieDoKopca(head, a, h, licznik);
					if((pow(2, h))==licznik)//jezeli 2 do potegi h jest rowne licznikowi 
					{
						h++;//wysokosc zwieksz o 1
						licznik=1;//licznik ustaw na wartosc poczatkowa
					}
					else//jezeli potega 2 do h nie jest rowna licznikowi zwieksz go o 1
					{
						licznik++;
					}
				}
				break;
			}
	}

	cout<<endl<<"wykres kopca: "<<endl<<endl;
	wykresKopca( "", "", head );
	
	ofstream plik("wy.txt", ios::app);
	plik<<"-----------------------Kopiec---------------------"<<endl;
	cout<<"Wypisanie VLR wzdluzne: "<<endl;
	plik<<"Wypisanie VLR wzdluzne: "<<endl;
	VLRwzdluzne(head);
	

	cout<<endl<<"Wypisanie LVR poprzeczene: "<<endl;
	plik<<endl<<"Wypisanie LVR poprzeczene: "<<endl;
	LVRpoprzeczne(head);
	
	cout<<endl<<"Wypisanie LRV wsteczne: "<<endl;
	plik<<endl<<"Wypisanie LRV wsteczne: "<<endl;
	LRVwsteczne(head);
	plik<<endl<<"-----------------------Nastepne wywolanie---------------------"<<endl;
	plik.close();
	
	
	int usuwana;
	cout<<endl<<"Jaki wezel maskymalny chcesz usunac: ";
	cin>>usuwana;
	usuniecieWybranegoWezlaKopca(&head, usuwana);
	cout<<endl<<"wykres kopca: "<<endl<<endl;
	wykresKopca( "", "", head );
	
	
	usuniecieKopca(&head);
	cout<<endl<<endl;
	if(head==NULL)
	{
		cout<<"Kopiec usuniety";
	}
	return 0;
}
