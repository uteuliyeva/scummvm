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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MM1_VIEWS_ENH_LOCATIONS_LOCATION_H
#define MM1_VIEWS_ENH_LOCATIONS_LOCATION_H

#include "mm/mm1/views_enh/scroll_view.h"

namespace MM {
namespace MM1 {
namespace ViewsEnh {
namespace Locations {

class Location : public ScrollView {
protected:
	/**
	 * Called when an active timeout countdown expired
	 */
	void timeout() override {
		leave();
	}

	/**
	 * Change character
	 */
	virtual void changeCharacter(uint index);

	/**
	 * Subtract gold from current character
	 */
	bool subtractGold(uint amount);

	/**
	 * Display a message
	 */
	void displayMessage(const Common::String &msg);

	/**
	 * Displays not enough gold
	 */
	void notEnoughGold();

	/**
	 * Displays backpack is full
	 */
	void backpackFull();

public:
	Location(const Common::String &name);

	/**
	 * Leave the location, turning around
	 */
	void leave();
};

} // namespace Locations
} // namespace ViewsEnh
} // namespace MM1
} // namespace MM

#endif
