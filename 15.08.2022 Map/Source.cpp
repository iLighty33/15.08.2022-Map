#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <algorithm>
#include <fstream>

// ������� ��������� ������������� �� 10'000 
// ���������
// ��������� ���������� ��������� map 
// �������� ����� ���������� �� ����� � ������������
// ������ � �������� ������ � ����������� map
//
// ����� 10 ������������� � ����������� �������� � ������� ���������
// �������� � ���� ������ �������������(� ������ ��������)

class User {
public:
	User() = default;
	int id;
	std::string name;
	bool dayShift; // 0 - nigth, 1 - day
	int salary; // ��������
	double temp;

	User(int id, std::string name, bool dayShift, int salary) 
		:id(id), 
		name(name), 
		dayShift(dayShift), 
		salary(salary) {}

	bool operator==(const User& other)const {
		return id == other.id && name == other.name;
	}


	
	friend std::ostream& operator << (std::ostream& out, const User& obj) {
		out << obj.id << ' ' << obj.name << ' ' << obj.dayShift << ' ' << obj.salary << ' ';
		return out;
	}

	friend std::istream& operator>>(std::istream& in, User& obj) {
		in >> obj.id >> obj.name >> obj.dayShift >> obj.salary;
		return in;
	}
};

void task(int count) {
	std::vector<User> database;
	database.reserve(count);
	auto begin = std::chrono::steady_clock::now();
	for (int i = 0; i < database.capacity(); i++)
	{
		database.emplace_back(i + 1, "user" + std::to_string(i + 1), static_cast<bool>(::rand()%2), 32000+ ::rand());
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms =
		std::chrono::duration_cast<std::chrono::nanoseconds>
		(end - begin);
	std::cout << "create vector: " << elapsed_ms.count() << " ms\n";

	std::map<std::string, User*> searchTree;

	begin = std::chrono::steady_clock::now();
	for (auto& user : database) {
		searchTree.insert({ user.name, &user });
	}
	end = std::chrono::steady_clock::now();
	elapsed_ms =
		std::chrono::duration_cast<std::chrono::nanoseconds>
		(end - begin);
	std::cout << "create map: " << elapsed_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	auto vec_tmp = std::find(
		database.begin(),
		database.end(),
		User{ count,"user" + std::to_string(count), true, 12345 }
	);
	end = std::chrono::steady_clock::now();
	elapsed_ms =
		std::chrono::duration_cast<std::chrono::nanoseconds>
		(end - begin);
	std::cout << "Find in vector: " <<
		elapsed_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	auto map_tmp = searchTree.find("user" + std::to_string(count));
	end = std::chrono::steady_clock::now();
	elapsed_ms =
		std::chrono::duration_cast<std::chrono::nanoseconds>
		(end - begin);
	std::cout << "Find in map: " <<
		elapsed_ms.count() << " ms\n";
}

std::map<std::string, User> g_Users;

int main() {
	/*g_Users.insert({"user", {1, "user"}}); // ������ �� ���� ����������� �� ����� ���������� ������������ �����������.
	User local;
	local.id = 2;
	local.name = "User2";
	g_Users.insert({ local.name, local });
	g_Users["User3"]; // ���� ���� � map ����, ������� ��������� � User3 - ����� ���� ���������. ���������� ������ ����� ������������.
	g_Users["User3"].id = 3;
	g_Users["User3"].name = "User3";
	std::pair<const std::string, User> &tmp = *(g_Users.begin());
	g_Users.find("User3"); // ���������� �������������� User3.
	
	auto where_ = g_Users.find("User3");
	where_->second.id; // �����������. ����� ����� ���������� ��� ���� second ������.
	
	auto& [login, user] = *(g_Users.find("User3"));// ��� ������ map ���������. ������ ���������, ��� ��������� User3. �������� ������������ � ��� �����
	user.id; // ��������� ��������� ��� ���� ��� �� ������� (login, user) � � ���������� ������������ ����, ��� �� ��� ��������.
	*/
	
	// Vector

	//task(1'000'000);

	std::vector <User> Users;
	Users.reserve(100);

	for (int i = 0; i < Users.capacity(); i++)
	{
		Users.emplace_back(i + 1, "user" + std::to_string(i + 1), static_cast<bool>(::rand() % 2), 32000 + ::rand());
	}

	std::cout << "Id:\t" << "Name:\t" << "dayShift:\t" << "salary:\t\n";

	int avarageSalary = 0;

	for (auto& el : Users) {

		std::cout << el.id << "\t";
		std::cout << el.name << "\t";
		std::cout << el.dayShift << "\t\t";
		std::cout << el.salary << "\t";
		std::cout << std::endl;
		avarageSalary += el.salary;
		
	}
	avarageSalary = avarageSalary / 100;

	std::cout << "\nAverage salary: " << avarageSalary << std::endl;

	// Finding 3 users near average Salary

	for (auto& el : Users) {
		el.temp = (double)(el.salary - avarageSalary);
		if(el.temp > 2000 && el.temp < 2600)
		std::cout << "Name: " << el.name << " " << "Salary: " << el.salary << "\n";
	}

	std::ofstream out;          // ����� ��� ������
	out.open("C:\\Users\\� - 3\\source\\repos\\���������� �\\15.08.2022 Map\\15.08.2022 Map\\hello.txt"); // ��������� ���� ��� ������
	
	for (auto& el : Users) {
		if (out.is_open())
		{
			out << el.id << "\t";
			out << el.name << "\t";
			out << el.dayShift << "\t\t";
			out << el.salary << "\t";
			out << std::endl;
		}
		else
			std::cout << "Error openning file!\n";

	
	}
	std::cout << "End of program" << std::endl;

	// Using Multimap



	return 0;

}