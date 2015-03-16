class CVMTHookManager64
{
public:
	CVMTHookManager64(void)
	{
		std::cout << "Initialized void \n";
		memset(this, 0, sizeof(CVMTHookManager64));
	}

	CVMTHookManager64(PDWORD64* ppdwClassBase)
	{
		std::cout << "Initialized base \n";
		bInitialize(ppdwClassBase);
	}

	~CVMTHookManager64(void)
	{
		UnHook();
	}

	bool bInitialize(PDWORD64* ppdwClassBase)
	{
		std::cout << "Entered initialize \n";
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD64[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64)*m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
		std::cout << "Exited initialized \n";
		return true;
	}

	bool bInitialize(PDWORD64** pppdwClassBase)
	{
		std::cout << "Initialize 2 \n";
		return bInitialize(*pppdwClassBase);
	}
	void UnHook(void)
	{
		dwHookMethod(oFunction, unhookindex);
	}

	void ReHook(void)
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount(void)
	{
		return(int)m_dwVMTSize;
	}

	DWORD64 dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
		{
			std::cout << "get address \n";
			oFunction = m_pdwOldVMT[Index];
			unhookindex = Index;
			std::cout << "end address \n";
			return m_pdwOldVMT[Index];
		}
	}

	PDWORD64 pdwGetOldVMT(void)
	{
		return m_pdwOldVMT;
	}

	DWORD64 dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT &&iIndex <= m_dwVMTSize&&iIndex >= 0)
		{
			std::cout << "start hook \n";
			m_pdwNewVMT[iIndex] = dwNewFunc;
			std::cout << "end hook \n";
			return m_pdwOldVMT[iIndex];
		}
		return NULL;
	}
private:
	DWORD64 dwGetVMTCount(PDWORD64 pdwVMT)
	{
		DWORD dwIndex = 0;
		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (!IsValidPtr((PVOID)pdwVMT[dwIndex]))
			{
				std::cout << "Index Count: " << dwIndex << "\n";
				break;
			}
		}
		std::cout << "Index Count: " << dwIndex << "\n";
		return dwIndex;
	}

	PDWORD64* m_ppdwClassBase;
	PDWORD64 m_pdwNewVMT, m_pdwOldVMT;
	DWORD64 m_dwVMTSize, oFunction;
	int unhookindex;
};