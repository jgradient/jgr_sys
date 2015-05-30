# -----------------------------------------------------------------------------
# Setup targets
# -----------------------------------------------------------------------------
set(libsrc sys.c)

set(JGR_SYS_LIBDIR_SUFFIX "" CACHE STRING "Library installation directory suffix (none/32/64)")

add_library(jgr_sys SHARED ${libsrc})
	set_target_properties(jgr_sys PROPERTIES
	                      VERSION "${JGR_SYS_VERSION_MAJOR}.${JGR_SYS_VERSION_MINOR}"
	                      SOVERSION "${JGR_SYS_VERSION_MAJOR}.${JGR_SYS_VERSION_MINOR}")
	if(JGR_SYS_LINK_RT)
		target_link_libraries(jgr_sys ${JGR_SYS_LINK_RT})
	endif()
	install(TARGETS jgr_sys
	        RUNTIME DESTINATION bin
	        LIBRARY DESTINATION lib${JGR_SYS_LIBDIR_SUFFIX}
	        ARCHIVE DESTINATION lib${JGR_SYS_LIBDIR_SUFFIX})
