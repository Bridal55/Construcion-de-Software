#include <iostream>
#include <vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<ctime>
using namespace std;

int numericMonth(string& m) {
	if (m == "Jun")
		return 5;
	else if (m == "Jul")
		return 6;
	else if (m == "Aug")
		return 7;
	else if (m == "Sep")
		return 8;
	else if (m == "Oct")
		return 9;
}

time_t convertTime(string month, int day, string hour) {
	tm t = {};
	t.tm_year = 2025 - 1900; 
	t.tm_mon = numericMonth(month);
	t.tm_mday = day;

	stringstream ts(hour);
	string h, m, s;

	getline(ts, h, ':');
	getline(ts, m, ':');
	getline(ts, s, ':');

	t.tm_hour = stoi(h);
	t.tm_min = stoi(m);
	t.tm_sec = stoi(s);

	time_t definitive_date = mktime(&t);
	return definitive_date;
}

class Registers {
private:
	string readable_date;
	time_t date;
	string ip;
	string reason;
public:
	Registers(string readable_d,time_t d,string i, string r){
		readable_date = readable_d;
		date = d;
		ip = i;
		reason = r;
	}

	Registers() {}

	void merge(vector<Registers>& p, int left, int mid, int right) {
		int n1 = mid - left + 1;
		int n2 = right - mid;

		vector<Registers> l(n1);
		vector<Registers> r(n2);

		for (int i = 0; i < n1; i++) {
			l[i] = p[left + i];
		}
		for (int j = 0; j < n2; j++) {
			r[j] = p[mid + 1 + j];
		}

		int i = 0, j = 0;
		int k = left;

		while (i < n1 && j < n2) {
			if (l[i].date < r[j].date) {
				p[k] = l[i];
				i++;
			}
			else {
				p[k] = r[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			p[k] = l[i];
			i++;
			k++;
		}

		while (j < n2) {
			p[k] = r[j];
			j++;
			k++;
		}
	}

	void merge_sort(vector <Registers>& r, int left, int right) {
		if (left >= right)
			return;
		int mid = left + (right - left) / 2;
		merge_sort(r, left, mid);
		merge_sort(r, mid + 1, right);
		merge(r, left, mid, right);
	}

	void findLogs(vector<Registers>& r) {
		string stmonth, stday, sthour, emonth, eday, ehour;
		
		
		cout << "Enter the Month of the start date (Jun,Jul,Aug,Sep,Oct): ";
		cin >> stmonth;
		cout << "Enter the Day of the start date: ";
		cin >> stday;
		cout << "Enter the Hour of the start date (12:23:39): ";
		cin >> sthour;
		cout << "Enter the Month of the end date (Jun,Jul,Aug,Sep,Oct ): ";
		cin >> emonth;
		cout << "Enter the Day of the end date: ";
		cin >> eday;
		cout << "Enter the Hour of the end date (12:23:39): ";
		cin >> ehour;

		time_t start = convertTime(stmonth, stoi(stday), sthour);
		time_t end = convertTime(emonth, stoi(eday), ehour);

		for (int i = 0; i < r.size(); i++) {
			if (r[i].date >= start && r[i].date <= end) {
				cout << r[i].readable_date << "   " << r[i].ip << "   " << r[i].reason << endl;
			}
		}

	}

	void save(vector <Registers> &r) {
		ofstream f2("C:/Users/gking/Desktop/Organized Data.txt");
		for (int i = 0; i < r.size(); i++) {
			f2 << r[i].readable_date << "   " << r[i].ip << "   " << r[i].reason << endl;
		}
		f2.close();
	}

};

int main() {
	vector<Registers> bitacora = {};
	string line;
	int i;


	ifstream f("C:/Users/gking/Downloads/bitacora.txt");
	while (getline(f, line)) {
		stringstream ss(line);
		vector <string> value;
		string holder;
		string reas = "";
		string read = "";
		i = 0;
		while (getline(ss, holder, ' ')) {
			value.push_back(holder);
		}
		for (int j = 4; j<value.size(); j++) {
			reas += " ";
			reas += value[j];
		}
		read = value[0] + " " + value[1] + " " + value[2];
		time_t date = convertTime(value[0], stoi(value[1]), value[2]);

		bitacora.push_back(Registers(read, date, value[3], reas));
	}

	bitacora[1].merge_sort(bitacora, 0, bitacora.size() - 1);

	while (true) {
		int choice;
		cout << "\nSelect which of the following you want to do:\n1. Enter two dates and print every register between them\n2. Save\n3. Exit the program" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			bitacora[1].findLogs(bitacora);
			break;
		case 2:
			bitacora[1].save(bitacora);
			break;
		case 3:
			cout << "Program ended" << endl;
			exit(0);
			return 0;
		}
	}
	}