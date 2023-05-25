#include <iostream>
#include <vector>
#include <map>


// Command Pattern

class Command {

public:
    virtual void app() = 0;
	virtual ~Command() {}

};

class RegisterCommand : public Command {

	std::string reciever;

public:

	RegisterCommand(const std::string& reciever) : reciever(reciever) {}

	void app() override {
		std::cout << "Запуск регистрации пользователя. Получатель: " << reciever << std::endl;
	}

};

class CheckUserCommand : public Command {

	std::string reciever;
	
public:

	CheckUserCommand(const std::string &reciever) : reciever(reciever) {}

	void app() override {
		std::cout << "Запуск проверки пользователя. Получатель: " << reciever << std::endl;
	}

};

class DBAddCommand : public Command {

	std::vector<std::map<std::string, std::string>> usersList{};

public:

	DBAddCommand(const std::vector<std::map<std::string, std::string>>& usersList) : usersList(usersList) {}

	void app() override {

		for (const auto& user : usersList) {
			std::cout << "Никнейм: " << user.at("nick") << " || Доступ: " << user.at("access") << std::endl;
		}

	}

};


class Sender {

	std::vector<Command*> commands;

public:

	~Sender() {
		for (Command* command : commands) {
			delete command;
		}
	}

	void addCommand(Command* command) {
		commands.push_back(command);
	}

	void StartCommands() {

		for (Command* command : commands) {

			command->app();

		}
	}

};


int main() {
	
	setlocale(LC_ALL, "ru");

	

	std::vector < std::map<std::string, std::string>> userDB{

		{{"nick", "Kirill"}, {"access", "Administrator"}},
		{{"nick", "Anna"}, {"access", "Default"}},
		{{"nick", "Kira"}, {"access", "Default"}}
		{{"nick", "Nikita"}, {"access", "Director"}}

	};



	Command* app1 = new DBAddCommand(userDB);
	Command* app2 = new RegisterCommand("User1");
	Command* app3= new CheckUserCommand("User2");

	Sender sender;

	sender.addCommand(app1);
	sender.addCommand(app2);
	sender.addCommand(app3);

	sender.StartCommands();

	delete app1;
	delete app2;
	delete app3;
    
	return 0;
}
