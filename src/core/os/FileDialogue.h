#pragma once

#include <string>
#include "common/types/Types.h"

namespace Vivid
{
	/*!
	 * @namespace FileDialogue
	 * @brief Contains functions to open and save files.
	 * @details FileDialogue is a namespace that contains utility functions to open and save files. This uses the native file dialogues of the OS, using the WinAPI for Windows, Cocoa for macOS, and GTK for Linux.
	 */
	namespace FileDialogue
	{
		/*!
		 * @brief Opens a file dialogue to open a file.
		 * @details Opens a file dialogue to open a file. It takes in a Vector of strings that contains the filter names and a Vector of strings that contains the filter specifications.
		 * @param filterName The filter names.
		 * @param filterSpecs The filter specifications.
		 * @return The path of the file.
		 */
		String OpenFile(Vector<String> filterName, Vector<String> filterSpecs);

		/*!
		 * @brief Opens a file dialogue to save a file.
		 * @details Opens a file dialogue to save a file. It takes in a Vector of strings that contains the filter names and a Vector of strings that contains the filter specifications.
		 * @param filter The filter names.
		 * @param filterSpecs The filter specifications.
		 * @return The path of the file.
		 */
		String SaveFile(Vector<String> filter, Vector<String> filterSpecs);
	};

}
