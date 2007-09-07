/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [ActiveScripting implemented with Tamarin].
 *
 * The Initial Developer of the Original Code is Mozilla Corp.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Mark Hammond.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "axtam.h"
#include "mscom.h"
#include "Profiler.h"
#include "ActiveScriptError.h"

// we use std stream IO for now.
//#include <iostream>
#include <fstream>

using namespace axtam;

static MMgc::FixedMalloc* fm = NULL;

class ATL_NO_VTABLE CActiveScript :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CActiveScript, &CLSID_ActiveScript>,
	public IActiveScript, // is this correct?
	public IActiveScriptParseProcedure2,
	public IActiveScriptParse,
	public IObjectSafety
{
public:
	CActiveScript();
	virtual ~CActiveScript() {;}

	// Our AvmCore instance.
	AXTam *core;

DECLARE_REGISTRY_RESOURCEID(IDR_ACTIVESCRIPT)

BEGIN_COM_MAP(CActiveScript)
	COM_INTERFACE_ENTRY(IActiveScript)
	COM_INTERFACE_ENTRY(IActiveScriptParseProcedure2)
	COM_INTERFACE_ENTRY(IActiveScriptParse)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CATEGORY_MAP(CActiveScript)
    IMPLEMENTED_CATEGORY(AXT_CATID_ActiveScript)
    IMPLEMENTED_CATEGORY(AXT_CATID_ActiveScriptParse)
END_CATEGORY_MAP()

	// IActiveScript
    STDMETHOD(SetScriptSite)( 
        /* [in] */ IActiveScriptSite *pass);
    
    STDMETHOD(GetScriptSite)( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppvObject);
    
    STDMETHOD(SetScriptState)( 
        /* [in] */ SCRIPTSTATE ss);

    STDMETHOD(GetScriptState)( 
        /* [out] */ SCRIPTSTATE *pssState);

    STDMETHOD(Close)(void);

    STDMETHOD(AddNamedItem)( 
        /* [in] */ LPCOLESTR pstrName,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(AddTypeLib)( 
        /* [in] */ REFGUID rguidTypeLib,
        /* [in] */ DWORD dwMajor,
        /* [in] */ DWORD dwMinor,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(GetScriptDispatch)( 
        /* [in] */ LPCOLESTR pstrItemName,
        /* [out] */ IDispatch **ppdisp);

    STDMETHOD(GetCurrentScriptThreadID)( 
        /* [out] */ SCRIPTTHREADID *pstidThread);

    STDMETHOD(GetScriptThreadID)( 
        /* [in] */ DWORD dwWin32ThreadId,
        /* [out] */ SCRIPTTHREADID *pstidThread);
    
    STDMETHOD(GetScriptThreadState)( 
        /* [in] */ SCRIPTTHREADID stidThread,
        /* [out] */ SCRIPTTHREADSTATE *pstsState);

    STDMETHOD(InterruptScriptThread)( 
        /* [in] */ SCRIPTTHREADID stidThread,
        /* [in] */ const EXCEPINFO *pexcepinfo,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(Clone)( 
        /* [out] */ IActiveScript **ppscript);

	// IActiveScriptParseProcedure2
	STDMETHOD(ParseProcedureText)( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrFormalParams,
            /* [in] */ LPCOLESTR pstrProcedureName,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDispatch **ppdisp);


	// IActiveScriptParse
	STDMETHOD(InitNew)(void);

	STDMETHOD(AddScriptlet)( 
            /* [in] */ LPCOLESTR pstrDefaultName,
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ LPCOLESTR pstrSubItemName,
            /* [in] */ LPCOLESTR pstrEventName,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ BSTR *pbstrName,
            /* [out] */ EXCEPINFO *pexcepinfo);
        
	STDMETHOD(ParseScriptText)( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ VARIANT *pvarResult,
            /* [out] */ EXCEPINFO *pexcepinfo);

	// IObjectSafety
    STDMETHOD(GetInterfaceSafetyOptions)( 
            /* [in] */ REFIID riid,
            /* [out] */ DWORD *pdwSupportedOptions,
            /* [out] */ DWORD *pdwEnabledOptions);

	STDMETHOD(SetInterfaceSafetyOptions)( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions);
protected:
	CComPtr<IActiveScriptSite> m_site;
	SCRIPTSTATE m_ss;
};

OBJECT_ENTRY_AUTO(CLSID_ActiveScript, CActiveScript)

// Constructor
CActiveScript::CActiveScript()
{
		// move this to DLL init?
	if (!fm) {
		MMgc::GCHeap::Init();
		MMgc::FixedMalloc::Init();

		fm = MMgc::FixedMalloc::GetInstance();
	}

	MMgc::GCHeap* heap = MMgc::GCHeap::GetGCHeap();

	// XXX - memory exceptions?
	MMgc::GC *gc = new MMgc::GC(heap); // XXX - delete this pointer??
	core = new AXTam(gc);
}

// Implementation methods.
STDMETHODIMP CActiveScript::SetScriptSite( 
            /* [in] */ IActiveScriptSite *pass)
{
	if (!pass)
		return E_POINTER;
	m_site = pass;
	return S_OK;
}

STDMETHODIMP CActiveScript::GetScriptSite( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject)
{
	if (!m_site) {
		ATLTRACE2("GetScriptSite with no site!");
		return E_FAIL;
	}
	return m_site.p->QueryInterface(riid, ppvObject);
}

STDMETHODIMP CActiveScript::SetScriptState( 
            /* [in] */ SCRIPTSTATE ss)
{
	m_ss = ss;
	return S_OK;
}

STDMETHODIMP CActiveScript::GetScriptState( 
            /* [out] */ SCRIPTSTATE *pssState)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptState"));
}

STDMETHODIMP CActiveScript::Close(void)
{
	ATLTRACENOTIMPL(_T("CActiveScript::Close"));
}

STDMETHODIMP CActiveScript::AddNamedItem( 
            /* [in] */ LPCOLESTR pstrName,
            /* [in] */ DWORD dwFlags)
{
	ATLTRACE2("CActiveScript::AddNamedItem(\"%S\", 0x%x)", pstrName, dwFlags);

	if (!m_site)
		return E_FAIL;
	CComPtr<IUnknown> punk;
	HRESULT hr = m_site->GetItemInfo(pstrName, SCRIPTINFO_IUNKNOWN, &punk, NULL);
	if (FAILED(hr))
		return hr;

	// ack - I'm making this up as I go :)
	String *name = new (core->GetGC()) String((const avmplus::wchar *)pstrName, wcslen(pstrName));
	name->setInterned(core);
//	Multiname mname(core->publicNamespace, name);

	MSCom *d = core->mscomClass->create(punk, name->atom());
	core->toplevel->setAtomProperty (name->atom(), d->atom());
	return S_OK;
}

STDMETHODIMP CActiveScript::AddTypeLib( 
            /* [in] */ REFGUID rguidTypeLib,
            /* [in] */ DWORD dwMajor,
            /* [in] */ DWORD dwMinor,
            /* [in] */ DWORD dwFlags)
{
	ATLTRACENOTIMPL(_T("CActiveScript::AddTypeLib"));
}

STDMETHODIMP CActiveScript::GetScriptDispatch( 
            /* [in] */ LPCOLESTR pstrItemName,
            /* [out] */ IDispatch **ppdisp)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptDispatch"));
}

STDMETHODIMP CActiveScript::GetCurrentScriptThreadID( 
            /* [out] */ SCRIPTTHREADID *pstidThread)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetCurrentScriptThreadID"));
}

STDMETHODIMP CActiveScript::GetScriptThreadID( 
            /* [in] */ DWORD dwWin32ThreadId,
            /* [out] */ SCRIPTTHREADID *pstidThread)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptThreadID"));
}

STDMETHODIMP CActiveScript::GetScriptThreadState( 
            /* [in] */ SCRIPTTHREADID stidThread,
            /* [out] */ SCRIPTTHREADSTATE *pstsState)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptThreadState"));
}

STDMETHODIMP CActiveScript::InterruptScriptThread( 
            /* [in] */ SCRIPTTHREADID stidThread,
            /* [in] */ const EXCEPINFO *pexcepinfo,
            /* [in] */ DWORD dwFlags)
{
	ATLTRACENOTIMPL(_T("CActiveScript::InterruptScriptThread"));
}

STDMETHODIMP CActiveScript::Clone( 
            /* [out] */ IActiveScript **ppscript)
{
	ATLTRACENOTIMPL(_T("CActiveScript::Clone"));
}

	// IActiveScriptParseProcedure2
STDMETHODIMP CActiveScript::ParseProcedureText( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrFormalParams,
            /* [in] */ LPCOLESTR pstrProcedureName,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDispatch **ppdisp)
{
	ATLTRACENOTIMPL(_T("CActiveScript::ParseProcedureText"));
}

// IActiveScriptParse implementation
STDMETHODIMP CActiveScript::InitNew(void)
{
	if (!core) {
		ATLTRACE2("Engine failing to initialize - no core!");
		return E_OUTOFMEMORY;
	}
	return core->InitNew();
}

STDMETHODIMP CActiveScript::AddScriptlet( 
            /* [in] */ LPCOLESTR pstrDefaultName,
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ LPCOLESTR pstrSubItemName,
            /* [in] */ LPCOLESTR pstrEventName,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ BSTR *pbstrName,
            /* [out] */ EXCEPINFO *pexcepinfo)
{
	ATLTRACENOTIMPL(_T("CActiveScript::AddScriptlet"));
}

STDMETHODIMP CActiveScript::ParseScriptText( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ VARIANT *pvarResult,
            /* [out] */ EXCEPINFO *pexcepinfo)
{
	// until we get a compiler, assume the text passed to us contains
	// the name of a file with the .abc!  This will do in the short
	// term.
	TRY(core, kCatchAction_ReportAsError) {
		std::fstream file(pstrCode, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
		std::ifstream::pos_type size(file.tellg());
		ScriptBuffer code = core->newScriptBuffer(size);
		file.seekg(0);
		file.read((char *)code.getBuffer(), size);

		// Return a new DomainEnv for the user code
		DomainEnv* domainEnv = new (core->GetGC()) DomainEnv(core,
															 core->domain,
															 core->toplevel->domainEnv());

		axtam::CodeContext* codeContext = new (core->GetGC()) axtam::CodeContext();
		codeContext->domainEnv = domainEnv;

		// parse new bytecode
		core->handleActionBlock(code, 0, domainEnv, core->toplevel, NULL, NULL, NULL, codeContext);

	}
	CATCH(Exception * exception)
	{
		#ifdef DEBUGGER
		if (!(exception->flags & Exception::SEEN_BY_DEBUGGER))
		{
			ATLTRACE2("*sob* - how to get exception??" /*(const wchar_t *)exception->atom */);
			ATLTRACE2("\n");
		}
		if (exception->getStackTrace()) {
			ATLTRACE2((const wchar_t *)exception->getStackTrace()->format(core));
			ATLTRACE2("\n");
		}
		#else
			ATLTRACE2("*sob*");//string(exception->atom));
			ATLTRACE2("\n");
		#endif

		// Notify script site of error
		CGCRootComObject<CActiveScriptError> *err;
		ATLTRY(err = new CGCRootComObject<CActiveScriptError>(core->gc));
		if (m_site && err) {
			err->exception = exception; // can we really just copy the pointer here?
			CComQIPtr<IActiveScriptError, &IID_IActiveScriptError> ase(err);
			m_site->OnScriptError(ase);
		}

	}
	END_CATCH
	END_TRY

	#ifdef DEBUGGER
	delete core->profiler;
	#endif

	#ifdef AVMPLUS_PROFILE
		core->dump();
	#endif

	return S_OK;
}

// IObjectSafety
STDMETHODIMP CActiveScript::GetInterfaceSafetyOptions( 
            /* [in] */ REFIID riid,
            /* [out] */ DWORD *pdwSupportedOptions,
            /* [out] */ DWORD *pdwEnabledOptions)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetInterfaceSafetyOptions"));
}

STDMETHODIMP CActiveScript::SetInterfaceSafetyOptions( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions)
{
	ATLTRACENOTIMPL(_T("CActiveScript::SetInterfaceSafetyOptions"));
}
