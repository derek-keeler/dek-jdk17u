/*
 * Copyright (c) 1999, 2021, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef OS_BSD_OS_BSD_INLINE_HPP
#define OS_BSD_OS_BSD_INLINE_HPP

// os_bsd.hpp included by os.hpp

#include "runtime/os.hpp"
#include "os_posix.inline.hpp"

inline bool os::uses_stack_guard_pages() {
  return true;
}

inline bool os::must_commit_stack_guard_pages() {
  assert(uses_stack_guard_pages(), "sanity check");
#if !defined(__FreeBSD__) || __FreeBSD__ < 5
  // Since FreeBSD 4 uses malloc() for allocating the thread stack
  // there is no need to do anything extra to allocate the guard pages
  return false;
#else
  // FreeBSD 5+ uses mmap MAP_STACK for allocating the thread stacks.
  // Must 'allocate' them or guard pages are ignored.
  return true;
#endif
}

// Bang the shadow pages if they need to be touched to be mapped.
inline void os::map_stack_shadow_pages(address sp) {
}

// stubbed-out trim-native support
inline bool os::can_trim_native_heap() { return false; }
inline bool os::trim_native_heap(os::size_change_t* rss_change) { return false; }

#endif // OS_BSD_OS_BSD_INLINE_HPP
