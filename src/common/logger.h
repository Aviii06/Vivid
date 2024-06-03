#pragma once
#include <common/types/Types.h>

namespace Vivid
{
	class Logger
	{
		Logger();
	public:
		static void INIT();
		static void LOG(String msg);
		static void ERR(String msg);
		static void WARN(String msg);
	};
}
