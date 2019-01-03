#pragma once

#include "Render2.h"

// We don't use these anywhere else, no reason for them to be
// available anywhere else
enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE2 = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum FontRenderFlag_t
{
	FONT_LEFT = 0,
	FONT_RIGHT = 1,
	FONT_CENTER = 2
};

enum FontCreateFlag_t
{
	FONT_CREATE_NONE = 0,
	FONT_CREATE_BOLD = 1,
	FONT_CREATE_ITALIC = 2,
	FONT_CREATE_OUTLINE = 4,
	FONT_CREATE_SPRITE = 8,
	FONT_CREATE_ANTIALIASED = 16
};

// Initialises the rendering system, setting up fonts etc
void Render::SetupFonts()
{
	font.Default = 0x1D; // MainMenu Font from vgui_spew_fonts 
	font.DEF = Interfaces::Surface()->FontCreate();

	Interfaces::Surface()->SetFontGlyphSet(font.DEF, "Arial", 16, 500, 0, 0, FONTFLAG_OUTLINE2);
}

RECT Render::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	Interfaces::Engine()->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

void Render::Clear(int x, int y, int w, int h, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawFilledRect(x, y, x + w, y + h);
}

void Render::DrawRect(int x, int y, int w, int h, Color col)
{
	Interfaces::Surface()->DrawSetColor(col);
	Interfaces::Surface()->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::DrawOutlineRect(int x, int y, int w, int h, Color color)
{
	DrawRect(x, y, w, h, Color::Black());
	DrawRect(x + 1, y + 1, w - 2, h - 2, color);
	DrawRect(x + 2, y + 2, w - 4, h - 4, Color::Black());
}

void Render::DrawString2(DWORD font, int x, int y, Color color, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	uint8_t r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	int width, height;

	Interfaces::Surface()->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextColor(r, g, b, a);
	Interfaces::Surface()->DrawSetTextPos(x, y - height / 2);
	Interfaces::Surface()->DrawPrintText(wbuf, wcslen(wbuf));
}




void Render::DrawHeader(int x, int y, int w, int HealthBarWidth)
{
	int i = 0;
	int xCoord = x;
	int yCoord = y;

	for (i = 0; i < 5; i++)
	{
		FillRGBA(x - i, y + i, w, 1, Color::Black());

		FillRGBA(x - i, y + i, HealthBarWidth + 2, 1, Color(0, 250, 0));

		FillRGBA(x - 3, y + 3, HealthBarWidth + 2, 1, Color(0, 170, 0));

		FillRGBA(x - 4, y + 4, HealthBarWidth + 2, 1, Color(0, 170, 0));
	}

	FillRGBA(x, y, w, 1, Color::White());

	FillRGBA((x + 1) - 5, y + 5, w, 1, Color::White());

	for (i = 0; i < 5; i++)
	{
		FillRGBA(x, y, 1, 1, Color::White());
		x--;
		y++;
	}

	x = xCoord;
	y = yCoord;

	for (i = 0; i < 5; i++)
	{
		if (i != 0)
			FillRGBA(x + w, y, 1, 1, Color::White());

		x--;
		y++;
	}


	

}

void Render::OutlineRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
{
	Color colColor(0, 0, 0);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		DrawOutlineRect(x + i, y, 1, height, colRainbow);
	}
}

void Render::Pixel(int x, int y, Color col)
{
	Interfaces::Surface()->DrawSetColor(col);
	Interfaces::Surface()->DrawFilledRect(x, y, x + 1, y + 1);
}

void Render::Line(int x, int y, int x2, int y2, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawLine(x, y, x2, y2);
}

void Render::PolyLine(int *x, int *y, int count, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawPolyLine(x, y, count);
}

bool Render::WorldToScreen(Vector &in, Vector &out)
{
	const VMatrix& worldToScreen = Interfaces::Engine()->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	out.z = 0; //Screen doesn't have a 3rd dimension.

	if (w > 0.001) //If the object is within view.
	{
		RECT ScreenSize = GetViewport();
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f); //Get the X dimension and push it in to the Vector.
		out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void Render::Text(int x, int y, Color color, DWORD font, const char* text, ...)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	Interfaces::Surface()->DrawSetTextFont(font);

	Interfaces::Surface()->DrawSetTextColor(color);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(wcstring, wcslen(wcstring));
}

void Render::OutlinedBox2(int x, int y, int w, int h, Color color)
{
	DrawRect(x, y, w, h, Color::Black());
	DrawRect(x + 1, y + 1, w - 2, h - 2, color);
}



void Render::DrawRectFilled(int x0, int y0, int x1, int y1, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawFilledRect(x0, y0, x1, y1);
}

void Render::DrawVerBar(int x, int y, int w, int h, int val, Color color1, Color color2)
{
	if (val > 100) val = 100;
	int size = (h * val) / 100;

	DrawRect(x, y, w, h, Color(0, 0, 0));
	FillRGBA(x + 1, y + 1, w - 2, h - 2, color2);

	if (size == h)
		FillRGBA(x + 1, y + 1 + h - size, w - 2, size - 2, color1);
	else
		FillRGBA(x + 1, y + 1 + h - size, w - 2, size, color1);
}

void Render::FillRGBA(int x, int y, int w, int h, Color c)
{
	Interfaces::Surface()->DrawSetColor(c);
	Interfaces::Surface()->DrawFilledRect(x, y, x + w, y + h);
}


void Render::TexturedPolygon(int n, std::vector<SDK::Vertex_t> vertice, Color color)
{
	static int texture_id = Interfaces::Surface()->CreateNewTextureID(true); // 
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	Interfaces::Surface()->DrawSetTextureRGBA(texture_id, buf, 1, 1); //
	Interfaces::Surface()->DrawSetColor(color); //
	Interfaces::Surface()->DrawSetTexture(texture_id); //
	Interfaces::Surface()->DrawTexturedPolygon(n, vertice.data()); //
}

void Render::DrawFilledCircle(Vector2D center, Color color, float radius, float points) {
	std::vector<Vertex_t> vertices;
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + center.x, radius * sinf(a) + center.y)));

	TexturedPolygon((int)points, vertices, color);
}

void Render::Text(int x, int y, Color color, DWORD font, const wchar_t* text)
{
	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextColor(color);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(text, wcslen(text));
}

void Render::Text(int x, int y, DWORD font, const wchar_t* text)
{
	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(text, wcslen(text));
}

void Render::Textf(int x, int y, Color color, DWORD font, const char* fmt, ...)
{
	if (!fmt) return; //if the passed string is null return
	if (strlen(fmt) < 2) return;

	//Set up va_list and buffer to hold the params 
	va_list va_alist;
	char logBuf[256] = { 0 };

	//Do sprintf with the parameters
	va_start(va_alist, fmt);
	_vsnprintf_s(logBuf + strlen(logBuf), 256 - strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	Text(x, y, color, font, logBuf);
}

/*RECT Render::GetTextSize(DWORD font, const char* text)
{
char Buffer[1024] = { '\0' };

/* set up varargs*
va_list Args;

va_start(Args, text);
vsprintf_s(Buffer, text, Args);
va_end(Args);

size_t Size = strlen(Buffer) + 1;
wchar_t* WideBuffer = new wchar_t[Size];

mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);

RECT rect;
int x, y;
Interfaces::Surface()->GetTextSize(font, WideBuffer, x, y);
rect.left = x;
rect.bottom = y;
rect.right = x;
return rect;
}*/

void Render::DrawCoalBox(int x, int y, int w, int h, Color color)
{
	int iw = w / 4;
	int ih = h / 4;
	// top
	Line(x, y, x + iw, y, color);					// left
	Line(x + w - iw, y, x + w, y, color);			// right
	Line(x, y, x, y + ih, color);					// top left
	Line(x + w - 1, y, x + w - 1, y + ih, color);	// top right
													// bottom
	Line(x, y + h, x + iw, y + h, color);			// left
	Line(x + w - iw, y + h, x + w, y + h, color);	// right
	Line(x, y + h - ih, x, y + h, color);			// bottom left
	Line(x + w - 1, y + h - ih, x + w - 1, y + h, color);	// bottom right
}

void Render::DrawOutlineCoalBox(int x, int y, int w, int h, Color color)
{
	int iw = w / 4;
	int ih = h / 4;
	DrawCoalBox(x, y, w, h, Color::Black());

	// top left
	Line(x + 1, y + 1, x + iw, y + 1, color);
	Line(x + iw, y, x + iw, y + 2, Color::Black());
	Line(x + 1, y + 1, x + 1, y + ih, color);
	Line(x, y + ih, x + 2, y + ih, Color::Black());

	// top right
	Line(x + w - iw, y + 1, x + w - 1, y + 1, color);
	Line(x + w - iw - 1, y, x + w - iw, y + 2, Color::Black());
	Line(x + w - 2, y + 1, x + w - 2, y + ih, color);
	Line(x + w - 2, y + ih, x + w, y + ih, Color::Black());

	// bottom left
	Line(x + 1, y + h - ih, x + 1, y + h, color);
	Line(x, y + h - ih - 1, x + 2, y + h - ih - 1, Color::Black());
	Line(x + 1, y + h - 1, x + iw, y + h - 1, color);
	Line(x + iw, y + h - 1, x + iw, y + h + 1, Color::Black());

	// bottom right
	Line(x + w - iw, y + h - 1, x + w - 1, y + h - 1, color);
	Line(x + w - iw - 1, y + h - 1, x + w - iw, y + h + 1, Color::Black());
	Line(x + w - 2, y + h - ih, x + w - 2, y + h, color);
	Line(x + w - 2, y + h - ih - 1, x + w, y + h - ih - 1, Color::Black());

	DrawCoalBox(x + 2, y + 2, w - 4, h - 4, Color::Black());
}

void Render::BoxDefault(DrawData Data, Color pColor)
{
	Interfaces::Surface()->DrawSetColor(pColor);
	Interfaces::Surface()->DrawOutlinedRect(Data.Left, Data.Up, Data.Right, Data.Down);
}

void Render::GradientV(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = float(i), fh = float(h);
		float a = float(fi / fh);
		DWORD ia = DWORD(a * 255);
		Clear(x, y + i, w, 1, Color(first, second, third, ia));
	}
}

void Render::GradientH(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = float(i), fw = float(w);
		float a = float(fi / fw);
		DWORD ia = DWORD(a * 255);
		Clear(x + i, y, 1, h, Color(first, second, third, ia));
	}
}

void Render::Polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = Interfaces::Surface()->CreateNewTextureID(true); //need to make a texture with procedural true
	unsigned char buffer[4] = { 255, 255, 255, 255 };//{ color.r(), color.g(), color.b(), color.a() };

	Interfaces::Surface()->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
	Interfaces::Surface()->DrawSetColor(color); // keep this full color and opacity use the RGBA @top to set values.
	Interfaces::Surface()->DrawSetTexture(Texture); // bind texture

	Interfaces::Surface()->DrawTexturedPolygon(count, Vertexs);
}

void Render::PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Polygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = int(Vertexs[i].m_Position.x);
		y[i] = int(Vertexs[i].m_Position.y);
	}

	PolyLine(x, y, count, colorLine);
}

void Render::PolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = int(Vertexs[i].m_Position.x);
		y[i] = int(Vertexs[i].m_Position.y);
	}

	PolyLine(x, y, count, colorLine);
}

void Render::DrawWave(Vector loc, float radius, Color color)
{
	static float Step = M_PI * 3.0f / 40;
	Vector prev;
	for (float lat = 0; lat <= M_PI * 3.0f; lat += Step)
	{
		float sin1 = sin(lat);
		float cos1 = cos(lat);
		float sin3 = sin(0.0);
		float cos3 = cos(0.0);

		Vector point1;
		point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
		Vector point3 = loc;
		Vector Out;
		point3 += point1;

		if (WorldToScreen(point3, Out))
		{
			if (lat > 0.000) {

				Line(prev.x, prev.y, Out.x, Out.y, color);
			}
		}
		prev = Out;
	}
}

void Render::DrawCircle3D(Vector position, float points, float radius, Color Color)
{
	float Step = (float)M_PI * 2.0f / points;

	std::vector<Vector> points3d;

	for (float a = 0; a < (M_PI * 2.0f); a += Step)
	{
		Vector Start(radius * cosf(a) + position.x, radius * sinf(a) + position.y, position.z);
		Vector End(radius * cosf(a + Step) + position.x, radius * sinf(a + Step) + position.y, position.z);

		Vector start2d, end2d;

		if (!WorldToScreen(Start, start2d) || !WorldToScreen(End, end2d))
			return;

		Line(start2d.x, start2d.y, end2d.x, end2d.y, Color);
	}
}

void Render::OutlineCircle(int x, int y, int r, int seg, Color color)
{
	Interfaces::Surface()->DrawSetColor(0, 0, 0, 255);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r - 1, seg);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r + 1, seg);
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r, seg);
}

Render* g_Render = new(Render);