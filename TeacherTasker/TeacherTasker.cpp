#include <iostream>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

// Структура яка описує дату
struct Date
{
	int day; // День
	int month; // Місяць
	int year; // Рік
};
// Структура яка описує викладача
struct Teachers
{
	string nameAndSurname; // Ініціали
	string conferenceVenue; // Місто проведення конференції
	Date date; // Дата проведення конференції
	string topic; // Тема конференції
	string topicTeacher; // Тема доповіді викладача
};
// Структура з унікальними даними
struct Teacher
{
	string nameAndSurname; // Ініціали
	int amount; // Скільки разів викладача приймав участь у конференції
};

// Змінює напис при використанні функції system("pause"); з російської на українську
void pause_ua(string message);
// Завантажує дані з файлу в масив структур
void loadDataFromFile(Teachers teachers[], int* elem_arr);
// Виводить дані з масиву структур
void printDataFromStruct(Teachers teachers[], int* elem_arr);
// Додає дані до масиву структур
void addDataToStruct(Teachers teachers[], int* elem_arr);
// Виводить індивідуальне меню
void individualMenu();
// Сортує дані за полем nameAndSurname по алфавіту
void sortByAlphabet(Teachers teacher[], int* elem_arr);
// Перевіряє введені користувачем пункти меню
int checker();
// Виводить викладачів за вказаним користувачем періодом 
void printTeachersByDate(Teachers teachers[], int* elem_arr);
// Перевіряе дату на коректність
Date dateChecker();
// Виводить найактивніших викладачів
void activityTeachers(Teachers teachers[], int* elem_arr);
// Сортує викладачів за активністю
void sortActivityTeachers(Teacher teacher[], int k);
// Виводить теми викладача за вказаними ініціалами
void teacherTopic(Teachers teachers[], int* elem_arr);

Teachers teachers[50];
int elem_arr(0);

int main()
{
	system("chcp 1251");

	bool isExit = false;
	int action;

	while (!isExit)
	{
		system("cls");
		cout << "      Головне меню програми\n";
		cout << "1. Завантаження даних\n";
		cout << "2. Перегляд даних\n";
		cout << "3. Додавання нових записів\n";
		cout << "4. Індивідуальні завдання\n";
		cout << "5. Вийти\n";
		cout << "Оберіть пункт меню: ";
		action = checker();

		switch (action)
		{
		case 1:
			loadDataFromFile(teachers, &elem_arr);
			break;
		case 2:
			printDataFromStruct(teachers, &elem_arr);
			break;
		case 3:
			addDataToStruct(teachers, &elem_arr);
			break;
		case 4:
			individualMenu();
			break;
		case 5:
			pause_ua("Програма завершує свою роботу!");
			isExit = true;
			break;
		default:
		{
			pause_ua("Такого пункта меню не існує!");
			break;
		}
		}
	}
	return 0;
}

void pause_ua(string message)
{
	system("cls");
	cout << message << endl;
	cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
	system("PAUSE>nul");
}

void loadDataFromFile(Teachers teachers[], int* elem_arr)
{
	system("cls");

	cout << "Завантаження даних із файлу...\n";

	string str;
	fstream file;
	int k(0);
	bool isFileOpen;

	file.open("C:\\Users\\danil\\source\\repos\\TeacherTasker\\TeacherTasker\\resources\\teachers.txt", ios::in);
	if (file.is_open())
	{
		isFileOpen = true;
		const char* inputData;
		while (!file.eof())
		{
			getline(file, str);
			teachers[k].nameAndSurname = str;

			getline(file, str);
			teachers[k].conferenceVenue = str;

			getline(file, str);
			inputData = str.c_str();
			teachers[k].date.day = atoi(inputData);

			getline(file, str);
			inputData = str.c_str();
			teachers[k].date.month = atoi(inputData);

			getline(file, str);
			inputData = str.c_str();
			teachers[k].date.year = atoi(inputData);

			getline(file, str);
			teachers[k].topic = str;

			getline(file, str);
			teachers[k].topicTeacher = str;

			k++;
		}
	}
	else
	{
		pause_ua("Неможливо відкрити файл");
		return;
	}
	file.close();

	*elem_arr = k;

	if (elem_arr == 0)
	{
		cout << "Файл порожній!\n";
		cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
		system("PAUSE>nul");
		return;
	}

	cout << "Дані успішно вивантажені з файлу!\n";
	cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
	system("PAUSE>nul");
}

void printDataFromStruct(Teachers teachers[], int* elem_arr)
{

	if (elem_arr == 0)
	{
		pause_ua("Структура порожня, або ви не завантажили дані з неї!");
		return;
	}
	else
	{
		system("cls");

		sortByAlphabet(teachers, elem_arr);

		cout << "Викладачі які приймають участь\n\n";

		cout << "Усього записів: " << *elem_arr << endl;
		cout << "+-------------------------------+\n";

		cout.setf(ios::left);
		cout.width(16);
		cout << "Викладач";
		cout.setf(ios::left);
		cout.width(12);
		cout << "Місто";
		cout.setf(ios::left);
		cout.width(13);
		cout << "Дата";
		cout.setf(ios::left);
		cout.width(14);
		cout << "Тематика";
		cout.setf(ios::left);
		cout.width(15);
		cout << "Тема";

		cout << endl << endl;

		for (int i = 0; i < *elem_arr; i++)
		{
			cout.setf(ios::left);
			cout.width(16);
			cout << teachers[i].nameAndSurname;
			cout.setf(ios::left);
			cout.width(12);
			cout << teachers[i].conferenceVenue;

			cout.setf(ios::left);
			cout.width(1);
			if (teachers[i].date.day < 10) cout << 0 << teachers[i].date.day;
			else cout << teachers[i].date.day;
			cout << ".";
			cout.setf(ios::left);
			cout.width(1);
			if (teachers[i].date.month < 10) cout << 0 << teachers[i].date.month;
			else cout << teachers[i].date.month;
			cout << ".";
			cout.setf(ios::left);
			cout.width(7);
			cout << teachers[i].date.year;

			cout.setf(ios::left);
			cout.width(14);
			cout << teachers[i].topic;
			cout.setf(ios::left);
			cout.width(15);
			cout << teachers[i].topicTeacher << endl;
		}

		cout << "\n+-------------------------------+\n";
		cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
		system("PAUSE>nul");
	}
}

void addDataToStruct(Teachers teachers[], int* elem_arr)
{
	char nameSurname[256];
	char conferenceVenue[256];
	char topic[256];
	char topicTeacher[256];

	fstream file;
	file.open("C:\\Users\\danil\\source\\repos\\TeacherTasker\\TeacherTasker\\resources\\teachers.txt", ios::app);
	bool isExit = true;
	int k = *elem_arr;
	string action;
	bool isPresent = false;

	system("cls");
	cout << "Додавання нових даних\n";
	cout << "================\n";
	if (file.is_open())
	{
		while (isExit)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "П.І.Б викладача: ";
			cin.getline(nameSurname, 256);

			cout << "Місто пров. конференції: ";
			cin.getline(conferenceVenue, 256);

			cout << "Введіть дату проведення конференції\n";

			Date date = dateChecker();

			if (char(cin.peek()) == '\n') cin.ignore();

			cout << "Тематика конференції: ";
			cin.getline(topic, 256);

			cout << "Тема доповіді викладача: ";
			cin.getline(topicTeacher, 256);

			for (int i = 0; i < *elem_arr; i++)
			{
				if (nameSurname == teachers[i].nameAndSurname 
					&& conferenceVenue == teachers[i].conferenceVenue
					&& date.day == teachers[i].date.day
					&& date.month == teachers[i].date.month
					&& date.year == teachers[i].date.year
					&& topic == teachers[i].topic
					&& topicTeacher == teachers[i].topicTeacher)
				{
					isPresent = true;
					break;
				}
			}

			if (isPresent)
			{
				pause_ua("Такий викладач вже бере участь у конференції!");
				return;
			}
			else
			{
				teachers[k].nameAndSurname = nameSurname;
				file << '\n' << teachers[k].nameAndSurname << '\n';

				teachers[k].conferenceVenue = conferenceVenue;
				file << teachers[k].conferenceVenue << '\n';

				teachers[k].date.day = date.day;
				file << teachers[k].date.day << '\n';

				teachers[k].date.month = date.month;
				file << teachers[k].date.month << '\n';

				teachers[k].date.year = date.year;
				file << teachers[k].date.year << '\n';

				teachers[k].topic = topic;
				file << teachers[k].topic << "\n";

				teachers[k].topicTeacher = topicTeacher;
				file << teachers[k].topicTeacher;
			}

			cout << "Бажаєте додати ще один запис? y/n: ";
			cin >> action;
			isExit = (action == "y") ? true : false;
			k++;
		}
		*elem_arr = k;
	}
	else
	{
		pause_ua("Помилка відкриття файлу");
		return;
	}
	file.close();
}

void individualMenu()
{
	bool isExit = false;
	int action;
	while (!isExit) {
		system("cls");
		cout << "      Меню індивідуальних завдань\n";
		cout << "1. Список викладачів на конференціях за певний період часу\n";
		cout << "2. 5 найкращих викладачів на конференціях\n";
		cout << "3. Теми доповідей обраного викладача\n";
		cout << "4. Повернуться до головного меню\n";
		cout << "Оберіть пункт меню: ";
		action = checker();

		switch (action)
		{
		case 1:
			printTeachersByDate(teachers, &elem_arr);
			break;
		case 2:
			activityTeachers(teachers, &elem_arr);
			break;
		case 3:
			teacherTopic(teachers, &elem_arr);
			break;
		case 4:
			isExit = true;
			break;
		default:
		{
			pause_ua("Такого пункта меню не існує!");
			break;
		}
		}
	}
}

void sortByAlphabet(Teachers teacher[], int* elem_arr)
{
	Teachers t;
	for (int i = *elem_arr - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (teacher[j].nameAndSurname > teacher[j + 1].nameAndSurname)
			{
				t = teacher[j];
				teacher[j] = teacher[j + 1];
				teacher[j + 1] = t;
			}
		}
	}
	return;
}

void sortActivityTeachers(Teacher teacher[], int k)
{
	Teacher t;
	for (int i = k - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (teacher[j].amount < teacher[j + 1].amount)
			{
				t = teacher[j];
				teacher[j] = teacher[j + 1];
				teacher[j + 1] = t;
			}
		}
	}
	return;
}

int checker()
{
	char strFirst[256];
	char strSecond[256];
	int i, k(1);

	while (k != 0)
	{
		k = 0;
		cin >> strFirst;
		i = atoi(strFirst);
		if (i == 0)
		{
			k = 1;
		}
		else
		{
			itoa(i, strSecond, 10);
			if (strcmp(strFirst, strSecond) != 0) k = 1;
		}
		if (k == 1) cout << "Ви ввели літери чи не цілі числа! Повторіть введення: ";
	}
	return i;
}

void printTeachersByDate(Teachers teachers[], int* elem_arr)
{
	Date dateFirst, dateSecond;
	bool isResult = false;
	int k(0);

	system("cls");

	if (*elem_arr == 0)
	{
		cout << "Масив структур порожній!\n";
		cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
		system("PAUSE>nul");
		return;
	}
	else
	{
		cout << "Показ викладачів у вказаний період часу\n\n";

		cout << "Введіть першу дату\n";
		cout << "========\n";
		cout << "День: ";
		cin >> dateFirst.day;
		cout << "Місяць: ";
		cin >> dateFirst.month;
		cout << "Рік: ";
		cin >> dateFirst.year;
		cout << endl;

		cout << "Введіть другу дату\n";
		cout << "========\n";
		cout << "День: ";
		cin >> dateSecond.day;
		cout << "Місяць: ";
		cin >> dateSecond.month;
		cout << "Рік: ";
		cin >> dateSecond.year;

		if (dateFirst.year < 1980 || dateSecond.year < 1980)
		{
			pause_ua("Система обліку конференцій вчителів не може зберігати дані до 1980 року.");
			return;
		}
		else if (dateFirst.day > 31 && dateFirst.month  == 1 
			|| dateSecond.day > 31 && dateSecond.month == 1 
			|| dateFirst.day > 31 && dateFirst.month == 3
			|| dateSecond.day > 31 && dateSecond.month == 3
			|| dateFirst.day > 31 && dateFirst.month == 7
			|| dateSecond.day > 31 && dateSecond.month == 7
			|| dateFirst.day > 31 && dateFirst.month == 8
			|| dateSecond.day > 31 && dateSecond.month == 8
			|| dateFirst.day > 31 && dateFirst.month == 10
			|| dateSecond.day > 31 && dateSecond.month == 10
			|| dateFirst.day > 31 && dateFirst.month == 12
			|| dateSecond.day > 31 && dateSecond.month == 12)
		{
			pause_ua("В місяцях: Січень, Березень, Травень, Липень, Серпень, Жовтень, Грудень, не може бути більше 31 днів!");
			return;
		}
		else if (dateFirst.day > 30 && dateFirst.month == 4
			|| dateSecond.day > 30 && dateSecond.month == 4
			|| dateFirst.day > 30 && dateFirst.month == 6
			|| dateSecond.day > 30 && dateSecond.month == 6
			|| dateFirst.day > 30 && dateFirst.month == 9
			|| dateSecond.day > 30 && dateSecond.month == 9
			|| dateFirst.day > 30 && dateFirst.month == 11
			|| dateSecond.day > 30 && dateSecond.month == 11)
		{
			pause_ua("В місяцях: Квітень, Червень, Вересень, Листопад, не може бути більше 30 днів!");
			return;
		}
		else if (dateFirst.day <= 0 || dateSecond.day <= 0)
		{
			pause_ua("День не може бути менше або дорівнювати нулю!");
		}
		else if (dateFirst.month <= 0 || dateSecond.month <= 0)
		{
			pause_ua("Місяць не може бути менше або дорівнювати нулю!");
		}
		else if (dateFirst.day > 29 && dateFirst.month == 2)
		{
			pause_ua("В Лютому не може бути більше 29 днів!");
			return;
		}
		else if (dateFirst.month > 12 || dateSecond.month > 12)
		{
			pause_ua("Місяців не може бути більше 12!");
			return;
		}
		else if (dateFirst.month > dateSecond.month)
		{
			pause_ua("Перший зазначений вами місяць не може бути більшим за другий!");
			return;
		}
		else if (dateFirst.year > dateSecond.year)
		{
			pause_ua("Перший зазначений вами рік не може бути більшим за другий!");
			return;
		}

		sortByAlphabet(teachers, elem_arr);

		system("cls");

		cout << "Перегляд викладачів в заданий період часу\n\n";

		cout << "+-------------------------------+\n";
		cout.setf(ios::left);
		cout.width(16);
		cout << "Викладач";
		cout.setf(ios::left);
		cout.width(12);
		cout << "Місто";
		cout.setf(ios::left);
		cout.width(13);
		cout << "Дата";
		cout.setf(ios::left);
		cout.width(14);
		cout << "Тематика";
		cout.setf(ios::left);
		cout.width(15);
		cout << "Тема";

		cout << endl << endl;

		for (int i = 0; i < *elem_arr; i++)
		{
			isResult = false;

			if (teachers[i].date.year > dateFirst.year && teachers[i].date.year < dateSecond.year) isResult = true;
			if (teachers[i].date.year == dateFirst.year && teachers[i].date.year < dateSecond.year && teachers[i].date.month > dateFirst.month) isResult = true;
			if (teachers[i].date.year == dateFirst.year && teachers[i].date.month == dateFirst.month && teachers[i].date.day >= dateFirst.day) isResult = true;
			if (teachers[i].date.year == dateSecond.year && teachers[i].date.month < dateSecond.month) isResult = true;
			if (teachers[i].date.year == dateSecond.year && teachers[i].date.month == dateSecond.month && teachers[i].date.day <= dateSecond.day) isResult = true;

			if (isResult)
			{
				cout.setf(ios::left);
				cout.width(16);
				cout << teachers[i].nameAndSurname;
				cout.setf(ios::left);
				cout.width(12);
				cout << teachers[i].conferenceVenue;

				cout.setf(ios::left);
				cout.width(1);
				if (teachers[i].date.day < 10) cout << 0 << teachers[i].date.day;
				else cout << teachers[i].date.day;
				cout << ".";
				cout.setf(ios::left);
				cout.width(1);
				if (teachers[i].date.month < 10) cout << 0 << teachers[i].date.month;
				else cout << teachers[i].date.month;
				cout << ".";
				cout.setf(ios::left);
				cout.width(7);
				cout << teachers[i].date.year;

				cout.setf(ios::left);
				cout.width(14);
				cout << teachers[i].topic;
				cout.setf(ios::left);
				cout.width(15);
				cout << teachers[i].topicTeacher << endl;
				k++;
			}
		}
		cout << "\n+-------------------------------+\n";

		if (k == 0)
		{
			system("cls");
			cout << "В заданий період часу вчителі не брали участі у конференціях!\n";
		}

		cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
		system("PAUSE>nul");
	}
	return;
}

Date dateChecker()
{
	Date date;
	bool isExit = true;
	bool isCorrectly;

	while (isExit)
	{
		cout << "День: ";
		cin >> date.day;

		cout << "Місяць: ";
		cin >> date.month;

		cout << "Рік: ";
		cin >> date.year;

		isCorrectly = true;

		if (date.day <= 0 || date.month <= 0)
		{
			cout << "+================+\n";
			cout << "День або місяць не може будти менше нуля або дорівнювати нулю!\n";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (date.day > 31 && date.month == 1
			|| date.day > 31 && date.month == 3
			|| date.day > 31 && date.month == 7
			|| date.day > 31 && date.month == 8
			|| date.day > 31 && date.month == 10
			|| date.day > 31 && date.month == 12)
		{
			cout << "+================+\n";
			cout << "В місяцях: Січень, Березень, Травень, Липень, Серпень, Жовтень, Грудень, не може бути більше 31 днів!\n";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (date.day > 30 && date.month == 4
			|| date.day > 30 && date.month == 6
			|| date.day > 30 && date.month == 9
			|| date.day > 30 && date.month == 11)
		{
			cout << "+================+\n";
			cout << "В місяцях: Квітень, Червень, Вересень, Листопад, не може бути більше 30 днів!\n";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (date.day > 29 && date.month == 2)
		{
			cout << "+================+\n";
			cout << "В Лютому не може бути більше 29 днів!";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (date.month > 12)
		{
			cout << "+================+\n";
			cout << "Місяців не може бути більше ніж 12!\n";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (date.year < 1980)
		{
			cout << "+================+\n";
			cout << "Система обліку конференцій вчителів не може зберігати дані до 1980 року.\n";
			cout << "+================+\n";
			isCorrectly = false;
		}

		if (isCorrectly) isExit = false;
	}
	return date;
}

void activityTeachers(Teachers teachers[], int* elem_arr)
{
	if (*elem_arr == 0)
	{
		pause_ua("Масив даних пустий!");
		return;
	}

	Teacher teacher[100];
	int k = 0;

	system("cls");
	
	cout << "5 викладачів які найчастіше приймають участь у конференціях\n\n";

	teacher[0].nameAndSurname = teachers[0].nameAndSurname;
	teacher[0].amount = 0;
	k++;

	sortByAlphabet(teachers, elem_arr);

	for (int i = 0; i < *elem_arr; i++)
	{
		bool isPresent = true;
		for (int j = 0; j < k; j++)
		{
			if (teacher[j].nameAndSurname == teachers[i].nameAndSurname) 
			{
				isPresent = false;
			}

			if (isPresent)
			{
				bool isReally = false;

				for (int e = 0; e <= k; e++)
				{
					if (teacher[e].nameAndSurname == teachers[i].nameAndSurname)
					{
						isReally = true;
						break;
					}
				}

				if (!isReally)
				{
					teacher[k].nameAndSurname = teachers[i].nameAndSurname;
					teacher[k].amount = 0;
					k++;
				}
			}
		}
	}

	for (int j = 0; j < k; j++)
	{
		for (int i = 0; i < *elem_arr; i++)
		{
			if (teacher[j].nameAndSurname == teachers[i].nameAndSurname) teacher[j].amount += 1;
		}
	}

	sortActivityTeachers(teacher, k);

	cout << "+-------------------------------+\n";

	cout.setf(ios::left);
	cout.width(16);
	cout << "Викладач";

	cout.setf(ios::left);
	cout.width(2);
	cout << "Кількість";

	cout << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout.setf(ios::left);
		cout.width(16);
		cout << teacher[i].nameAndSurname;

		cout.setf(ios::left);
		cout.width(2);
		cout << teacher[i].amount << endl;
	}

	cout << "\n+-------------------------------+\n";

	cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
	system("PAUSE>nul");
}

void teacherTopic(Teachers teachers[], int* elem_arr)
{
	if (*elem_arr == 0)
	{
		pause_ua("Масив даних пустий!");
		return;
	}

	system("cls");

	char teacherName[256];
	bool isFind = false;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Теми доповідей обраного викладача\n\n";
	cout << "Ведіть ініціали викладача: ";
	cin.getline(teacherName, 256);

	for (int i = 0; i < *elem_arr; i++)
	{
		if (teacherName == teachers[i].nameAndSurname)
		{
			isFind = true;
		}
	}

	system("cls");

	if (isFind)
	{
		cout << "Теми доповідей обраного викладача\n\n";

		cout << "+-------------------------------+\n";

		cout.setf(ios::left);
		cout.width(16);
		cout << "Викладач";

		cout.setf(ios::left);
		cout.width(15);
		cout << "Тема";

		cout << endl << endl;

		for (int i = 0; i < *elem_arr; i++)
		{
			if (teacherName == teachers[i].nameAndSurname)
			{
				cout.setf(ios::left);
				cout.width(16);
				cout << teachers[i].nameAndSurname;

				cout.setf(ios::left);
				cout.width(15);
				cout << teachers[i].topicTeacher << endl;
			}
		}

		cout << "\n+-------------------------------+\n";

		cout << "Щоб продовжити, натисніть будь-яку клавішу . . .";
		system("PAUSE>nul");
	}
	else
	{
		pause_ua("Вікладач з такими ініціалами не приймав участі в конференціях!");
	}
}