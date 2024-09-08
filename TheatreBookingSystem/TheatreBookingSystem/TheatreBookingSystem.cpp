#include <iostream>
#include <map>
#include <deque>
#include <set>
using namespace std;

class Seat {
public:
	int seatNumber;
	bool isBooked;

	Seat(int seatNumber) : seatNumber(seatNumber), isBooked(0) {}
	Seat() : seatNumber(1), isBooked(0) {}

	void book() {
		isBooked = 1;
	}
	void cancel() {
		isBooked = 0;
	}
};


class Theatre {
public:
	map<int, Seat> seats;
	set<int> availableSeats;
	set<int> bookedSeats;

	Theatre(int numberOfSeats) {
		for (int i = 1; i <= numberOfSeats; i++) {
			seats[i] = Seat(i);
			availableSeats.insert(i);
		}
	}

	void bookSeat(int seatNumber) {
		if (seats.find(seatNumber) == seats.end()) {
			cout << "The seat number " << seatNumber << " does not exist.\n";
			cout << "Please, choose another one.\n\n";
		}
		else if (seats[seatNumber].isBooked) {
			cout << "The seat number " << seatNumber << " is already booked.\n";
			cout << "Please, choose another one.\n\n";
		}
		else {
			seats[seatNumber].book();
			bookedSeats.insert(seatNumber);
			availableSeats.erase(seatNumber);

			cout << "The seat number " << seatNumber << " is successfully booked!\n\n";
		}
	}
	void cancelSeat(int seatNumber) {
		if (seats.find(seatNumber) == seats.end()) {
			cout << "The seat number " << seatNumber << " does not exist.\n";
			cout << "Please, choose another one.\n\n";
		}
		else if (!seats[seatNumber].isBooked) {
			cout << "The seat number " << seatNumber << " is already available and does not need cancelling.\n\n";
		}
		else {
			seats[seatNumber].cancel();
			bookedSeats.erase(seatNumber);
			availableSeats.insert(seatNumber);

			cout << "The seat number " << seatNumber << " is successfully cancelled!\n\n";
		}
	}
	void showNextAvailableSeat() {
		if (availableSeats.empty()) {
			cout << "There is no more available seats!\n\n";
		}
		else {
			cout << "The next available seat number is " << *availableSeats.begin();
		}
	}
};


class BookingMenu {
public:
	static void displayMainMenu() {
		cout << "Enter a number to choose the respective option:\n";
		cout << "1. Book a Seat;\n";
		cout << "2. Cancel Booking;\n";
		cout << "3. Show Next Available Seat;\n";
		cout << "4. Exit.\n\n";
	}

	static void handleOption1(Theatre& theatre) {
		int seatNumber;
		cout << "Enter the number of seat you want to book: ";
		cin >> seatNumber;
		cout << "\n";

		theatre.bookSeat(seatNumber);

		cout << "=========================================================\n\n";
	}
	static void handleOption2(Theatre& theatre) {
		int seatNumber;
		cout << "Enter the number of seat you want to cancel: ";
		cin >> seatNumber;
		cout << "\n";

		theatre.cancelSeat(seatNumber);

		cout << "=========================================================\n\n";
	}
	static void handleOption3(Theatre& theatre) {
		theatre.showNextAvailableSeat();

		cout << "\n\n=========================================================\n\n";
	}
	static void handleOption4() {
		cout << "Exiting program.\n";
	}
	static void handleInvalidInput() {
		cout << "Invalid input. Please, try again.\n\n";

		cout << "=========================================================\n\n";
	}
};


int main() {
	auto theatre = Theatre(100);

	while (true) {
		BookingMenu::displayMainMenu();

		int input;
		cin >> input;
		cout << "\n";

		switch (input) {
		case 1:
			BookingMenu::handleOption1(theatre);
			break;
		case 2:
			BookingMenu::handleOption2(theatre);
			break;
		case 3:
			BookingMenu::handleOption3(theatre);
			break;
		case 4:
			BookingMenu::handleOption4();
			return 0;
		default:
			BookingMenu::handleInvalidInput();
		}
	}
}