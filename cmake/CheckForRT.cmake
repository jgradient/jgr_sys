# The function clock_gettime in gnu libc requires linking additional rt library
# in versions of libc prior to 2.17
# 
# This cmake script will set the variable JGR_SYS_LINK_RT to the value "rt"
# if the function clock_gettime requires linking rt library, and to the value
# "" otherwise.
#
if(WIN32)
	set(JGR_SYS_LINK_RT "")
else()
	try_compile(TEST_TIMING ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/cmake/test_timing.c)
	if(${TEST_TIMING})
		set(JGR_SYS_LINK_RT "")
	else()
		try_compile(TEST_TIMING ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/cmake/test_timing.c LINK_LIBRARIES rt)
		if(${TEST_TIMING})
			set(JGR_SYS_LINK_RT "rt")
		endif()
	endif()
endif()
