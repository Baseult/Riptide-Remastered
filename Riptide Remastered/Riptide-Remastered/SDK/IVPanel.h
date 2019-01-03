namespace SDK
{
	class IVPanel
	{
	public:
		const char* GetName(int iPanel);
		void SetMouseInputEnabled(unsigned int panel, bool state);
	};
}