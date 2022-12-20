//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#include <stdexcept>
#include <windows.h>
#include<cctype>
#include<iomanip>
#include<conio.h>
#include <ctime>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int month, year, paid;
	double  interest_rate, loan_amount, total_amount, monthly_amount;
	int number_of_years;
	int acno;
	char name[50];
	int deposit;
	char type;
	float saving;
	int discount;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	bool merge(account ac, int num1, int num2); //function to merge a secont account with the current one
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
	void savings();  //This function will give the user an option to put into his existing bank account
	int retursaving() const;
	void LoanCalculator();
	void update();
	bool isLoanPaid();
	void setDiscuont(int);
	int getdiscount() const;
};    //class ends here

void account::create_account()
{
	paid = 0;
	int d; 
	month = 0;
	year = 0;
	interest_rate = 0;
	total_amount = 0;
	monthly_amount = 0;
	number_of_years = 0;
	cout << "\nEnter The account No. : ";
	cin >> acno;
	cout << "\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin >> deposit;
	cout << "\nEnter The Savings :";
	cin >> saving;
	cout << "\nEnter type of discuont:\n  1 - Soldier\n 2 - Student\n 3 - Veteran\n 4 - Newlywed\n 5 or defulty - Regular account\n";
	cin >> d;
	setDiscuont(d);
	cout << "\n\n\nAccount Created..";
}


void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
	cout << "\nSavings account : " << saving;

}


void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account : ";
	cin >> type;
	type = toupper(type);
	cout << "\nModify Balance amount : ";
	cin >> deposit;
	cout << "\nSavings account : ";
	cin >> saving;
}

bool account::merge(account ac, int num1, int num2)
{
	int temp;
	cout << "\nEnter A New Account No. : ";
	cin >> temp;
	if (temp == num1 || temp == num2)
	{
		cout << "The new account number must be different than the account numbers enterd";
		return false;
	}
	acno = temp;
	cout << "\nWrite The Account Holders Names : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account : ";
	cin >> type;
	type = toupper(type);
	this->deposit += ac.deposit;
	return true;
}

void account::dep(int x)
{
	deposit += x - discount;
}

void account::draw(int x)
{
	deposit -= x + discount;
}


void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(11) << " " << type << setw(10) << deposit << setw(8) << saving << endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

int account::retursaving() const
{
	return saving;
}

char account::rettype() const
{
	return type;
}

void account::setDiscuont(int d)
{
	discount = 5;//Regular account
	if (d == 1)//Soldier
	{
		discount = 1;
	}
	if (d == 2)//Student
	{
		discount = 2;
	}
	if (d == 3)//Veteran
	{
		discount = 3;
	}
	if (d == 4)//Newlywed
	{
		discount = 4;
	}
}
int account::getdiscount() const
{
	return discount;
}


void account::savings() {
	cout << "\nDo you want to deposit or withdraw money from your savings? (d/w): ";
	char choice;
	cin >> choice;

	// declare a variable to save the amount of money to be deposited or withdrawn
	int amount;

	// check if the user wants to deposit or withdraw money
	if (choice == 'd') {
		cout << "\nEnter the amount of money to deposit: ";
		cin >> amount;
		cout << "\nEnter from the account [a] or enter from another source [s] : (a/s) ";
		cin >> choice;

		// add the amount to the current savings
		if (choice == 'a')
		{
			saving += amount;
			deposit -= amount;
		}
		else if (choice == 's')
		{
			saving += amount;
		}

	}
	else if (choice == 'w') {
		cout << "\nEnter the amount of money to withdraw: ";
		cin >> amount;
		cout << "\nwithdraw or [w] withdraw and put into the account [a] : (w/a) ";
		cin >> choice;
		// subtract the amount from the current savings
		if (choice == 'w')
		{
			saving -= amount;
		}
		else if (choice == 'a')
		{
			saving -= amount;
			deposit += amount;
		}
	}


	ofstream outfile("savings.txt");
	outfile << saving << endl;
	outfile.close();
}
void account::LoanCalculator()
{
	cout << "\nEnter the loan amount: ";
	cin >> loan_amount;
	cout << endl;
	cout << "Enter the interest rate: ";
	cin >> interest_rate;
	cout << endl;
	cout << "The number of years: ";
	cin >> number_of_years;
	cout << endl;
	time_t now = time(nullptr);

	// Convert the time to a local time structure
	tm* localTime = localtime(&now);

	// Get the month (0-11)
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;

	total_amount = loan_amount + (loan_amount * (interest_rate / 100.00));
	monthly_amount = total_amount / (number_of_years * 12);

	cout << "Total amount to be paid: " << (int)total_amount << endl;
	cout << "Total interest: " << loan_amount * (interest_rate / 100.00) << endl;
	cout << "Monthly amount to be paid: " << monthly_amount << endl;
	dep(loan_amount);
}

void account::update()
{
	if (total_amount != 0) {
		// Get the current time
		time_t now = time(nullptr);

		// Convert the time to a local time structure
		tm* localTime = localtime(&now);

		// Get the month (0-11)
		int Nmonth = localTime->tm_mon + 1;
		int Nyear = localTime->tm_year + 1900;
		if (paid != (Nyear - year) * 12 + Nmonth - month) {
			draw(monthly_amount);
			paid++;
		}
		if (paid == total_amount / monthly_amount) {
			paid = 0;
			month = 0;
			year = 0;
			interest_rate = 0;
			total_amount = 0;
			monthly_amount = 0;
			number_of_years = 0;
		}
	}
}

bool account::isLoanPaid()
{
	update();
	if (total_amount != 0)
		return false;
	return true;
}

//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
bool merge_accounts(int, int); // function to merge 2 accounts
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
void entry();
int Access_to_savings(int); //A function that checks the account number and from there there will be an entry for a change within the savings account
void LoanCalculator(int);
void modify_discount(int);
string getpassword(const string& prompt = "Enter password> ");


//****************************************************************************
//					Login Class
//****************************************************************************

class login
{
private:
	char username[25], pass[25];
public:
	void addUser();
	void validate();
};
void login::validate()
{
	login ln;
	string password;
	char pwd[15], user[25];
	cout << "Please Enter Username : ";
	cin >> user;
	password = getpassword("Please Enter Password : ");
	strcpy(pwd, password.c_str());

	bool flag = false;
	ifstream inFile;
	inFile.open("login.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (inFile.read(reinterpret_cast<char*> (&ln), sizeof(login)))
	{
		if (strcmp(ln.username, user) == 0 && strcmp(ln.pass, pwd) == 0)
		{
			cout << "\nLoginned Successfully...\n";
			getchar();
			flag = true;
			break;
		}
	}
	inFile.close();
	if (flag == false)
	{
		cout << "\nYou Entered Incorrect Details...Please Login again...\n";
		getchar();
		entry();
	}


}


void login::addUser()
{

	login ln;
	string password, password1;
	char pass1[15];
	cout << "Please Enter Username : ";
	cin >> ln.username;
	password = getpassword("Please Enter Password : ");
	password1 = getpassword("\nPlease Confirm Password : ");
	strcpy(ln.pass, password.c_str());
	strcpy(pass1, password1.c_str());
	if (1) //Condistion to check if user already exist or not
	{
		if (strcmp(ln.pass, pass1) == 0)
		{
			ofstream outFile;
			outFile.open("login.dat", ios::binary | ios::app);

			outFile.write(reinterpret_cast<char*> (&ln), sizeof(login));
			outFile.close();

			cout << "\nUser Registered Successfully...\n";
			getchar();
			entry();
		}
		else
		{
			cout << "\nPasswords don't Match...\n";
			getchar();
			entry();
		}
	}
	else
	{
		cout << "\nUser already exist...Please Login..\n";
		getchar();
		entry();
	}

}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	int num, num2, menu;
	bool flag;
	intro();
	entry();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t[01]. NEW ACCOUNT";
		cout << "\n\n\t[02]. DEPOSIT AMOUNT";
		cout << "\n\n\t[03]. WITHDRAW AMOUNT";
		cout << "\n\n\t[04]. BALANCE ENQUIRY";
		cout << "\n\n\t[05]. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t[06]. CLOSE AN ACCOUNT";
		cout << "\n\n\t[07]. MODIFY AN ACCOUNT";
		cout << "\n\n\t[08]. SAVINGS ACCOUNT";
		cout << "\n\n\t[09]. MERGE ACCOUNT";
		cout << "\n\n\t[10]. TAKE A LOAN";
		cout << "\n\n\t[11]. MODIFY AN DISCOUNT";
		cout << "\n\n\t[12]. EXIT";
		cout << "\n\n\tSelect Your Option (1-12) ";
		cin >> menu;
		system("cls");
		switch (menu)
		{
		case 1:
			write_account();
			break;
		case 2:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case 3:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case 4:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			display_sp(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			delete_account(num);
			break;
		case 7:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			modify_account(num);
			break;

		case 8:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			Access_to_savings(num);
			break;
		case 9:
			cout << "\n\n\tEnter The first account's No.: "; cin >> num;
			cout << "\n\n\tEnter The second account's No.: "; cin >> num2;
			flag = merge_accounts(num, num2);
			if (flag = true)
			{
				delete_account(num);
				delete_account(num2);
			}
			else
				cout << "Failed!";
			break;
		case 10:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			LoanCalculator(num);
			break;
		case 11:
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			modify_discount(num);
			break;
		case 12:
			cout << "\n\n\tThanks for using bank record system";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (menu != 12);
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	function to merge accounts
//****************************************************************

bool merge_accounts(int n1, int n2)
{
	bool found = false;
	account ac1, ac2;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	while (!File.eof() && found == false)
	{
		if (ac1.retacno() != n1 && ac1.retacno() != n2)
			File.read(reinterpret_cast<char*> (&ac1), sizeof(account));
		if (ac2.retacno() != n1 && ac2.retacno() != n2)
			File.read(reinterpret_cast<char*> (&ac2), sizeof(account));
		if ((ac1.retacno() == n1 && ac2.retacno() == n2) || (ac1.retacno() == n2 && ac2.retacno() == n1))
		{
			ac1.show_account();
			cout << endl;
			ac2.show_account();
			cout << "\n\nEnter The Details of the new shared account: " << endl;
			if (ac1.merge(ac2, n1, n2) == false)
				break;
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac1), sizeof(account));
			if (ac2.retacno() == n1)
				delete_account(n1);
			else
				delete_account(n2);
			ac1.show_account();
			cout << "\n\n\t Accounts Merged";
			found = true;
		}
	}
	File.close();
	return found;
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "==============================================================\n";
	cout << "A/c no.      NAME           Type  Balance  Savings account\n";
	cout << "==============================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.update();
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}


int Access_to_savings(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return 0;

	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			ac.savings();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
	{
		cout << "\n\n Record Not Found ";
		return 0;
	}
	return 1;
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout << "\n\n\n\t\t\t\t\t  B A N K";
	cout << "\n\n\t\t\t\t\tR E C O R D";
	cout << "\n\n\t\t\t\t\tS Y S T E M";
	cout << "\n\n\n\n\t\t\t\tMADE BY : Iqra Shahbaz 172123";
	cout << "\n\n\t\t\t\tAir University, Multan Campus";
	cin.get();
}


//***************************************************************
//    	LOGIN FUNCTION
//****************************************************************


void entry()
{
	int ch;
	login user;
	system("CLS");
	cout << "\n\n\n\n";
	cout << "\t[1] Login \n";
	cout << "\t[2] Register \n";
	cout << "\t[3] Exit\n\t";
	cin >> ch;
	if (ch == 1)
	{
		user.validate();
	}
	else if (ch == 2)
	{
		user.addUser();
	}
	else if (ch == 3)
	{
		cout << "\nProgram is Exiting.\n";
		getchar();
		exit(1);
	}
	else
	{
		cout << "\nYou Entered Incorrect Option.\n";
		getchar();
		exit(1);

	}
}

string getpassword(const string& prompt)
{
	string result;

	// Set the console mode to no-echo, not-line-buffered input
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw runtime_error(
			"getpassword: You must be connected to a console to use this program.\n"
		);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	// Get the password string
	WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}

	// Restore the console mode
	SetConsoleMode(ih, mode);

	return result;
}
//***************************************************************
//    			LOANING
//***************************************************************

void LoanCalculator(int num)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == num)
		{
			ac.show_account();
			if (ac.isLoanPaid()) {
				ac.LoanCalculator();
				cout << "\n\n\t Record Updated";
			}
			else {
				cout << "\n\n\t You Have LOANING";
			}
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));

			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}


void modify_discount(int n)
{
	int d;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\nEnter type of discuont: \n 1 - Soldier\n 2 - Student\n 3 - Veteran\n 4 - Newlywed\n 5 or defulty - Regular account\n";
			cin >> d;
			ac.setDiscuont(d);
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************