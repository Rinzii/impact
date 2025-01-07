// Copyright (c) 2024-2025 Ian Pike

#pragma once
#include <algorithm>

#if IMPACT_PLATFORM_WINDOWS || IMPACT_PLATFORM_DURANGO || defined(_WIN32)
#include "impact/core/platform/windows.hpp"
using HardwareModule = HMODULE;
#else
	using HardwareModule = void*;
#endif

namespace imp {
    // RAII helper to load a dynamic library and free it at the end of the scope.
    class DynamicLibrary {
    public:
        explicit DynamicLibrary(const char *szLibraryPath);

        DynamicLibrary(const DynamicLibrary &other) = delete;

        DynamicLibrary(DynamicLibrary &&other) noexcept : m_hModule(std::move(other.m_hModule)) { // NOLINT
            other.m_hModule = nullptr;
        }

        ~DynamicLibrary() {
            Free();
        }

        void Free();

        void Set(const char *szLibraryPath);

        void ReleaseOwnership() { m_hModule = nullptr; }

        [[nodiscard]] bool IsLoaded() const { return m_hModule != nullptr; }

        template<typename TProcedure>
        TProcedure GetProcedureAddress(const char *szName);


        HardwareModule m_hModule{};
    };
} // namespace imp