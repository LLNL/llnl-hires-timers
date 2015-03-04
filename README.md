# hrTimer

[![Build Status](https://travis-ci.org/alehaa/hrtimer.svg?branch=travis_ci)](https://travis-ci.org/alehaa/hrtimer)

This is the hrTimer library, a library to support platform-specific
high-resolution timers by a platform-independent c-call.

At compile time the best available timer at your platform will be selected and
the platform-specific call to get the best timer will be used to return the
timer value in nanoseconds.



## Building

To build, you need to use cmake. We recommend that you build out of source. That
is, you should make a directory to build in first.

```sh
mkdir build
cd build
cmake ..
make
```



# Usage

You can use hrTimer by calling the following function:
```C
timing_t get_time_ns();
```

`timing_t` is defined as:
```C
typedef unsigned long long timing_t;
```

At compile-time you should link (static or dynamic) against libadept_timing,
with `-ladept_timing`.



## License

See the [LICENSE](LICENSE.md) file for license and distribution information.
