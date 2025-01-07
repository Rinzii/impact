// Copyright (c) 2024-2025 Ian Pike

#pragma once


#include <cstdio>
#include <utility>
#include <string_view>

#include "impact/core/platform/dynamic_library.hpp"

#if defined(IMPACT_PLATFORM_WINDOWS) || defined(IMPACT_PLATFORM_DURANGO) || defined(_WIN32)
#include "impact/core/platform/windows.hpp"

namespace imp {

inline HMODULE LoadLibrary(const char* libName) {
#if defined(IMPACT_PLATFORM_WINDOWS) || defined(_WIN32)
    return ::LoadLibraryA(libName);
#elif defined(IMPACT_PLATFORM_DURANGO)
    return ::LoadLibraryExA(libName, 0, 0);
#endif
}

inline HMODULE GetCurrentModule() {
    return ::GetModuleHandle(nullptr);
}

inline DWORD GetModuleFileName(HMODULE module, char* filename, DWORD size) {
    return ::GetModuleFileName(module, filename, size);
}

inline FARPROC GetProcAddress(HMODULE libHandle, const char* procName) {
    return ::GetProcAddress(libHandle, procName);
}

inline BOOL FreeLibrary(HMODULE libHandle) {
    return ::FreeLibrary(libHandle);
}

constexpr bool SharedLibrarySupported = true;
constexpr const char* SharedLibraryPrefix = "";
constexpr const char* SharedLibraryExtension = ".dll";

} // namespace imp

#elif defined(IMPACT_PLATFORM_LINUX) || defined(IMPACT_PLATFORM_ANDROID) || defined(IMPACT_PLATFORM_APPLE)

#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

namespace imp {

inline void* LoadLibrary(const char* libName, bool bLazy = false, bool bInModulePath = true) {
    if (strlen(libName) == 0) {
        return nullptr;
    }

    char finalPath[_MAX_PATH] = {};
    const char* filePre = strncmp(libName, SharedLibraryPrefix, strlen(SharedLibraryPrefix)) != 0 ? SharedLibraryPrefix : "";
    const char* fileExt = strncmp(libName + strlen(libName) - strlen(SharedLibraryExtension), SharedLibraryExtension, strlen(SharedLibraryExtension)) != 0 ? SharedLibraryExtension : "";

    const char* libPath = bInModulePath ? (GetModulePath() ? GetModulePath() : ".") : "";
    snprintf(finalPath, sizeof(finalPath), "%s%s%s%s%s", libPath, libPath ? "/" : "", filePre, libName, fileExt);

#if defined(IMPACT_PLATFORM_LINUX)
    return ::dlopen(finalPath, (bLazy ? RTLD_LAZY : RTLD_NOW) | RTLD_DEEPBIND);
#else
    return ::dlopen(finalPath, bLazy ? RTLD_LAZY : RTLD_NOW);
#endif
}

inline void* GetCurrentModule() {
    return ::dlopen(nullptr, RTLD_LAZY);
}

inline size_t GetModuleFileName(void* handle, char* path, size_t size) {
    if (handle == nullptr) {
        readlink("/proc/self/exe", path, size);
        return strlen(path);
    }

    Dl_info info;
    ::dladdr(handle, &info);
    if (info.dli_sname == nullptr && info.dli_saddr == nullptr) {
        return 0;
    }

    size_t len = strlen(info.dli_fname);
    std::memcpy(path, info.dli_fname, len);
    return len;
}

inline void* GetProcAddress(void* libHandle, const char* procName) {
    return ::dlsym(libHandle, procName);
}

inline int FreeLibrary(void* libHandle) {
    return ::dlclose(libHandle);
}

constexpr bool SharedLibrarySupported = true;
constexpr const char* SharedLibraryPrefix = "lib";
#if defined(IMPACT_PLATFORM_APPLE)
constexpr const char* SharedLibraryExtension = ".dylib";
#else
constexpr const char* SharedLibraryExtension = ".so";
#endif

const char* GetModulePath() {
    static const char* gEnvName = "MODULE_PATH";
    return getenv(gEnvName);
}

void SetModulePath(const char* pModulePath) {
    static const char* gEnvName = "MODULE_PATH";
    setenv(gEnvName, pModulePath ? pModulePath : "", true);
}

} // namespace imp

#else

namespace imp {

inline void* LoadLibrary(const char* libName) {
    return nullptr;
}

inline void* GetProcAddress(void* libHandle, const char* procName) {
    return nullptr;
}

inline void FreeLibrary(void* libHandle) {}

inline void* GetCurrentModule() {
    return nullptr;
}

constexpr bool SharedLibrarySupported = false;
constexpr const char* SharedLibraryPrefix = "";
constexpr const char* SharedLibraryExtension = "";

} // namespace imp

#endif

namespace imp {

inline void LibraryDefName(char* buffer, size_t bufferSize, const char* libName) {
    snprintf(buffer, bufferSize, "%s%s%s", SharedLibraryPrefix, libName, SharedLibraryExtension);
}

inline auto LoadLibraryDefName(const char* libName) {
    char buffer[256];
    LibraryDefName(buffer, sizeof(buffer), libName);
    return LoadLibrary(buffer);
}

} // namespace imp

namespace imp {
    template<typename TProcedure>
    TProcedure DynamicLibrary::GetProcedureAddress(const char *szName) {
        return static_cast<TProcedure>(imp::GetProcAddress(m_hModule, szName));
    }
} // namespace imp
