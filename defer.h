#ifndef CPP_DEFER_H
#define CPP_DEFER_H

// clang-format off
#ifndef HAS_CXX17
    #ifdef __cplusplus
        #if __cplusplus >= 201703L
            #define HAS_CXX17 1
        #elif defined(_MSVC_LANG)
            #if _MSVC_LANG >= 201703L
                #define HAS_CXX17 1
            #else
                #define HAS_CXX17 0
            #endif
        #else
            #define HAS_CXX17 0
        #endif
    #else
        #define HAS_CXX17 0
    #endif
#endif

#ifndef CPP_DEFER_NODISCARD
    #if HAS_CXX17
        #define CPP_DEFER_NODISCARD [[nodiscard]]
    #else
        #if defined(__GNUC__)
            #define CPP_DEFER_NODISCARD __attribute__((warn_unused_result))
        #else
            #define CPP_DEFER_NODISCARD _Check_return_
        #endif
    #endif
#endif
// clang-format on

// Adapted from llvm/ADT/ScopeExit.h - Execute code at scope exit
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions
// See https://llvm.org/LICENSE.txt for license information

#include <type_traits>
#include <utility>

namespace cppdefer {
namespace detail {

template <typename Callable> class scope_exit {
    Callable m_exit_f;
    bool m_engaged = true;

public:
    template <typename CallableParam>
    explicit scope_exit(CallableParam &&param)
        : m_exit_f(std::forward<CallableParam>(param)) {}

    scope_exit(scope_exit &&rhs)
        : m_exit_f(std::move(rhs.m_exit_f)), m_engaged(rhs.m_engaged) {
        rhs.release();
    }

    scope_exit(const scope_exit &) = delete;
    scope_exit &operator=(scope_exit &&) = delete;
    scope_exit &operator=(const scope_exit &) = delete;

    void release() {
        m_engaged = false;
    }

    ~scope_exit() {
        if (m_engaged) {
            m_exit_f();
        }
    }
};

template <typename Callable>
CPP_DEFER_NODISCARD scope_exit<typename std::decay<Callable>::type>
make_scope_exit(Callable &&f) {
    return scope_exit<typename std::decay<Callable>::type>(
        std::forward<Callable>(f));
}

// Adapted from swift/Defer.h - 'defer' helper macro
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors

struct defer_task {};
template <typename Callable>
auto operator+(defer_task, Callable &&f)
    -> decltype(make_scope_exit(std::forward<Callable>(f))) {
    return make_scope_exit(std::forward<Callable>(f));
}

} // namespace detail
} // namespace cppdefer

#define CPP_DEFER_CONCAT_IMPL(x, y) x##y
#define CPP_DEFER_MACRO_CONCAT(x, y) CPP_DEFER_CONCAT_IMPL(x, y)

/// Usage:
///
/// defer {
///     stuff;
///     more_stuff();
/// };
///
#define defer                                                                 \
    auto CPP_DEFER_MACRO_CONCAT(defer_func, __COUNTER__) =                    \
        ::cppdefer::detail::defer_task() + [&]()

#endif // CPP_DEFER_H
