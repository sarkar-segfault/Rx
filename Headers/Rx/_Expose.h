/*
  Defines macros to expose public functions from the shared library across different platforms.

  Specifically, it defines `Rx__Export`, `Rx__Extern`, and `Rx__Expose`.
  This file is not to be included in user code.
*/

// IWYU pragma: private
// IWYU pragma: no_include

#ifndef Rx__ExposeH
#define Rx__ExposeH

/*
  ## Macro `Rx__Export`
  Marks symbols for export if we are building as a shared library.

  When building a shared library with certain compilers or on certain platforms,
  we have to export our symbols explicitly. We use platform or compiler specific
  macros to reliably export our symbols. On unknown systems, or if we are not
  building as shared, the macro is left blank.
*/
#ifdef Rx__Shared
  #ifdef _WIN32
    #ifdef Rx__Build
      #define Rx__Export __declspec(dllexport)
    #else
      #define Rx__Export __declspec(dllimport)
    #endif
  #elif defined(__GNUC__)
    #define Rx__Export __attribute__((visibility("default")))
  #else
    #define Rx__Export
  #endif
#else
  #define Rx__Export
#endif

/*
  ## Macro `Rx__Extern`
  Marks symbols as C to make sure C++ compilers don't choke on our code.

  When a C++ compiler tries to compile C code, it cannot recognize the code as such
  and thinks they are C++. This is a problem because C++ mangles all symbol names,
  to make its many useless and stupid features like overloading possible. To shield
  our code from such blasphemy, we use the `extern "C"` syntax to mark our code as C.

  We set this to `extern` if we're not on C++ so that the compiler understands the symbols
  as declared, not defined. I know that nowadays compilers can do all sorts of gymnastics
  and figure this out, but my brain just does not let me ignore small details like this.
  Case in point, I have IWYU pragmas sprinkled all over instead of letting it infer them.
*/
#ifdef __cplusplus
  #define Rx__Extern extern "C"
#else
  #define Rx__Extern extern
#endif

/*
  ## Macro `Rx__Expose`
  Combines `Rx__Extern` and `Rx__Export` together to properly declare our symbols.

  This macro combines `Rx__Extern` and `Rx__Export` together so that it is more convenient when
  defining symbols.
*/
#define Rx__Expose Rx__Extern Rx__Export

#endif
