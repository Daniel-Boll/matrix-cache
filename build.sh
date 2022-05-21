#!/usr/bin/env bash

RUN=false
TEST=false
BENCHMARK=false
REBUILD=false
FORCE=false

MODE="Release"
FLAGS=""
PROGRAM_PARAMETERS=""

export CPM_SOURCE_CACHE=$HOME/.cache/CPM

usage() { # Function: Print a help message.
	echo "Usage: $0 [ -r RUN ] [ -d DEBUG ] [ -b BENCHMARK ] [ -R (RE)BUILD ] [ -F FORCE ] [ -P program parameters ] [ -f flags ]" 1>&2
}

exit_abnormal() { # Function: Exit with error.
	usage
	exit 1
}

# If no arguments, print usage.
if [ $# -eq 0 ]; then
	exit_abnormal
fi

while getopts "rtbf:dRFP:" options; do
	case "${options}" in
	r)
		RUN=true
		;;
	t)
		TEST=true
		;;

	b)
		BENCHMARK=true
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
	P)
		PROGRAM_PARAMETERS="${OPTARG}"
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
		mv build/test/compile_commands.json . >/dev/null 2>&1

		./build/test/CacheMatrixTests
		exit 0
	elif [ $BENCHMARK = true ]; then
		CC=gcc CXX=g++ cmake -S benchmark -B build/benchmark -DCMAKE_BUILD_TYPE="${MODE}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${FLAGS}"
		cmake --build build/benchmark
		mv build/benchmark/compile_commands.json . >/dev/null 2>&1

		./build/benchmark/CacheMatrixBenchmark
		exit 0
	else
		CC=clang CXX=clang++ cmake -S standalone -B build/"${MODE}"/standalone -DCMAKE_BUILD_TYPE="${MODE}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${FLAGS}"
	fi
fi

if [ $BENCHMARK = true ]; then
	# Enable compiler as g++
	export CC=g++
	export CXX=g++
	cmake -S benchmark -B build/benchmark -DCMAKE_BUILD_TYPE="${MODE}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${FLAGS}"
	cmake --build build/benchmark
	mv build/benchmark/compile_commands.json . >/dev/null 2>&1

	./build/benchmark/CacheMatrixBenchmark
	exit 0
fi

if [ $TEST = true ]; then
	# Enable compiler as g++
	export CC=g++
	export CXX=g++

	cmake -S test -B build/test
	cmake --build build/test -- --quiet
	# CTEST_OUTPUT_ON_FAILURE=1 GTEST_COLOR=yes cmake --build build/test --target test -- -j8
	mv build/test/compile_commands.json . >/dev/null 2>&1
	./build/test/CacheMatrixTests

	exit 0
fi

if cmake --build build/"${MODE}"/standalone -- -j8; then
	mv build/"${MODE}"/standalone/compile_commands.json . >/dev/null 2>&1
	if [ $RUN = true ]; then
		if [ $MODE = "Release" ]; then
			./build/${MODE}/standalone/CacheMatrix ${PROGRAM_PARAMETERS}
		else
			lldb ./build/${MODE}/standalone/CacheMatrix "${PROGRAM_PARAMETERS}"
		fi
	fi
else
	echo "Build failed"
	exit 1
fi
