#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

class BankingSystem {
private:
	class Account {
	public:
		string ownerName;
		double balance;
		int accountNumber;


		Account(string ownerName, double initialDeposit, int id) {
			this->ownerName = ownerName;
			deposit(initialDeposit);
			this->accountNumber = id;
		}

		void depositBonus(double& amount) {
			mt19937 mtGenerator;
			bernoulli_distribution bonusChance(0.05);

			if (bonusChance(mtGenerator)) {
				uniform_int_distribution<int> bonusAmount(10, 20);
				int bonusPercent = bonusAmount(mtGenerator);

				amount *= 1.0 + (double)bonusPercent / 100;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "You are lucky! You get bonus " << bonusPercent << "% of deposit for free!" << endl;
			}
		}

		void deposit(double& amount) {
			depositBonus(amount);
			balance += amount;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "The deposit succeed. Your current balance is " << balance << "." << endl;
		}

		bool isWithdrawalSucceed(double amount) const {
			return balance >= amount;
		}

		void withdrawalFee(double& amount) {
			mt19937 mtGenerator;
			bernoulli_distribution feeChance(0.05);

			if (feeChance(mtGenerator)) {
				uniform_int_distribution<int> feeAmount(1, 3);
				int feePercent = feeAmount(mtGenerator);

				isWithdrawalSucceed(1.0 + (double)feePercent / 100);
				amount *= 1.0 + (double)feePercent / 100;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "Unfortunately, you get fee of " << feePercent << "% of withdrawal!" << endl;
			}
		}

		void withdraw(double amount) {
			withdrawalFee(amount);
			balance -= amount;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "The withdrawal succeed. Your current balance is " << balance << "." << endl;
		}

		double getBalance() {
			return balance;
		}

		void displayAccountInfo() const {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			cout << "Owner's name: " << ownerName << endl;
			cout << "Current balance: " << balance << endl;
		}
	};

	static void backToMenuMessage() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << endl;
		cout << "Going back to menu." << endl;
		cout << endl;
		cout << "=====================================================================================" << endl;
		cout << endl;
	}
	static void accountNotFoundMessage() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "Error! This account is not found! Please, try again." << endl;
	}

public:
	class Bank {
	private:
		vector<Account> Accounts;
		int ID;

	public:
		int generateNewID() {
			mt19937 mtGenerator;
			uniform_int_distribution<int> distribution(100000000, 9999999999);

			return distribution(mtGenerator);
		}

		int getID() {
			return ID;
		}

		void addAccount(const string& const ownerName, const double& const initialDeposit) {
			ID = generateNewID();
			Accounts.push_back(Account(ownerName, initialDeposit, ID));
		}

		bool doesAccountExist(const int& const accountNumber) {
			for (vector<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++) {
				if ((*iter).accountNumber == accountNumber) {
					return true;
				}
			}

			return false;
		}

		Account& findAccount(int &accountNumber) {
			for (vector<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++) {
				if ((*iter).accountNumber == accountNumber) {
					return *iter;
				}
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "Error! This account is not found! Please, try again.";
		}

		void deleteAccount(int &accountNumber) {
			for (vector<Account>::iterator iter = Accounts.begin(); iter != Accounts.end(); iter++) {
				if ((*iter).accountNumber == accountNumber) {
					Accounts.erase(iter);
					return;
				}
			}
		}
	};


	static void displayMainMenu() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "<<< Available Banking System options >>>" << endl;
		cout << "1. Create Account" << endl;
		cout << "2. Deposit Money" << endl;
		cout << "3. Withdraw Money" << endl;
		cout << "4. Check Balance" << endl;
		cout << "5. Exit" << endl;
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "> Enter a number to choose the respective option: ";
	}

	static void handleOption1(Bank& bank) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "You have chosen to create an account!" << endl;
		cout << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		string name;
		cout << "> Enter your name: ";
		cin >> name;

		double initialDeposit;
		cout << "> Enter an amount of your initial deposit: ";
		cin >> initialDeposit;

		bank.addAccount(name, initialDeposit);
		cout << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "Your account is successfully created! Your autogenerated unique ID is " << bank.getID() << "." << endl;

		backToMenuMessage();
	}

	static void handleOption2(Bank& bank) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "You have chosen to deposit money!" << endl;
		cout << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int id;
		cout << "> Enter your ID: ";
		cin >> id;

		if (bank.doesAccountExist(id)) {
			double deposit;
			cout << "> Enter an amount of your deposit: ";
			cin >> deposit;

			bank.findAccount(id).deposit(deposit);
		}
		else {
			accountNotFoundMessage();
		}

		backToMenuMessage();
	}

	static void handleOption3(Bank& bank) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "You have chosen to withdraw money!" << endl;
		cout << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int id;
		cout << "> Enter your ID: ";
		cin >> id;

		if (bank.doesAccountExist(id)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "Your current balance is " << bank.findAccount(id).getBalance() << "." << endl;
			cout << endl;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			double withdrawalAmount;
			cout << "> Enter an amount of your withdrawal: ";
			cin >> withdrawalAmount;

			if (bank.findAccount(id).isWithdrawalSucceed(withdrawalAmount)) {
				bank.findAccount(id).withdraw(withdrawalAmount);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "Error! Insufficient funds! Please, try again." << endl;
			}
		}
		else {
			accountNotFoundMessage();
		}

		backToMenuMessage();
	}

	static void handleOption4(Bank& bank) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "You have chosen to check your balance!" << endl;
		cout << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int id;
		cout << "> Enter your ID: ";
		cin >> id;
		cout << endl;

		if (bank.doesAccountExist(id)) {
			bank.findAccount(id).displayAccountInfo();
		}
		else {
			accountNotFoundMessage();
		}

		backToMenuMessage();
	}

	static void handleOption5(Bank& bank) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "Exiting program." << endl;
	}

	static void handleInvalidInput() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "Error! Invalid choice. Please, try again." << endl;

		backToMenuMessage();
	}
};


int main() {
	BankingSystem::Bank bank;

	while (true) {
		BankingSystem::displayMainMenu();

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			BankingSystem::handleOption1(bank);
			break;
		case 2:
			BankingSystem::handleOption2(bank);
			break;
		case 3:
			BankingSystem::handleOption3(bank);
			break;
		case 4:
			BankingSystem::handleOption4(bank);
			break;
		case 5:
			BankingSystem::handleOption5(bank);
			return 0;
		default:
			BankingSystem::handleInvalidInput();
		}
	}
}
