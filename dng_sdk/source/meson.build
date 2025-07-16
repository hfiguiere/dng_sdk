# SPDX-FileCopyrightText: 2023 Hubert Figuière
#
# SPDX-License-Identifier: MIT

dng_sdk = static_library(
  'dng_sdk',

  'dng_1d_function.cpp',
  'dng_1d_table.cpp',
  'dng_abort_sniffer.cpp',
  'dng_area_task.cpp',
  'dng_bad_pixels.cpp',
  'dng_big_table.cpp',
  'dng_bottlenecks.cpp',
  'dng_camera_profile.cpp',
  'dng_color_space.cpp',
  'dng_color_spec.cpp',
  'dng_date_time.cpp',
  'dng_exceptions.cpp',
  'dng_exif.cpp',
  'dng_file_stream.cpp',
  'dng_filter_task.cpp',
  'dng_fingerprint.cpp',
  'dng_gain_map.cpp',
  'dng_globals.cpp',
  'dng_host.cpp',
  'dng_hue_sat_map.cpp',
  'dng_ifd.cpp',
  'dng_image.cpp',
  'dng_image_writer.cpp',
  'dng_info.cpp',
  'dng_iptc.cpp',
  'dng_jpeg_image.cpp',
  'dng_jpeg_memory_source.cpp',
  'dng_jxl.cpp',
  'dng_lens_correction.cpp',
  'dng_linearization_info.cpp',
  'dng_local_string.cpp',
  'dng_lossless_jpeg.cpp',
  'dng_lossless_jpeg_shared.cpp',
  'dng_matrix.cpp',
  'dng_memory.cpp',
  'dng_memory_stream.cpp',
  'dng_misc_opcodes.cpp',
  'dng_mosaic_info.cpp',
  'dng_mutex.cpp',
  'dng_negative.cpp',
  'dng_opcode_list.cpp',
  'dng_opcodes.cpp',
  'dng_orientation.cpp',
  'dng_parse_utils.cpp',
  'dng_pixel_buffer.cpp',
  'dng_point.cpp',
  'dng_preview.cpp',
  'dng_pthread.cpp',
  'dng_rational.cpp',
  'dng_read_image.cpp',
  'dng_rect.cpp',
  'dng_ref_counted_block.cpp',
  'dng_reference.cpp',
  'dng_render.cpp',
  'dng_resample.cpp',
  'dng_safe_arithmetic.cpp',
  'dng_shared.cpp',
  'dng_simple_image.cpp',
  'dng_spline.cpp',
  'dng_stream.cpp',
  'dng_string.cpp',
  'dng_string_list.cpp',
  'dng_tag_types.cpp',
  'dng_temperature.cpp',
  'dng_tile_iterator.cpp',
  'dng_tone_curve.cpp',
  'dng_update_meta.cpp',
  'dng_utils.cpp',
  'dng_xmp.cpp',
  'dng_xmp_sdk.cpp',
  'dng_xy_coord.cpp',

  install: true,
  include_directories: [
    '..' / 'projects' / 'meson',
    '..' / '..' / 'xmp' / 'toolkit' / 'public' / 'include'
  ],
  cpp_args: [
    '-DUNIX_ENV=1',
    '-DXMP_ClientBuild=1',
    '-DqDNGUseLibJPEG=1',
    '-DAdobePrivate=0'
  ],
  dependencies: [ zlib, expat ],
  link_with: [ xmp_sdk, ]
)


dng_validate = executable(
  'dng_validate',
  'dng_validate.cpp',
  cpp_args: [
    '-DqDNGUseLibJPEG=1',
    '-DqDNGUseXMP=1',
    '-DqDNGValidateTarget=1'
  ],
  include_directories: [
    '..' / 'projects' / 'meson',
  ],

  dependencies: [ zlib, expat, libjpeg, jpegxl, jpegxl_threads ],
  link_with: [ dng_sdk, xmp_sdk ]
)
