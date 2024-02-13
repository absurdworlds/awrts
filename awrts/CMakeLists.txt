
aw_add_library(awrts-lib STATIC
	GLOB_HEADERS
	SOURCES
		logging.c++
		main.c++
		map_loader.c++
		players/player.c++
		units/unit_factory.c++
		units/unit_table.c++
)

target_link_libraries(awrts-lib
	PUBLIC
		aw::log
		aw::graphics
		aw::io
		aw::doc)

add_executable(awrts
	exe.c++)

target_link_libraries(awrts
	PUBLIC
		awrts-graphics
		awrts-lib)
