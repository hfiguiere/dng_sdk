DNG SDK
=======

This a git repository containing all the DNG SDK revisions and a meson
buildsystem to build `dng_validate` on Linux.

Each DNG SDK revision archive was imported as-is in the repository,
including the build artifacts. Each revision is tagged.

## Build

```shell
mkdir _build
meson _build
ninja -C _build
```

The `dng_validate` binary will be in
`_build/dng_sdk/source/dng_validate`.

## License

Please don't consider this code to be under an OSI license.

### XMP SDK

The XMP SDK as shipped doesn't have proper license annotation. However
the upsream XMP SDK is available at
https://github.com/adobe/XMP-Toolkit-SDK and licensed under a
BSD-3-Clause license. You should be able to use that version as a
drop-in replacement.

### DNG SDK

The DNG SDK is under license that is unspecified.

#### DNG SDK 1.1

The following license information was included in DNG 1.1 and DNG 1.2.

Lossless JPEG code adapted from:

Copyright (C) 1991, 1992, Thomas G. Lane.
Part of the Independent JPEG Group's software.
See the file Copyright for more details.

Copyright (c) 1993 Brian C. Smith,
The Regents of the University of California
All rights reserved.

Copyright (c) 1994 Kongji Huang and Brian C. Smith.
Cornell University
All rights reserved.

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose, without fee, and without written
agreement is hereby granted, provided that the above copyright notice
and the following two paragraphs appear in all copies of this
software.

IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
CORNELL UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CORNELL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
ON AN "AS IS" BASIS, AND CORNELL UNIVERSITY HAS NO OBLIGATION TO
PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

Copyright © 2006 Adobe Systems Incorporated. All rights reserved.

Adobe is a registered trademark or trademark of Adobe Systems
Incorporated in the United States and/or other countries. Windows is
either a registered trademark or a trademark of Microsoft Corporation
in The United States and/or other countries. Mac is a trademark of
Apple Computer, Inc., registered in the United States and other
countries. All trademarks noted herein are the property of their
respective owners.
