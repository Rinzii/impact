#pragma once

#ifdef __cplusplus
    #define IMP_EXTERN_C extern "C"
#else
    #define IMP_EXTERN_C
#endif

// Define import macro
#ifndef IMP_IMPORT
    #if defined(_MSC_VER) // MSVC Compiler
        #define IMP_IMPORT __declspec(dllimport)
    #elif defined(__GNUC__) || defined(__clang__) // GCC or Clang
        #define IMP_IMPORT __attribute__((visibility("default")))
    #else
        #define IMP_IMPORT // Unknown compiler: no specific import
    #endif
#endif

// Define export macro
#ifndef IMP_EXPORT
    #if defined(_MSC_VER) // MSVC Compiler
        #define IMP_EXPORT __declspec(dllexport)
    #elif defined(__GNUC__) || defined(__clang__) // GCC or Clang
        #define IMP_EXPORT __attribute__((visibility("default")))
    #else
        #define IMP_EXPORT // Unknown compiler: no specific export
    #endif
#endif

// Suppress MSVC C4251 warning for exported classes
#ifdef _MSC_VER
    #pragma warning(disable : 4251)
#endif

// Define the main API macro based on shared or static library usage
// IMP_API should be used for classes and functions that will only be used in C++ code
// but need to be exported/imported from a shared library for use by other C++ code.
#if defined(IMP_DLL) // Shared library build
    #if defined(IMP_DLL_EXPORT)
        #define IMP_API IMP_EXPORT // Export when building the DLL
    #else
        #define IMP_API IMP_IMPORT // Import when using the DLL
    #endif
#else
    #define IMP_API // Static library or no export/import
#endif

// Define external API macro for shared/static library usage with extern "C" support
// Only used for functions that must interop with C# code. Can't be used on C++ classes.
#if defined(IMP_DLL) // Shared library build
    #if defined(IMP_DLL_EXPORT)
        #define IMP_API_EXTERN IMP_EXTERN_C IMP_EXPORT // Export when building the DLL
    #else
        #define IMP_API_EXTERN IMP_EXTERN_C IMP_IMPORT // Import when using the DLL
    #endif
#else
    #define IMP_API_EXTERN IMP_EXTERN_C // Static library or no export/import
#endif
