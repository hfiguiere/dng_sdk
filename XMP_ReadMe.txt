To build the DNG SDK, you also need to download and install the Adobe XMP SDK. It is available from:

https://www.adobe.com/devnet/xmp.html

Rename the "XMP-Toolkit-SDK-<version>" folder to "xmp_sdk", and place it next to the dng_sdk folder (i.e. as a sibling of this read-me file).

Note that the current XMP SDK also requires you to download some additional source code.  See the ReadMe.txt files inside the XMP SDK's third-party folder for details.

This version of the DNG SDK requires libc++, and the XMP-Toolkit-SDK-CC201607 requires some modification.

The following changes are required to the XMP toolkit CC201607:

1. File: XMP-Toolkit-SDK-CC201607/XMPCommon/Interfaces/BaseInterfaces/IConfigurable_I.h
Line 26: typedef std::pair< const uint64, TypeValuePair > KeyValuePair;
Line 27: typedef std::pair< const uint64, eDataType > KeyValueTypePair;

2. File: XMP-Toolkit-SDK-CC201607/XMPCore/ImplHeaders/DOMImplementationRegistryImpl.h
Line 38: typedef std::map< spcIUTF8String, spcIDOMParser, IUTF8StringComparator, TAllocator< std::pair<const spcIUTF8String,spcIDOMParser> > > ParserMap;

Line 39: typedef std::map< spcIUTF8String, spcIDOMSerializer, IUTF8StringComparator, TAllocator< std::pair<const spcIUTF8String, spcIDOMSerializer> > > SerializerMap;

3. File: XMP-Toolkit-SDK-CC201607/XMPCore/ImplHeaders/NameSpacePrefixMapImpl.h
Line 43: typedef std::map< spcIUTF8String, spcIUTF8String, IUTF8StringComparator, TAllocator< std::pair<const spcIUTF8String,  spcIUTF8String> > > NameSpacePrefixMap;

4. File: XMP-Toolkit-SDK-CC201607/XMPCore/ImplHeaders/StructureNodeImpl.h
Line 49 : typedef std::map< QualifiedName, spINode, CompareQualifiedName, TAllocator< std::pair< const QualifiedName ,spINode> > > QualifiedNameNodeMap;

5. File: XMP-Toolkit-SDK-CC201607/build/XMP_Config.cmake
Line 24: set(INCLUDE_CPP_DOM_SOURCE FALSE)

6. File: XMP-Toolkit-SDK-CC201607/build/ProductConfig.cmake
Line 184:    set(XMP_SHARED_COMPILE_DEBUG_FLAGS "${XMP_SHARED_COMPILE_DEBUG_FLAGS} /MTd")
Line 185:    set(XMP_SHARED_COMPILE_RELEASE_FLAGS "${XMP_SHARED_COMPILE_RELEASE_FLAGS} /MT")

7. File: XMP-Toolkit-SDK-CC201607/XMPCore/build/CMakeListsCommon.txt
Line 115: if(WIN32 AND XMP_BUILD_STATIC)

8. After generating the XCode project files using CMake, you need to open the XCode projects and switch the "C++ standard Library" to "libc++".

After making these changes, open the project files and build the static library targets for both XMPCore and XMPFiles, both Release and Debug.
