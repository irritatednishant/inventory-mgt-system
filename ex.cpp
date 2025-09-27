#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

	
	void login();
	void registration();

int main(){ 
	system("cls");
	system("color 6");
	int choice;
	cout<<"\t\t\t________________________________________________________________-______________\n\n\n";
	cout<<"\t\t\t______________________       WELCOME TO LOGIN PAGE        _____________________\n\n\n";
	cout<<"\t\t\t___________________________          MENU        ______________________________\n\n\n";
	cout<<"\t\t\t                                                                                \n\n\n";
    cout<<"\t\t\t| PRESS 1 TO LOGIN               |"<<endl;
    cout<<"\t\t\t| PRESS 2 TO REGISTER            |"<<endl;
    cout<<"\t\t\t| PRESS 3 TO EXIT                |\n\n"<<endl;
    cout<<"\t\t\t  Enter your choice : ";
    cin>>choice;
	cout<<endl;

    switch (choice)
	{
	case 1: login();
		break;
	case 2: registration();
		break;
	case 3: 
			cout<<"\t\t\tThank you !...";
		break;
	
	default:
			cout<<"\t\t\tPlease select from the optiond givrn above...!\n\t\t\t";
			system("pause");
			main();
		break;
	}



}


void login(){
	system("color 3");
	int count=0;
	char userID[30],password[15],id[30],pass[15];
	cout<<"\t\t\tEnter user ID and Password.\n";
	cout<<"\t\t\tUser ID : ";
	cin>>userID;
	cout<<"\t\t\tPassword : ";
	cin>>password;

	fstream file;
	file.open("login.dat",ios::in|ios::binary);
	 while (file.read((char*)&id, sizeof(id)) && file.read((char*)&pass, sizeof(pass))) {
    
        if (strcmp(id, userID) == 0  ) {
          if( strcmp(pass, password) == 0){
            count++; 
            break;
			
		  }
    }
	}


		if (count==1)
		{
			cout<<"\t\t\tlogin Successful...";
			system("pause");
			main();
		}
		else{
			cout<<"\n LOGIN ERROR \n Please check your username and password";
			system("pause");
			main();
		}
		
	
	file.close();

}
void registration(){
	system("color 2");
	char userID[30],password[15],id[30],pass[15];
   system("cls");
   cout<<"\t\t\tEnetr username : ";
   cin>>userID;
   cout<<"\t\t\tEnter passwrd : ";
   cin>>password;
   fstream file;
   file.open("login.dat",ios::app|ios::binary);
   if(!file){
	cout<<"error opening file...!";
   }
    else{
   file.write((char*)&userID,sizeof(userID));
   file.write((char*)&password,sizeof(password));
	}
   file.close();
   system("cls");
   cout<<"\t\t\tRegestration successful...!";
   main();
}

	
