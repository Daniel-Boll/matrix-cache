[![Actions Status](https://github.com/Daniel-Boll/matrix-cache/workflows/MacOS/badge.svg)](https://github.com/Daniel-Boll/matrix-cache/actions)
[![Actions Status](https://github.com/Daniel-Boll/matrix-cache/workflows/Windows/badge.svg)](https://github.com/Daniel-Boll/matrix-cache/actions)
[![Actions Status](https://github.com/Daniel-Boll/matrix-cache/workflows/Ubuntu/badge.svg)](https://github.com/Daniel-Boll/matrix-cache/actions)
[![Actions Status](https://github.com/Daniel-Boll/matrix-cache/workflows/Style/badge.svg)](https://github.com/Daniel-Boll/matrix-cache/actions)
[![Actions Status](https://github.com/Daniel-Boll/matrix-cache/workflows/Install/badge.svg)](https://github.com/Daniel-Boll/matrix-cache/actions)
[![codecov](https://codecov.io/gh/Daniel-Boll/matrix-cache/branch/main/graph/badge.svg)](https://codecov.io/gh/Daniel-Boll/matrix-cache)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>

# ModernCppStarter

This repo was generated using [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter). Follow their repo to see more.

# Develop

## Build (or rebuild)

The build (or rebuild) the whole `build` folder again use the helper script as follow

```bash
./build.sh -RF
```

It can be combined to already build (or rebuild) and run (or test) as soon as it build

```
./build.sh -RFr
```

> For run

```
./build.sh -RFt
```

> For test

The F flag indicates forcefully delete the build folder and start from zero, whereas the R flags just tries to build it again, but probably will use off more cache than only deps cache.

## Run (or test)

And as one can already guess to run (or test) you just need to

```
./build.sh -r
```

> For run

```
./build.sh -t
```

> For test

## Debug

It uses lldb for debug so you must build in debug mode and then run the code

```
./build.sh -dr
```

## Extra

### f flag

If you need to pass flags to `cmake` you can use the `f` flag

```
./build.sh -r -f "-DCmake...=..."
```
> will run normally and also pass to cmake the flag

It will usually complain as the f flag is setted to "", so the following warning is expected

```
CMake Warning:
  Ignoring empty string ("") provided on the command line.
```
