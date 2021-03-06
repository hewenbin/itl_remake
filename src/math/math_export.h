// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_MATH_EXPORT_H_
#define MATH_MATH_EXPORT_H_

#include "config.h"

/// Defines MATH_EXPORT so that functionality implemented by
/// the math module can be exported to consumers.

#if defined(OS_WIN)
#define MATH_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define MATH_EXPORT __attribute__((visibility("default")))
#endif

#endif  // MATH_MATH_EXPORT_H_
