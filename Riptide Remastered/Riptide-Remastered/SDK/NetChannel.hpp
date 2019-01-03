#include "../Engine/Engine.h"

namespace SDK
{
	class NetChannel
	{
	public:



		uint8_t pad_0x0000[0x17];
		bool m_bShouldDelete;
		int m_nOutSequenceNr;
		int m_nInSequenceNr;
		int m_nOutSequenceNrAck;
		int m_nOutReliableState;
		int m_nInReliableState;
		int m_nChokedPackets;
	};
}

NetChannel* GetNetChannel()
{
	auto client_state = *reinterpret_cast<uintptr_t*>(uintptr_t(GetModuleHandle("engine.dll")) + 0x57F85C);

	if (!client_state)
		return nullptr;

	auto net_channel = *reinterpret_cast<uintptr_t*>(client_state + 0x9C);
	return reinterpret_cast<NetChannel*>(net_channel);
}
