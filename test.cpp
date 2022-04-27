//#include <cstdio>
//#include <iostream>
//#include <cfloat>
//#include <pmmintrin.h>
//
///**
// * Runtime Library printf/iostream Assert Failure Project
// * \author Nicholas Kooij
// * \date 16 Sep 2020
// *
// * \note run in Debug mode to reproduce the assert runtime library
// * assert failure.
// *
// * In Debug  builds, with  the FPU  set in  Denormals-Are-Zero mode,  the C++
// * runtime  library C  printf  family  of functions,  and  the C++  iostreams
// * library assert false, when outputting a denormal number.
// *
// * ### Denormal Number Performance Issues
// *
// * Operations are on floating point denormal numbers can be hundreds of times
// * slower  than normalized  numbers.  Intel processor  in  particular can  be
// * hundreds of  times slower  won denormal input  due to  denormal arithmetic
// * being handled by microcode.
// *
// *
// * ### Applications Requiring Performance over IEEE-754 Denormal Compliance
// *
// * A  broad  class of  applications  require  fast/consistent floating  point
// * performance  more  than  full  IEEE-754 denormal  number  compliance  with
// * respect to denormals.  For example:
// * 1.  Video Games
// * 2.  CODECs:
// *   - Audio (IIR filters are particularly susceptible to this phenomenon)
// *   - Video
// * 3.  General Signal Processing Algorithms
// * 4.  Neural Network Training
// *
// * For such applications where  fast/consistent performance is more important
// * than fully compliant  IEEE-754, the modern Intel SSE2 FPU  can be placed a
// * mode that:
// * - Flushes denormal output to 0 [FTZ]
// * - Treats denormal input as [DAZ]
// *
// * ### Printf Assert False Bug
// *
// * When using printf/iostreams to output a denormal number, with the FPU set
// * in denormals-are-zero mode, the runtime should either:
// * - output zero
// * - output the number as a denormal
// *
// * Either of these outcomes is acceptable when non-IEEE-754 compliant
// * denormals-are-zero mode is set.
// *
// * Unfortunately,  when the  FPU is  placed in  Denormals-are-zero mode,  the
// * Microsoft Visual C++ Debug Runtime will  assert false if a denormal output
// * is traced with either:
// * - C printf family of functions
// * - C++ iostreams
// *
// * ### Impacted Compiler Runtimes:  _MSC_VER >= 1900
// *
// * This impacts the following compilers [as they all share the same runtime]:
// * - Visual Studio 2019 16.7.2 clang-cl 10.0.0 _MSC_FULL_VER=192729111
// * - Visual Studio 2019 16.7.2 _MSC_FULL_VER=192729111
// * - Visual Studio 2017 15.9.25 _MSC_FULL_VER=191627042
// * - Visual Studio 2015 14.0 Update 3 _MSC_FULL_VER=190024215
// *
// * Older compilers, _MSC_VER < 1900, do not have this issue:
// * - Visual Studio 2012 11.0 Update 5 _MSC_FULL_VER=170061030 17.0.61030
// *
// * ## Impact on Existing Software
// *
// * ### Security Ramifications
// *
// * There  are security  ramifications  for software  running  with the  Debug
// * runtime  library, and  FPU  appropriately, as  crafted  input can  trigger
// * runtime library assert failure.
// *
// * [This does actually happen in practice:  many large Enterprises are running
// * applications using Debug builds.]
// *
// * Some software projects have experienced this problem, but due to difficult
// * diagnosis of the issue, resolved the issue by using earlier compilers. For
// * example see [3], user ettudagny:
// *
// * > I've tried my  code on VS 2013  (instead of 2015) and...  It worked! Idk
// * > how it works, maybe it just problem with my computer.
// *
// * ### References
// *
// * [1] _Denormal number_
// * * https://en.m.wikipedia.org/wiki/Denormal_number
// *
// * [2] _x87 and SSE Floating Point Assists in IA-32: Flush-To-Zero (FTZ) and Denormals-Are-Zero (DAZ)_
// * * https://software.intel.com/content/www/us/en/develop/articles/x87-and-sse-floating-point-assists-in-ia-32-flush-to-zero-ftz-and-denormals-are-zero-daz.html
// *
// * [3] _C - unexpected input value: log10 failed - Stack Overflow_
// * * https://stackoverflow.com/questions/36500316/unexpected-input-value-log10-failed
// */
//int main() {
//    // set FPU CSR register Denormals are Zero bit.
//    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
//
//    // denormal number
//    const double denormal = DBL_MIN * 0.5;
//
//    // Output  denormal  number  using  printf family  of  functions  or  C++
//    // iostreams results in assert false.
//    printf("%f\n", denormal);
//
//    std::cout << denormal << "\n";
//
//    return 0;
//}