cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

function clean_cmake {
	rm -rf "$1"CMakeFiles
	rm -f "$1"CMakeCache.txt
	rm -f "$1"Makefile
	rm -f "$1"cmake_install.cmake
	rm -rf "$1"lib
}

clean_cmake ./
clean_cmake ArduinoDue/
clean_cmake Misc/
