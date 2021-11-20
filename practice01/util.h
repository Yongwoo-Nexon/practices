#ifndef UTIL_H_
#define UTIL_H_

#include <algorithm>

#include "util_common.h"

#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS)
#include "util_win32.h"
#endif // defined(WIN32) || defined(WIN64) || defined(_WINDOWS)

#endif // UTIL_H_