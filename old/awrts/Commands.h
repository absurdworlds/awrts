
#include <units/CUnitManager.h>

namespace hrengin {
namespace awrts {
class Thingy : public core::IShell::ICommand {
public:
	Thingy(core::ILogger* logger, CUnitManager* umg) : lokker_(logger), uman_(umg) {};
	void pushArg(std::string arg)
	{
		if(argnum < max_args) {
			args[argnum] = arg;
			argnum++;
		} else {
			lokker_->push("create_unit: too many arguments");
		}
	}

	void execute()
	{
		if(argnum == 0) {
			lokker_->push("create_unit: no arguments passed");
			return;
		}
		u32 id = (args[0].c_str()[0] << 24) +
			(args[0].c_str()[1] << 16) + 
			(args[0].c_str()[2] << 8) + 
			args[0].c_str()[3];
		f64 x = 0;
		f64 y = 0;
		f64 f = 0;
		if(argnum >= 3) {
			x = std::stod(args[1]);
			y = std::stod(args[2]);
		}
		if(argnum >= 4) {
			f = std::stod(args[3]);
		}
		uman_->createUnit(id,Vector3d<f32>(x,10,y),f);
		lokker_->push("create_unit: unit created");

		argnum = 0;
	}
private:
	core::ILogger* lokker_;
	CUnitManager* uman_;
	const int max_args = 4;
	int argnum = 0; 
	std::array<std::string,4> args;
};
}
}