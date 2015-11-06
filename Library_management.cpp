/*   PROJECT: LIBRARY MANAGEMENT
     DEVELOPED BY: AGAM GUPTA, DIVIK BHATNAGAR, ADITYA MALIK
*/
#include <fstream.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define Tab "      "
#define Line "_______________________________________________________________________________"
#include<dos.h>
#include<stdlib.h>
#include<iomanip.h>
void Color(int TC,int TB);
void issue();
void login();
void Menu();
void rreturn();
void display();
void Color(int TC,int TB)
 { textcolor(TC);
   textbackground(TB);
 }
void Quit()
 {
   cout<<"Quitting";
   for(int i=1;i<71;i++)
    {
     cout<<".";
     delay(3);
    }
   exit(0);
 }
class library
{
   int qnty,qntyi,ino;char name[80];char authname[80];char category;
   public:
   int rino(){ return ino;}
   char* Rname(){ return name;}
   char* Rauthname(){ return authname;}
   int Rqnty(){ return qnty;}
   int Rqntyi(){ return qntyi;}
   char Rcategory(){ return category;}
   void issuechange()
      {
      if(qnty>0)
      qnty--;
      }
   void issue(int val);
   void returnchange()
     {
      if(qnty<qntyi)
      qnty++;
     }
   void rreturn();
   void Editrec();
   void input(int val);
   void output(int r);
   void displayN();
};
void library::displayN()
{  cout<<ino;
 cout<<name<<" ";
 cout<<qnty<<"  ";
 cout<<authname<<"  ";
 cout<<category<<endl;
}
void library::Editrec()
{ int choice2; char repeat;
    do
     {
      cout<<"Enter what you want to edit:\n 1.Book Name\t2. Book Quantity\t3.Authorname"<<endl;
      cin>>choice2;
      switch(choice2)
       {
	case 1: cout<<"New name:";
		gets(name);
		break;
	case 2: cout<<"New Quantity:";
		cin>>qnty;
		qntyi=qnty;
		break;
	case 3: cout<<"New Authorname:";
		gets(authname);
       }
       cout<<"Want to edit more?(Y/N)"<<endl;
       cin>>repeat;
      }while(repeat!='N');
}
void library::input(int val)
  {
      ino=val;
      cout<<"Enter the name of the book: ";
      gets(name);
      cout<<endl<<"Enter the number of books in stock:";
      cin>>qnty;
      qntyi=qnty;
      cout<<endl<<"Enter the name of the author:";
      gets(authname);
      cout<<endl<<"Enter the Category of the book:"<<endl;
      gotoxy(30,30);cout<<" A) Thriller .";
      gotoxy(30,34);cout<<" B) Biographies.";
      gotoxy(30,38);cout<<" C) Physics.";
      gotoxy(30,42);cout<<" D) Maths.";
      gotoxy(30,46);cout<<" E) Computer science."<<endl<<endl;
      cin>>category;
   }
void library::output(int r)
{
 gotoxy(5,r); cout<<ino;
 gotoxy(20,r);cout<<name;
 gotoxy(40,r);cout<<qnty;
 gotoxy(50,r);cout<<authname;
 switch(category)
  { case 'A':gotoxy(65,r);cout<<"Thriller";
	     break;
    case 'B':gotoxy(65,r);cout<<"Biographies";
	     break;
    case 'C':gotoxy(65,r);cout<<"Physics";
	     break;
    case 'D':gotoxy(65,r);cout<<"Maths";
	     break;
    case 'E':gotoxy(65,r);cout<<"Computer Science";
  }
}

void serialnumber()
{
   fstream fil;
   library l,l1;
   fil.open("lib.dat",ios::binary|ios::in|ios::out);
   fil.seekg(0,ios::end);
   int v=fil.tellg();


   if(v)
   {
   fil.seekg(fil.tellg()-sizeof(l));
   fil.read((char*)&l,sizeof(l));
   int val=l.rino();
   val=val+1;
   l1.input(val);
   l1.displayN();
   getch();}
   else
      { l1.input(1);
	  l1.displayN();}
   fil.write((char*)&l1,sizeof(l1));

   fil.close();
}

void Edit()
{
 fstream fil;
 fil.open("lib.dat",ios::binary|ios::in|ios::out);
 library L; int sino,found=0;
 cout<<"Enter the Serial number of the record to be edited:"; cin>>sino;
 while (!found && fil.read((char*)&L,sizeof(L)))
  {
   if(L.rino()==sino)
   found++;
  }

 if(found)
  {
   L.Editrec();
   int N=(fil.tellg()-sizeof(L));
   fil.seekp(N);
   fil.write((char*)&L,sizeof(L));
  }
 else
 cout<<"No record matching for editing...."<<endl;
 fil.close();
 getch();
}

void display()
{
   clrscr();
   int Page=1;
   cout<<"PAGE : "<<Page<<endl;
   cout<<"The following books are available in the stock:\n\n";
   gotoxy(2,6);cout<<"Serial no.";
   gotoxy(20,6);cout<<"Book";
   gotoxy(35,6);cout<<"Quantity";
   gotoxy(50,6);cout<<"Author name";
   gotoxy(65,6);cout<<"Category"<<endl<<Line<<endl;
   library d;
   fstream fil;
   char lin[80];
   fil.open("lib.dat",ios::binary|ios::in);
   int r=8;
   while(fil.read((char*)&d,sizeof(d)))
    {
     if (r==24)
      {
	cout<<"***************** Press Any Key to Continue *******************"<<endl;
	getch();
	clrscr();
	gotoxy(1,1);cout<<"Page:"<<++Page<<endl<<Line;
	gotoxy(2,6);cout<<"Serial Number";
	gotoxy(20,6);cout<<"Book";
	gotoxy(35,6);cout<<"Quantity";
	gotoxy(50,6);cout<<"Author name";
	gotoxy(65,6);cout<<"Category"<<endl<<Line<<endl;
	r=8;
      }
    d.output(r++);
   }
  fil.close();
  getch();
}

void search()
{
   int ch,cino,f=0;char bookname[80];char aname[80]; char issuechoice; char categ;
   library d;
   cout<<"1.Search by book name."<<"\t"<<"2.Search by author name"<<"\t"<<"3.Search By Category"<<endl;
   cin>>ch;
   fstream fil;
   fil.open("lib.dat",ios::binary|ios::out|ios::in);
   switch(ch)
     {
	case 1:  cout<<"Enter the name of the book to be searched"<<endl;
		 gets(bookname);
		 cout<<endl<<" The following books have the name "<< bookname<<" in the library "<<":"<<endl;
		 cout<<" Accession Number \t Book Name \t Number in stock"<<endl;
		 while(fil.read((char*)&d,sizeof(d)))
		  { if(!strcmp(bookname,d.Rname()))
		    cout<<"\t"<<d.rino()<<"\t"<<d.Rname()<<"\t"<<d.Rqnty()<<endl;
		  }
		 break;

	case 2:  cout<<"Enter the name of the author whose books you want to search:";
		 gets(aname);
		 cout<<endl<<" The following books in the library have been written by "<<aname<<":"<<endl;
		 cout<<" Accession Number \t Book Name \t Number in stock"<<endl;
		 while(fil.read((char*)&d,sizeof(d)))
		   { if(!strcmp(aname,d.Rauthname()))
		      cout<<"\t"<<d.rino()<<"\t"<<d.Rname()<<"\t"<<d.Rqnty()<<endl;
		   }
		  break;

	case 3:  cout<<" The following Categories are available:"<<endl;
		 gotoxy(30,30);cout<<" A) Thriller .";
		 gotoxy(30,34);cout<<" B) Biographies.";
		 gotoxy(30,38);cout<<" C) Physics.";
		 gotoxy(30,42);cout<<" D) Maths.";
		 gotoxy(30,46);cout<<" E) Computer science."<<endl<<endl;
		 cout<<" Enter your choice>:";
		 cin>>categ;
		 cout<<endl<<" The following books in the library are of type "<<categ<<":"<<endl;
		 cout<<" Accession Number\t Book Name\t Number in stock"<<endl<<endl;
		 while(fil.read((char*)&d,sizeof(d)))
		  { if(categ==d.Rcategory())
		    cout<<"\t"<<d.rino()<<"\t"<< d.Rname()<<"\t"<<d.Rqnty()<<endl;
		  }
		 break;
      }

       cout<<endl<<endl<<"Do you want to issue any of the books shown above??(y/n)"<<endl;
       cin>>issuechoice;
	if(issuechoice=='y')
	  { cout<<" Enter the Accession Number of the book you want to issue";
	    cin>>cino;
	    fil.seekg(0,ios::beg);
	    while(f==0&&fil.read((char*)&d,sizeof(d)))
	      { if(d.rino()==cino)
		 { d.issuechange();
		   int n=fil.tellg()-sizeof(d);
		   fil.seekp(n);
		   fil.write((char*)&d,sizeof(d));
		   f++;
		 }
	      }

		 if(f)
		 cout<<"No such record found. Quitting";
	 }
      fil.close();
}

void rreturn()
{ library d;
  char returnbook[80]; int found=0;
  cout<<endl<<"Enter the name of the book you want to return:"<<endl;
  gets(returnbook);
  fstream fill;
  fill.open("lib.dat",ios::binary|ios::out|ios::in);
   while(fill.read((char*)&d,sizeof(d))&&(found==0))
    { if(strcmp(d.Rname(),returnbook)==0&&(d.Rqnty()<d.Rqntyi()))
	  {  d.returnchange();
	     int n=fill.tellg()-sizeof(d);
	     fill.seekp(n);
	     fill.write((char*)&d,sizeof(d));
	     found++;
	     cout<<returnbook<<"\t has been returned"<<endl;
	  }
       else
       cout<<"No such book in our records"<<endl;
    }
  fill.close();
}

void Delete()
{ fstream fil, fil2;
  library s;
  int inod;
  fil.open("lib.dat",ios::binary|ios::in);
  fil2.open("temp.dat",ios::binary|ios::out);
  cout<<"Enter ACCESSION NO. of the book to be deleted"<<endl;
  cin>>inod;
  int del=0;
  while(fil.read((char*)&s,sizeof(s))&&(del==0))
      {
       if(s.rino()!=inod)
	fil2.write((char*)&s,sizeof(s));
       else
	del++;
      }
   fil2.write((char*)&s,sizeof(s));
  if(del==0)
   cout<<"Book match not found"<<endl;
  else
   cout<<"Book"<<s.Rname()<<"deleted"<<endl;
  fil.close();
  fil2.close();
  remove("lib.dat");
  rename("temp.dat","lib.dat");
}

void main()
{ login(); }

void login()
{
    Color(BLACK,WHITE);
    clrscr();
    char id[20];char password[20];
    cout<<"                      LOGIN WINDOW:\n\n";
    cout<<"                      Enter ID:";
    gets(id);
    cout<<"                      Enter Password:";
    char ch;
    int i=0;
    do
     {
      ch=getch();
      cout<<"*";
      password[i++]=ch;
     }while(ch!=13);
    password[i-1]='\0';
    if(strcmp(password,"dbrox")==0 && strcmp(id,"hitman")==0 )
     {
      clrscr();
      gotoxy(10,2);
      cout<<"LOADING" <<endl;
      for(int i=1;i<71;i++)
       {
	cout<<".";
	delay(30);
       }
      clrscr();
      gotoxy(15,10);
      cout<<"WELCOME TO OUR LIBRARY MANAGEMENT SYSTEM"<<endl;
      getch();
      clrscr();
      Menu();
    }
   else
    {
     cout<<endl<<"Wrong password.Please try again."<<endl;
     cout<<"Enter Any key to continue";
     getch();
     login();
    }
  getch();
 }
 void Menu()
 {
   int choice;library l;
    do
      {
       clrscr();

       cout<<" MAIN MENU\n"<<endl;
       cout<<"1.ADD A BOOK\n2.DISPLAY BOOKS\n3.ISSUE A BOOK\n4.RETURN A BOOK\n5.DELETION OF BOOK\n6.EDITING RECORDS\n7.EXIT"<<endl;
       cin>>choice;
       switch(choice)
	   {
	   case 1:serialnumber();
		break;
	   case 2:display();
		break;
	   case 3:search();
		break;
	   case 4:rreturn();
		break;
	   case 5:Delete();
		  break;
	   case 6:Edit();
		  break;
	   case 7: Quit();

	   }
       }while(choice!=7);
 }
