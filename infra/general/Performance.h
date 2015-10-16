#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>

template <class T>
inline int measureExecutionTime(T& instance,const void (&fptr)())
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	(instance->fptr)();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	return duration;
}

inline int measureExecutionTime(void (&fptr)())
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	fptr();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	return duration;
}

// To-Do "user" and "system" time, getrusage (manpage)

#endif
