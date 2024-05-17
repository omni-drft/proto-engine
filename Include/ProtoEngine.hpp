#ifndef PROTOENGINE_HPP
#define PROTOENGINE_HPP

#ifdef _WIN32
	#define PROTO_API __declspec(dllexport)
#else
	#define PROTO_API
#endif

#include "ProtoApp.hpp"


#endif // !PROTOENGINE_HPP
