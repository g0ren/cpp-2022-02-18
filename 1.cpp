/*
 * Реализовать дневник наблюдения за погодой. Создать двумерный массив, где строки это месяцы, а столбцы –это дни.
 * Каждая ячейка будет хранить дневную температуру в этот день. Необходимо реализовать:
 - метод генерации данных. Сделать его максимально приближенным к реальности (зимой холодно, летом тепло)
 - метод вывода всего календаря на экран. Продумайте внешний вид.
 - метод определения самого холодного и самого теплого дня в месяце ( месяц выбирает пользователь).
 - метод определения самого холодного и самого теплого дня в году.
 - метод корректировки температуры в выбранный пользователем день.
 - метод определения среднемесячной температуры. Месяц выбирает пользователь.
 Общение с пользователем реализовать с помощью меню, меню должно быть удобным и понятным. Вывод информации
 сделать удобным, например – «12 февраля самый холодный день в году.».
 В программе продумать и реализовать все необходимые функции, постарайтесь максимально структурировать код программы. Удачи!
 */

#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
const int months[12] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const string monthnames[12] { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
		"Aug", "Sep", "Oct", "Nov", "Dec" };
// Данные о максимальных и минимальных температурах в Санкт-Петербурге взяты с:
// https://en.wikipedia.org/wiki/Saint_Petersburg#Climate
const double mintemp[12] { -35.9, -35.2, -29.9, -21.8, -6.6, 0.1, 4.9, 1.3,
		-3.1, -12.9, -22.2, -34.4 };
const double maxtemp[12] { 8.7, 10.2, 15.3, 25.3, 33.0, 35.9, 35.3, 37.1, 30.4,
		21.0, 12.3, 10.9 };
// Прототипы функций:
double** makeCalendar();
void menu(double **cal);
void generateTemps(double **cal);
void printCalendar(double **cal);
void coldestOfYear(double **cal);
void hottestOfYear(double **cal);
void coldestOfMonth(double **cal);
void hottestOfMonth(double **cal);
void averageOfMonth(double **cal);
void changeTemp(double **cal);

int main() {
	srand(time(NULL));
	double **cal { };
	cal = makeCalendar();
	generateTemps(cal);
	menu(cal);
	return 0;
}

// Функции:
double** makeCalendar() {
	double **cal = new double*[12] { };
	for (int i = 0; i < 12; i++) {
		cal[i] = new double[months[i] + 1] { };
		cal[i][0] = months[i];
	}
	return cal;
}

//- метод генерации данных. Сделать его максимально приближенным к реальности (зимой холодно, летом тепло)
void generateTemps(double **cal) {
	for (int m = 0; m < 12; m++) {
		for (int d = 1; d <= cal[m][0]; d++) {
			cal[m][d] = mintemp[m]
					+ (maxtemp[m] - mintemp[m]) * rand() / (double) RAND_MAX;
		}
	}
}

//- метод вывода всего календаря на экран. Продумайте внешний вид.
void printCalendar(double **cal) {
	cout << "    ";
	for (int i = 1; i <= 31; i++) {
		printf("%*d", 7, i);
	}
	cout << endl;
	for (int m = 0; m < 12; m++) {
		cout << monthnames[m] << ": ";
		for (int d = 1; d <= cal[m][0]; d++) {
			printf("%*.*f ", 6, 2, cal[m][d]);
		}
		cout << endl;
	}
}

// - метод определения самого холодного и самого теплого дня в году.
void coldestOfYear(double **cal) {
	int month { 0 }, day { 1 };
	for (int m = 0; m < 12; m++) {
		for (int d = 1; d <= cal[m][0]; d++) {
			if (cal[m][d] < cal[month][day]) {
				month = m;
				day = d;
			}
		}
	}
	cout << "The coldest day of the year is " << monthnames[month] << " " << day
			<< endl;
}

void hottestOfYear(double **cal) {
	int month { 0 }, day { 1 };
	for (int m = 0; m < 12; m++) {
		for (int d = 1; d <= cal[m][0]; d++) {
			if (cal[m][d] > cal[month][day]) {
				month = m;
				day = d;
			}
		}
	}
	cout << "The hottest day of the year is " << monthnames[month] << " " << day
			<< endl;
}

// - метод определения самого холодного и самого теплого дня в месяце ( месяц выбирает пользователь).
void coldestOfMonth(double **cal) {
	int month { }, day { 1 };
	cout << "Enter the month (1 to 12): ";
	cin >> month;
	month--;
	if (month < 0 || month > 11) {
		cout << "Wrong month!" << endl;
		return;
	}
	for (int d = 1; d <= cal[month][0]; d++)
		if (cal[month][d] < cal[month][day])
			day = d;
	cout << "The coldest day of " << monthnames[month] << " is "
			<< monthnames[month] << " " << day << endl;
}

void hottestOfMonth(double **cal) {
	int month { }, day { 1 };
	cout << "Enter the month (1 to 12): ";
	cin >> month;
	month--;
	if (month < 0 || month > 11) {
		cout << "Wrong month!" << endl;
		return;
	}
	for (int d = 1; d <= cal[month][0]; d++)
		if (cal[month][d] > cal[month][day])
			day = d;
	cout << "The hottest day of " << monthnames[month] << " is "
			<< monthnames[month] << " " << day << endl;
}

//- метод определения среднемесячной температуры. Месяц выбирает пользователь.
void averageOfMonth(double **cal) {
	int month { }, avg { };
	cout << "Enter the month (1 to 12): ";
	cin >> month;
	month--;
	if (month < 0 || month > 11) {
		cout << "Wrong month!" << endl;
		return;
	}
	for (int d = 1; d <= cal[month][0]; d++) {
		avg += cal[month][d];
	}
	avg /= cal[month][0];
	cout << "Average temperature of " << monthnames[month] << " is " << avg
			<< endl;
}

//- метод корректировки температуры в выбранный пользователем день.
void changeTemp(double **cal) {
	int month { }, day { 1 };
	double newtemp { };
	cout << "Enter the month (1 to 12): ";
	cin >> month;
	month--;
	if (month < 0 || month > 11) {
		cout << "Wrong month!" << endl;
		return;
	}
	cout << "Enter the day (1 to " << cal[month][0] << "): ";
	cin >> day;
	if (day < 1 || day > cal[month][0]) {
		cout << "Wrong day!" << endl;
		return;
	}
	cout << "Current value of temperature in " << monthnames[month] << " "
			<< day << " is ";
	printf("%-.2f\n", cal[month][day]);
	cout << "Enter the new value: ";
	cin >> newtemp;
	cal[month][day] = newtemp;
}

// Меню
void menu(double **cal) {
	int command { };
	enum commands {
		EXIT, COLDEST_Y, HOTTEST_Y, COLDEST_M, HOTTEST_M, AVG_M, CORR
	};
	do {
		printCalendar(cal);
		cout << "Enter command: " << endl;
		cout << "1. Find the coldest day of the year" << endl;
		cout << "2. Find the hottest day of the year" << endl;
		cout << "3. Find the coldest day of a month" << endl;
		cout << "4. Find the hottest day of a month" << endl;
		cout << "5. Find average temperature of a month" << endl;
		cout << "6. Change the temperature for a particular day" << endl;
		cout << "0. Exit" << endl;
		cin >> command;
		switch (command) {
		case EXIT:
			return;
		case COLDEST_Y:
			coldestOfYear(cal);
			break;
		case HOTTEST_Y:
			hottestOfYear(cal);
			break;
		case COLDEST_M:
			coldestOfMonth(cal);
			break;
		case HOTTEST_M:
			hottestOfMonth(cal);
			break;
		case AVG_M:
			averageOfMonth(cal);
			break;
		case CORR:
			changeTemp(cal);
			break;
		default:
			cout << "Wrong command!" << endl;
		}
	} while (command);
}
