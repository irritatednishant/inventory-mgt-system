
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

void login();
void registration();

class dept
{
	int Item_code;
	char itm_name[30];
	char c_name[30];
	int no_item;
	int price;
	char date[10];

public:
	void control_panel();
	void add_item();
	void display_item();
	void check_item();
	void update_item();
	void delete_item();
	void generate_report();
};

void dept ::control_panel()
{

	system("Color 0A");
	system("cls");
	cout << "**********************************************"
			"**********************************";
	cout << "\n\n\t\t\tInventory Management System";
	cout << "\n\n\t\t\t\t Control Panel\n";
	cout << "\n********************************************"
			"************************************\n";
	cout << "\n\n\t\t\t 1. Add New Item";

	cout << "\n\t\t\t 2. Display Items";
	cout << "\n\t\t\t 3. Check Specific Item";

	cout << "\n\t\t\t 4. Update Item";

	cout << "\n\t\t\t 5. Delete Item";
	cout << "\n\t\t\t 6. Generate Report";
	cout << "\n\t\t\t 7. Exit";
}

void dept::add_item()
{
	fstream file;
	string IdStr;
	bool valid = false;
	bool exists = false;

	cout << "\n\n\t\t\t\t\t Add New Item: \n";
	cout << "----------------------------------------------"
			"----------------------------\n";

	while (!valid)
	{
		cout << "\n\t\t\tEnter Item ID: ";
		cin >> IdStr;

		valid = true;
		for (int i = 0; IdStr[i] != '\0'; ++i)
		{
			if (!isdigit(IdStr[i]))
			{
				valid = false;
				cout << "\n\t\tInvalid input! Item ID must be an integer." << endl;
				break;
			}
		}

		if (valid)
		{
			Item_code = 0;
			for (int i = 0; IdStr[i] != '\0'; ++i)
			{
				Item_code = Item_code * 10 + (IdStr[i] - '0');
			}

			file.open("item.dat", ios::in | ios::binary);
			if (file.is_open())
			{
				int temp_code;
				exists = false;
				while (file.read((char *)&temp_code, sizeof(temp_code)))
				{
					file.seekg(sizeof(itm_name) + sizeof(c_name) + sizeof(price) + sizeof(no_item), ios::cur);
					if (temp_code == Item_code)
					{
						exists = true;
						break;
					}
				}
				file.close();
			}

			if (exists)
			{
				cout << "\t\t\tError: Item with ID " << IdStr << " already exists." << endl;
				valid = false;
			}
		}
	}

	cout << "----------------------------------------------"
			"----------------------------\n";
	cout << "\n\n\t\t\tItem Name: ";
	cin.ignore();
	cin.getline(itm_name, 30);

	cout << "\n\n\t\t\tCompany Name: ";
	cin.getline(c_name, 30);

	string priceStr;
	valid = false;
	while (!valid)
	{
		cout << "\n\n\t\t\tEnter Item Price: ";
		cin >> priceStr;

		valid = true;
		for (int i = 0; priceStr[i] != '\0'; ++i)
		{
			if (!isdigit(priceStr[i]))
			{
				valid = false;
				cout << "\n\t\tInvalid input! Item price must be an integer." << endl;
				break;
			}
		}
	}

	price = 0;
	for (int i = 0; priceStr[i] != '\0'; ++i)
	{
		price = price * 10 + (priceStr[i] - '0');
	}

	string countStr;
	valid = false;
	while (!valid)
	{
		cout << "\n\n\t\t\tEnter Item count: ";
		cin >> countStr;

		valid = true;
		for (int i = 0; countStr[i] != '\0'; ++i)
		{
			if (!isdigit(countStr[i]))
			{
				valid = false;
				cout << "\n\t\tInvalid input! Item count must be an integer." << endl;
				break;
			}
		}
	}

	no_item = 0;
	for (int i = 0; countStr[i] != '\0'; ++i)
	{
		no_item = no_item * 10 + (countStr[i] - '0');
	}

	cout << "\n\t\t\tEnter date (DD/MM/YYYY): ";
	cin.ignore();
	cin.getline(date, 11);

	file.open("item.dat", ios::app | ios::binary);
	if (file.is_open())
	{
		file.write((char *)&Item_code, sizeof(Item_code));
		file.write((char *)&itm_name, sizeof(itm_name));
		file.write((char *)&c_name, sizeof(c_name));
		file.write((char *)&price, sizeof(price));
		file.write((char *)&no_item, sizeof(no_item));
		file.write((char *)&date, sizeof(date));
		file.close();
		cout << "\t\t\tItem added successfully!" << endl;
	}
	else
	{
		cout << "\t\t\tError opening file..." << endl;
	}
}

void dept ::display_item()
{
	system("cls");
	system("Color 0A");
	dept item;
	fstream file;
	int no_item, Item_code;
	char itm_name[30];
	char c_name[30];
	file.open("item.dat", ios::in | ios::binary);
	if (!file.is_open())
	{
		cout << "File Opening Error.......";
	}
	else
	{
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << setw(20) << left << "\tItem Code"
			 << setw(15) << left << "Item Name"
			 << setw(20) << left << "Company Name"
			 << setw(10) << left << "Price"
			 << setw(15) << left << "No. of Items"
			 << setw(10) << left << "Entry Date\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
	}
	while (file.read((char *)&Item_code, sizeof(Item_code)))
	{
		file.read((char *)&itm_name, sizeof(itm_name));
		file.read((char *)&c_name, sizeof(c_name));
		file.read((char *)&price, sizeof(price));
		file.read((char *)&no_item, sizeof(no_item));
		file.read((char *)&date, sizeof(date));
		cout << "\t" << setw(20) << left << Item_code
			 << setw(15) << left << itm_name
			 << setw(20) << left << c_name
			 << setw(10) << left << price
			 << setw(15) << left << no_item
			 << setw(15) << left << date << "\n";
	}
	cout << "=========================================="
			"======================================================================"
		 << endl;

	file.close();
}

void dept ::check_item()

{
	system("cls");

	system("Color 0A");
	fstream file;
	int count = 0;
	cout << "\n\n\t\t\t\t\t Check Specific Product\n";
	cout << "----------------------------------------------"
			"----------------------------------\n";
	file.open("item.dat", ios::in | ios::binary);
	if (!file)
	{
		cout << "\t\t\tFile Opening Error....";
	}
	else
	{
		int It_code;
		cout << "\n\n\t\t\t Item Code: ";
		cin >> It_code;
		cout << "\n----------------------------------------"
				"----------------------------------\n";

		while (file.read((char *)&Item_code, sizeof(Item_code)))
		{
			file.read((char *)&itm_name, sizeof(itm_name));
			file.read((char *)&c_name, sizeof(c_name));
			file.read((char *)&price, sizeof(price));
			file.read((char *)&no_item, sizeof(no_item));
			file.read((char *)&date, sizeof(date));
			if (It_code == Item_code)
			{
				system("cls");
				cout
					<< "\n\n\t\t\t\t\tCheck Specific Product";
				cout << "\n\n\t\t\tItem Code : " << Item_code;
				cout << "\n\n\t\t\tItem Name : "
					 << itm_name;
				cout << "\n\n\t\t\tCompany : " << c_name;
				cout << "\n\n\t\t\tPrice : " << price;
				cout << "\n\n\t\t\tNo. of Item : "
					 << no_item;
				cout << "\n\n\t\t\tDate : " << date;
				count++;
				break;
			}
		}
		file.close();
		if (count == 0)
		{
			cout << "\t\t\tItem Not Found....";
		}
	}
}

void dept::update_item()
{
	system("cls");
	fstream file1, file2;
	file1.open("item.dat", ios::in | ios::binary);
	file2.open("temp.dat", ios::out | ios::binary);
	int count = 0, x;
	int temp_id;
	char temp_itm_name[30] = {0};
	char temp_c_name[30] = {0};
	int temp_price = 0;
	int temp_count = 0;
	char temp_date[10];
	if (!file1)
	{
		cout << "\t\t\tError while opening File!!";
	}
	else
	{
		cout << "\t\t\tEnter the Item ID you want to update details for" << endl;
		cout << "\t\t\tEnter ID : ";
		cin >> temp_id;
		while (file1.read((char *)&Item_code, sizeof(Item_code)))
		{
			file1.read((char *)&itm_name, sizeof(itm_name));
			file1.read((char *)&c_name, sizeof(c_name));
			file1.read((char *)&price, sizeof(price));
			file1.read((char *)&no_item, sizeof(no_item));
			file1.read((char *)&date, sizeof(date));

			if (temp_id == Item_code)
			{
				int updateChoice;
				system("cls");

				cout << "--------------------------------------------------------------------";
				cout << "\n\t\tUpdating Item Details for  ID : "
					 << temp_id << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cout << "\n\t\tWhat do you want to update??\n"
					 << endl;
				cout << "\t\t\t1.Item name\n\t\t\t2.Company Name\n\t\t\t3.Price\n\t\t\t4.Count\n\t\t\t5.Date\n\t\t\t6.Exit" << endl;
				cout << "\t\t\tEnter Choice : ";
				cin >> updateChoice;
				system("cls");

				switch (updateChoice)
				{
				case 1:
					cout << "\t\t\tUpdate Item Name : ";
					cin >> temp_itm_name;
					for (int i = 0; c_name[i] != '\0'; ++i)
					{
						temp_c_name[i] = c_name[i];
					}
					temp_price = price;
					temp_count = no_item;
					for (int i = 0; date[i] != '\0'; ++i)
					{
						temp_date[i] = date[i];
					}
					break;

				case 2:
					for (int i = 0; itm_name[i] != '\0'; ++i)
					{
						temp_itm_name[i] = itm_name[i];
					}
					cout << "\t\t\tUpdate Company Name : ";
					cin >> temp_c_name;
					temp_price = price;
					temp_count = no_item;
					for (int i = 0; date[i] != '\0'; ++i)
					{
						temp_date[i] = date[i];
					}
					break;

				case 3:
					for (int i = 0; itm_name[i] != '\0'; ++i)
					{
						temp_itm_name[i] = itm_name[i];
					}
					for (int i = 0; c_name[i] != '\0'; ++i)
					{
						temp_c_name[i] = c_name[i];
					}

					cout << "\t\t\tUpdate Price : ";
					cin >> temp_price;

					temp_count = no_item;
					for (int i = 0; date[i] != '\0'; ++i)
					{
						temp_date[i] = date[i];
					}
					break;

				case 4:
					for (int i = 0; itm_name[i] != '\0'; ++i)
					{
						temp_itm_name[i] = itm_name[i];
					}
					for (int i = 0; c_name[i] != '\0'; ++i)
					{
						temp_c_name[i] = c_name[i];
					}
					temp_price = price;
					cout << "\t\t\tUpdate Item count : ";
					cin >> temp_count;
					for (int i = 0; date[i] != '\0'; ++i)
					{
						temp_date[i] = date[i];
					}

					break;

				case 5:
					for (int i = 0; itm_name[i] != '\0'; ++i)
					{
						temp_itm_name[i] = itm_name[i];
					}
					for (int i = 0; c_name[i] != '\0'; ++i)
					{
						temp_c_name[i] = c_name[i];
					}
					temp_price = price;
					temp_count = no_item;
					cin.ignore();
					cout << "\t\t\tUpdate Date : ";
					cin >> temp_date;
					break;

				case 6:
				    exit(0);
					break;
				}
				file2.write((char *)&Item_code, sizeof(Item_code));
				file2.write((char *)&temp_itm_name, sizeof(temp_itm_name));
				file2.write((char *)&temp_c_name, sizeof(temp_c_name));
				file2.write((char *)&temp_price, sizeof(temp_price));
				file2.write((char *)&temp_count, sizeof(temp_count));
				file2.write((char *)&temp_date, sizeof(temp_date));
				count++;
				x = Item_code;
			}
			else
			{
				file2.write((char *)&Item_code, sizeof(Item_code));
				file2.write((char *)&itm_name, sizeof(itm_name));
				file2.write((char *)&c_name, sizeof(c_name));
				file2.write((char *)&price, sizeof(price));
				file2.write((char *)&no_item, sizeof(no_item));
				file2.write((char *)&date, sizeof(date));
			}
		}
	}
	file1.close();
	file2.close();
	if (count == 0)
	{
		cout << "\t\t\tItem Doesn't Exist!";
		update_item();
	}
	else
	{
		cout << "\t\t\tDetails for Item Id " << x << " is updated successfully!!\n"
			 << endl;
		system("pause");
		system("cls");
	}

	remove("item.dat");
	rename("temp.dat", "item.dat");
}

void dept::delete_item()
{
	fstream file, file2;
	file.open("item.dat", ios::in);
	file2.open("temp.dat", ios::out);

	if (!file)
	{
		cout << "\n\n\t\t\t File opening error...";
		return;
	}

	int it_code, count = 0;
	int Item_code, no_item;
	char itm_name[30], c_name[30];
	int price;

	cout << "Item code : ";
	cin >> it_code;

	while (file.read((char *)&Item_code, sizeof(Item_code)))
	{
		file.read((char *)&itm_name, sizeof(itm_name));
		file.read((char *)&c_name, sizeof(c_name));
		file.read((char *)&price, sizeof(price));
		file.read((char *)&no_item, sizeof(no_item));
		file.read((char *)&date, sizeof(date));
		if (it_code != Item_code)
		{
			file2.write((char *)&Item_code, sizeof(Item_code));
			file2.write((char *)&itm_name, sizeof(itm_name));
			file2.write((char *)&c_name, sizeof(c_name));
			file2.write((char *)&price, sizeof(price));
			file2.write((char *)&no_item, sizeof(no_item));
			file2.write((char *)&date, sizeof(date));
		}

		else
		{

			count++;
		}
	}

	file.close();
	file2.close();

	if (count == 0)
	{
		cout << "\t\t\tItem does not exist..." << endl;
	}
	else
	{
		cout << "\t\t\tItem deleted successfully..." << endl;

		remove("item.dat");
		rename("temp.dat", "item.dat");
	}
}
 
 void dept::generate_report()
{
    fstream file;
    file.open("item.dat", ios::in | ios::binary);
    
    if (!file.is_open()) {
        cout << "File opening error...\n";
        return;
    }
    
    int totalItems = 0;
    int totalValue = 0;
    int totalEntries = 0;
    
    cout << "\n\n\t\t\t Inventory Report\n";
    cout << "---------------------------------------------------------------------\n";
    cout << setw(10) << left << "Item Code"
         << setw(15) << left << "Item Name"
         << setw(20) << left << "Company Name"
         << setw(10) << left << "Price"
         << setw(10) << left << "Count"
         << setw(15) << left << "Entry Date\n";
    cout << "---------------------------------------------------------------------\n";

    while (file.read((char *)&Item_code, sizeof(Item_code))) {
        file.read((char *)&itm_name, sizeof(itm_name));
        file.read((char *)&c_name, sizeof(c_name));
        file.read((char *)&price, sizeof(price));
        file.read((char *)&no_item, sizeof(no_item));
        file.read((char *)&date, sizeof(date));

        cout << setw(10) << left << Item_code
             << setw(15) << left << itm_name
             << setw(20) << left << c_name
             << setw(10) << left << price
             << setw(10) << left << no_item
             << setw(15) << left << date << "\n";

        totalItems += no_item;
        totalValue += price * no_item;
        totalEntries++;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "\n\tTotal number of items: " << totalItems;
    cout << "\n\tTotal value of inventory: $" << totalValue;
    cout << "\n\tTotal number of entries: " << totalEntries;
    cout << "\n---------------------------------------------------------------------\n";
    
    file.close();
    
    // Optionally save this report to a file
    fstream reportFile;
    reportFile.open("inventory_report.txt", ios::out);
    
    if (reportFile.is_open()) {
        reportFile << "Inventory Report\n";
        reportFile << "---------------------------------------------------------------------\n";
        reportFile << setw(10) << left << "Item Code"
                   << setw(15) << left << "Item Name"
                   << setw(20) << left << "Company Name"
                   << setw(10) << left << "Price"
                   << setw(10) << left << "Count"
                   << setw(15) << left << "Entry Date\n";
        reportFile << "---------------------------------------------------------------------\n";

        file.open("item.dat", ios::in | ios::binary);
        while (file.read((char *)&Item_code, sizeof(Item_code))) {
            file.read((char *)&itm_name, sizeof(itm_name));
            file.read((char *)&c_name, sizeof(c_name));
            file.read((char *)&price, sizeof(price));
            file.read((char *)&no_item, sizeof(no_item));
            file.read((char *)&date, sizeof(date));

            reportFile << setw(10) << left << Item_code
                       << setw(15) << left << itm_name
                       << setw(20) << left << c_name
                       << setw(10) << left << price
                       << setw(10) << left << no_item
                       << setw(15) << left << date << "\n";
        }
        
        reportFile << "---------------------------------------------------------------------\n";
        reportFile << "\nTotal number of items: " << totalItems;
        reportFile << "\nTotal value of inventory: $" << totalValue;
        reportFile << "\nTotal number of entries: " << totalEntries;
        reportFile << "\n---------------------------------------------------------------------\n";
        
        reportFile.close();
        cout << "\nReport saved to 'inventory_report.txt'\n";
    } else {
        cout << "Error saving report to file...\n";
    }
}




int main()
{
	system("cls");
	system("color 6");
	bool flag = true;

	while (flag)
	{
		int choice;
		cout << "\t\t\t_______________________________________________________________________________\n\n\n";
		cout << "\t\t\t______________________       WELCOME TO LOGIN PAGE        _____________________\n\n\n";
		cout << "\t\t\t___________________________          MENU        ______________________________\n\n\n";
		cout << "\t\t\t                                                                                \n\n\n";
		cout << "\t\t\t| PRESS 1 TO LOGIN               |" << endl;
		cout << "\t\t\t| PRESS 2 TO REGISTER            |" << endl;
		cout << "\t\t\t| PRESS 3 TO EXIT                |\n\n"
			 << endl;
		cout << "\t\t\t  Enter your choice : ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			login();
			break;
		case 2:
			registration();
			break;
		case 3:
			cout << "\t\t\tThank you !...";
			flag = false;
			break;

		default:
			cout << "\t\t\tPlease select from the options given above...!\n\t\t\t";
			system("pause");
			// system("cls");
			break;
		}
	}
}
void function()
{

	dept d;
	while (true)
	{

		d.control_panel();
		int choice;

		char again;
		cout << "\n\n\t\t Your Choice : ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			do
			{
				d.add_item();
				cout << "\t\t\tDo You Want To Add Another Item (y/n) "
						": ";
				cin >> again;
			} while (again == 'y' || again == 'Y');
			break;
		case 2:
			d.display_item();
			break;
		case 3:
			d.check_item();
			break;

		case 4:
			d.update_item();
			break;
		case 5:
			d.delete_item();
			break;
		case 6:
			d.generate_report();
			break;
		case 7:
			exit(0);
			break;

		default:
			cout << "\n\n Invalid Value....Please Try again";
			main();
		}

		cout << "\n";
		getch();
	}
}

void login()
{
	system("color 3");
	int count = 0;
	char userID[30], password[15], id[30], pass[15];
    int index = 0;
	cout << "\t\t\tEnter user ID and Password.\n";
	cout << "\t\t\tUser ID : ";
	cin >> userID;
	cout << "\t\t\tPassword : ";
	
	
    char ch;
    while (true) {
        ch = getch(); 
        if (ch == 13) { 
            password[index] = '\0'; 
            break;
        } else if (ch == 8) { 
            if (index > 0) {
                cout << "\b \b"; 
                index--;
            }
        } else if (index < 14) { 
            password[index] = ch; 
            cout <<'*'; 
            index++;
        }
    }

	fstream file;
	file.open("login.dat", ios::in | ios::binary);
	while (file.read((char *)&id, sizeof(id)) && file.read((char *)&pass, sizeof(pass)))
	{

		if (strcmp(id, userID) == 0)
		{
			if (strcmp(pass, password) == 0)
			{
				count++;
				break;
			}
		}
	}

	if (count == 1)
	{
		cout << "\t\t\tlogin Successful...";
		system("pause");
		function();
	}
	else
	{
		cout << "\n LOGIN ERROR \n Please check your username and password";
		system("pause");
		main();
	}

	file.close();
}


void registration()
{
	system("color 2");
	char userID[30], password[15];
	bool isValidPassword = false;
	bool isUniqueUsername = false;
	fstream file2;

    system("cls");


    while (!isUniqueUsername) {
        cout << "\t\t\tEnter username : ";
        cin >> userID;

        file2.open("login.dat", ios::in | ios::binary);
        if (!file2) {
            cout << "error opening file...!";
            return;
        }

        char existingUserID[30];
        bool usernameExists = false;


        while (file2.read((char *)&existingUserID, sizeof(existingUserID))) {

            if (strcmp(userID, existingUserID) == 0) {
                usernameExists = true;
                break;
            }

            file2.seekg(sizeof(char[15]), ios::cur);
        }

        file2.close();

        if (usernameExists) {
            cout << "\t\t\tUsername already exists!!! Please try again.\n";
        } else {
            isUniqueUsername = true;
        }
    }

	

	while (!isValidPassword)
	{
		cout << "\t\t\tEnter password : ";
		cin >> password;

		bool hasLetter = false, hasDigit = false, hasSpecial = false;

		
		for (int i = 0; i < strlen(password); ++i)
		{
			if (isalpha(password[i]))
				hasLetter = true;
			else if (isdigit(password[i]))
				hasDigit = true;
			else if (ispunct(password[i])) 
				hasSpecial = true;
		}

		if (hasLetter && hasDigit && hasSpecial && strlen(password) >= 8) 
		{
			isValidPassword = true;
		}
		else
		{
			cout << "\t\t\tPassword must contain at least one letter, one number, one special character, and be at least 8 characters long.\n";
		}
	}


	fstream file;
	file.open("login.dat", ios::app | ios::binary);
	if (!file)
	{
		cout << "error opening file...!";
	}
	else
	{
		file.write((char *)&userID, sizeof(userID));
		file.write((char *)&password, sizeof(password));
	}
	file.close();
	system("cls");
	cout << "\t\t\tRegistration successful...!";
	main();
}
