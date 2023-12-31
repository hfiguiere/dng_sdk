/*
* DO NOT EDIT THIS FILE MANNUALLY.
*
*
* Header file generated AUTOMATICALLY by ZBFGen2 using the template PDFL_Str.tmpl,
* a ZString2.0 library program.
* DO NOT EDIT THIS FILE MANNUALLY. THIS IS CLOSELY TIED WITH THE ZString2.0 Binary
* Format. Regenerate this whenever the Binary file changes.
*
*/

#ifndef PDFLErrorsFromASF_H
#define PDFLErrorsFromASF_H

#include "PDFErrorCodes.h"

typedef struct 
{
	ASEnum16 id;
	const char * str;
} PDFLZStringEntry;

const PDFLZStringEntry PDFLZStrings[] = {

	{asFileErrNoErr, "asFileErrNoErr"},
	{asFileErrGeneral, "asFileErrGeneral"},
	{asFileErrObsolete, "asFileErrObsolete"},
	{asFileErrDirFull, "asFileErrDirFull"},
	{asFileErrDiskFull, "asFileErrDiskFull"},
	{asFileErrNSV, "asFileErrNSV"},
	{asFileErrIO, "asFileErrIO"},
	{asFileErrRead, "asFileErrRead"},
	{asFileErrWrite, "asFileErrWrite"},
	{asFileErrEOF, "asFileErrEOF"},
	{asFileErrLocked, "asFileErrLocked"},
	{asFileErrVLocked, "asFileErrVLocked"},
	{asFileErrBusy, "asFileErrBusy"},
	{asFileErrExists, "asFileErrExists"},
	{asFileErrAlreadyOpen, "asFileErrAlreadyOpen"},
	{asFileErrPerm, "asFileErrPerm"},
	{asFileErrWrPerm, "asFileErrWrPerm"},
	{asFileErrFNF, "asFileErrFNF"},
	{asFileErrOpenFailed, "asFileErrOpenFailed"},
	{asFileErrBytesNotReady, "asFileErrBytesNotReady"},
	{asFileErrUserRequestedStop, "asFileErrUserRequestedStop"},
	{asFileErrIOTimeout, "asFileErrIOTimeout"},
	{asFileErrReadBlocked, "asFileErrReadBlocked"},
	{asFileErrNotADir, "asFileErrNotADir"},
	{asFileErrTempCreate, "asFileErrTempCreate"},
	{asFileErrTooBig, "asFileErrTooBig"},
	{asGenErrNoError, "asGenErrNoError"},
	{asGenErrGeneral, "asGenErrGeneral"},
	{asGenErrNoMemory, "asGenErrNoMemory"},
	{asGenErrBadParm, "asGenErrBadParm"},
	{asGenErrListOverflow, "asGenErrListOverflow"},
	{asGenErrBadUnlock, "asGenErrBadUnlock"},
	{asGenErrExceptionStackOverflow, "asGenErrExceptionStackOverflow"},
	{asGenErrResourceLoadFailed, "asGenErrResourceLoadFailed"},
	{asGenErrNameAlreadyRegistered, "asGenErrNameAlreadyRegistered"},
	{asGenErrMethodNotImplemented, "asGenErrMethodNotImplemented"},
	{asGenErrCanceled, "asGenErrCanceled"},
	{asGenErrNoValidSerialNoFound, "asGenErrNoValidSerialNoFound"},
	{asGenErrOutOfRange, "asGenErrOutOfRange"},
	{asGenErrBadStream, "asGenErrBadStream"},
	{cosErrNoError, "cosErrNoError"},
	{cosErrReadError, "cosErrReadError"},
	{cosErrWriteError, "cosErrWriteError"},
	{cosErrBadSyntax, "cosErrBadSyntax"},
	{cosErrNeedRebuild, "cosErrNeedRebuild"},
	{cosErrRebuildFailed, "cosErrRebuildFailed"},
	{cosErrCantOpenTempFile, "cosErrCantOpenTempFile"},
	{cosErrTempFileFull, "cosErrTempFileFull"},
	{cosErrStreamTooShort, "cosErrStreamTooShort"},
	{cosErrBadFilterName, "cosErrBadFilterName"},
	{cosErrListOverflow, "cosErrListOverflow"},
	{cosErrDocTableFull, "cosErrDocTableFull"},
	{cosErrInt16OutOfRange, "cosErrInt16OutOfRange"},
	{cosErrExpectedNull, "cosErrExpectedNull"},
	{cosErrExpectedDict, "cosErrExpectedDict"},
	{cosErrExpectedArray, "cosErrExpectedArray"},
	{cosErrExpectedNumber, "cosErrExpectedNumber"},
	{cosErrExpectedBoolean, "cosErrExpectedBoolean"},
	{cosErrExpectedName, "cosErrExpectedName"},
	{cosErrExpectedString, "cosErrExpectedString"},
	{cosErrExpectedStream, "cosErrExpectedStream"},
	{cosErrInvalidAssignment, "cosErrInvalidAssignment"},
	{cosErrAfterSave, "cosErrAfterSave"},
	{cosErrInvalidObj, "cosErrInvalidObj"},
	{cosErrArrayBounds, "cosErrArrayBounds"},
	{cosErrDictKeyNotName, "cosErrDictKeyNotName"},
	{cosErrNeedFullSave, "cosErrNeedFullSave"},
	{cosErrEncryptionErr, "cosErrEncryptionErr"},
	{cosErrDCTError, "cosErrDCTError"},
	{cosErrCCFError, "cosErrCCFError"},
	{cosErrLZWError, "cosErrLZWError"},
	{cosErrFlateError, "cosErrFlateError"},
	{cosErrExpectedDirect, "cosErrExpectedDirect"},
	{cosErrBadIndex, "cosErrBadIndex"},
	{cosErrOldLinFormat, "cosErrOldLinFormat"},
	{cosErrTempTooShort, "cosErrTempTooShort"},
	{cosErrCancelSave, "cosErrCancelSave"},
	{cosErrEncryptionNotSupported, "cosErrEncryptionNotSupported"},
	{cosErrNoEncryptionKeySupplied, "cosErrNoEncryptionKeySupplied"},
	{cosErrDuplicateFilterName, "cosErrDuplicateFilterName"},
	{cosErrNoDecodeFilter, "cosErrNoDecodeFilter"},
	{cosErrNoEncodeFilter, "cosErrNoEncodeFilter"},
	{cosErrCryptAuthFailed, "cosErrCryptAuthFailed"},
	{cosErrExpectedObjectStream, "cosErrExpectedObjectStream"},
	{cosErrExpectedIndirect, "cosErrExpectedIndirect"},
	{cosErrExpectedProc, "cosErrExpectedProc"},
	{cosErrExpectedCollection, "cosErrExpectedCollection"},
	{cosErrNotCompressed, "cosErrNotCompressed"},
	{cosErrCompressed, "cosErrCompressed"},
	{cosMsgCopyngFile, "cosMsgCopyngFile"},
	{cosMsgLinSave, "cosMsgLinSave"},
	{cosMsgIncrSave, "cosMsgIncrSave"},
	{cosMsgSavingFile, "cosMsgSavingFile"},
	{cosErrBadRefcount, "cosErrBadRefcount"},
	{cosErrObjFreed, "cosErrObjFreed"},
	{cosErrMemMgrError, "cosErrMemMgrError"},
	{cosErrNeedXrefStm, "cosErrNeedXrefStm"},
	{cosErrCryptSystem, "cosErrCryptSystem"},
	{cosSynErrNoError, "cosSynErrNoError"},
	{cosSynErrNoHeader, "cosSynErrNoHeader"},
	{cosSynErrNoEOF, "cosSynErrNoEOF"},
	{cosSynErrNoStartXRef, "cosSynErrNoStartXRef"},
	{cosSynErrNoStartAddress, "cosSynErrNoStartAddress"},
	{cosSynErrBadXref, "cosSynErrBadXref"},
	{cosSynErrBadXrefHeader, "cosSynErrBadXrefHeader"},
	{cosSynErrBadXrefEntry, "cosSynErrBadXrefEntry"},
	{cosSynErrBadTrailerStart, "cosSynErrBadTrailerStart"},
	{cosSynErrBadObjectLabel, "cosSynErrBadObjectLabel"},
	{cosSynErrUnknownName, "cosSynErrUnknownName"},
	{cosSynErrUnknownTokenType, "cosSynErrUnknownTokenType"},
	{cosSynErrNoEndStream, "cosSynErrNoEndStream"},
	{cosSynErrExtraEndStream, "cosSynErrExtraEndStream"},
	{cosSynErrUnterminatedString, "cosSynErrUnterminatedString"},
	{cosSynErrStringTooLong, "cosSynErrStringTooLong"},
	{cosSynErrTokenTooLong, "cosSynErrTokenTooLong"},
	{cosSynErrBadCharInHexString, "cosSynErrBadCharInHexString"},
	{cosSynErrUnexpectedType, "cosSynErrUnexpectedType"},
	{cosSynErrImageNeverEnded, "cosSynErrImageNeverEnded"},
	{cosSynErrUnexpectedDict, "cosSynErrUnexpectedDict"},
	{cosSynErrUnexpectedArray, "cosSynErrUnexpectedArray"},
	{cosSynErrBadDict, "cosSynErrBadDict"},
	{cosSynErrBadObject, "cosSynErrBadObject"},
	{cosSynErrBadArrayDict, "cosSynErrBadArrayDict"},
	{cosSynErrBadFRef, "cosSynErrBadFRef"},
	{cosSynErrPStackUnderflow, "cosSynErrPStackUnderflow"},
	{cosSynErrBadLinearized, "cosSynErrBadLinearized"},
	{cosSynErrBadHexCharInName, "cosSynErrBadHexCharInName"},
	{cosSynErrBadName, "cosSynErrBadName"},
	{cosSynErrBadObjectRef, "cosSynErrBadObjectRef"},
	{cosSynErrBadXrefStream, "cosSynErrBadXrefStream"},
	{cosSynErrPrematureEOF, "cosSynErrPrematureEOF"},
	{cosSynErrBadStreamStart, "cosSynErrBadStreamStart"},
	{cosSynErrBadObjStream, "cosSynErrBadObjStream"},
	{cosSynErrDictKeyNotName, "cosSynErrDictKeyNotName"},
	{cosSynErrExpectedNull, "cosSynErrExpectedNull"},
	{cosSynErrExpectedNumber, "cosSynErrExpectedNumber"},
	{cosSynErrExpectedInteger, "cosSynErrExpectedInteger"},
	{cosSynErrExpectedReal, "cosSynErrExpectedReal"},
	{cosSynErrExpectedUnsigned, "cosSynErrExpectedUnsigned"},
	{cosSynErrExpectedBoolean, "cosSynErrExpectedBoolean"},
	{cosSynErrExpectedName, "cosSynErrExpectedName"},
	{cosSynErrExpectedString, "cosSynErrExpectedString"},
	{cosSynErrExpectedDict, "cosSynErrExpectedDict"},
	{cosSynErrExpectedArray, "cosSynErrExpectedArray"},
	{cosSynErrExpectedStream, "cosSynErrExpectedStream"},
	{cosSynErrIllegalStream, "cosSynErrIllegalStream"},
	{cosSynErrNoLength, "cosSynErrNoLength"},
	{cosSynErrExpectedIndirect, "cosSynErrExpectedIndirect"},
	{cosSynErrExpectedDirect, "cosSynErrExpectedDirect"},
	{cosSynErrIllegalIndRef, "cosSynErrIllegalIndRef"},
	{fsErrNoError, "fsErrNoError"},
	{fsErrInitFailed, "fsErrInitFailed"},
	{fsErrNoMMFonts, "fsErrNoMMFonts"},
	{fsErrNoATM, "fsErrNoATM"},
	{fsErrNeedNewATM, "fsErrNeedNewATM"},
	{fsErrNoT1ZapfDingbats, "fsErrNoT1ZapfDingbats"},
	{fsErrDownloadFailed, "fsErrDownloadFailed"},
	{fsErrDownloadAborted, "fsErrDownloadAborted"},
	{fsErrBadParameter, "fsErrBadParameter"},
	{fsErrMissingFont, "fsErrMissingFont"},
	{pageErrNoError, "pageErrNoError"},
	{pageErrTooFewOps, "pageErrTooFewOps"},
	{pageErrWrongOpType, "pageErrWrongOpType"},
	{pageErrOpTooLarge, "pageErrOpTooLarge"},
	{pageErrBadContents, "pageErrBadContents"},
	{pageErrImageExpectedNumber, "pageErrImageExpectedNumber"},
	{pageErrExpectedEndOfColor, "pageErrExpectedEndOfColor"},
	{pageErrExpectedHexOrASC85, "pageErrExpectedHexOrASC85"},
	{pageErrErrorParsingImage, "pageErrErrorParsingImage"},
	{pageErrBadTypeInXTextArray, "pageErrBadTypeInXTextArray"},
	{pageErrUnexpectedOpInDisplay, "pageErrUnexpectedOpInDisplay"},
	{pageErrInvalidGRestore, "pageErrInvalidGRestore"},
	{pageErrFontNotSet, "pageErrFontNotSet"},
	{pageErrTooFewPathOps, "pageErrTooFewPathOps"},
	{pageErrImageTooBig, "pageErrImageTooBig"},
	{pageErrParseContextError, "pageErrParseContextError"},
	{pageErrBadType3Font, "pageErrBadType3Font"},
	{pageErrFontNotInResources, "pageErrFontNotInResources"},
	{pageErrInvalidDash, "pageErrInvalidDash"},
	{pageErrArrayLenWrong, "pageErrArrayLenWrong"},
	{pageErrNumberOutOfRange, "pageErrNumberOutOfRange"},
	{pageErrColorOutOfRange, "pageErrColorOutOfRange"},
	{pageErrIllegalOpInTextOutline, "pageErrIllegalOpInTextOutline"},
	{pageErrWrongNumOpsInCurve, "pageErrWrongNumOpsInCurve"},
	{pageErrSeveralParsingErrors, "pageErrSeveralParsingErrors"},
	{pageErrWrongOperand, "pageErrWrongOperand"},
	{pageErrFontNotInResDict, "pageErrFontNotInResDict"},
	{pageErrXObjectNotFound, "pageErrXObjectNotFound"},
	{pageErrFormNotFound, "pageErrFormNotFound"},
	{pageErrUnknownXObjectType, "pageErrUnknownXObjectType"},
	{pageErrReadLessImageData, "pageErrReadLessImageData"},
	{pageErrUnrecognizedToken, "pageErrUnrecognizedToken"},
	{pageErrTokenTypeNotRec, "pageErrTokenTypeNotRec"},
	{pageErrTooFewArgs, "pageErrTooFewArgs"},
	{pageErrTooManyArgs, "pageErrTooManyArgs"},
	{pageErrOperandTooLarge, "pageErrOperandTooLarge"},
	{pageErrErrorReadingPage, "pageErrErrorReadingPage"},
	{pageErrImageExpectedEI, "pageErrImageExpectedEI"},
	{pageErrUnknownFilterName, "pageErrUnknownFilterName"},
	{pageErrBadDecodeArray, "pageErrBadDecodeArray"},
	{pageErrIllegalOpInPath, "pageErrIllegalOpInPath"},
	{pageErrIllegalOpInTextObj, "pageErrIllegalOpInTextObj"},
	{pageErrReadLessImageColor, "pageErrReadLessImageColor"},
	{pageErrWrongArgsForSetColor, "pageErrWrongArgsForSetColor"},
	{pageErrUnknownColorSpace, "pageErrUnknownColorSpace"},
	{pageErrColorSpaceNotFound, "pageErrColorSpaceNotFound"},
	{pageErrBadForm, "pageErrBadForm"},
	{pageErrIllegalTextOp, "pageErrIllegalTextOp"},
	{pageErrFormTypeNotAvailable, "pageErrFormTypeNotAvailable"},
	{pageErrOBSOLETE, "pageErrOBSOLETE"},
	{pageErrRecursiveMachine, "pageErrRecursiveMachine"},
	{pageErrInvalidImageMaskDepth, "pageErrInvalidImageMaskDepth"},
	{pageErrBadPattern, "pageErrBadPattern"},
	{pageErrPatternTypeNotAvailable, "pageErrPatternTypeNotAvailable"},
	{pageErrPatternNotFound, "pageErrPatternNotFound"},
	{pageErrBadColorSpace, "pageErrBadColorSpace"},
	{pageErrMissingResource, "pageErrMissingResource"},
	{pageErrMissingKey, "pageErrMissingKey"},
	{pageErrEGStateNotFound, "pageErrEGStateNotFound"},
	{pageErrBadEGS, "pageErrBadEGS"},
	{pageErrBadFunction, "pageErrBadFunction"},
	{pageErrBadEPSColorSpace, "pageErrBadEPSColorSpace"},
	{pageErrBadShading, "pageErrBadShading"},
	{pageErrBadMaskImage, "pageErrBadMaskImage"},
	{pageErrTooManyComps, "pageErrTooManyComps"},
	{pageErrNotLevel3, "pageErrNotLevel3"},
	{pageErrBadAltXObject, "pageErrBadAltXObject"},
	{pageErrBadTGroup, "pageErrBadTGroup"},
	{pageErrBadSoftMask, "pageErrBadSoftMask"},
	{pageErrBadHalftone, "pageErrBadHalftone"},
	{pageErrIllegalColorOp, "pageErrIllegalColorOp"},
	{pageErrRefXObjTargetNotFound, "pageErrRefXObjTargetNotFound"},
	{pageErrRefXObjPageNum, "pageErrRefXObjPageNum"},
	{pageErrRefXObjMissingInvalidID, "pageErrRefXObjMissingInvalidID"},
	{pageErrRefXObjUnmatchedID, "pageErrRefXObjUnmatchedID"},
	{pageErrRefXObjMissingInvalidMetadata, "pageErrRefXObjMissingInvalidMetadata"},
	{pageErrRefXObjRecursive, "pageErrRefXObjRecursive"},
	{pageErrUnableRenderImage, "pageErrUnableRenderImage"},
	{pageErrErrorParsingInlineImage, "pageErrErrorParsingInlineImage"},
	{pdErrNoError, "pdErrNoError"},
	{pdErrBadFont, "pdErrBadFont"},
	{pdErrEmbeddingFont, "pdErrEmbeddingFont"},
	{pdErrBadRootObj, "pdErrBadRootObj"},
	{pdErrBadBaseObj, "pdErrBadBaseObj"},
	{pdErrBadOutlineObj, "pdErrBadOutlineObj"},
	{pdErrBadResMetrics, "pdErrBadResMetrics"},
	{pdErrBadPageObj, "pdErrBadPageObj"},
	{pdErrThumbError, "pdErrThumbError"},
	{pdErrBadAnnotation, "pdErrBadAnnotation"},
	{pdErrBadPageTree, "pdErrBadPageTree"},
	{pdErrUnknownProcsets, "pdErrUnknownProcsets"},
	{pdErrUnableToOpenDoc, "pdErrUnableToOpenDoc"},
	{pdErrIsFileLocked, "pdErrIsFileLocked"},
	{pdErrUnableToWrite, "pdErrUnableToWrite"},
	{pdErrUnableToRenameTemp, "pdErrUnableToRenameTemp"},
	{pdErrUnableToRecover, "pdErrUnableToRecover"},
	{pdErrUnableToRead, "pdErrUnableToRead"},
	{pdErrUnknownFileType, "pdErrUnknownFileType"},
	{pdErrAlreadyOpen, "pdErrAlreadyOpen"},
	{pdErrTooManyPagesForOpen, "pdErrTooManyPagesForOpen"},
	{pdErrNotEnoughSpaceForTempFile, "pdErrNotEnoughSpaceForTempFile"},
	{pdErrTooManyPagesForInsert, "pdErrTooManyPagesForInsert"},
	{pdErrBookmarksError, "pdErrBookmarksError"},
	{pdErrCannotOpenMoreBkMark, "pdErrCannotOpenMoreBkMark"},
	{pdErrUnableToExtractFontErr, "pdErrUnableToExtractFontErr"},
	{pdErrCannotOpenNotes, "pdErrCannotOpenNotes"},
	{pdErrNoNotes, "pdErrNoNotes"},
	{pdErrCopyPageFailed, "pdErrCopyPageFailed"},
	{pdErrNeedRebuild, "pdErrNeedRebuild"},
	{pdErrBadFontFlags, "pdErrBadFontFlags"},
	{pdErrBadFontBBox, "pdErrBadFontBBox"},
	{pdErrBadFontWidths, "pdErrBadFontWidths"},
	{pdErrOldCosFileOBSOLETE, "pdErrOldCosFileOBSOLETE"},
	{pdErrTrySaveAs, "pdErrTrySaveAs"},
	{pdErrAbortNotes, "pdErrAbortNotes"},
	{pdErrPagesLockedNotDeleted, "pdErrPagesLockedNotDeleted"},
	{pdErrNotEnoughMemoryToOpenDoc, "pdErrNotEnoughMemoryToOpenDoc"},
	{pdErrUnableToCloseDueToRefs, "pdErrUnableToCloseDueToRefs"},
	{pdErrNeedPassword, "pdErrNeedPassword"},
	{pdErrOpNotPermitted, "pdErrOpNotPermitted"},
	{pdErrNoCryptHandler, "pdErrNoCryptHandler"},
	{pdErrBadThread, "pdErrBadThread"},
	{pdErrBadBead, "pdErrBadBead"},
	{pdErrThreadProcessing, "pdErrThreadProcessing"},
	{pdErrUnknownAction, "pdErrUnknownAction"},
	{pdErrBadAction, "pdErrBadAction"},
	{pdErrCantUseNewVersion, "pdErrCantUseNewVersion"},
	{pdErrOldEncryption, "pdErrOldEncryption"},
	{pdErrUnableToExtractFont, "pdErrUnableToExtractFont"},
	{pdErrUnableToFindFont, "pdErrUnableToFindFont"},
	{pdErrBadAnnotColor, "pdErrBadAnnotColor"},
	{pdErrNeedCryptHandler, "pdErrNeedCryptHandler"},
	{pdErrBadFontDescMetrics, "pdErrBadFontDescMetrics"},
	{pdErrWhileRecoverInsertPages, "pdErrWhileRecoverInsertPages"},
	{pdErrBadBookmark, "pdErrBadBookmark"},
	{pdErrBadFileSpec, "pdErrBadFileSpec"},
	{pdErrAfterSave, "pdErrAfterSave"},
	{pdErrUnableToXlateText, "pdErrUnableToXlateText"},
	{pdErrTextStringTooShort, "pdErrTextStringTooShort"},
	{pdErrBadCMap, "pdErrBadCMap"},
	{pdErrOldATMVersion, "pdErrOldATMVersion"},
	{pdErrZeroPageFile, "pdErrZeroPageFile"},
	{pdErrATMMemory, "pdErrATMMemory"},
	{pdErrOptMemory, "pdErrOptMemory"},
	{pdErrCancelSave, "pdErrCancelSave"},
	{pdErrCannotMergeWithSubsetFonts, "pdErrCannotMergeWithSubsetFonts"},
	{pdErrCannotReopenDoc, "pdErrCannotReopenDoc"},
	{pdErrNoPDDocForCosDoc, "pdErrNoPDDocForCosDoc"},
	{pdErrHostEncodingNotSet, "pdErrHostEncodingNotSet"},
	{pdErrInvalidEmbeddedFont, "pdErrInvalidEmbeddedFont"},
	{pdErrCannotDeleteAllPages, "pdErrCannotDeleteAllPages"},
	{pdErrStartLessThanEnd, "pdErrStartLessThanEnd"},
	{pdErrNotValidPage, "pdErrNotValidPage"},
	{pdErrCannotBeBlankPage, "pdErrCannotBeBlankPage"},
	{pdErrInvalidPageNumber, "pdErrInvalidPageNumber"},
	{pdErrExceedEncryptionLength, "pdErrExceedEncryptionLength"},
	{pdErrExceedEncryptionVersion, "pdErrExceedEncryptionVersion"},
	{pdErrRequireTrustedMode, "pdErrRequireTrustedMode"},
	{pdErrMissingGlyphs, "pdErrMissingGlyphs"},
	{pdErrNeedTradChinese, "pdErrNeedTradChinese"},
	{pdErrNeedSimpChinese, "pdErrNeedSimpChinese"},
	{pdErrNeedKorean, "pdErrNeedKorean"},
	{pdErrNeedJapanese, "pdErrNeedJapanese"},
	{pdErrMissingSubsetFont, "pdErrMissingSubsetFont"},
	{pdErrCMapNotFound, "pdErrCMapNotFound"},
	{pdMsgOptimizingImages, "pdMsgOptimizingImages"},
	{pdMsgOptimizingGraphics, "pdMsgOptimizingGraphics"},
	{pdMsgCopyingFile, "pdMsgCopyingFile"},
	{pdMsgLinearizing, "pdMsgLinearizing"},
	{pdMsgGarbageCollecting, "pdMsgGarbageCollecting"},
	{pdMsgSavingFile, "pdMsgSavingFile"},
	{pdErrLimitcheck, "pdErrLimitcheck"},
	{pdErrPrintAsImageSpoolFileFull, "pdErrPrintAsImageSpoolFileFull"},
	{pdErrInvalidMediaBox, "pdErrInvalidMediaBox"},
	{pdMsgOptimizingFonts, "pdMsgOptimizingFonts"},
	{pdMsgOptimizingStreams, "pdMsgOptimizingStreams"},
	{pdEnumCanceled, "pdEnumCanceled"},
	{pdErrFontEmbeddingFailed, "pdErrFontEmbeddingFailed"},
	{pdMsgEmbeddingFonts, "pdMsgEmbeddingFonts"},
	{pdMsgCharacterUsage, "pdMsgCharacterUsage"},
	{pdErrFontEmbeddingCanceled, "pdErrFontEmbeddingCanceled"},
	{pdErrMultipleDocuments, "pdErrMultipleDocuments"},
	{pdErrBadOCObject, "pdErrBadOCObject"},
	{pdErrNoInlineImage, "pdErrNoInlineImage"},
	{pdErrNoCryptFilterHandler, "pdErrNoCryptFilterHandler"},
	{pdErrBadEncryptDict, "pdErrBadEncryptDict"},
	{pdMsgCompressingObjects, "pdMsgCompressingObjects"},
	{pdErrNoPermHandler, "pdErrNoPermHandler"},
	{pdErrDuplicatePermHandler, "pdErrDuplicatePermHandler"},
	{pdErrExceedMaxPermHandlers, "pdErrExceedMaxPermHandlers"},
	{pdMsgOptimizingJBIG2Dicts, "pdMsgOptimizingJBIG2Dicts"},
	{pdErrBadEncoding, "pdErrBadEncoding"},
	{pdErrMatrixTooBig, "pdErrMatrixTooBig"},
	{pdErrProcess, "pdErrProcess"},
	{pdErrCyan, "pdErrCyan"},
	{pdErrMagenta, "pdErrMagenta"},
	{pdErrYellow, "pdErrYellow"},
	{pdErrBlack, "pdErrBlack"},
	{pdErrUnknownOutputCondition, "pdErrUnknownOutputCondition"},
	{pdErrNeedExtendedLang, "pdErrNeedExtendedLang"},
	{pdErrUnknownCryptFilter, "pdErrUnknownCryptFilter"},
	{pdErrNeed3D, "pdErrNeed3D"},
	{pdErr3DUnsupported, "pdErr3DUnsupported"},
	{pdErrNonFIPSCrypt, "pdErrNonFIPSCrypt"},
	{pdfxErrNoError, "pdfxErrNoError"},
	{pdfxErrWrongCallbacks, "pdfxErrWrongCallbacks"},
	{pdfxErrDuringCallback, "pdfxErrDuringCallback"},
	{pdfxErrCannotLaunchAcrobat, "pdfxErrCannotLaunchAcrobat"},
	{pdfxErrCannotFindEWH, "pdfxErrCannotFindEWH"},
	{pdfxErrMissingOutputIntent, "pdfxErrMissingOutputIntent"},
	{pdMetadataErrBadXAP, "pdMetadataErrBadXAP"},
	{pdMetadataErrBadPDF, "pdMetadataErrBadPDF"},
	{pdMetadataErrCouldntCreateMetaXAP, "pdMetadataErrCouldntCreateMetaXAP"},
	{pdMetadataErrInternalError, "pdMetadataErrInternalError"},
	{pdModErrNoError, "pdModErrNoError"},
	{pdModErrEncTablesFailed, "pdModErrEncTablesFailed"},
	{pdModErrDuplicateCryptName, "pdModErrDuplicateCryptName"},
	{pdModErrDuplicatePermName, "pdModErrDuplicatePermName"},
	{pdModErrBadNavigator, "pdModErrBadNavigator"},
	{pdModErrNewNavigator, "pdModErrNewNavigator"},
	{pdModErrNavUnknownExtension, "pdModErrNavUnknownExtension"},
	{pdModErrNavInvalidMimeType, "pdModErrNavInvalidMimeType"},
	{pdModErrNavMissingSwf, "pdModErrNavMissingSwf"},
	{pdModErrNavMissingNavigatorXML, "pdModErrNavMissingNavigatorXML"},
	{pdModErrNavMissingLocalesXML, "pdModErrNavMissingLocalesXML"},
	{pdModErrNavMissingStringsXML, "pdModErrNavMissingStringsXML"},
	{pdModErrNavInvalidNavigatorXML, "pdModErrNavInvalidNavigatorXML"},
	{pdModErrNavInvalidLocalesXML, "pdModErrNavInvalidLocalesXML"},
	{pdModErrNavInvalidStringsXML, "pdModErrNavInvalidStringsXML"},
	{pdPErrNoError, "pdPErrNoError"},
	{pdPErrPageDimOutOfRange, "pdPErrPageDimOutOfRange"},
	{pdPErrBadType3Font, "pdPErrBadType3Font"},
	{pdPErrType3TooComplex, "pdPErrType3TooComplex"},
	{pdPErrFormTooComplex, "pdPErrFormTooComplex"},
	{pdPErrUnableToCreateRasterPort, "pdPErrUnableToCreateRasterPort"},
	{pdsErrRequiredMissing, "pdsErrRequiredMissing"},
	{pdsErrBadPDF, "pdsErrBadPDF"},
	{pdsErrWrongTypeEntry, "pdsErrWrongTypeEntry"},
	{pdsErrWrongTypeParameter, "pdsErrWrongTypeParameter"},
	{pdsErrAlreadyExists, "pdsErrAlreadyExists"},
	{pdsErrCantDo, "pdsErrCantDo"},
	{peErrNoError, "peErrNoError"},
	{peErrUnknownPDEColorSpace, "peErrUnknownPDEColorSpace"},
	{peErrWrongPDEObjectType, "peErrWrongPDEObjectType"},
	{peErrUnknownResType, "peErrUnknownResType"},
	{peErrPStackUnderflow, "peErrPStackUnderflow"},
	{peErrCantCreateFontSubset, "peErrCantCreateFontSubset"},
	{peErrBadBlockHeader, "peErrBadBlockHeader"},
	{peErrCantGetAttrs, "peErrCantGetAttrs"},
	{peErrCantGetWidths, "peErrCantGetWidths"},
	{peErrFontToEmbedNotOnSys, "peErrFontToEmbedNotOnSys"},
	{peErrCantEmbedFont, "peErrCantEmbedFont"},
	{peErrCantGetImageDict, "peErrCantGetImageDict"},
	{peErrCantReadImage, "peErrCantReadImage"},
	{peErrCantGetShading, "peErrCantGetShading"},
	{peErrWrongOpType, "peErrWrongOpType"},
	{peErrTooFewPathOps, "peErrTooFewPathOps"},
	{peErrErrorParsingImage, "peErrErrorParsingImage"},
	{peErrReadLessImageColor, "peErrReadLessImageColor"},
	{peErrReadLessImageData, "peErrReadLessImageData"},
	{peErrBadResMetrics, "peErrBadResMetrics"},
	{peErrBadType3Font, "peErrBadType3Font"},
	{peErrInvalidUnicodeAttribute, "peErrInvalidUnicodeAttribute"},
	{peErrIllegalUTFText, "peErrIllegalUTFText"},
	{peErrToUnicodeUsesPUA, "peErrToUnicodeUsesPUA"},
	{peErrBadFont, "peErrBadFont"},
	{rasErrNoError, "rasErrNoError"},
	{rasErrInitFailed, "rasErrInitFailed"},
	{rasErrCreatePort, "rasErrCreatePort"},
	{rasErrDraw, "rasErrDraw"},
	{rasErrGPUFailed, "rasErrGPUFailed"},
	{tkErr2ndInit, "tkErr2ndInit"},
	{xmErrNoError, "xmErrNoError"},
	{xmErrOutOfDateHFT, "xmErrOutOfDateHFT"},
	{xmErrNoPLUGResource, "xmErrNoPLUGResource"},
	{xmErrPlugInIncompatible, "xmErrPlugInIncompatible"},
	{xmErrInitializationFailed, "xmErrInitializationFailed"},
	{xmErrDuplicatePlugInName, "xmErrDuplicatePlugInName"},
	{xmErrCannotReplaceSelector, "xmErrCannotReplaceSelector"},
	{xmErrCalledObsoleteProc, "xmErrCalledObsoleteProc"},
	{xmErrPlugInLoadFailed, "xmErrPlugInLoadFailed"},
	{xmErrNotPrivileged, "xmErrNotPrivileged"},
	{xmErr68KOnly, "xmErr68KOnly"},
	{xmErrPPCOnly, "xmErrPPCOnly"},
	{xmErrPlugInNotTrusted, "xmErrPlugInNotTrusted"},
	{xmErrPlugInNotCarbonized, "xmErrPlugInNotCarbonized"},
	{xmErrPluginResourceMismatch, "xmErrPluginResourceMismatch"},
	{WinBadFileErr, "WinBadFileErr"},
	{WinBadPathErr, "WinBadPathErr"},
	{WinTooManyErr, "WinTooManyErr"},
	{WinAccessErr, "WinAccessErr"},
	{WinBadHdlErr, "WinBadHdlErr"},
	{WinMemErr, "WinMemErr"},
	{WinBadDiskErr, "WinBadDiskErr"},
	{WinBadDriveErr, "WinBadDriveErr"},
	{WinWrPermErr, "WinWrPermErr"},
	{WinNotDosErr, "WinNotDosErr"},
	{WinGeneralErr, "WinGeneralErr"},
	{WinShareErr, "WinShareErr"},
	{WinLockErr, "WinLockErr"},
	{WinDeviceErr, "WinDeviceErr"},
	{WinExistsErr, "WinExistsErr"},
	{mdMacAppErrNoError, "mdMacAppErrNoError"},
	{mdAppCantPrintToPDFWriter, "mdAppCantPrintToPDFWriter"},
	{mdAppNoDAsWhilePrint, "mdAppNoDAsWhilePrint"},
	{mdAppNoPrinter, "mdAppNoPrinter"},
	{mdAppAsstToolboxActive, "mdAppAsstToolboxActive"},
	{mdAppIncorrectTTEmbed, "mdAppIncorrectTTEmbed"},
	{cfMacNoErr, "cfMacNoErr"},
	{cfMacdirFulErr, "cfMacdirFulErr"},
	{cfMacdskFulErr, "cfMacdskFulErr"},
	{cfMacnsvErr, "cfMacnsvErr"},
	{cfMacioErr, "cfMacioErr"},
	{cfMaceofErr, "cfMaceofErr"},
	{cfMacfLckdErr, "cfMacfLckdErr"},
	{cfMacvLckdErr, "cfMacvLckdErr"},
	{cfMacfBsyErr, "cfMacfBsyErr"},
	{cfMacdupFNErr, "cfMacdupFNErr"},
	{cfMacopWrErr, "cfMacopWrErr"},
	{cfMacvolOffLinErr, "cfMacvolOffLinErr"},
	{cfMacpermErr, "cfMacpermErr"},
	{cfMacnoMacDskErr, "cfMacnoMacDskErr"},
	{cfMacwrPermErr, "cfMacwrPermErr"},
	{cfMacdsMemFullErr, "cfMacdsMemFullErr"},
	{cfMacmemFullErr, "cfMacmemFullErr"},
	{cfMacresNotFound, "cfMacresNotFound"},
	{cfMacGenPSErr, "cfMacGenPSErr"},
	{cfMaciIOAbort, "cfMaciIOAbort"},
	{cfMaciPrSavPFil, "cfMaciPrSavPFil"},
	{cfMacServerLostConnection, "cfMacServerLostConnection"},
	{mdUnixAppErrNoError, "mdUnixAppErrNoError"},
	{mdAppOpenMsgPartFailed, "mdAppOpenMsgPartFailed"},
	{mdAppOpenMsgFailed, "mdAppOpenMsgFailed"},
	{mdAppModalWindowOpen, "mdAppModalWindowOpen"},
	{mdAppBadPropertyFormat, "mdAppBadPropertyFormat"},
	{mdAppGetPropertyError, "mdAppGetPropertyError"},
	{mdAppBadPlatformThing, "mdAppBadPlatformThing"},
	{mdAppSIGBUS, "mdAppSIGBUS"},
	{mdAppSIGILL, "mdAppSIGILL"},
	{mdAppSIGSEGV, "mdAppSIGSEGV"},
	{mdAppSIGUnknown, "mdAppSIGUnknown"},
	{mdAppLPTERM, "mdAppLPTERM"},
	{mdAppLPSTOP, "mdAppLPSTOP"},
	{mdAppBadTmpDir, "mdAppBadTmpDir"},
	{mdSysNoErr, "mdSysNoErr"},
	{mdSysEDOM, "mdSysEDOM"},
	{mdSysERANGE, "mdSysERANGE"},
	{mdSysEPERM, "mdSysEPERM"},
	{mdSysENOENT, "mdSysENOENT"},
	{mdSysESRCH, "mdSysESRCH"},
	{mdSysEINTR, "mdSysEINTR"},
	{mdSysEIO, "mdSysEIO"},
	{mdSysENXIO, "mdSysENXIO"},
	{mdSysEBADF, "mdSysEBADF"},
	{mdSysEAGAIN, "mdSysEAGAIN"},
	{mdSysENOMEM, "mdSysENOMEM"},
	{mdSysEACCES, "mdSysEACCES"},
	{mdSysEEXIST, "mdSysEEXIST"},
	{mdSysENOTDIR, "mdSysENOTDIR"},
	{mdSysEISDIR, "mdSysEISDIR"},
	{mdSysENFILE, "mdSysENFILE"},
	{mdSysEMFILE, "mdSysEMFILE"},
	{mdSysENOSPC, "mdSysENOSPC"},
	{mdSysEROFS, "mdSysEROFS"},
	{mdSysEMLINK, "mdSysEMLINK"},
	{mdSysEDQUOT, "mdSysEDQUOT"},
	{mdSysELOOP, "mdSysELOOP"},
	{mdSysEMULTIHOP, "mdSysEMULTIHOP"},
	{mdSysENAMETOOLONG, "mdSysENAMETOOLONG"},
	{mdSysEFAULT, "mdSysEFAULT"},
	{mdSysNOLINK, "mdSysNOLINK"},
	{mdSysOVERFLOW, "mdSysOVERFLOW"},
	{acInit, "acInit"},
	{acDocOpen, "acDocOpen"},
	{acDocWrite, "acDocWrite"},
	{acDoc, "acDoc"},
	{acPage, "acPage"},
	{acAnnot, "acAnnot"},
	{acTextAnnot, "acTextAnnot"},
	{acLinkAnnot, "acLinkAnnot"},
	{acPILoad, "acPILoad"},
	{acPIUnload, "acPIUnload"},
	{acBookmarks, "acBookmarks"},
	{acThread, "acThread"},
	{acDest, "acDest"},
	{acAction, "acAction"},
	{acActionPerform, "acActionPerform"},
	{acPrint, "acPrint"},
	{acCopyClipboard, "acCopyClipboard"},
	{acThumb, "acThumb"},
	{acPrintCancelled, "acPrintCancelled"},
	{avErrNoError, "avErrNoError"},
	{avErrCantOpenMoreThanMaxDocs, "avErrCantOpenMoreThanMaxDocs"},
	{avErrPrintJobTooBig, "avErrPrintJobTooBig"},
	{avErrTooManyChars, "avErrTooManyChars"},
	{avErrNoText, "avErrNoText"},
	{avErrCantOpenDialog, "avErrCantOpenDialog"},
	{avErrActionExternal, "avErrActionExternal"},
	{avErrActionFullScreen, "avErrActionFullScreen"},
	{avErrActionRestricted, "avErrActionRestricted"},
	{avErrCantOpenPrinting, "avErrCantOpenPrinting"},
	{avErrBadAnnotationCopy, "avErrBadAnnotationCopy"},
	{avErrBadActionCopy, "avErrBadActionCopy"},
	{avErrUpdateInternalError, "avErrUpdateInternalError"},
	{avErrUpdateInternetError, "avErrUpdateInternetError"},
	{avErrUpdateNoWebServices, "avErrUpdateNoWebServices"},
	{avErrBadThreadLinkError, "avErrBadThreadLinkError"},
	{avInvalidPageRange, "avInvalidPageRange"},
	{avErrDownloadHelpError, "avErrDownloadHelpError"},
	{avSAInsufficientPermission, "avSAInsufficientPermission"},
	{avSA128EncryptionPresent, "avSA128EncryptionPresent"},
	{avSerConErrConversionBusy, "avSerConErrConversionBusy"},
	{avSerConErrNetworkNotConnected, "avSerConErrNetworkNotConnected"},
	{avSerConErrUploadingError, "avSerConErrUploadingError"},
	{avSerConErrConvertingError, "avSerConErrConvertingError"},
	{avSerConErrDownloadingError, "avSerConErrDownloadingError"},
	{0, 0}
};

#endif /*  PDFLErrorsFromASF_H */

/* End of automatic generated header file */

/***** End of file ***********************************************************/
