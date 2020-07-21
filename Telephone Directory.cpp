//Shobhitaa Barik
//XII A
//Cs Project: Telephone Directory

#include<iostream>
#include<fstream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>

using namespace std;

class info
{
protected:
    char name[30];
    int hno;
    char to[10];
    long tno;

public:

    void smem();

    void putdata1()
    {
        cout<<endl<<endl;
        cout<<"\tName: "<<name<<endl;
        cout<<"\tHouse number: "<<hno<<endl;
        cout<<"\tTelephone number: "<<tno<<endl;
        cout<<"\tAuthority over the house: "<<to<<endl;
    }

    int houseno()
    {
        return hno;
    }

};

class edit_data: public info
{
public:
    void smod();
    void ed();
    void edel();
};

int x=1;

int main();
int show_no(int);
void edit_menu();

void info:: smem()
{
      cout<<"\n\n\tEnter name: ";
      cin.ignore(50,'\n');
      gets(name);
      cout<<"\n\tEnter house no.: ";
      cin>>hno;
      cout<<"\n\tEnter telephone no.: ";
      cin>>tno;
      cout<<"\n\tTenant or Owner: ";
      cin.ignore(50,'\n');
      gets(to);
}

void form(int &x)
{
    system("cls");

    cout<<"================================================================================"<<endl;
    cout<<"\n\t\t\t      SOCIETY MEMBER FORM\n";
    cout<<"\t\t\t      ___________________\n";

    if(x==0)
    {
        info M1;
        char chin;
        ofstream fout;
        fout.open("smem.dat",ios::binary|ios::out);
        M1.smem();
        fout.write((char*)&M1,sizeof(M1));
        fout.close();
        x=1;
        cout<<"\n\n   press any key to go back to main menu...";
        cin>>chin;
        main();
    }
    A:

    info M1;
    info M2;

    char ch='n';
    ifstream fin("smem.dat",ios::in|ios::binary);
    ofstream fout("temp.dat",ios::out|ios::binary|ios::app);
    M2.smem();
    fin.read((char*)&M1,sizeof(M1));
    while(!fin.eof()&&ch=='n')
    {
        if(M2.houseno()<=M1.houseno())
        {
            fout.write((char*)&M2,sizeof(M2));
            ch='y';
            break;
        }
        else
        {
            fout.write((char*)&M1,sizeof(M1));
        }
        fin.read((char*)&M1,sizeof(M1));
    }

    if(ch=='y')
    {
        while(!fin.eof())
        {
            fout.write((char*)&M1,sizeof(M1));
            fin.read((char*)&M1,sizeof(M1));
        }
    }

    else
    {
        fout.write((char*)&M2,sizeof(M2));
    }

    fin.close();
    fout.close();
    remove("smem.dat");
    rename("temp.dat","smem.dat");

    char ch7;

    cout<<"\n\n   press any key to go back to main menu...";
    cin>>ch7;
    main();

}

///////////////**DISPLAY**//////////////

void read_data1()
{
    info M1;
    ifstream fin;
    fin.open("smem.dat",ios::in|ios::binary);

    while(!fin.eof())
    {
        while(fin.read((char*)&M1,sizeof(M1)))
        {
            M1.putdata1();
        }
    }

    fin.close();

}

void display(int x)
{
	system("cls");
	char ch;
    cout<<"\n\n\t\t     +++++++++++++++++++++++++++++++++++++";
    cout<<"\n\n\t\t\t         MAIN DIRECTORY\n\n";
    cout<<"\t\t     +++++++++++++++++++++++++++++++++++++\n\n";
    if(x==0)
    {
        cout<<"\t\tDirectory is empty...";
        cout<<"\n\t\tPress any key to go to main menu: ";
        cin>>ch;
        main();
    }
    else
    {
	read_data1();
	cout<<"\n   Press any key to go to main menu... ";
	cin>>ch;
    main();
    }
}

////////////////**SEARCH DATA**///////////////

void search_data()
{
    system("cls");
    int n;
    char cha1;
    cout<<"\n\n     SEARCH BY HOUSE NUMBER:";
    cout<<"\n     _______________________";
    A:
    cout<<"\n\n\n\tEnter hno: ";
    cin>>n;
    show_no(n);

    cout<<"\n\n   press f to search another record"<<endl;
    cout<<"   press any other key to go to main menu"<<endl;

    cout<<"   Enter choice: ";
    cin>>cha1;
    if (cha1=='f'||cha1=='F')
    goto A;
    else
    main();
}

int show_no(int n)
{
    info M1;
    int x=0;
    int ed=0;
    int found=0;
    ifstream fin;
    fin.open("smem.dat",ios::binary);
    fin.seekg(0);

        while(fin.read((char*)&M1,sizeof(M1)))
        {
            x= M1.houseno();
            if(x==n)
            {
                found=1;
                break;
            }
            else
                continue;
        }


        if(found==1)
            M1.putdata1();

        else
        {
            cout<<"\n\tRecord does not exist.";
            ed=1;
        }

        fin.close();
        return ed;
}

///////////////**EDIT DATA**//////////////////

void edit_data:: smod()
{
      cout<<"\n\n\tEnter name: ";
      cin.ignore(50,'\n');
      gets(name);
      cout<<"\n\tEnter telephone no.: ";
      cin>>tno;
      cout<<"\n\tTenant or Owner: ";
      cin.ignore(50,'\n');
      gets(to);
}

void edit_data:: ed()
{
    system("cls");
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\n\t\t\t             MODIFY\n";
	cout<<"\t\t\t\t     ======\n\n\n";
    int found = 0,n;
    cout<<"Enter house no of record you want to modify: ";
    cin>>n;
	edit_data E1;
	fstream File;
	File.open("smem.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not open !! Press any key...";
	}
	while (!File.eof()&&found == 0)
	{

		File.read((char*)&E1, sizeof(E1));
		if (E1.houseno() == n)
		{
			E1.putdata1();
			cout << "\n\nPlease enter the new details" << endl;
			E1.smod();
			int pos = (-1)*(sizeof(E1));
			File.seekp(pos, ios::cur);
			File.write((char*)&E1, sizeof(E1));
			cout << "\n\n\tRecord Updated.";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n Record Not Found.";

}


void  edit_data:: edel()
{
    system("cls");
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\n\t\t\t             DELETE\n";
	cout<<"\t\t\t\t     ======\n\n\n";
	cout<<"   Enter house no of record you want to delete: ";
    int n,fi;
    fi=0;
    cin>>n;
    edit_data E2;
	ifstream fin;
	fin.open("smem.dat", ios::binary);
	if (!fin)
	{
		cout << "File could not be open!! Press any key...";
	}

	ofstream fout;
	fout.open("Temp.dat", ios::out);
	fin.seekg(0, ios::beg);
	while (fin.read((char*)&E2,sizeof(E2)))
	{
		if (E2.houseno() != n)
		{
			fout.write((char*)&E2, sizeof(E2));
		}
		else
        {
            fi=1;
        }
	}
	fout.close();
	fin.close();
	remove("smem.dat");
	rename("Temp.dat", "smem.dat");
	if(fi==1)
	cout << "\n\n\tRecord Deleted...";
    else cout<<"\n\n\tRecord does not exist";
}

void edit_menu()
{
    system("cls");
    cout<<"################################################################################"<<endl;
	cout<<"\n\t\t\t           EDIT RECORD\n";
	cout<<"\t\t\t\t   ===========\n\n\n";
    int x;
    edit_data E;
    cout<<"\n\n\t1. Modify data";
    cout<<"\n\n\t2. Delete data";

    A:
    cout<<"\n\n\tEnter choice: ";
    cin>>x;

    switch(x)
    {
        case 1: E.ed();
                break;

        case 2: E.edel();
                break;


        default: cout<<"\n\n\tInvalid.\n";
                 goto A;
    }

    char ch;

    cout<<"\n\n\n   press any key to go to main menu...";

    cin>>ch;
        main();
}

//////////////**RESET**////////////////

void reset(int &x)
{
	system("cls");
	char ch,ch1;
	int cnt=0;
	cout<<"################################################################################"<<endl;
	cout<<"\n\t\t\t\t   RESET DATA\n\n\n";
    char pass[8];
    char PA[9]="ksjimd33";
    cout<<"   Are you sure that you want to delete all the data?(y/n):";

    cin>>ch1;

    if (ch1=='y'||ch1=='Y')
        goto R;
    else
        main();

    R:

    cout<<"\n\n   Enter password: ";
    for(int v=0;v<8;v++)
    {
          pass[v]=getch();
          cout<<"*";
    }

    for(int w=0;w<8;w++)
    {
        if(pass[w]==PA[w])
        cnt++;
    }

    if(cnt==8)
    {
        remove("smem.dat");
        cout<<"\n\n   Process completed. Directory is empty.\n";
        x=0;
    }
    else
    {
        cout<<"\n\n   Wrong password..."<<endl;
    }


	cout<<"\n\n   press any key to go to main menu...";
	cin>>ch;
    main();
}

///////////////////**MAIN MENU**///////////////////////

int main()
 {
     system("cls");
     int ch;

     cout<<"\n\n\t\t     *************************************";
     cout<<"\n\n\t\t        SILVER OAKS TELEPHONE DIRECTORY\n\n";
     cout<<"\t\t     *************************************\n\n";
     cout<<"\n\t\t\t\t   MAIN MENU\n\n\n";
     cout<<"\n\t1. The Main Directory"<<endl;
     cout<<"\n\t2. Forms"<<endl;
     cout<<"\n\t3. Selective Display"<<endl;
     cout<<"\n\t4. Edit Records"<<endl;
     cout<<"\n\t5. Reset"<<endl;
     cout<<"\n\t6. Exit"<<endl;

     M:
     cout<<"\n\tEnter your choice: ";
     cin>>ch;

         switch(ch)
         {
             case 1 :  display(x);
                       break;
             case 2 :  form(x);
                       break;
             case 3 :  search_data();
                       break;
             case 4 :  edit_menu();
                       break;
             case 5 :  reset(x);
                       break;
             case 6 :  exit(0);

             default:  cout<<"\n\tInvalid.\n\n";
                       goto M;
         }

 }

/////////////////////**THE END**//////////////////////////


