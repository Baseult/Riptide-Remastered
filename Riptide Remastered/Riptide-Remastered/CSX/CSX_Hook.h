#pragma once

#include "CSX.h"

namespace CSX
{
	namespace Hook
	{
		PVOID WriteVTable(PVOID pTablePtr, PVOID pFuncAddress, DWORD dwIndex);

		class VTable
		{
		public:

			VTable();
			//[swap_lines]
			bool InitTable(PVOID pTablePtrPtr);

			void HookIndex(DWORD dwIndex, PVOID pNewAddress);

			PVOID GetFuncAddress(DWORD dwIndex);
			PVOID GetHookIndex(DWORD dwIndex, PVOID pNewAddress);

			void UnHook();
			void ReHook();
			//[/swap_lines]
		private:
			//[swap_lines]
			PVOID * pPtrPtrTable;
			PVOID* pPtrOldTable;
			PVOID* pPtrNewTable;

			DWORD dwCountFunc;
			DWORD dwSizeTable;
			//[/swap_lines]
		};


		class VTHookManager
		{
		private:
			BOOL NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
		public:
			VTHookManager();
			explicit VTHookManager(PDWORD* ppdwClassBase);
			~VTHookManager();
			bool bInitialize(PDWORD* ppdwClassBase);
			bool bInitialize(PDWORD** pppdwClassBase);
			void UnHook() const;

			void ReHook() const;

			int iGetFuncCount() const;
			DWORD dwGetMethodAddress(int Index) const;

			PDWORD pdwGetOldVMT() const;
			DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex) const;

			DWORD dwUnHookMethod(unsigned int iIndex) const;
			PDWORD m_pdwNewVMT, m_pdwOldVMT;
		private:
			static DWORD dwGetVMTCount(PDWORD pdwVMT);

			PDWORD* m_ppdwClassBase;
			DWORD m_dwVMTSize;
		};
	}
}