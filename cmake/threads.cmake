set(CMAKE_THREAD_PREFIX_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if(NOT Threads_FOUND)
	message(FATAL_ERROR "External library \"Threads\" not found.")
endif()
