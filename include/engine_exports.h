#ifndef PROTOENGINE_INCLUDE_ENGINEEXPORTS_
#define PROTOENGINE_INCLUDE_ENGINEEXPORTS_

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport) 
#else
#define ENGINE_API __declspec(dllimport) 
#endif
#else
#define ENGINE_API __attribute__((visibility("default")))
#endif

#endif