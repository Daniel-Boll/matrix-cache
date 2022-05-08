#!/usr/bin/env bash

REBUILD=false
RUN=false
MODE="Release"
FORCE=false
FLAGS=""
TEST=false

export CPM_SOURCE_CACHE=$HOME/.cache/CPM
# export LANG=C++
# Enable compiler as clang++
# export CC=g++
# export CXX=clang++

usage() { # Function: Print a help message.
	echo "Usage: $0 [ -r RUN ] [ -R (RE)BUILD ] [ -d DEBUG ] [ -f flags ] [ -F FORCE ]" 1>&2
}

exit_abnormal() { # Function: Exit with error.
	usage
	exit 1
}

# If no arguments, print usage.
if [ $# -eq 0 ]; then
	exit_abnormal
fi

while getopts "rtf:dRF" options; do
	case "${options}" in
	r)
		RUN=true
		;;
	t)
		TEST=true
		;;
	R)
		REBUILD=true
		;;
	d)
		MODE="Debug"
		;;
	f)
		FLAGS="${OPTARG}"
		;;
	F)
		FORCE=true
		;;
	*) # If unknown (any other) option:
		exit_abnormal
		;;
	esac
done

# If rebuild
if [ $REBUILD = true ]; then
	[[ $FORCE = true ]] && rm -rf build
	if [ $TEST = true ]; then
		cmake -S test -B build/test -DCMAKE_BUILD_TYPE="${MODE}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${FLAGS}"
		cmake --build build/test
		CTEST_OUTPUT_ON_FAILURE=1 GTEST_COLOR=yes cmake --build build/test --target test -- -j8
		exit 0
	else
		cmake -S standalone -B build/"${MODE}"/standalone -DCMAKE_BUILD_TYPE="${MODE}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${FLAGS}"
	fi
fi

if [ $TEST = true ]; then
	cmake -S test -B build/test
	cmake --build build/test
	CTEST_OUTPUT_ON_FAILURE=1 GTEST_COLOR=yes cmake --build build/test --target test -- -j8

	exit 0
fi

if cmake --build build/"${MODE}"/standalone -- -j8; then
	mv build/"${MODE}"/standalone/compile_commands.json . >/dev/null 2>&1
	if [ $RUN = true ]; then
		if [ $MODE = "Release" ]; then
			./build/${MODE}/standalone/CacheMatrix
		else
			lldb ./build/${MODE}/standalone/CacheMatrix
		fi
	fi
else
	echo "Build failed"
	exit 1
fi
