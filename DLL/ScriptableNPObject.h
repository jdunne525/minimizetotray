#pragma once

typedef bool (*p_JSMethod)(NPNetscapeFuncs *pBrowserFuncs, NPP pluginInstance, const uint32_t argCount, const NPVariant *args);

class CScriptableNPObject : public NPObject
{
public:
	typedef map<string, p_JSMethod> JSMethodsMap;

public:
	CScriptableNPObject(NPP pluginInstance);
	~CScriptableNPObject(void);

public:
	bool RegisterMethod(const char* lpszMethod, p_JSMethod method);
	bool HasMethod(const char* lpszMethod);
	bool CallMethod(const char* lpszMethod, const uint32_t nCount, const NPVariant *args);

protected:
	void Deallocate();

	bool HasMethod(NPIdentifier name);
	bool InvokeMethod(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

	void Invalidate();

	bool HasProperty(NPIdentifier name); 
	bool GetProperty(NPIdentifier name,	NPVariant *result); 
	bool SetProperty(NPIdentifier name, const NPVariant *value); 
	bool RemoveProperty(NPIdentifier name);

	bool Enumerate(NPIdentifier **identifier, uint32_t *count); 
	bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);

public:
	static NPObject* NP_Allocate(NPP npp, NPClass *npClass)
	{
		DebugLog(_T("CScriptableNPObject::NP_Allocate\n"));

		NPObject *obj		= new CScriptableNPObject(npp);
		obj->referenceCount = 0;

		return obj;
	}

	static void NP_Deallocate(NPObject *npobj)
	{
		DebugLog(_T("CScriptableNPObject::NP_Deallocate\n"));
		((CScriptableNPObject*)npobj)->Deallocate();
	}

	static bool NP_HasMethod(NPObject *npobj, NPIdentifier name)
	{
		DebugLog(_T("CScriptableNPObject::NP_HasMethod\n"));
		return ((CScriptableNPObject*)npobj)->HasMethod(name);
	}

	static bool NP_InvokeMethod(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
	{
		DebugLog(_T("CScriptableNPObject::NP_InvokeMethod\n"));
		return ((CScriptableNPObject*)npobj)->InvokeMethod(name, args, argCount, result);
	}

	static bool NP_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
	{
		DebugLog(_T("CScriptableNPObject::NP_InvokeDefault\n"));
		return ((CScriptableNPObject*)npobj)->InvokeDefault(args, argCount, result);
	}

	static void NP_Invalidate(NPObject *npobj)
	{
		DebugLog(_T("CScriptableNPObject::NP_Invalidate\n"));
		((CScriptableNPObject*)npobj)->Invalidate();
	}

	static bool NP_HasProperty(NPObject *npobj, NPIdentifier name)
	{
		DebugLog(_T("CScriptableNPObject::NP_HasProperty\n"));
		return ((CScriptableNPObject*)npobj)->HasProperty(name);
	}

	static bool NP_GetProperty(NPObject *npobj, NPIdentifier name,	NPVariant *result)
	{
		DebugLog(_T("CScriptableNPObject::NP_GetProperty\n"));
		return ((CScriptableNPObject*)npobj)->GetProperty(name, result);
	}

	static bool NP_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
	{
		DebugLog(_T("CScriptableNPObject::NP_SetProperty\n"));
		return ((CScriptableNPObject*)npobj)->SetProperty(name, value);
	}

	static bool NP_RemoveProperty(NPObject *npobj, NPIdentifier name)
	{
		DebugLog(_T("CScriptableNPObject::NP_RemoveProperty\n"));
		return ((CScriptableNPObject*)npobj)->RemoveProperty(name);
	}

	static bool NP_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
	{
		DebugLog(_T("CScriptableNPObject::NP_Enumerate\n"));
		return ((CScriptableNPObject*)npobj)->Enumerate(identifier, count);
	}

	static bool NP_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
	{
		DebugLog(_T("CScriptableNPObject::NP_Construct\n"));
		return ((CScriptableNPObject*)npobj)->Construct(args, argCount, result);
	}

	static NPClass			m_npClass;
	static NPNetscapeFuncs *m_pBrowserFuncs;

public:
	NPP GetPluginInstance()
	{
		return m_PluginInstance;
	}

	NPNetscapeFuncs* GetBrowserFuncs()
	{
		return m_pBrowserFuncs;
	}

protected:
	JSMethodsMap			m_JSMethods;

	NPP						m_PluginInstance;
};
