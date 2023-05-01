DEPENDENCIES

To build the DNG SDK, you also need the libjpeg and XMP SDK libraries.
Brief instructions are given in the following two sections.

----------------------------------------------------------------------

LIBJPEG

libjpeg is available from:

    http://libjpeg.sourceforge.net/

For the Mac:

  1. It is recommended to visit the archive of distributions here:

		http://www.ijg.org/files/

	 and to download the "jpegsrc.v9b.tar.gz" distribution:

		http://www.ijg.org/files/jpegsrc.v9b.tar.gz

  2. Decompress the archive, rename the folder "libjpeg", and place it
	 next to the dng_sdk folder (i.e. as a sibling of this read-me
	 file).

  3. In Terminal, cd to the "libjpeg" folder and enter:

		 ./configure

	 This will generate the required libjpeg configuration header
	 file (jconfig.h).
 
For Windows:

  1. It is recommended to visit the archive of distributions here:

		http://www.ijg.org/files/

	 and to download the "jpegsrc.v9b.zip" distribution:

		http://www.ijg.org/files/jpegsr9b.zip

  2. Decompress the archive, rename the folder "libjpeg", and place it
	 next to the dng_sdk folder (i.e. as a sibling of this read-me
	 file).

  3. Inside the libjpeg folder, rename the file "jconfig.vc" to
     "jconfig.h" (or rename a copy of the file).

     This is a pre-supplied libjpeg configuration header for the
     Visual C++ compiler.

For other platforms (iOS, Android, Linux, etc.), consult the README
and install.txt files inside the libjpeg distribution folder for setup
instructions.

----------------------------------------------------------------------

XMP SDK

Building DNG SDK requires the XMP SDK. This package includes the XMP
SDK headers and pre-built static libraries for Mac OS (64-bit) and
Windows (32-bit and 64-bit). Thus if you plan to build the DNG SDK on
Mac OS using Xcode and/or on Windows using Visual Studio/C++, no
further action is needed.

If you would like to build the DNG SDK for other platforms (iOS,
Android, Linux, etc.) you will need to download the XMP SDK sources
from:

http://www.adobe.com/devnet/xmp/

Rename the "XMP-Toolkit-SDK-<version>" folder to "xmp" and place it
next to the dng_sdk folder (i.e. as a sibling of this read-me file).
Then follow the (downloaded) instructions for building the XMP SDK.

Note that building the current XMP SDK also requires you to download
and install CMake (an open-source build system).

----------------------------------------------------------------------

PROJECT FILES

This package includes Mac and Windows project files for building the
DNG SDK.

The Mac Xcode project files are here:

    dng_sdk/projects/mac/dng_sdk.xcodeproj
    dng_sdk/projects/mac/dng_validate.xcodeproj

The "dng_sdk" project builds a static library, and the "dng_validate"
project builds a command-line executable. These project files have
been tested with Xcode versions 5.1.1 through 7.3.

The Windows Visual Studio solution file is here:

    dng_sdk/projects/win/dng_sdk.sln

The "dng_sdk" project builds a static library, and the "dng_validate"
project builds a command-line executable. The solution and project
files have been tested with Visual Studio 2013 (Service Pack 4). To
build dng_validate, choose the Configuration "Validate Debug" or
"Validate Release" in Visual Studio.
