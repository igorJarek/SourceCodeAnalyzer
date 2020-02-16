#include "StructsEnums2String.h"

string CXDiagnosticSeverity2String(const CXDiagnosticSeverity diagnosticSeverity)
{
    string str;
    switch (diagnosticSeverity)
    {
    case CXDiagnostic_Ignored:
        str += "CXDiagnostic_Ignored";
        break;

    case CXDiagnostic_Note:
        str += "CXDiagnostic_Note";
        break;

    case CXDiagnostic_Warning:
        str += "CXDiagnostic_Warning";
        break;

    case CXDiagnostic_Error:
        str += "CXDiagnostic_Error";
        break;

    case CXDiagnostic_Fatal:
        str += "CXDiagnostic_Fatal";
        break;
    }

    return str;
}

string CXDiagnosticDisplayOptions2String(uint32_t options)
{
    string str;

    if (options & CXDiagnostic_DisplaySourceLocation)
        str += "CXDiagnostic_DisplaySourceLocation | ";

    if (options & CXDiagnostic_DisplayColumn)
        str += "CXDiagnostic_DisplayColumn | ";

    if (options & CXDiagnostic_DisplaySourceRanges)
        str += "CXDiagnostic_DisplaySourceRanges | ";

    if (options & CXDiagnostic_DisplayOption)
        str += "CXDiagnostic_DisplayOption | ";

    if (options & CXDiagnostic_DisplayCategoryId)
        str += "CXDiagnostic_DisplayCategoryId | ";

    if (options & CXDiagnostic_DisplayCategoryName)
        str += "CXDiagnostic_DisplayCategoryName | ";

    str.erase(str.find_last_of("|"));

    return str;
}

string CXSourceLocation2String(const CXSourceLocation sourceLocation, uint32_t offset)
{
    string str;
    CXFile file1, file2;
    uint32_t line1, line2;
    uint32_t column1, column2;
    uint32_t offset1, offset2;

    clang_getExpansionLocation(sourceLocation, &file1, &line1, &column1, &offset1);
    clang_getSpellingLocation(sourceLocation, &file2, &line2, &column2, &offset2);

    str += tabOffset(offset) + "ExpansionLocation : \n";
    str += tabOffset(offset + 1) + "File : " + _11_CXString2String(clang_getFileName(file1)) + '\n';
    str += tabOffset(offset + 1) + "Line : " + to_string(line1) + '\n';
    str += tabOffset(offset + 1) + "Column : " + to_string(column1) + '\n';
    str += tabOffset(offset + 1) + "Offset : " + to_string(offset1) + "\n\n";

    str += tabOffset(offset) + "SpellingLocation : \n";
    str += tabOffset(offset + 1) + "File : " + _11_CXString2String(clang_getFileName(file2)) + '\n';
    str += tabOffset(offset + 1) + "Line : " + to_string(line2) + '\n';
    str += tabOffset(offset + 1) + "Column : " + to_string(column2) + '\n';
    str += tabOffset(offset + 1) + "Offset : " + to_string(offset2) + "\n\n";

    return str;
}

string CXSourceRange2String(const CXSourceRange sourceRange, uint32_t offset)
{
    string str;

    CXSourceLocation rangeStart = clang_getRangeStart(sourceRange);
    CXSourceLocation rangeEnd = clang_getRangeEnd(sourceRange);

    str += tabOffset(offset) + "RangeStart : \n";
    str += CXSourceLocation2String(rangeStart, offset + 1);
    str += tabOffset(offset) + "RangeEnd : \n";;
    str += CXSourceLocation2String(rangeEnd, offset + 1);

    return str;
}

string CXCursorKind2String(CXCursorKind cursorKind)
{
    switch (cursorKind)
    {
		case CXCursor_UnexposedDecl:
			return "CXCursor_UnexposedDecl | CXCursor_FirstDecl";
		case CXCursor_StructDecl:
			return "CXCursor_StructDecl";
		case CXCursor_UnionDecl:
			return "CXCursor_UnionDecl";
		case CXCursor_ClassDecl:
			return "CXCursor_ClassDecl";
		case CXCursor_EnumDecl:
			return "CXCursor_EnumDecl";
		case CXCursor_FieldDecl:
			return "CXCursor_FieldDecl";
		case CXCursor_EnumConstantDecl:
			return "CXCursor_EnumConstantDecl";
		case CXCursor_FunctionDecl:
			return "CXCursor_FunctionDecl";
		case CXCursor_VarDecl:
			return "CXCursor_VarDecl";
		case CXCursor_ParmDecl:
			return "CXCursor_ParmDecl";
		case CXCursor_ObjCInterfaceDecl:
			return "CXCursor_ObjCInterfaceDecl";
		case CXCursor_ObjCCategoryDecl:
			return "CXCursor_ObjCCategoryDecl";
		case CXCursor_ObjCProtocolDecl:
			return "CXCursor_ObjCProtocolDecl";
		case CXCursor_ObjCPropertyDecl:
			return "CXCursor_ObjCPropertyDecl";
		case CXCursor_ObjCIvarDecl:
			return "CXCursor_ObjCIvarDecl";
		case CXCursor_ObjCInstanceMethodDecl:
			return "CXCursor_ObjCInstanceMethodDecl";
		case CXCursor_ObjCClassMethodDecl:
			return "CXCursor_ObjCClassMethodDecl";
		case CXCursor_ObjCImplementationDecl:
			return "CXCursor_ObjCImplementationDecl";
		case CXCursor_ObjCCategoryImplDecl:
			return "CXCursor_ObjCCategoryImplDecl";
		case CXCursor_TypedefDecl:
			return "CXCursor_TypedefDecl";
		case CXCursor_CXXMethod:
			return "CXCursor_CXXMethod";
		case CXCursor_Namespace:
			return "CXCursor_Namespace";
		case CXCursor_LinkageSpec:
			return "CXCursor_LinkageSpec";
		case CXCursor_Constructor:
			return "CXCursor_Constructor";
		case CXCursor_Destructor:
			return "CXCursor_Destructor";
		case CXCursor_ConversionFunction:
			return "CXCursor_ConversionFunction";
		case CXCursor_TemplateTypeParameter:
			return "CXCursor_TemplateTypeParameter";
		case CXCursor_NonTypeTemplateParameter:
			return "CXCursor_NonTypeTemplateParameter";
		case CXCursor_TemplateTemplateParameter:
			return "CXCursor_TemplateTemplateParameter";
		case CXCursor_FunctionTemplate:
			return "CXCursor_FunctionTemplate";
		case CXCursor_ClassTemplate:
			return "CXCursor_ClassTemplate";
		case CXCursor_ClassTemplatePartialSpecialization:
			return "CXCursor_ClassTemplatePartialSpecialization";
		case CXCursor_NamespaceAlias:
			return "CXCursor_NamespaceAlias";
		case CXCursor_UsingDirective:
			return "CXCursor_UsingDirective";
		case CXCursor_UsingDeclaration:
			return "CXCursor_UsingDeclaration";
		case CXCursor_TypeAliasDecl:
			return "CXCursor_TypeAliasDecl";
		case CXCursor_ObjCSynthesizeDecl:
			return "CXCursor_ObjCSynthesizeDecl";
		case CXCursor_ObjCDynamicDecl:
			return "CXCursor_ObjCDynamicDecl";
		case CXCursor_CXXAccessSpecifier:
			return "CXCursor_CXXAccessSpecifier | CXCursor_LastDecl";
		case CXCursor_FirstRef:
			return "CXCursor_FirstRef | CXCursor_ObjCSuperClassRef";
		case CXCursor_ObjCProtocolRef:
			return "CXCursor_ObjCProtocolRef";
		case CXCursor_ObjCClassRef:
			return "CXCursor_ObjCClassRef";
		case CXCursor_TypeRef:
			return "CXCursor_TypeRef";
		case CXCursor_CXXBaseSpecifier:
			return "CXCursor_CXXBaseSpecifier";
		case CXCursor_TemplateRef:
			return "CXCursor_TemplateRef";
		case CXCursor_NamespaceRef:
			return "CXCursor_NamespaceRef";
		case CXCursor_MemberRef:
			return "CXCursor_MemberRef";
		case CXCursor_LabelRef:
			return "CXCursor_LabelRef";
		case CXCursor_OverloadedDeclRef:
			return "CXCursor_OverloadedDeclRef";
		case CXCursor_VariableRef:
			return "CXCursor_VariableRef | CXCursor_LastRef";
		case CXCursor_FirstInvalid:
			return "CXCursor_FirstInvalid | CXCursor_InvalidFile";
		case CXCursor_NoDeclFound:
			return "CXCursor_NoDeclFound";
		case CXCursor_NotImplemented:
			return "CXCursor_NotImplemented";
		case CXCursor_InvalidCode:
			return "CXCursor_InvalidCode | CXCursor_LastInvalid";
		case CXCursor_FirstExpr:
			return "CXCursor_FirstExpr | CXCursor_UnexposedExpr";
		case CXCursor_DeclRefExpr:
			return "CXCursor_DeclRefExpr";
		case CXCursor_MemberRefExpr:
			return "CXCursor_MemberRefExpr";
		case CXCursor_CallExpr:
			return "CXCursor_CallExpr";
		case CXCursor_ObjCMessageExpr:
			return "CXCursor_ObjCMessageExpr";
		case CXCursor_BlockExpr:
			return "CXCursor_BlockExpr";
		case CXCursor_IntegerLiteral:
			return "CXCursor_IntegerLiteral";
		case CXCursor_FloatingLiteral:
			return "CXCursor_FloatingLiteral";
		case CXCursor_ImaginaryLiteral:
			return "CXCursor_ImaginaryLiteral";
		case CXCursor_StringLiteral:
			return "CXCursor_StringLiteral";
		case CXCursor_CharacterLiteral:
			return "CXCursor_CharacterLiteral";
		case CXCursor_ParenExpr:
			return "CXCursor_ParenExpr";
		case CXCursor_UnaryOperator:
			return "CXCursor_UnaryOperator";
		case CXCursor_ArraySubscriptExpr:
			return "CXCursor_ArraySubscriptExpr";
		case CXCursor_BinaryOperator:
			return "CXCursor_BinaryOperator";
		case CXCursor_CompoundAssignOperator:
			return "CXCursor_CompoundAssignOperator";
		case CXCursor_ConditionalOperator:
			return "CXCursor_ConditionalOperator";
		case CXCursor_CStyleCastExpr:
			return "CXCursor_CStyleCastExpr";
		case CXCursor_CompoundLiteralExpr:
			return "CXCursor_CompoundLiteralExpr";
		case CXCursor_InitListExpr:
			return "CXCursor_InitListExpr";
		case CXCursor_AddrLabelExpr:
			return "CXCursor_AddrLabelExpr";
		case CXCursor_StmtExpr:
			return "CXCursor_StmtExpr";
		case CXCursor_GenericSelectionExpr:
			return "CXCursor_GenericSelectionExpr";
		case CXCursor_GNUNullExpr:
			return "CXCursor_GNUNullExpr";
		case CXCursor_CXXStaticCastExpr:
			return "CXCursor_CXXStaticCastExpr";
		case CXCursor_CXXDynamicCastExpr:
			return "CXCursor_CXXDynamicCastExpr";
		case CXCursor_CXXReinterpretCastExpr:
			return "CXCursor_CXXReinterpretCastExpr";
		case CXCursor_CXXConstCastExpr:
			return "CXCursor_CXXConstCastExpr";
		case CXCursor_CXXFunctionalCastExpr:
			return "CXCursor_CXXFunctionalCastExpr";
		case CXCursor_CXXTypeidExpr:
			return "CXCursor_CXXTypeidExpr";
		case CXCursor_CXXBoolLiteralExpr:
			return "CXCursor_CXXBoolLiteralExpr";
		case CXCursor_CXXNullPtrLiteralExpr:
			return "CXCursor_CXXNullPtrLiteralExpr";
		case CXCursor_CXXThisExpr:
			return "CXCursor_CXXThisExpr";
		case CXCursor_CXXThrowExpr:
			return "CXCursor_CXXThrowExpr";
		case CXCursor_CXXNewExpr:
			return "CXCursor_CXXNewExpr";
		case CXCursor_CXXDeleteExpr:
			return "CXCursor_CXXDeleteExpr";
		case CXCursor_UnaryExpr:
			return "CXCursor_UnaryExpr";
		case CXCursor_ObjCStringLiteral:
			return "CXCursor_ObjCStringLiteral";
		case CXCursor_ObjCEncodeExpr:
			return "CXCursor_ObjCEncodeExpr";
		case CXCursor_ObjCSelectorExpr:
			return "CXCursor_ObjCSelectorExpr";
		case CXCursor_ObjCProtocolExpr:
			return "CXCursor_ObjCProtocolExpr";
		case CXCursor_ObjCBridgedCastExpr:
			return "CXCursor_ObjCBridgedCastExpr";
		case CXCursor_PackExpansionExpr:
			return "CXCursor_PackExpansionExpr";
		case CXCursor_SizeOfPackExpr:
			return "CXCursor_SizeOfPackExpr";
		case CXCursor_LambdaExpr:
			return "CXCursor_LambdaExpr";
		case CXCursor_ObjCBoolLiteralExpr:
			return "CXCursor_ObjCBoolLiteralExpr";
		case CXCursor_ObjCSelfExpr:
			return "CXCursor_ObjCSelfExpr";
		case CXCursor_OMPArraySectionExpr:
			return "CXCursor_OMPArraySectionExpr";
		case CXCursor_ObjCAvailabilityCheckExpr:
			return "CXCursor_ObjCAvailabilityCheckExpr";
		case CXCursor_FixedPointLiteral:
			return "CXCursor_FixedPointLiteral | CXCursor_LastExpr";
		case CXCursor_FirstStmt | CXCursor_UnexposedStmt:
			return "CXCursor_FirstStmt";
		case CXCursor_LabelStmt:
			return "CXCursor_LabelStmt";
		case CXCursor_CompoundStmt:
			return "CXCursor_CompoundStmt";
		case CXCursor_CaseStmt:
			return "CXCursor_CaseStmt";
		case CXCursor_DefaultStmt:
			return "CXCursor_DefaultStmt";
		case CXCursor_IfStmt:
			return "CXCursor_IfStmt";
		case CXCursor_SwitchStmt:
			return "CXCursor_SwitchStmt";
		case CXCursor_WhileStmt:
			return "CXCursor_WhileStmt";
		case CXCursor_DoStmt:
			return "CXCursor_DoStmt";
		case CXCursor_ForStmt:
			return "CXCursor_ForStmt";
		case CXCursor_GotoStmt:
			return "CXCursor_GotoStmt";
		case CXCursor_IndirectGotoStmt:
			return "CXCursor_IndirectGotoStmt";
		case CXCursor_ContinueStmt:
			return "CXCursor_ContinueStmt";
		case CXCursor_BreakStmt:
			return "CXCursor_BreakStmt";
		case CXCursor_ReturnStmt:
			return "CXCursor_ReturnStmt";
		case CXCursor_GCCAsmStmt:
			return "CXCursor_GCCAsmStmt | CXCursor_AsmStmt";
		case CXCursor_ObjCAtTryStmt:
			return "CXCursor_ObjCAtTryStmt";
		case CXCursor_ObjCAtCatchStmt:
			return "CXCursor_ObjCAtCatchStmt";
		case CXCursor_ObjCAtFinallyStmt:
			return "CXCursor_ObjCAtFinallyStmt";
		case CXCursor_ObjCAtThrowStmt:
			return "CXCursor_ObjCAtThrowStmt";
		case CXCursor_ObjCAtSynchronizedStmt:
			return "CXCursor_ObjCAtSynchronizedStmt";
		case CXCursor_ObjCAutoreleasePoolStmt:
			return "CXCursor_ObjCAutoreleasePoolStmt";
		case CXCursor_ObjCForCollectionStmt:
			return "CXCursor_ObjCForCollectionStmt";
		case CXCursor_CXXCatchStmt:
			return "CXCursor_CXXCatchStmt";
		case CXCursor_CXXTryStmt:
			return "CXCursor_CXXTryStmt";
		case CXCursor_CXXForRangeStmt:
			return "CXCursor_CXXForRangeStmt";
		case CXCursor_SEHTryStmt:
			return "CXCursor_SEHTryStmt";
		case CXCursor_SEHExceptStmt:
			return "CXCursor_SEHExceptStmt";
		case CXCursor_SEHFinallyStmt:
			return "CXCursor_SEHFinallyStmt";
		case CXCursor_MSAsmStmt:
			return "CXCursor_MSAsmStmt";
		case CXCursor_NullStmt:
			return "CXCursor_NullStmt";
		case CXCursor_DeclStmt:
			return "CXCursor_DeclStmt";
		case CXCursor_OMPParallelDirective:
			return "CXCursor_OMPParallelDirective";
		case CXCursor_OMPSimdDirective:
			return "CXCursor_OMPSimdDirective";
		case CXCursor_OMPForDirective:
			return "CXCursor_OMPForDirective";
		case CXCursor_OMPSectionsDirective:
			return "CXCursor_OMPSectionsDirective";
		case CXCursor_OMPSectionDirective:
			return "CXCursor_OMPSectionDirective";
		case CXCursor_OMPSingleDirective:
			return "CXCursor_OMPSingleDirective";
		case CXCursor_OMPParallelForDirective:
			return "CXCursor_OMPParallelForDirective";
		case CXCursor_OMPParallelSectionsDirective:
			return "CXCursor_OMPParallelSectionsDirective";
		case CXCursor_OMPTaskDirective:
			return "CXCursor_OMPTaskDirective";
		case CXCursor_OMPMasterDirective:
			return "CXCursor_OMPMasterDirective";
		case CXCursor_OMPCriticalDirective:
			return "CXCursor_OMPCriticalDirective";
		case CXCursor_OMPTaskyieldDirective:
			return "CXCursor_OMPTaskyieldDirective";
		case CXCursor_OMPBarrierDirective:
			return "CXCursor_OMPBarrierDirective";
		case CXCursor_OMPTaskwaitDirective:
			return "CXCursor_OMPTaskwaitDirective";
		case CXCursor_OMPFlushDirective:
			return "CXCursor_OMPFlushDirective";
		case CXCursor_SEHLeaveStmt:
			return "CXCursor_SEHLeaveStmt";
		case CXCursor_OMPOrderedDirective:
			return "CXCursor_OMPOrderedDirective";
		case CXCursor_OMPAtomicDirective:
			return "CXCursor_OMPAtomicDirective";
		case CXCursor_OMPForSimdDirective:
			return "CXCursor_OMPForSimdDirective";
		case CXCursor_OMPParallelForSimdDirective:
			return "CXCursor_OMPParallelForSimdDirective";
		case CXCursor_OMPTargetDirective:
			return "CXCursor_OMPTargetDirective";
		case CXCursor_OMPTeamsDirective:
			return "CXCursor_OMPTeamsDirective";
		case CXCursor_OMPTaskgroupDirective:
			return "CXCursor_OMPTaskgroupDirective";
		case CXCursor_OMPCancellationPointDirective:
			return "CXCursor_OMPCancellationPointDirective";
		case CXCursor_OMPCancelDirective:
			return "CXCursor_OMPCancelDirective";
		case CXCursor_OMPTargetDataDirective:
			return "CXCursor_OMPTargetDataDirective";
		case CXCursor_OMPTaskLoopDirective:
			return "CXCursor_OMPTaskLoopDirective";
		case CXCursor_OMPTaskLoopSimdDirective:
			return "CXCursor_OMPTaskLoopSimdDirective";
		case CXCursor_OMPDistributeDirective:
			return "CXCursor_OMPDistributeDirective";
		case CXCursor_OMPTargetEnterDataDirective:
			return "CXCursor_OMPTargetEnterDataDirective";
		case CXCursor_OMPTargetExitDataDirective:
			return "CXCursor_OMPTargetExitDataDirective";
		case CXCursor_OMPTargetParallelDirective:
			return "CXCursor_OMPTargetParallelDirective";
		case CXCursor_OMPTargetParallelForDirective:
			return "CXCursor_OMPTargetParallelForDirective";
		case CXCursor_OMPTargetUpdateDirective:
			return "CXCursor_OMPTargetUpdateDirective";
		case CXCursor_OMPDistributeParallelForDirective:
			return "CXCursor_OMPDistributeParallelForDirective";
		case CXCursor_OMPDistributeParallelForSimdDirective:
			return "CXCursor_OMPDistributeParallelForSimdDirective";
		case CXCursor_OMPDistributeSimdDirective:
			return "CXCursor_OMPDistributeSimdDirective";
		case CXCursor_OMPTargetParallelForSimdDirective:
			return "CXCursor_OMPTargetParallelForSimdDirective";
		case CXCursor_OMPTargetSimdDirective:
			return "CXCursor_OMPTargetSimdDirective";
		case CXCursor_OMPTeamsDistributeDirective:
			return "CXCursor_OMPTeamsDistributeDirective";
		case CXCursor_OMPTeamsDistributeSimdDirective:
			return "CXCursor_OMPTeamsDistributeSimdDirective";
		case CXCursor_OMPTeamsDistributeParallelForSimdDirective:
			return "CXCursor_OMPTeamsDistributeParallelForSimdDirective";
		case CXCursor_OMPTeamsDistributeParallelForDirective:
			return "CXCursor_OMPTeamsDistributeParallelForDirective";
		case CXCursor_OMPTargetTeamsDirective:
			return "CXCursor_OMPTargetTeamsDirective";
		case CXCursor_OMPTargetTeamsDistributeDirective:
			return "CXCursor_OMPTargetTeamsDistributeDirective";
		case CXCursor_OMPTargetTeamsDistributeParallelForDirective:
			return "CXCursor_OMPTargetTeamsDistributeParallelForDirective";
		case CXCursor_OMPTargetTeamsDistributeParallelForSimdDirective:
			return "CXCursor_OMPTargetTeamsDistributeParallelForSimdDirective";
		case CXCursor_OMPTargetTeamsDistributeSimdDirective:
			return "CXCursor_OMPTargetTeamsDistributeSimdDirective";
		case CXCursor_BuiltinBitCastExpr:
			return "CXCursor_BuiltinBitCastExpr | CXCursor_LastStmt";
		
		/* UNDEFINED
		case CXCursor_OMPMasterTaskLoopDirective:
			return "CXCursor_OMPMasterTaskLoopDirective";
		case CXCursor_OMPParallelMasterTaskLoopDirective:
			return "CXCursor_OMPParallelMasterTaskLoopDirective";
		case CXCursor_OMPMasterTaskLoopSimdDirective:
			return "CXCursor_OMPMasterTaskLoopSimdDirective";
		*/

		case CXCursor_TranslationUnit:
			return "CXCursor_TranslationUnit";
		case CXCursor_FirstAttr:
			return "CXCursor_FirstAttr | CXCursor_UnexposedAttr";
		case CXCursor_IBActionAttr:
			return "CXCursor_IBActionAttr";
		case CXCursor_IBOutletAttr:
			return "CXCursor_IBOutletAttr";
		case CXCursor_IBOutletCollectionAttr:
			return "CXCursor_IBOutletCollectionAttr";
		case CXCursor_CXXFinalAttr:
			return "CXCursor_CXXFinalAttr";
		case CXCursor_CXXOverrideAttr:
			return "CXCursor_CXXOverrideAttr";
		case CXCursor_AnnotateAttr:
			return "CXCursor_AnnotateAttr";
		case CXCursor_AsmLabelAttr:
			return "CXCursor_AsmLabelAttr";
		case CXCursor_PackedAttr:
			return "CXCursor_PackedAttr";
		case CXCursor_PureAttr:
			return "CXCursor_PureAttr";
		case CXCursor_ConstAttr:
			return "CXCursor_ConstAttr";
		case CXCursor_NoDuplicateAttr:
			return "CXCursor_NoDuplicateAttr";
		case CXCursor_CUDAConstantAttr:
			return "CXCursor_CUDAConstantAttr";
		case CXCursor_CUDADeviceAttr:
			return "CXCursor_CUDADeviceAttr";
		case CXCursor_CUDAGlobalAttr:
			return "CXCursor_CUDAGlobalAttr";
		case CXCursor_CUDAHostAttr:
			return "CXCursor_CUDAHostAttr";
		case CXCursor_CUDASharedAttr:
			return "CXCursor_CUDASharedAttr";
		case CXCursor_VisibilityAttr:
			return "CXCursor_VisibilityAttr";
		case CXCursor_DLLExport:
			return "CXCursor_DLLExport";
		case CXCursor_DLLImport:
			return "CXCursor_DLLImport";
		case CXCursor_NSReturnsRetained:
			return "CXCursor_NSReturnsRetained";
		case CXCursor_NSReturnsNotRetained:
			return "CXCursor_NSReturnsNotRetained";
		case CXCursor_NSReturnsAutoreleased:
			return "CXCursor_NSReturnsAutoreleased";
		case CXCursor_NSConsumesSelf:
			return "CXCursor_NSConsumesSelf";
		case CXCursor_NSConsumed:
			return "CXCursor_NSConsumed";
		case CXCursor_ObjCException:
			return "CXCursor_ObjCException";
		case CXCursor_ObjCNSObject:
			return "CXCursor_ObjCNSObject";
		case CXCursor_ObjCIndependentClass:
			return "CXCursor_ObjCIndependentClass";
		case CXCursor_ObjCPreciseLifetime:
			return "CXCursor_ObjCPreciseLifetime";
		case CXCursor_ObjCReturnsInnerPointer:
			return "CXCursor_ObjCReturnsInnerPointer";
		case CXCursor_ObjCRequiresSuper:
			return "CXCursor_ObjCRequiresSuper";
		case CXCursor_ObjCRootClass:
			return "CXCursor_ObjCRootClass";
		case CXCursor_ObjCSubclassingRestricted:
			return "CXCursor_ObjCSubclassingRestricted";
		case CXCursor_ObjCExplicitProtocolImpl:
			return "CXCursor_ObjCExplicitProtocolImpl";
		case CXCursor_ObjCDesignatedInitializer:
			return "CXCursor_ObjCDesignatedInitializer";
		case CXCursor_ObjCRuntimeVisible:
			return "CXCursor_ObjCRuntimeVisible";
		case CXCursor_ObjCBoxable:
			return "CXCursor_ObjCBoxable";
		case CXCursor_FlagEnum:
			return "CXCursor_FlagEnum";
		case CXCursor_ConvergentAttr:
			return "CXCursor_ConvergentAttr";
		case CXCursor_WarnUnusedAttr:
			return "CXCursor_WarnUnusedAttr";
		case CXCursor_WarnUnusedResultAttr:
			return "CXCursor_WarnUnusedResultAttr";
		case CXCursor_AlignedAttr:
			return "CXCursor_AlignedAttr | CXCursor_LastAttr";
		case CXCursor_PreprocessingDirective:
			return "CXCursor_PreprocessingDirective | CXCursor_FirstPreprocessing";
		case CXCursor_MacroDefinition:
			return "CXCursor_MacroDefinition";
		case CXCursor_MacroExpansion:
			return "CXCursor_MacroExpansion | CXCursor_MacroInstantiation";
		case CXCursor_InclusionDirective:
			return "CXCursor_InclusionDirective | CXCursor_LastPreprocessing";
		case CXCursor_ModuleImportDecl:
			return "CXCursor_ModuleImportDecl | CXCursor_FirstExtraDecl";
		case CXCursor_TypeAliasTemplateDecl:
			return "CXCursor_TypeAliasTemplateDecl";
		case CXCursor_StaticAssert:
			return "CXCursor_StaticAssert";
		case CXCursor_FriendDecl:
			return "CXCursor_FriendDecl | CXCursor_LastExtraDecl";
		case CXCursor_OverloadCandidate:
			return "CXCursor_OverloadCandidate";

		default:     
			return "Undefined CXCursorKind";
    }
}

string CXTUResourceUsage2String(const CXTUResourceUsage& TUResourceUsage, uint32_t offset)
{
	string str;

	if (TUResourceUsage.numEntries)
	{
		for (uint32_t index{ 0 }; index < TUResourceUsage.numEntries; ++index)
		{
			CXTUResourceUsageEntry resourceUsageEntry = TUResourceUsage.entries[index];
			CXTUResourceUsageKind kind = resourceUsageEntry.kind;
			uint64_t amount = resourceUsageEntry.amount;

			str += tabOffset(offset) +
				_6_CXTUResourceUsageKind2constChar(kind) + '\n';
			str += tabOffset(offset) + "Amount: " + to_string(amount) + "\n\n";
		}
	}

	return str;
}

string CXErrorCode2String(CXErrorCode errorCode)
{
	switch (errorCode)
	{
		case CXError_Success:
			return "CXError_Success";
		case CXError_Failure:
			return "CXError_Failure";
		case CXError_Crashed:
			return "CXError_Crashed";
		case CXError_InvalidArguments:
			return "CXError_InvalidArguments";
		case CXError_ASTReadError:
			return "CXError_ASTReadError";

		default:
			return "Undefined CXErrorCode";
	}
}

string CXSaveError2String(int32_t saveError)
{
	switch (saveError)
	{
		case CXSaveError_None:
			return "CXSaveError_None";
		case CXSaveError_Unknown:
			return "CXSaveError_Unknown";
		case CXSaveError_TranslationErrors:
			return "CXSaveError_TranslationErrors";
		case CXSaveError_InvalidTU:
			return "CXSaveError_InvalidTU";

		default:
			return "Undefined CXSaveError";
	}
}