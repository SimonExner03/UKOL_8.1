#include <iostream>
using namespace std;

//--------------CLIENT------------------
class Client {
private:
	int code;
	string name;
public:
	Client(int c, string n);

	int GetCode();
	string GetName();
};

Client::Client(int c, string n) {
	this->code = c;
	this->name = n;
}

int Client::GetCode() {
	return this->code;
}
string Client::GetName() {
	return this->name;
}

//-------------AbstractAccount---------------
class AbstractAccount {
public:
	AbstractAccount();
	virtual ~AbstractAccount();

	virtual bool CanWithdraw(double a) = 0;
};

AbstractAccount::AbstractAccount() {
	cout << "AbstractAccount construktor" << endl;
}
AbstractAccount::~AbstractAccount() {
	cout << "AbstractAccount destruktor" << endl;
}

//------------------ACCOUNT--------------
class Account :public AbstractAccount {
private:
	int number;
	double balance;
	double interestRate;
	Client* owner;

public:
	Account(int n, Client* c);
	Account(int n, Client* c, double ir);
	virtual ~Account();

	int GetNumber();
	double GetBalance();
	double GetInterestRate();
	Client* GetOwner();
	virtual bool CanWithdraw(double a);

	void Deposit(double a);
	bool Withdraw(double a);
	void AddInterest();
};

Account::Account(int n, Client* c) {
	this->number = n;
	this->owner = c;
	this->balance = 0;
	this->interestRate = 0;
}
Account::Account(int n, Client* c, double ir) {
	this->number = n;
	this->owner = c;
	this->interestRate = ir;
	this->balance = 0;
}

Account::~Account() {
	cout << "Account destructor" << endl;
}

int Account::GetNumber() {
	return this->number;
}
double Account::GetBalance() {
	return this->balance;
}
double Account::GetInterestRate() {
	return this->interestRate;
}
Client* Account::GetOwner() {
	return this->owner;
}

bool Account::CanWithdraw(double a) {
	if (a < this->balance) {
		return true;
	}
	return false;
}

void Account::Deposit(double a) {
	this->balance += a;
}
bool Account::Withdraw(double a) {
	if (this->CanWithdraw(a)) {
		this->balance -= a;
		return true;
	}
	return false;
}
void Account::AddInterest() {
	this->balance += this->interestRate * this->balance;
}

//------------------Credit Account--------------------

class CreditAccount : public Account {
private:
	double credit;

public:
	CreditAccount(int n, Client* o, double c);
	CreditAccount(int n, Client* o, double ir, double c);
	~CreditAccount();

	virtual bool CanWithdraw(double a);
};

CreditAccount::CreditAccount(int n, Client* o, double c) : Account(n, o) {
	this->credit = c;
}

CreditAccount::CreditAccount(int n, Client* o, double ir, double c) : Account(n, o, ir) {
	this->credit = c;
}

CreditAccount::~CreditAccount() {
	cout << "CreditAccount destructor" << endl;
}

bool CreditAccount::CanWithdraw(double a) {
	return ((this->GetBalance() + this->credit) >= a);
}

//---------------main()--------------------------
int main() {
	Client* o = new Client(0, "Smith");
	CreditAccount* ca = new CreditAccount(1, o, 1000);
	AbstractAccount* aa = ca;

	delete aa;
	delete o;
	return 0;
}