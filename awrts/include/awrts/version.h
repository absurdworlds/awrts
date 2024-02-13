#ifndef awrts_version_h
#define awrts_version_h
#include <aw/utility/to_string.h>
#define AWRTS_BUILD_STRING "Sranton Wars"

namespace aw::rts {

constexpr struct {
	unsigned short num[4];
	char suffix;
} version {{0, 0, 0, 0}, 'a'};


template<typename Formatter = formatter::pretty_print>
std::string to_string(decltype(version) ver, Formatter&& fmt = Formatter{})
{
	using namespace std::string_view_literals;
	fmt.convert(ver.num[0]);
	fmt.literal("."sv);
	fmt.convert(ver.num[1]);
	fmt.literal("."sv);
	fmt.convert(ver.num[2]);
	fmt.literal("."sv);
	fmt.convert(ver.num[3]);
	fmt.convert(ver.suffix);
	return fmt;
}
} // namespace aw::rts
#endif//awrts_version_h
