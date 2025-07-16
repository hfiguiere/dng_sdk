# SPDX-FileCopyrightText: 2023 Hubert Figuière
#
# SPDX-License-Identifier: MIT

project('dng_sdk', 'cpp', version: '1.7')

zlib = dependency('zlib')
expat = dependency('expat')
libjpeg = dependency('libjpeg')
jpegxl = dependency('libjxl', version: '>= 0.11.0')
jpegxl_threads = dependency('libjxl_threads')

subdir('xmp/toolkit')
subdir('dng_sdk/source')
