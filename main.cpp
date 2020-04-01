#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

vector<int> collection;
vector<int>map;
bool *is_sum;
int greatest=0;
int ammount_of_elem = 0;
int immerion = 0;
bool found = false;
bool *tab;

void read() {

	ifstream file;
	int number;
	string name;
	cout << "Enter name of file:" << endl;
	cin >> name;
	name += ".txt";
	file.open(name, std::ios::in);
	if (file.good() == false)
		cout << "Unable to open file!" << endl;
	else {
		while (file.good()) {
			file >> number;
			collection.push_back(number);
		}
		cout << "File successfully loaded!" << endl;
		file.close();
	}
}

int Check_Immerion() {
	int i = 1;
	while(ammount_of_elem*2 != i*(i+1)){
		i++;
		if (i*(i + 1) > ammount_of_elem * 2) {
			cout << "Erroneous collection!" << endl;
			return 0;
		}
	}
	return i;
}

bool Sum_Compatible() {
	int local_sum = 0;
	bool a=1;
	for (int i = 0; i < ammount_of_elem; i++) {
		is_sum[i] = false;
	}
	for (int i = 0; i < map.size(); i++) {
		local_sum = 0;
		for (int j = i; j < map.size(); j++) {
			a = 0;
			local_sum += map[j];
			if (local_sum > greatest) {
				return 0;
			}
			if (find(collection.begin(), collection.end(), local_sum) == collection.end()) {
				return 0;
			}
			for (int i = 0; i < ammount_of_elem; i++) {
				if (collection[i] == local_sum && is_sum[i] == false) {
					is_sum[i]= true;
					a = 1;
					break;
				
				}
			}
			if (a == 0)
				return 0;
		}
	}
	return 1;
}

bool SumAll() {
	int sum = 0;
	for (int i = 0; i < map.size(); i++)
		sum += map[i];
	if (sum == greatest)
		return 1;
	else return 0;
}
void Nemo(int dodaj, int *jest, int poziom_zaglebienia) {

	int temp;
	vector<int>checked;
	int item;
	
	map.push_back(dodaj);
	//for (int i = 0; i < mapka.size(); i++)
	//	cout << mapka[i] << " ";
	//cout << endl;

	for (int i = 0; i < ammount_of_elem; i++) {
		if (collection[i] == dodaj && tab[i] == 0) {
				tab[i] = true;
				break;
		}
	}
	if (poziom_zaglebienia == 0)
		checked.push_back(dodaj);

	if (Sum_Compatible()) {
		if (poziom_zaglebienia < immerion-1) {
			for (int i = 0; i < ammount_of_elem; i++) {
				if(tab[i] == false){
					checked.push_back(collection[i]);
					Nemo(collection[i], jest, (poziom_zaglebienia + 1));
					break;
				}
			}
		}
		else if (SumAll()) {
			*jest = true;
		}
		else {
			for (int i = 0; i < ammount_of_elem; i++) {
				int c = map[map.size() - 1];
				if (collection[i] == c && tab[i] ==true) {
					tab[i] = false; break;
				}
			}
			map.pop_back();
			return;
		}
	}
	else {
		for (int i = 0; i < ammount_of_elem; i++) {
			int c = map[map.size() - 1];
			if (collection[i] == c && tab[i] == true) {
				tab[i] = false; break;
			}
		}
		map.pop_back();
		return;

	}
 	if (*jest == true) {
		return;
	}
	else {
		for (int i = 0; i < ammount_of_elem; i++) {
			item = collection[i];
			if (find(checked.begin(), checked.end(), item) == checked.end() && tab[i] == false) {
				checked.push_back(collection[i]);
				Nemo(collection[i], jest, (poziom_zaglebienia + 1));
				if (*jest == true) return;
			}
		}
		for (int i = 0; i < ammount_of_elem; i++) {
			int c = map[map.size() - 1];
			if (collection[i] == c && tab[i] == true) {
					tab[i] = false; break;
			}
		}
		map.pop_back();
		return;

	}
}
int main(){
    std::cout << "Hello World!\n"; 
	
	read();

	for (int i = 0; i < collection.size(); i++) {
		cout << collection[i] << " ";
	}

	int is_found = false;
	double stoper;
	clock_t start, stop;
	sort(collection.begin(), collection.end());
	greatest = collection[collection.size() - 1];
	ammount_of_elem = collection.size();
	immerion = Check_Immerion();
	if (immerion != 0) {
		tab = new bool[ammount_of_elem];
		is_sum = new bool[ammount_of_elem];


		for (int i = 0; i < ammount_of_elem; i++) {
			tab[i] = false;
			is_sum[i] = false;
		}
		cout << endl;
		start = clock();
		for (int i = 0; i < collection.size(); i++) {
			//	tab[i] = 1;
			Nemo(collection[i], &is_found, 0);
			if (is_found == true) break;
		}
		stop = clock();
		long time = (long)(stop - start);
		if (is_found == false)
			cout << "No solution " << endl;
		else {
			cout << "The map is: " << endl;
			for (int i = 0; i < map.size(); i++)
				cout << map[i] << " ";
			cout << "Operating time: " << time << "ms" << endl;
		}
	}
	
	system("pause");
}

