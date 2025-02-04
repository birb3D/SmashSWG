/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDCRAFTINGMODULEDATACOMPONENT_H_
#define DROIDCRAFTINGMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class DroidCraftingModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int craftingType;
	int craftingBonus;
	String attributeListString;
	ManagedReference<CraftingStation*> craftingStation;

public:
	DroidCraftingModuleDataComponent();

	~DroidCraftingModuleDataComponent();

	String getModuleName() const;

	void initializeTransientMembers();

	void initialize(DroidObject* droid);

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);

	void loadSkillMods(CreatureObject* player);

	void unloadSkillMods(CreatureObject* player);

	bool skillsByRange();

	void handlePetCommand(String cmd, CreatureObject* speaker);

	int getBatteryDrain();

	void deactivate();

	bool actsAsCraftingStation();

	String toString() const;

	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	// crafting droid module specific
	CraftingStation* getCraftingStation();

	bool isWeaponDroidGeneric() const;

	bool isFoodChemical() const;

	bool isClothingArmor() const;

	bool isStructureFurniture() const;

	bool isShip() const;

	bool validCraftingType(int type);

	void onCall();

	void onStore();

	void copy(BaseDroidModuleComponent* other);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDCRAFTINGMODULEDATACOMPONENT_H_ */
