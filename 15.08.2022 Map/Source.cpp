#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <stdlib.h>

class User {
public:
	int id;
	std::string name;
	bool graphicOfWork = 0; // 1-day 0-night
	int Salary = 0; // from 10 000 to 20 000 usd
	//10 users - 

	User(int id, std::string name):id(id), name(name){}

	bool operator ==(const User& other) const {
		return id == other.id && name == other.name;
	}
};

std::map<std::string, User> g_Users;

int main() {
	/*g_Users.insert({"user", {1, "user"}}); // данные из пары скопируютс€ во вновь созданного конструктора копировани€.
	User local;
	local.id = 2;
	local.name = "User2";
	g_Users.insert({ local.name, local });
	g_Users["User3"]; // если нету в map узла, который хранитьс€ в User3 - такой узел создастс€. √енерирует пустой класс пользовател€.
	g_Users["User3"].id = 3;
	g_Users["User3"].name = "User3";
	std::pair<const std::string, User> &tmp = *(g_Users.begin());
	g_Users.find("User3"); // возвращает местоположение User3.
	
	auto where_ = g_Users.find("User3");
	where_->second.id; // малоудобна€. ѕотом нужно разъ€сн€ть что этот second значит.
	
	auto& [login, user] = *(g_Users.find("User3"));// „то внутри map находитс€. ¬ернет указатель, где хранитьс€ User3. ѕолучили пользовател€ и его логин
	user.id; // ѕозвол€ет подсказку дл€ себ€ что ты получил (login, user) и в дальнейшем пользоватьс€ всем, что ты там разложил.
	*/
	
	// Vector

	int count = 10000;

	std::vector < User > myVector;
	myVector.reserve(count);
	auto begin = std::chrono::steady_clock::now();
	for (std::size_t i = 0; i < myVector.capacity(); i++) {
		myVector.emplace_back(i + 1, "User" + std::to_string(i + 1));
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast <std::chrono::milliseconds>
		(end - begin);
	std::cout << "create vector: " << elapsed_ms.count() << " ms\n";

	// Map

	std::map < std::string, User* > myMap;
	
	begin = std::chrono::steady_clock::now();

	for (auto& user : myVector) {
		myMap.insert({ user.name, &user });
	}
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin);
	
	std::cout << "create map: " << elapsed_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	auto vec_tmp = std::find(
		myMap.begin(),
		myMap.end(),
		User{ count, "user" + std::to_string(count) }
	);

	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "Find in vector: " <<
		elapsed_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	auto map_tmp = myMap.find("user" + std::to_string(count));
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "Find in map: " << elapsed_ms.count() << " ms\n";
}


