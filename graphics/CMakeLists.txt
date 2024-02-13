
find_package(glfw3 3.3 REQUIRED)

aw_add_library(awrts-graphics STATIC
	GLOB_HEADERS
	SOURCES
		model_loader.c++
		video_manager.c++
)

target_link_libraries(awrts-graphics
	PUBLIC
		glfw
		aw::log
		aw::graphics
		aw::graphics-importer)
