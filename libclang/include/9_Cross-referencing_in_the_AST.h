#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;CXString			_9_getCursorUSR							(CXCursor C);
CXString			_9_constructUSR_ObjCClass				(const char *class_name);
CXString			_9_constructUSR_ObjCCategory			(const char *class_name, const char *category_name);
CXString			_9_constructUSR_ObjCProtocol			(const char *protocol_name);
CXString			_9_constructUSR_ObjCIvar				(const char *name, CXString classUSR);
CXString			_9_constructUSR_ObjCMethod				(const char *name, unsigned isInstanceMethod, CXString classUSR);
CXString			_9_constructUSR_ObjCProperty			(const char *property, CXString classUSR);
CXString			_9_getCursorSpelling					(CXCursor C);
CXSourceRange		_9_Cursor_getSpellingNameRange			(CXCursor C, unsigned pieceIndex, unsigned options);
unsigned			_9_PrintingPolicy_getProperty			(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property);
void				_9_PrintingPolicy_setProperty			(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property, unsigned Value);
CXPrintingPolicy	_9_getCursorPrintingPolicy				(CXCursor C);
void				_9_PrintingPolicy_dispose				(CXPrintingPolicy Policy);
CXString			_9_getCursorPrettyPrinted				(CXCursor Cursor, CXPrintingPolicy Policy);
CXString			_9_getCursorDisplayName					(CXCursor C);
CXCursor			_9_getCursorReferenced					(CXCursor C);
CXCursor			_9_getCursorDefinition					(CXCursor C);
unsigned			_9_isCursorDefinition					(CXCursor C);
CXCursor			_9_getCanonicalCursor					(CXCursor C);
int					_9_getObjCSelectorIndex					(CXCursor C);
int					_9_isDynamicCall						(CXCursor C);
CXType				_9_getReceiverType						(CXCursor C);
unsigned			_9_getObjCPropertyAttributes			(CXCursor C, unsigned reserved);
CXString			_9_getObjCPropertyGetterName			(CXCursor C);
CXString			_9_getObjCPropertySetterName			(CXCursor C);
unsigned			_9_getObjCDeclQualifiers				(CXCursor C);
unsigned			_9_isObjCOptional						(CXCursor C);
unsigned			_9_isVariadic							(CXCursor C);
unsigned			_9_isExternalSymbol						(CXCursor C, CXString *language, CXString *definedIn, unsigned *isGenerated);
CXSourceRange		_9_getCommentRange						(CXCursor C);
CXString			_9_getRawCommentText					(CXCursor C);
CXString 			_9_getBriefCommentText					(CXCursor C);
