# SPDX-License-Identifier: MIT
#
# Copyright 2024 lunaspis
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the “Software”), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(SRCS ctx.c dbg_disasm.c)

set(HDRS_PUBLIC ${PROJECT_SOURCE_DIR}/include/psycho/cpu_defs.h
		${PROJECT_SOURCE_DIR}/include/psycho/ctx.h
		${PROJECT_SOURCE_DIR}/include/psycho/dbg_disasm.h
		${PROJECT_SOURCE_DIR}/include/psycho/types.h)

set(HDRS_PRIVATE compiler.h cpu_defs.h)

# We only support building static libraries for now.
add_library(psycho STATIC ${SRCS} ${HDRS_PUBLIC} ${HDRS_PRIVATE})

# We need to use our public include files, but so do others. Make sure that any
# target which links with us also has access to our public include files.
target_include_directories(psycho PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Ensure that we are using the project wide C settings.
target_link_libraries(psycho PRIVATE psycho_build_config_c)
