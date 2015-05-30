include(FindDoxygen)

configure_file(Doxyfile.in Doxyfile)
if(${DOXYGEN_FOUND})
	add_custom_target(doc ALL
	                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doc)
	file(GLOB_RECURSE PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
	add_custom_command(OUTPUT doc
	                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
	                   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	                           ${PROJECT_SOURCE_DIR}/README.md ${PUBLIC_HEADERS}
	                   COMMENT "Generating documentation...")
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
	        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/jgr_sys)
endif()
