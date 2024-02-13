
aw_add_library(awrts-graphics STATIC
	GLOB_HEADERS
	SOURCES
		model_loader.c++
		video_manager.c++
)

target_link_libraries(awrts-graphics
	PUBLIC
		aw::log
		aw::graphics
		aw::graphics-importer)
