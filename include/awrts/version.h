#ifndef awrts_version_h
#define awrts_version_h
#include <aw/utility/to_string.h>
#define AWRTS_BUILD_STRING "Sranton Wars"

namespace aw {
namespace rts {

constexpr struct {
	unsigned short num[4];
	char suffix;
} version {0, 0, 0, 0, 'a'};


template<typename Formatter = format::pretty_print>
std::string to_string(decltype(version) ver, Formatter&& fmt = Formatter{})
{
	using namespace sv_literals;
	fmt.convert(ver.num[0]);
	fmt.literal("."_s);
	fmt.convert(ver.num[1]);
	fmt.literal("."_s);
	fmt.convert(ver.num[2]);
	fmt.literal("."_s);
	fmt.convert(ver.num[3]);
	fmt.convert(ver.suffix);
	return fmt;
}
} // namespace rts
} // namespace aw
#endif//awrts_version_h
