
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <thread>
#include <random>
#include <array>

#include <hrengin/common/Matrix4.h>

#include "CGame.h"

#include "awrts.h"

namespace hrengin {
namespace awrts {

CGame& getGameManager()
{
	static CGame game;
	return game;
}

int main()
{
	CGame& game = getGameManager();
	
	game.run();

	return 0;
}

} // namespace awrts
} // namespace hrengin

int main(int c, char** v)
{
	return hrengin::awrts::main();
}
