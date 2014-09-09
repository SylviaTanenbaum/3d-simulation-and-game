/*
*
* �ļ�����	��	PX2FontManager.cpp
*
*/

#include "PX2FontManager.hpp"
#include "PX2FontGlyphMapFreeType.hpp"
#include "PX2CharCodingGBK.hpp"
#include "PX2CharCodingUTF8.hpp"
#include "PX2FontBitmapImpl.hpp"
#include "PX2FontCommonImpl.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
FontManager::FontManager ()
{
	FontGlyphMapFreeType::InitlizeFreeType();
}
//----------------------------------------------------------------------------
FontManager::~FontManager()
{
	FontGlyphMapFreeType::TerminateFreeType();
}
//----------------------------------------------------------------------------
bool FontManager::Initlize ()
{
	mFonts.clear();
	mDefaultFont = CreateTypeFont(24, 24, "Data/fonts/heiti.ttf", CCT_UTF8,
		FES_NORMAL);

	return true;
}
//----------------------------------------------------------------------------
bool FontManager::Terminate ()
{
	mDefaultFont = 0;
	mFonts.clear();

	return true;
}
//----------------------------------------------------------------------------
void FontManager::DumpTex ()
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i] && Font::FT_COMMON==mFonts[i]->GetFontType())
		{
			mFonts[i]->DumpTex();
		}
	}
}
//----------------------------------------------------------------------------
void FontManager::Update  ()
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i])
			mFonts[i]->UpdateFontTexs();
	}
}
//----------------------------------------------------------------------------
void FontManager::SetNeedUpdate()
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i])
			mFonts[i]->SetNeedUpdate();
	}
}
//----------------------------------------------------------------------------
Font *FontManager::CreateTypeFont (int fontWidth, int fontHeight, 
	const char *fontFilename, CharCodingType codingType,
	unsigned int fontExtStyle)
{
	std::string strFilename = fontFilename;

	if ("Data/fonts/heiti.TTF" == strFilename)
	{
		strFilename = "Data/fonts/heiti.ttf";
	}

	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i]->IsSame(fontWidth, fontHeight, strFilename.c_str(),
			codingType, fontExtStyle))
			return mFonts[i];
	}

	Font *font = new0 FontCommonImpl(FontGlyphMap::GT_FREETYPE);
	if (!font->Initlize(fontWidth, fontHeight, strFilename.c_str(), codingType,
		fontExtStyle))
	{
		assertion(false, "Create Font %s Failed.", strFilename.c_str());
		PX2_LOG_ERROR("Create Font %s Failed.", strFilename.c_str());

		delete0(font);
		font = 0;
		return 0;
	}

	mFonts.push_back(font);

	return font;
}
//----------------------------------------------------------------------------
Font *FontManager::CreateBitmapFont (int fontWidth, int fontHeight, 
	const char *fontFilename, CharCodingType codingType)
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i]->IsSame(fontWidth, fontHeight, fontFilename,
			codingType, 0))
			return mFonts[i];
	}

	FontBitmapImpl *font = new0 FontBitmapImpl();
	if (!font->Initlize(fontWidth, fontHeight, fontFilename, codingType,
		FES_NORMAL))
	{
		delete0(font);
		font = 0;
		return 0;
	}

	mFonts.push_back(font);

	return font;
}
//----------------------------------------------------------------------------
void FontManager::RenderText (TriMesh *mesh, Font *font, const char *text,
	unsigned int style, float x, float y,  const Float2 &space, const Float4 &color, 
	const Float3 &borderShadowColor, float shadowBorderSize, float scale, 
	bool doTransfer, float depth)
{
	if (!font)
	{
		assertion(false, "font must exist.\n");
		return;
	}

	font->TextOutM(mesh, text, x, y, space, color, borderShadowColor, 
		shadowBorderSize, style, doTransfer, scale, depth);
}
//----------------------------------------------------------------------------
void FontManager::RenderText (TriMesh *mesh, Font *font, const char *text, 
	unsigned int style,	unsigned int align, Rectf &rect, const Float2 &space, 
	const Float4 &color, const Float3 &borderShadowColor, 
	float shadowBorderSize, float scale, bool doTransfer)
{
	if (!font)
	{
		assertion(false, "font must exist.\n");
		return;
	}

	int fontWidth = 16;
	int fontHeight = 16;
	font->GetFontSize(fontWidth, fontHeight);
	float lineInterval = 0.0f;
	font->GetLineInterval(lineInterval);

	float textWidth = 0.0f;
	float textHeight = 0.0f;
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	font->GetTextExtent(text, textWidth, textHeight, doTransfer);

	textWidth *= scale;
	textHeight *= scale;

	if (align & TEXTALIGN_LEFT)
	{
		offsetX = rect.Left;
	}
	else if (align & TEXTALIGN_HCENTER)
	{
		offsetX = rect.Left + (rect.Width() - textWidth) / 2.0f;
	}
	else if (align & TEXTALIGN_RIGHT)
	{
		offsetX = rect.Left + (rect.Width() - textWidth);
	}

	if (align & TEXTALIGN_TOP)
	{
		offsetY = rect.Bottom + rect.Height() - (fontHeight+lineInterval)*scale;
	}
	else if (align & TEXTALIGN_VCENTER)
	{
		offsetY = rect.Bottom + rect.Height()/2.0f + textHeight/2.0f - (fontHeight+lineInterval)*scale;
	}
	else if (align & TEXTALIGN_BOTTOM)
	{
		offsetY = rect.Bottom + textHeight - (fontHeight+lineInterval)*scale;
	}

	RenderText(mesh, font, text, style, offsetX, offsetY, space, color,
		borderShadowColor, shadowBorderSize, scale, doTransfer);
}
//----------------------------------------------------------------------------
void FontManager::RenderText (TriMesh *mesh, Font *font, const char *text, 
	unsigned int style, Rectf &rect,  const Float2 &space, float offsetX, float offsetY, bool autoWrap,
	const Float4 &color, const Float3 &borderShadowColor, 
	float shadowBorderSize,  float scale, bool doTransfer)
{
	if (!font)
	{
		assertion(false, "font must exist.\n");
		return;
	}

	font->TextOutRect(mesh, text, rect, space, offsetX, offsetY, autoWrap, color,
		borderShadowColor, shadowBorderSize, style, doTransfer, scale);
}
//----------------------------------------------------------------------------