#pragma once

#if defined(_MSC_VER)
    #define DISABLE_WARNING_PUSH           __pragma(warning(push))
    #define DISABLE_WARNING_POP            __pragma(warning(pop))
    #define DISABLE_WARNING(WarningNumber) __pragma(warning(disable : WarningNumber))
    // helper defines for common warning codes in msvc
    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER DISABLE_WARNING(4100)
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION         DISABLE_WARNING(4505)
    #define DISABLE_WARNING_WITHOUT_EXTERN                // TODO: ? code for '-Wgnu-inline-cpp-without-extern'
    #define DISABLE_WARNING_MULTIPLE_METHOD_NAMES         // TODO: ? code for '-Wobjc-multiple-method-names'
#elif defined(__GNUC__) || defined(__clang__)
    #define DO_PRAGMA(X)                                  _Pragma(#X)
    #define DISABLE_WARNING_PUSH                          DO_PRAGMA(GCC diagnostic push)
    #define DISABLE_WARNING_POP                           DO_PRAGMA(GCC diagnostic pop)
    #define DISABLE_WARNING(WarningName)                  DO_PRAGMA(GCC diagnostic ignored #WarningName)
    // helper defines for common warning diagnostic flags in gcc/clang
    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER DISABLE_WARNING(-Wunused-parameter)
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION         DISABLE_WARNING(-Wunused-function)
    // attribute without ‘extern’ in C++ treated as externally available
    #define DISABLE_WARNING_WITHOUT_EXTERN                DISABLE_WARNING(-Wgnu-inline-cpp-without-extern)
    #define DISABLE_WARNING_MULTIPLE_METHOD_NAMES         DISABLE_WARNING(-Wobjc-multiple-method-names)
#else
    #define DISABLE_WARNING_PUSH
    #define DISABLE_WARNING_POP
    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION
    #define DISABLE_WARNING_WITHOUT_EXTERN
    #define DISABLE_WARNING_MULTIPLE_METHOD_NAMES
#endif
