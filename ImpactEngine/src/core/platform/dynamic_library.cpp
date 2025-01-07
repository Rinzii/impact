#include "impact/core/platform/dynamic_library.hpp"
#include "dynamic_library_internal.hpp" // Macros for cross-platform dynamic library loading

namespace imp {
    DynamicLibrary::DynamicLibrary(const char *szLibraryPath) {
        if (szLibraryPath != nullptr) {
            m_hModule = imp::LoadLibrary(szLibraryPath);
        }
    }

    void DynamicLibrary::Free() {
        if (this->m_hModule != nullptr) {
            imp::FreeLibrary(m_hModule);
            m_hModule = nullptr;
        }
    }

    void DynamicLibrary::Set(const char *szLibraryPath) {
        if (m_hModule != nullptr) {
            imp::FreeLibrary(m_hModule);
            m_hModule = nullptr;
        }

        if (szLibraryPath != nullptr) {
            m_hModule = imp::LoadLibrary(szLibraryPath);
        }
    }
} // namespace imp