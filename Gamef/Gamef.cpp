#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <io.h>
using namespace std;

class Staff {
protected:
	string name;
	double salary;
	int level;

public:
	//Констурктор
	Staff(string name, double salary, int level) : name(name), salary(salary), level(level) {}
	//Деконструктор
	virtual ~Staff() {}

	string getName() {
		return name;
	}
	double getSalary() {
		return salary;
	}
	int getLevel() {
		return level;
	}
	virtual void work() const {
		cout << name << " is working" << endl;
	}
};

class Barista : public Staff {
public:
	Barista(string name, double salary, int level) : name(name), salary(salary), level(level) {}

	void work() const override {
		cout << name << " is cooking coffee, skill level- " << level << endl;
	}
};

class Waiter : public Staff {
public:
	Waiter(string name, double salary, int level) : name(name), salary(salary), level(level) {}

	void work() const override {
		cout << name << " is serving clients, skill level- " << level << endl;
	}
};

class Ingredients {
private:
	int coffee;
	int milk, sugar, cups;
public:
	Ingredients(int c,int m,int s,int cp) : coffee(c),milk(m),sugar(s),cups(cp) {}

	//Дополнение запасов
	void addCoffee(int amount) {
		coffee += amount;
	}

	void addMilk(int amount) {
		milk += amount;
	}

	void addSugar(int amount) {
		sugar += amount;
	}

	void addCups(int amount) {
		cups += amount;
	}

	//Использование запасов
	bool useCoffee(int amount) {
		if (coffee >= amount) {
			coffee -= amount;
			return true;
		}
		else {
			return false;
		}
	}

	bool useMilk(int amount) {
		if (milk >= amount) {
			milk -= amount;
			return true;
		}
		else {
			return false;
		}
	}

	bool useSugar(int amount) {
		if (sugar >= amount) {
			sugar -= amount;
			return true;
		}
		else {
			return false;
		}
	}

	bool useCups(int amount) {
		if (cups >= amount) {
			cups -= amount;
			return true;
		}
		else {
			return false;
		}
	}

	void printStatus() const {
		cout << "\n <Ingredients>" << endl;
		cout << "Coffee: " << coffee << endl;
		cout << "Milk: " << milk << endl;
		cout << "Sugar: " << sugar << endl;
		cout << "Cups: " << cups << endl;
	}
};

class CoffeeShop {
private:
	string name;
	double balance;
	Ingredients ingredients;
	vector<Staff*> staff;
	int reputation;
	int day;

public:
	CoffeeShop(string n, double b) :
		name(n),
		balance(b),
		ingredients(17,17,17,17),
		reputation(4),
		day(1) {}

	~CoffeeShop() {
		for (auto s : staff) {
			delete s;
		}
	}

	void hireStaff(Staff* s) {
		staff.push_back(s);

	}

	void paySalary() {
		cout << "\n <Salary>" << endl;
		for (const auto& s : staff) {
			if (balance >= s->getSalary()) {
				balance -= s->getSalary();
				cout << "Viplocheno " << s->getSalary() << " for " << s->getName() << endl;
			}
			else {
				cout << "No money for salary " << s->getName() << endl;
				reputation--;
			}
		}
	}

	void buyIngredients() {
		int choice;
		int amount;
		cout << "\n<Buy igredients>" << endl;
		cout << "1. Coffee (5$)" << endl;
		cout << "2. Milk (3$)" << endl;
		cout << "3. Sugar (2$)" << endl;
		cout << "4. Cups (1$)" << endl;
		cout << "0. Exit" << endl;
		cout << "Balance: "<<balance << endl;
		cout << "Choose what to buy: " << endl;
		cin >> choice;

		if (choice == 0) {
			return;
		}

		cout << "How much: ";
		cin >> amount;

		switch (choice) {
			case 1:
				if (balance >= amount * 5) {
					ingredients.addCoffee(amount);
					balance -= amount * 5;
					cout << "You bought " << amount <<" coffee" << endl;
				}
				else {
					cout << "No money" << endl;
				}
			case 2:
				if (balance >= amount * 3) {
					ingredients.addMilk(amount);
					balance -= amount * 3;
					cout << "You bought " << amount << " milk" << endl;
				}
				else {
					cout << "No money" << endl;
				}
			case 3:
				if (balance >= amount * 2) {
					ingredients.addSugar(amount);
					balance -= amount * 2;
					cout << "You bought " << amount << " sugar" << endl;
				}
				else {
					cout << "No money" << endl;
				}
			case 4:
				if (balance >= amount) {
					ingredients.addCups(amount);
					balance -= amount;
					cout << "You bought " << amount << " cups" << endl;
				}
				else {
					cout << "No money" << endl;
				}
			default:
				cout << "Incorrect" << endl;
		}
	}

	void serveClients() {
		int clients = rand() % 11 + 1;
		int served = 0;
		cout << "\n<Clients serving>" << endl;
		cout << "Today " << clients << " clients" << endl;

		for (int i = 0;i < clients;i++) {
			if (ingredients.useCoffee(i)) {
				if (ingredients.useMilk(rand() % 2)) {
					if (ingredients.useSugar(rand() % 3)) {
						if (ingredients.useCups(i)){
							balance += 10;
							served++;
							cout << "Client is served" << i + 1 << endl;
							for (const auto& s : staff) {
								s->work();
							}
							continue;
						}
					}
				}
			}
			cout << "Ne udalos obsluvit clienta" << i + 1 << "no ingredients" << endl;
			reputation--;
		}
		cout << served << " clients are served"<<"\n All clients was "<<clients<<endl;
		cout << "You earned " << served * 10 << "$" << endl;

		if (served == clients) {
			reputation++;
			cout << "Well done: reputation is increased" << endl;
		}
	}

	void payBills() {
		double rent = 50;
		double utilites = 30;
		cout << "<Bills Paying>" << endl;
		cout << "Rent: " << rent << "$" << endl;
		cout << "Communal apartment: " << utilites << "$" << endl;

		if (balance>=rent +utilites) {
			balance -= rent + utilites;
			cout << "Bills are paied" << endl;
		}
		else {
			cout << "No money for bills. Reputation decreas";
			reputation--;
		}
	}

	void nextDay() {
		day++;
		cout << "The " << day << "day" << endl;
	}
};

int main(){

}
