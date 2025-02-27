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

#ifndef MM1_MAPS_MAP50_H
#define MM1_MAPS_MAP50_H

#include "mm/mm1/maps/map.h"

namespace MM {
namespace MM1 {
namespace Maps {

class Map50 : public Map {
	typedef void (Map50:: *SpecialFn)();
private:
	void special00();
	void special01();
	void special02();
	void special03();
	void special04();
	void special05();
	void special06();
	void special07();
	void special08();
	void special09();
	void special10();
	void special11();
	void special12();
	void special13();
	void special14();
	void special15();
	void special16();
	void special17();
	void special18();
	void special19();
	void special20();
	void special21();
	void special22();
	void special23();

	const SpecialFn SPECIAL_FN[24] = {
		&Map50::special00,
		&Map50::special01,
		&Map50::special02,
		&Map50::special03,
		&Map50::special04,
		&Map50::special05,
		&Map50::special06,
		&Map50::special07,
		&Map50::special08,
		&Map50::special09,
		&Map50::special10,
		&Map50::special11,
		&Map50::special12,
		&Map50::special13,
		&Map50::special14,
		&Map50::special15,
		&Map50::special16,
		&Map50::special17,
		&Map50::special18,
		&Map50::special19,
		&Map50::special20,
		&Map50::special21,
		&Map50::special22,
		&Map50::special23
	};
public:
	Map50() : Map(50, "pp1", 0xf01, 3) {}

	/**
	 * Handles all special stuff that happens on the map
	 */
	void special() override;
};

} // namespace Maps
} // namespace MM1
} // namespace MM

#endif
