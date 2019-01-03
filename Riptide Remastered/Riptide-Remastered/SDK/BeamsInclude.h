#include "../SDK/IViewRenderBeams.h"
#include "../Cheat/Client.h"

namespace SDK
{
	class shit
	{
	public:
		static IViewRenderBeams* g_pViewRenderBeams();
	private:
		static IViewRenderBeams* g_ViewRenderBeams;
	};
}