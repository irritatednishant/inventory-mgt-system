
#include <conio.h>
#include <fstream>
#include <iostream>
// #include <string>
using namespace std;

class dept
{
	int Item_code;
	string itm_name;
	string c_name;
	int no_item;
	double price;

public:
	void control_panel();
	void add_item();
	void display_item();
	void check_item();
	void update_item();
	void delete_item();
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
	cout << "\n\n 1. Add New Item";

	cout << "\n 2. Display Items";
	cout << "\n 3. Check Specific Item";

	cout << "\n 4. Update Item";

	cout << "\n 5. Delete Item";
	cout << "\n 6. Exit";
}

void dept ::add_item()
{
	system("cls");

	system("Color 0A");
	fstream file;
	int no_item, Item_Id;
	string itm_name;
	string c_name;
	double price;
	cout << "\n\n\t\t\t\t Add New Item: \n";
	cout << "----------------------------------------------"
			"----------------------------\n";
	cout << " Item Code : ";
	cin >> Item_Id;
	cout << "----------------------------------------------"
			"----------------------------\n";
	cout << "\n\n Item Name: ";
	cin >> itm_name;
	cout << "\n\n Company Name: ";
	cin >> c_name;
	cout << "\n\nPrice of item : ";
	cin >> price;
	cout << "\n\n No. Of Item: ";
	cin >> no_item;
	file.open("item1.txt", ios::out | ios::app);
	file << " " << Item_Id << " " << itm_name << " "
		 << c_name << " " << price << " " << no_item << "\n";
	cout << "=============================================="
			"============================"
		 << endl;
	file.close();
}

void dept ::display_item()
{
	system("cls");

	system("Color 0A");
	fstream file;
	int no_item, Item_code;
	string itm_name;
	string c_name;
	file.open("item1.txt", ios::in);
	if (!file)
	{
		cout << "File Opening Error....";
	}
	else
	{
		cout << "------------------------------------------"
				"---------------------------------\n";
		cout << "item code       item name       company name       price       no. of item\n";
		cout << "------------------------------------------"
				"---------------------------------"
			 << endl;
		file >> Item_code >> itm_name >> c_name >> price >> no_item;
		while (!file.eof())
		{
			cout << "   " << Item_code << "	         " << itm_name << "		 " << c_name << " \t\t " << price
				 << "\t\t  " << no_item
				 << "\n";
			file >> Item_code >> itm_name >> c_name >> price >> no_item;
		}
		cout << "=========================================="
				"================================="
			 << endl;

		file.close();
	}
}

void dept ::check_item()

{
	system("cls");

	system("Color 0A");
	fstream file;
	int count = 0;
	int Item_code;
	int no_item;
	string itm_name, c_name;
	double price;
	cout << "\n\n\t\t\t\t Check Specific Product\n";
	cout << "----------------------------------------------"
			"----------------------------------\n";
	file.open("item1.txt", ios ::in);
	if (!file)
	{
		cout << "File Opening Error....";
	}
	else
	{
		int It_code;
		cout << "\n\n Item Code: ";
		cin >> It_code;
		cout << "\n----------------------------------------"
				"----------------------------------\n";

		file >> Item_code >> itm_name >> c_name >> price >> no_item;
		while (!file.eof())
		{
			if (It_code == Item_code)
			{
				system("cls");
				cout
					<< "\n\n\t\t\t\tCheck Specific Product";
				cout << "\n\nItem Code : " << Item_code;
				cout << "\n\nItem Name : "
					 << itm_name;
				cout << "\n\nCompany : " << c_name;
				cout << "\n\nPrice : " << price;
				cout << "\n\nNo. of Item : "
					 << no_item;
				count++;
				break;
			}

			file >> Item_code >> itm_name >> c_name >> price >> no_item;
		}
		file.close();
		if (count == 0)
		{
			cout << "Item Not Found....";
		}
	}
}

void dept::update_item()
{
	system("cls");

	system("Color 0A");
	fstream file, file2;
	file.open("item1.txt", ios ::in | ios::out | ios::app);
	file2.open("temp.txt", ios::out);
	int it_code;
	int no_it;
	string it_name, cmp_name;
	double p;
	int count = 0;

	if (!file)
		cout << "\n\n\tFile Opening Error...";
	else
	{
		cout << "\n\n Item Code : ";
		cin >> it_code;
		cout << "\n----------------------------------------"
				"----------------------------------\n";
		file >> Item_code >> itm_name >> c_name >> price >> no_item;
		while (!file.eof())
		{
			if (Item_code == it_code)
			{
				system("cls");

				cout << "\n\nUpdate Book Record";
				cout << "\n\nNew Item Name : ";

				cin >> it_name;
				cout << "\n\nCompany Name : ";

				cin >> cmp_name;
				cout << "\n\nEnter price : ";
				cin >> p;
				cout << "\n\nNo. of Items : ";

				cin >> no_it;
				file2 << " " << it_code << " " << it_name
					  << " " << cmp_name << " " << p << " " << no_it
					  << "\n";
				count++;
			}
			else
			{
				file2 << " " << Item_code << " " << itm_name
					  << " " << c_name << " " << price << " " << no_item
					  << "\n";
			}

			file >> Item_code >> itm_name >> c_name >> price >> no_item;
		}
		if (count == 0)
		{
			cout << " no item found.....";
		}
	}
	file.close();
	file2.close();
	remove("item1.txt");
	file.open("item1.txt", ios::out);
	file2.open("temp.txt");
	if (file.is_open())
	{
		string line;
		while (getline(file2, line))
		{
			file << line << endl;
		}
		file2.close();
		cout << "\n\nItem Updated......";
	}
	else
		cout << "file updating error";
	file.close();
	remove("temp.txt");
}

void dept::delete_item()
{
	fstream file, file2;
	file.open("item1.txt", ios::in);
	file2.open("temp.txt", ios::out);

	if (!file)
	{
		cout << "\n\n File opening error...";
		return;
	}

	int it_code, count = 0;
	int Item_code, no_item;
	string itm_name, c_name;
	double price;

	cout << "Item code : ";
	cin >> it_code;
            
	file >> Item_code >> itm_name >> c_name >> price >> no_item;
	while (!file.eof())
	{
		if (it_code != Item_code)
		{
			file2 << Item_code << " " << itm_name << " " << c_name << " " << price << " " << no_item << endl;

			file >> Item_code >> itm_name >> c_name >> price >> no_item;
		}

		else
		{

			count++;
			file >> Item_code >> itm_name >> c_name >> price >> no_item;
		}
	}

	file.close();
	file2.close();

	if (count == 0)
	{
		cout << "Item does not exist..." << endl;
	}
	else
	{
		cout << "Item deleted successfully..." << endl;

		remove("item1.txt");
		rename("temp.txt", "item1.txt");
	}
}
int main()
{
	dept d;
	while (true)
	{

		d.control_panel();
		int choice;

		char x;
		cout << "\n\n Your Choice : ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			do
			{
				d.add_item();
				cout << "Do You Want To Add Another Item (y/n) "
						": ";
				cin >> x;
			} while (x == 'y');
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
			exit(0);
			break;

		default:
			cout << "\n\n Invalid Value....Please Try again";
		}

		cout << "\n";
		getch();
	}
}
