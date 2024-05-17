#ifndef PROTOAPP_HPP
#define PROTOAPP_HPP

#include "ProtoEngine.hpp"

namespace ProtoEngine
{
	class PROTO_API ProtoApp
	{
	public:
		void init();
		void mainLoop();
		void cleanup();
	private:
	};
}
#endif // !PROTOAPP_HPP

