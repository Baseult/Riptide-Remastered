#pragma once
#pragma warning
#include "Vector.hpp"
#include "..\SDK\Definitions.hpp"
#include "Color.hpp" 

namespace SDK
{
	class IDebugOverlay
	{
	public:
		virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
		virtual void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration) = 0;
		virtual void AddSphereOverlay(const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration) = 0;
		virtual void AddTriangleOverlay(const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
		virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
		virtual void AddTextOverlay(const Vector& origin, float duration, const char *format, ...) = 0;
		virtual void AddTextOverlay(const Vector& origin, int line_offset, float duration, const char *format, ...) = 0;
		virtual void AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
		virtual void AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const Vector & angles, int r, int g, int b, int a, float flDuration) = 0;
		virtual void AddGridOverlay(const Vector& origin) = 0;
		virtual void AddCoordFrameOverlay(const matrix3x4_t& frame, float flScale, int vColorTable[3][3] = NULL) = 0;

		void AddCapsuleOverlay(Vector& mins, Vector& maxs, float pillradius, int r, int g, int b, int a, float duration)

		{

			return GetMethod<void(__thiscall*)(void*, Vector&, Vector&, float&, int, int, int, int, float)>(this, 24)(this, mins, maxs, pillradius, r, g, b, a, duration);

		}

		int ScreenPosition(const Vector &vecOrigin, Vector &vecScreen)
		{
			VirtualFn(int)(PVOID, const Vector &, Vector &);
			return GetMethod< OriginalFn >(this, 13)(this, vecOrigin, vecScreen);
		}
		virtual int ScreenPosition(float flXPos, float flYPos, Vector& screen) = 0;

		virtual void *GetFirst(void) = 0;
		virtual void *GetNext(void *current) = 0;
		virtual void ClearDeadOverlays(void) = 0;
		virtual void ClearAllOverlays() = 0;

		virtual void AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
		virtual void AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;

		virtual void AddLineOverlayAlpha(const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
		virtual void AddBoxOverlay2(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, const Color& faceColor, const Color& edgeColor, float duration) = 0;

		virtual void PurgeTextOverlays() = 0;
	};
}