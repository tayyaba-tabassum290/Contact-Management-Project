#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
void call_menu();
void Add_contact();
char *shrink(char *ptr, int size);
void checkCharPtr(char*ptr);
void checkLongPtr(long long*ptr);
int word_size(char *ptr);
void Save_contact(char *name1, char *name2, long long *num, char *address, char *email);
void ListOfContact(char *filename);
bool searchOfContact(char *filename, char *name1, int n);
char *convert(long long number);
void EditContact(char *filename, char *ptr);
void copy_data(char *filename1, char *filename2);
void deletecontact(char *filename, char*ptr);
int main()
{
	int *choise;
	choise = new int;
	call_menu();
	cout << "\t\t\tEnetr the Choise : ";
	cin >> choise[0];
	if (choise[0] == 1)
	{
		Add_contact();
	}
	else if (choise[0] == 2)
	{
		char *filename = { "save.txt" };
		ListOfContact(filename);
		filename = nullptr;
	}
	else if (choise[0] == 3)
	{
		char *filename = { "save.txt" };
		int n;
		cout << "press 1 for search By Name & 2 for search by Number :"; cin >> n;
		if (n == 1)
		{
			char *name = nullptr;
			name = new char[20];
			cout << "Enter name :";
			cin.ignore();
			cin.getline(name, 20);
			bool flag = searchOfContact(filename, name, n);
			if (!flag)
			{
				cout << "contact is not found in list\n";

			}
			checkCharPtr(name);
		}
		else if (n == 2)
		{
			long long *number = nullptr;
			number = new long long;
			char *num = nullptr;
			cout << "Enter Number :";
			cin >> number[0];
			num = convert(number[0]);
			bool flag = searchOfContact(filename, num, n);
			if (!flag)
			{
				cout << "contact is not found in list\n";

			}
			checkLongPtr(number);
			checkCharPtr(num);
		}
		else
		{
			cout << "invalid num";
		}
		filename = nullptr;

	}
	else if (choise[0] == 4)
	{
		char *Name = nullptr, *filename = { "save.txt" };
		Name = new char[25];
		cout << "Enter Name for edit :";
		cin.ignore();
		cin.getline(Name, 25);
		EditContact(filename, Name);
		checkCharPtr(Name);
	}
	else if (choise[0]==5)
	{
		char *Name = nullptr, *filename = { "save.txt" };
		Name = new char[25];
		cout << "Enter Name for delete :";
		cin.ignore();
		cin.getline(Name, 25);
		deletecontact(filename, Name);
		checkCharPtr(Name);
	}
	else
	{
		cout << "Invalid Number\n";		
	}
	if (choise!=nullptr)
	{
		delete[]choise;
		choise = nullptr;
	}
	return 0;
}
void deletecontact(char *filename, char*ptr)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "File is not open\n";
		exit(1);
	}
	else
	{
		int flag = 0;
		char colon, *name = nullptr, *ignore = nullptr, *num = nullptr, *address = nullptr, *email = nullptr;
		name = new char[20];
		ignore = new char[20];
		num = new char[12];
		address = new char[30];
		email = new char[30];
		fin.ignore();
		while (fin.getline(ignore, 20, ' '))
		{
			fin >> colon;
			fin.getline(name, 20, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(num, 12, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(address, 30, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(email, 30, '\n');
			fin >> colon;
			if (strcmp(name, ptr) == 0)
			{
				flag++;
			}
			else
			{
				char *dummyfile = { "dummyfile.txt" };
				ofstream fout(dummyfile, ios::app);
				if (fout.is_open())
				{
					fout << "Name         :" << name << endl;
					fout << "Phone        :" << num << endl;
					fout << "Address      :" << address << endl;
					fout << "Email        :" << email << endl;
					fout << endl;
					fout.close();
				}
				else
				{
					cout << "File is not open" << endl;
					exit(1);
				}
				dummyfile = nullptr;
			}


		}
		fin.close();
		checkCharPtr(name);
		checkCharPtr(num);
		checkCharPtr(address);
		checkCharPtr(email);
		if (!flag)
		{
			cout << "contact is not found in List\n";

		}
		else
		{
			cout << "Your contact is Delete\n";
		}

	}
	char *file = { "dummyfile.txt" };
	copy_data(file, filename);
	remove(file);
}
void EditContact(char *filename, char *ptr)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "File is not open\n";
		exit(1);
	}
	else
	{
		int flag = 0;
		char colon, *name = nullptr, *ignore = nullptr, *num = nullptr, *address = nullptr, *email = nullptr;
		name = new char[20];
		ignore = new char[20];
		num = new char[12];
		address = new char[30];
		email = new char[30];
		fin.ignore();
		while (fin.getline(ignore, 20, ' '))
		{
			fin >> colon;
			fin.getline(name, 20, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(num, 12, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(address, 30, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(email, 30, '\n');
			fin >> colon;
			if (strcmp(name, ptr) == 0)
			{
				flag++;
				cout << "Contact is found\n";
				cout << "Name    : " << name << endl;
				cout << "Number  : " << num << endl;
				cout << "Address : " << address << endl;
				cout << "E-mail  : " << email << endl;
				cout << endl;

				cout << "(Enter 1 for Edit Name) \n(Enter 2 for Edit Number) \n(Enter 3 for Edit Address) \n(Enter 4 for Edit E-mail) \nEnter Number :";
				int no;
				cin >> no;
				if (no == 1)
				{
					char *choosname = nullptr;
					choosname = new char[20];
					cin.ignore();
					cout << "Enter Name :";
					cin.getline(choosname, 20);
					char *dummyfile = { "dummyfile.txt" };
					ofstream fout(dummyfile, ios::app);
					if (fout.is_open())
					{
						fout << "Name         :" << choosname << endl;
						fout << "Phone        :" << num << endl;
						fout << "Address      :" << address << endl;
						fout << "Email        :" << email << endl;
						fout << endl;
						fout.close();
					}
					else
					{
						cout << "File is not open" << endl;
						exit(1);
					}
					dummyfile = nullptr;
					checkCharPtr(choosname);
				}
				else if (no == 2)
				{
					long long*contact_num = nullptr;
					contact_num = new long long;
					cout << "Enter Phone Number :";
					cin >> contact_num[0];

					char *dummyfile = { "dummyfile.txt" };
					ofstream fout(dummyfile, ios::app);
					if (fout.is_open())
					{
						fout << "Name         :" << name << endl;
						fout << "Phone        :0" << contact_num[0] << endl;
						fout << "Address      :" << address << endl;
						fout << "Email        :" << email << endl;
						fout << endl;
						fout.close();
					}
					else
					{
						cout << "File is not open" << endl;
						exit(1);
					}
					dummyfile = nullptr;
					checkLongPtr(contact_num);
				}
				else if (no == 3)
				{
					char *choosname = nullptr;
					choosname = new char[30];
					cout << "Enter Address : ";
					cin.ignore();
					cin.getline(choosname, 30);
					char *dummyfile = { "dummyfile.txt" };
					ofstream fout(dummyfile, ios::app);
					if (fout.is_open())
					{
						fout << "Name         :" << name << endl;
						fout << "Phone        :" << num << endl;
						fout << "Address      :" << choosname << endl;
						fout << "Email        :" << email << endl;
						fout << endl;
						fout.close();
					}
					else
					{
						cout << "File is not open" << endl;
						exit(1);
					}
					dummyfile = nullptr;
				}
				else if (no == 4)
				{
					char *choosname = nullptr;
					choosname = new char[20];
					cout << "Enter E-mail : ";
					cin.ignore();
					cin.getline(choosname, 20);
					char *dummyfile = { "dummyfile.txt" };
					ofstream fout(dummyfile, ios::app);
					if (fout.is_open())
					{
						fout << "Name         :" << name << endl;
						fout << "Phone        :" << num << endl;
						fout << "Address      :" << address << endl;
						fout << "Email        :" << choosname << endl;
						fout << endl;
						fout.close();
					}
					else
					{
						cout << "File is not open" << endl;
						exit(1);
					}

					checkCharPtr(choosname);
					dummyfile = nullptr;
				}
				else
				{
					cout << "invalid num\n";
					exit(1);
				}

			}
			else
			{
				char *dummyfile = { "dummyfile.txt" };
				ofstream fout(dummyfile, ios::app);
				if (fout.is_open())
				{
					fout << "Name         :" << name << endl;
					fout << "Phone        :" << num << endl;
					fout << "Address      :" << address << endl;
					fout << "Email        :" << email << endl;
					fout << endl;
					fout.close();
				}
				else
				{
					cout << "File is not open" << endl;
					exit(1);
				}
				dummyfile = nullptr;
			}
		}
		fin.close();
		checkCharPtr(name);
		checkCharPtr(num);
		checkCharPtr(address);
		checkCharPtr(email);
		if (!flag)
		{
			cout << "contact is not found in List\n";

		}
		else
		{
			cout << "Your contact is Updated\n";
		}
	}
	char *file = { "dummyfile.txt" };
	copy_data(file, filename);
	remove(file);
}
void copy_data(char *filename1, char *filename2)
{
	ofstream fout(filename2);
	fout.close();
	ifstream fin(filename1);
	if (fin.is_open())
	{
		char colon, *name = nullptr, *ignore = nullptr, *num = nullptr, *address = nullptr, *email = nullptr;
		name = new char[20];
		ignore = new char[20];
		num = new char[12];
		address = new char[30];
		email = new char[30];
		fin.ignore();
		while (fin.getline(ignore, 20, ' '))
		{
			fin >> colon;
			fin.getline(name, 20, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(num, 12, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(address, 30, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(email, 30, '\n');
			fin >> colon;
			ofstream fout(filename2, ios::app);
			if (fout.is_open())
			{
				fout << "Name         :" << name << endl;
				fout << "Phone        :" << num << endl;
				fout << "Address      :" << address << endl;
				fout << "Email        :" << email << endl;
				fout << endl;
				fout.close();
			}
		}
		checkCharPtr(name);
		checkCharPtr(num);
		checkCharPtr(address);
		checkCharPtr(email);
	}
	else
	{
		cout << "File not open \n";
		exit(1);
	}
}
bool searchOfContact(char *filename, char *name1, int n)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "File is not open\n";
		exit(1);
	}
	else
	{
		char colon, *name = nullptr, *ignore = nullptr, *num = nullptr, *address = nullptr, *email = nullptr;
		name = new char[20];
		ignore = new char[20];
		num = new char[12];
		address = new char[30];
		email = new char[30];
		fin.ignore();
		while (fin.getline(ignore, 20, ' '))
		{
			fin >> colon;
			fin.getline(name, 20, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(num, 12, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(address, 30, '\n');
			fin.getline(ignore, 20, ' ');
			fin >> colon;
			fin.getline(email, 30, '\n');
			if (n == 1)
			{
				if (strcmp(name, name1) == 0)
				{
					cout << "Contact is found\n";
					cout << "Name    : " << name << endl;
					cout << "Number  : " << num << endl;
					cout << "Address : " << address << endl;
					cout << "E-mail  : " << email << endl;
					fin.close();
					checkCharPtr(name);
					checkCharPtr(num);
					checkCharPtr(address);
					checkCharPtr(email);
					return true;
				}
			}
			else
			{

				if (strcmp(num, name1) == 0)
				{
					cout << "Contact is found\n";
					cout << "Name    : " << name << endl;
					cout << "Number  : " << num << endl;
					cout << "Address : " << address << endl;
					cout << "E-mail  : " << email << endl;
					fin.close();
					checkCharPtr(name);
					checkCharPtr(num);
					checkCharPtr(address);
					checkCharPtr(email);
					return true;
				}
			}
		}
		checkCharPtr(name);
		checkCharPtr(num);
		checkCharPtr(address);
		checkCharPtr(email);
	}

	return false;
}
char *convert(long long number)
{

	char *num = new char[12];
	int  i = 11;
	num[i] = { '\0' };
	num[0] = '0';
	while (number > 0)
	{
		int remainder = number % 10;
		number /= 10;
		stringstream str;
		str << remainder;
		str >> num[--i];
	}
	return num;
}
void Add_contact()
{
	system("CLS");
	int *l;
	l = new int;
	char *contact_Firstname = nullptr;
	contact_Firstname = new char[15];
	cout << "Enter First Name : ";
	cin >> contact_Firstname;
	l[0] = word_size(contact_Firstname);
	contact_Firstname = shrink(contact_Firstname, l[0]);

	char * contact_secName = nullptr;
	contact_secName = new char[15];
	cout << "Enter Second Name : ";
	cin >> contact_secName;
	l[0] = word_size(contact_secName);
	contact_secName = shrink(contact_secName, l[0]);

	long long*contact_num = nullptr;
	contact_num = new long long;
	cout << "Enter Phone Number :";
	cin >> contact_num[0];

	char *address = nullptr;
	address = new char[30];
	cout << "Enter Address :";
	cin >> address;
	l[0] = word_size(address);
	address = shrink(address, l[0]);

	char *email = nullptr;
	email = new char[30];
	cout << "Enter Email :";
	cin >> email;
	l[0] = word_size(email);
	email = shrink(email, l[0]);

	Save_contact(contact_Firstname, contact_secName, contact_num, address, email);
	cout << "Number saved Successfully\n";
	checkCharPtr(contact_Firstname);
	checkCharPtr(contact_secName);
	checkLongPtr(contact_num);
	checkCharPtr(email);
	checkCharPtr(address);
	if (l != nullptr)
	{
		delete[]l;
		l = nullptr;
	}
}
void Save_contact(char *name1, char *name2, long long *num, char *address, char *email)
{
	ofstream fout("save.txt", ios::app);
	if (fout.is_open())
	{
		fout << "Name         :" << name1 << " " << name2 << endl;
		fout << "Phone        :0" << num[0] << endl;
		fout << "Address      :" << address << endl;
		fout << "Email        :" << email << endl;
		fout << endl;
		fout.close();
	}
	else
	{
		cout << "File is not open" << endl;
		exit(1);
	}

}
int word_size(char *ptr)
{
	int count = 1;
	for (int i = 0; ptr[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}
void checkLongPtr(long long*ptr)
{

	if (ptr != nullptr)
	{
		delete[]ptr;
		ptr = nullptr;
	}
}
void checkCharPtr(char*ptr)
{
	if (ptr != nullptr)
	{
		delete[]ptr;
		ptr = nullptr;
	}
}
void ListOfContact(char *filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Contact File is not Open\n";
		exit(1);
	}
	else
	{
		system("CLS");
		cout << endl;
		cout << "\t\t\t ************************************" << endl;
		cout << "\t\t\t\t LIST OF CONTACTS " << endl;
		cout << "\t\t\t ************************************" << endl;
		cout << "Name\t Phone No \t Address \t E-mail" << endl;
		cout << "*************************************************" << endl;
		char *ptr = nullptr;
		ptr = new char;
		while (fin.get(ptr[0]))
		{
			cout << ptr[0];
		}
		fin.close();
		checkCharPtr(ptr);
	}

}
char *shrink(char *ptr, int size)
{
	char *ptr1 = nullptr;
	ptr1 = new char[size];
	for (int i = 0; i < size; i++)
		ptr1[i] = ptr[i];
	checkCharPtr(ptr);
	return ptr1;

}
void call_menu()
{
	cout << endl << "\t\t **** Welcome to Contact Management System **** " << endl << endl;
	cout << "\t\t\t\t MAIN MANU " << endl;
	cout << "\t\t\t=======================" << endl;
	cout << "\t\t\t [1] Add a new Contact " << endl;
	cout << "\t\t\t [2] List all Contacts " << endl;
	cout << "\t\t\t [3] Search for Contact " << endl;
	cout << "\t\t\t [4] Edit a Contact " << endl;
	cout << "\t\t\t [5] Delete a Contact " << endl;
	cout << "\t\t\t [0] Exit " << endl;
	cout << "\t\t\t=======================" << endl;
}