#include <awgame/console/DefaultInterpreter.h>
#include <iostream>
int main()
{
	using namespace aw;

	console::DefaultInterpreter interp;
	using ArgumentList = std::vector<std::string>;

	auto set_time = [] (ArgumentList const& cmd, std::string& out) {
		out = "time is " + cmd[0] + "h";
		if (cmd.size() > 1)
			out += " " + cmd[1] + "m";
		return true;
	};

	auto set_gravity = [] (ArgumentList const& cmd, std::string& out) {
		out = "gravity set to " + cmd[0];
		return true;
	};

	auto set_var = [] (ArgumentList const& cmd, std::string& out) {
		out = "set " + cmd[0] + " = " + cmd[1];
		return true;
	};

	auto set_stub = [] (ArgumentList const& cmd, std::string& out) {
		out = "stub";
		return false;
	};

	interp.addCommand("set",         set_var);
	interp.addCommand("set time",    set_time);
	interp.addCommand("set gravity", set_gravity);
	interp.addCommand("set trueguild", set_stub);
	interp.addCommand("set guild",     set_stub);
	interp.addCommand("set some", set_stub);
	interp.addCommand("set some obscure", set_stub);
	interp.addCommand("set some obscure bullshit", set_stub);
	interp.addCommand("this command will not be found", set_stub);

	auto cmd = [&] (std::string c) {
		std::string msg;
		std::cout << "> " << c << '\n';
		using Result = console::DefaultInterpreter::Result;
		if (interp.processCommand(c, msg) == Result::NotFound)
			std::cout << "err: Command not found\n";
		else
			std::cout << msg << '\n';
	};
	cmd("set time 0");
	cmd("set gravity 10");
	cmd("set x 10");
	cmd("s gravity 10");
	cmd("zet x 10");
	cmd("set some obscure bullshit + huymorja");
	cmd("se ti 23 55");
	cmd("this command will pls");
	cmd("this command will");
	cmd("this command will pls be found x");
}
