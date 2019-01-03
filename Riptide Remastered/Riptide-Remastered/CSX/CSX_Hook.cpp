#include "CSX_Hook.h"
//[junk_enable /]
namespace CSX
{
	namespace Hook
	{
		PVOID WriteVTable(PVOID pTablePtr, PVOID pFuncAddress, DWORD dwIndex)
		{
			if (IsBadReadPtr(pTablePtr, sizeof(PVOID)))
				return nullptr;

			DWORD dwOffset = dwIndex * sizeof(PVOID);

			PVOID pFunc = (PVOID)((DWORD)pTablePtr + dwOffset);
			PVOID Func_o = (PVOID)*(PDWORD)pFunc;

			if (IsBadReadPtr(pFunc, sizeof(PVOID)))
				return nullptr;

			DWORD dwOld = 0;
			VirtualProtect(pFunc, sizeof(PVOID), PAGE_READWRITE, &dwOld);

			*(PDWORD)pFunc = (DWORD)pFuncAddress;

			VirtualProtect(pFunc, sizeof(PVOID), dwOld, &dwOld);

			return Func_o;
		}

		VTable::VTable()
		{
			pPtrPtrTable = nullptr;
			pPtrOldTable = nullptr;
			pPtrNewTable = nullptr;
			pPtrPtrTable = nullptr;

			dwCountFunc = 0;
			dwSizeTable = 0;
		}

		bool VTable::InitTable(PVOID pTablePtrPtr)
		{
			if (IsBadReadPtr(pTablePtrPtr, sizeof(PVOID)))
				return false;

			pPtrPtrTable = (PVOID*)pTablePtrPtr;
			pPtrOldTable = (PVOID*)(*(PDWORD)pPtrPtrTable);

			while (!CSX::Utils::IsBadReadPtr(pPtrOldTable[dwCountFunc]))
				dwCountFunc++;

			

			if (dwCountFunc)
			{
				dwSizeTable = sizeof(PVOID) * dwCountFunc;

				pPtrNewTable = (PVOID*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeTable);
				memcpy(pPtrNewTable, pPtrOldTable, dwSizeTable);

				*(PDWORD)pPtrPtrTable = (DWORD)pPtrNewTable;

				return true;
			}

			return false;
		}

		void VTable::HookIndex(DWORD dwIndex, PVOID pNewAddress)
		{
			if (pPtrNewTable)
				((PVOID*)pPtrNewTable)[dwIndex] = pNewAddress;
		}

		PVOID VTable::GetFuncAddress(DWORD dwIndex)
		{
			if (pPtrOldTable)
			{
				PVOID pAddres = ((PVOID*)pPtrOldTable)[dwIndex];
				return pAddres;
			}

			return nullptr;
		}

		PVOID VTable::GetHookIndex(DWORD dwIndex, PVOID pNewAddress)
		{
			if (pPtrNewTable)
			{
				PVOID pOld = ((PVOID*)pPtrNewTable)[dwIndex];
				((PVOID*)pPtrNewTable)[dwIndex] = pNewAddress;
				return pOld;
			}

			return nullptr;
		}

		void VTable::UnHook()
		{
			if (!CSX::Utils::IsBadReadPtr(pPtrPtrTable))
				*(PDWORD)pPtrPtrTable = (DWORD)pPtrOldTable;
		}

		void VTable::ReHook()
		{
			if (!CSX::Utils::IsBadReadPtr(pPtrPtrTable))
				*(PDWORD)pPtrPtrTable = (DWORD)pPtrNewTable;
		}



		BOOL	VTHookManager::NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
		{
			typedef LONG * NTAPI LPFN_NtProtectVirtualMemory(HANDLE, PVOID *, PULONG, ULONG, PULONG);
			LPFN_NtProtectVirtualMemory * NtProtectVirtualMemory = (LPFN_NtProtectVirtualMemory*)(GetProcAddress(GetModuleHandleA(("ntdll.dll")), ("NtProtectVirtualMemory")));

			if (!NtProtectVirtualMemory)
				return FALSE;

			NtProtectVirtualMemory(GetCurrentProcess(), (PVOID*)&lpAddress, (PULONG)&dwSize, flNewProtect, lpflOldProtect);

			return TRUE;
		}


		VTHookManager::VTHookManager()
		{
			DWORD oProtection;
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, PAGE_READWRITE, &oProtection);
			memset(this, 0, sizeof(VTHookManager));
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, oProtection, &oProtection);
		}

		VTHookManager::VTHookManager(PDWORD* ppdwClassBase)
		{
			bInitialize(ppdwClassBase);
		}

		VTHookManager::~VTHookManager()
		{
			UnHook();
		}

		bool 	VTHookManager::bInitialize(PDWORD* ppdwClassBase)
		{
			m_ppdwClassBase = ppdwClassBase;
			m_pdwOldVMT = *ppdwClassBase;
			m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
			m_pdwNewVMT = new DWORD[m_dwVMTSize];
			DWORD oProtection;
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, PAGE_READWRITE, &oProtection);
			memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD)* m_dwVMTSize);
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, oProtection, &oProtection);
			*ppdwClassBase = m_pdwNewVMT;
			return true;
		}

		bool 	VTHookManager::bInitialize(PDWORD** pppdwClassBase)
		{
			return bInitialize(*pppdwClassBase);
		}

		void	VTHookManager::UnHook() const
		{
			if (m_ppdwClassBase)
				*m_ppdwClassBase = m_pdwOldVMT;

		}

		void 	VTHookManager::ReHook() const
		{
			if (m_ppdwClassBase)
				*m_ppdwClassBase = m_pdwNewVMT;

		}

		int 	VTHookManager::iGetFuncCount() const
		{
			return static_cast<int>(m_dwVMTSize);
		}

		DWORD 	VTHookManager::dwGetMethodAddress(int Index) const
		{
			if (Index >= 0 && Index <= static_cast<int>(m_dwVMTSize) && m_pdwOldVMT != nullptr)
				return m_pdwOldVMT[Index];

			return NULL;
		}

		PDWORD 	VTHookManager::pdwGetOldVMT() const
		{
			return m_pdwOldVMT;
		}

		DWORD 	VTHookManager::dwHookMethod(DWORD dwNewFunc, unsigned int iIndex) const
		{
			if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
			{
				m_pdwNewVMT[iIndex] = dwNewFunc;
				return m_pdwOldVMT[iIndex];
			}

			return 0;
		}

		DWORD 	VTHookManager::dwUnHookMethod(unsigned int iIndex) const
		{
			if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
			{
				m_pdwNewVMT[iIndex] = m_pdwOldVMT[iIndex];
				return m_pdwOldVMT[iIndex];
			}

			return NULL;
		}

		DWORD  VTHookManager::dwGetVMTCount(PDWORD pdwVMT)
		{
			DWORD dwIndex = 0;

			for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
			{
				if (IsBadCodePtr(reinterpret_cast<FARPROC>(pdwVMT[dwIndex])))
					break;

			}
			return dwIndex;
		}

	}
}