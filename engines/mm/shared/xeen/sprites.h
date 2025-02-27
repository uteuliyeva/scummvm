/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MM_SHARED_XEEN_SPRITES_H
#define MM_SHARED_XEEN_SPRITES_H

#include "common/scummsys.h"
#include "common/array.h"
#include "common/file.h"
#include "graphics/surface.h"
#include "mm/shared/xeen/file.h"
#include "mm/shared/xeen/xsurface.h"

namespace MM {
namespace Xeen {
class XeenEngine;
class Window;
} // namespace Xeen

namespace Shared {
namespace Xeen {

enum {
	SCALE_MASK = 0x7FFF, SCALE_ENLARGE = 0x8000
};

enum SpriteFlags {
	SPRFLAG_MODE_MASK = 0xF00, SPRFLAG_DRAWER1 = 0x100, SPRFLAG_DRAWER2 = 0x200,
	SPRFLAG_DRAWER3 = 0x300, SPRFLAG_DRAWER4 = 0x400, SPRFLAG_DRAWER5 = 0x500, SPRFLAG_DRAWER6 = 0x600,
	SPRFLAG_DRAWER7 = 0x700, SPRFLAG_800 = 0x800, SPRFLAG_SCENE_CLIPPED = 0x2000,
	SPRFLAG_BOTTOM_CLIPPED = 0x4000, SPRFLAG_HORIZ_FLIPPED = 0x8000, SPRFLAG_RESIZE = 0x10000
};

class SpriteResource {
protected:
	struct IndexEntry {
		uint16 _offset1, _offset2;
	};
	Common::Array<IndexEntry> _index;
	size_t _filesize;
	byte *_data;
	Common::String _filename;
	static int _clippedBottom;

	/**
	 * Load a sprite resource from a stream
	 */
	void load(Common::SeekableReadStream &f);

	/**
	 * Draw the sprite onto the given surface
	 */
	void draw(XSurface &dest, int frame, const Common::Point &destPos,
		const Common::Rect &bounds, uint flags = 0, int scale = 0);

	/**
	 * Deep copy assuming that the current instance is clean
	 */
	void copy(const SpriteResource &src);
public:
	SpriteResource();
	SpriteResource(const Common::String &filename);
	SpriteResource(const SpriteResource &src);

	virtual ~SpriteResource();

	/**
	 * Copy operator for duplicating a sprite resource
	 */
	SpriteResource &operator=(const SpriteResource &src);

	/**
	 * Load a sprite resource from a given file
	 */
	void load(const Common::String &filename);

	/**
	 * Clears the sprite resource
	 */
	void clear();

	/**
	 * Draw a sprite onto a surface
	 * @param dest		Destination surface
	 * @param frame		Frame number
	 * @param destPos	Destination position
	 * @param flags		Flags
	 * @param scale		Scale: 0=No scale, SCALE_ENLARGE=Enlarge it
	 *					1..15   -> reduces the sprite: the higher, the smaller it'll be
	 */
	void draw(XSurface &dest, int frame, const Common::Point &destPos,
		uint flags = 0, int scale = 0);

	/**
	 * Draw the sprite onto the given surface
	 * @param dest		Destination surface
	 * @param frame		Frame number
	 */
	void draw(XSurface &dest, int frame);

	/**
	 * Draw the sprite onto a given surface
	 */
	void draw(Graphics::ManagedSurface *dest, int frame, const Common::Point &destPos);

	/**
	 * Gets the size of a sprite
	 */
	Common::Point getFrameSize(int frame) const;

	/**
	 * Returns the number of frames the sprite resource has
	 */
	size_t size() const {
		return _index.size();
	}

	/**
	 * Returns true if the sprite resource is empty (ie. nothing is loaded)
	 */
	bool empty() const {
		return _index.size() == 0;
	}

	/**
	 * Set the bottom Y position where sprites are clipped if SPRFLAG_BOTTOM_CLIPPED
	 * is applied
	 */
	static void setClippedBottom(int y) {
		_clippedBottom = y;
	}
};

/**
 * Basic sprite drawer
 */
class SpriteDrawer {
private:
	byte *_data = nullptr;
	size_t _filesize = 0;
protected:
	byte *_destTop = nullptr, *_destBottom = nullptr;
	byte *_destLeft = nullptr, *_destRight = nullptr;
	int _pitch = 0;
private:
	/**
	 * Scale a co-ordinate value based on the passed scaling mask
	 */
	static uint getScaledVal(int xy, uint16 &scaleMask);
protected:
	/**
	 * Roll carry right opcode emulation
	 */
	void rcr(uint16 &val, bool &cf);

	/**
	 * Output a pixel
	 */
	virtual void drawPixel(byte *dest, byte pixel);
public:
	/**
	 * Constructor
	 */
	SpriteDrawer(byte *data, size_t filesize) : _data(data), _filesize(filesize) {
	}

	/**
	 * Destructor
	 */
	virtual ~SpriteDrawer() {
	}

	/**
	 * Draw a sprite frame based on a passed offset into the data stream
	 */
	void draw(XSurface &dest, uint16 offset, const Common::Point &pt,
		const Common::Rect &clipRect, uint flags, int scale);
};

class SpriteDrawer1 : public SpriteDrawer {
private:
	byte _offset = 0, _mask = 0;
protected:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer1(byte *data, size_t filesize, int index);
};

/**
 * Scrambles up the sprite by drawing many of the pixels randomly
 * at a horizontal or vertical offset
 */
class SpriteDrawer2 : public SpriteDrawer {
private:
	uint16 _mask1 = 0, _mask2 = 0;
	uint16 _random1 = 0, _random2 = 0;
private:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer2(byte *data, size_t filesize, int index);
};

/**
 * Draws the sprite as faint ghostly, see-through.
 */
class SpriteDrawer3 : public SpriteDrawer {
private:
	uint16 _offset = 0, _mask = 0;
	byte _palette[256 * 3];
	bool _hasPalette = false;
private:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer3(byte *data, size_t filesize, int index);
};

class SpriteDrawer4 : public SpriteDrawer {
private:
	byte _threshold = 0;
protected:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer4(byte *data, size_t filesize, int index);
};

/**
 * Draws a sprite with a fuzziness effect where only some pixels of the sprite are randomly drawn
 */
class SpriteDrawer5 : public SpriteDrawer {
private:
	uint16 _threshold = 0, _random1 = 0, _random2 = 0;
protected:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer5(byte *data, size_t filesize, int index);
};

class SpriteDrawer6 : public SpriteDrawer {
private:
	byte _mask = 0;
protected:
	/**
	 * Output a pixel
	 */
	void drawPixel(byte *dest, byte pixel) override;
public:
	/**
	 * Constructor
	 */
	SpriteDrawer6(byte *data, size_t filesize, int index);
};

} // End of namespace Xeen
} // End of namespace Shared
} // End of namespace MM

#endif
