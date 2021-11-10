#include "Utility.h"

Result ReadTextFile(const std::string& path, std::string& result) {
	std::ifstream file(path);
	if (file.is_open()) {
		std::string buf;
		buf.reserve(50);
		result.reserve(50);
		while (std::getline(file, result)) {}
		file.close();
		return Result::Success;
	}
	else {
		return Result::Error;
	}
}

Configure ParseJsonToConfig(const std::string& json) {
	rapidjson::Document d;
	d.Parse(json.c_str());

	assert(d.HasMember("n"));
	assert(d["n"].IsInt());
	assert(d.HasMember("m"));
	assert(d["m"].IsInt());
	assert(d.HasMember("port"));
	assert(d["port"].IsInt());
	assert(d.HasMember("ip"));
	assert(d["ip"].IsString());

	return Configure(d["n"].GetInt(), d["m"].GetInt(), d["port"].GetInt(), d["ip"].GetString());
}


void ParseMessage(const std::string& input, std::string& command, std::string& message) {
	if (input.empty()) return;
	size_t count = input.find(' ');

	command = input.substr(1, count - 1);
	message = input.substr(count + 1);
}

Commands GetCommand(std::string command) {
	auto it = COMMANDS.find(command);
	if (it != COMMANDS.end()) {
		return it->second;
	}
	else {
		return Commands::NOT_FOUND;
	}
}

std::string genMessage(const std::string login, const std::string& message) {
	return "Client [ " + login + " ] : " + message;
}

std::string createMessageFromQueue(const std::deque<std::string>& deq) {
	std::string res;
	for (const auto& d : deq) {
		res += d + "\n";
	}
	res.pop_back();
	return res;
}