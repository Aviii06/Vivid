#pragma once

#include <string>
#include "common/types/Types.h"

namespace Vivid
{
	namespace FileDialogue
	{
		String OpenFile(Vector<String> filterName, Vector<String> filterSpecs);
		String SaveFile(Vector<String> filter, Vector<String> filterSpecs);
	};

}
