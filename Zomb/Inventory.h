#pragma once
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Stats.h"
#include "Media.h"
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	const std::vector<std::pair<int, bool> > &getItems();
	Stats getEquipmentStats();
	Weapon *getWeapon();

	bool inventoryFull();
	void addToInventory(ITEMS itemType);

	void applyStatusEffects(Player *p);

	void saveInventory();
	void loadInventory();

	void sellItem(int index);

	friend class InventoryState;
	friend class StatHoverWindow;
private:
	Weapon *getWeaponFrom(ITEMS itemType);
public:

private:
	// (item ID, is equipped)
	std::vector<std::pair<int, bool> > items;
};