/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidCraftingModuleDataComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/ZoneServer.h"
#include "templates/tangible/DroidCraftingModuleTemplate.h"

DroidCraftingModuleDataComponent::DroidCraftingModuleDataComponent() : craftingType(0), craftingBonus(0) {
	setLoggingName("DroidCraftingModule");
}

DroidCraftingModuleDataComponent::~DroidCraftingModuleDataComponent() {

}

String DroidCraftingModuleDataComponent::getModuleName() const {
	if (isClothingArmor())
		return "crafting_clothing";
	else if (isWeaponDroidGeneric())
		return "crafting_weapon";
	else if (isFoodChemical())
		return "crafting_food";
	else if (isStructureFurniture())
		return "crafting_structure";
	else if (isShip())
		return "crafting_ship";

	return "crafting_unknown";
}

void DroidCraftingModuleDataComponent::initializeTransientMembers() {
	// load template data here
	SceneObject* craftedModule = getParent();
	if (craftedModule == nullptr) {
		return;
	}

	craftingStation = nullptr;

	Reference<DroidCraftingModuleTemplate*> moduleTemplate = cast<DroidCraftingModuleTemplate*>(craftedModule->getObjectTemplate());
	if (moduleTemplate == nullptr) {
		info("Module was null");
		return;
	}

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == nullptr) {
		info("droidComponent was null");
		return;
	}

	if( droidComponent->hasKey( "mechanism_quality") ){
		craftingBonus = droidComponent->getAttributeValue( "mechanism_quality");
	}else{
		info( "mechanism_quality attribute not found" );
	}

	craftingType = moduleTemplate->getCraftingType();
	attributeListString = moduleTemplate->getAttributeListString();
}

void DroidCraftingModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	craftingBonus = values->getCurrentValue("mechanism_quality");
}

void DroidCraftingModuleDataComponent::initialize(DroidObject* droid) {
	// do we need to change any droid stats: no
}

void DroidCraftingModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute(attributeListString, craftingBonus);
}

void DroidCraftingModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// no menu options
}

int DroidCraftingModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	// no menu options
	return 0;
}

void DroidCraftingModuleDataComponent::loadSkillMods(CreatureObject* player) {
	// no op
}

void DroidCraftingModuleDataComponent::unloadSkillMods(CreatureObject* player) {
	// no op
}

bool DroidCraftingModuleDataComponent::skillsByRange() {
	// no op
	return false;
}

void DroidCraftingModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker) {
	// no op
}

int DroidCraftingModuleDataComponent::getBatteryDrain() {
	return 0;
}

void DroidCraftingModuleDataComponent::deactivate() {
	// no op
}

bool DroidCraftingModuleDataComponent::actsAsCraftingStation() {
	return true;
}

String DroidCraftingModuleDataComponent::toString() const {
	return BaseDroidModuleComponent::toString();
}

// crafting droid module specific
CraftingStation* DroidCraftingModuleDataComponent::getCraftingStation() {
	return craftingStation;
}

bool DroidCraftingModuleDataComponent::isWeaponDroidGeneric() const {
	return craftingType == CraftingTool::WEAPON;
}

bool DroidCraftingModuleDataComponent::isFoodChemical() const {
	return craftingType == CraftingTool::FOOD;
}

bool DroidCraftingModuleDataComponent::isClothingArmor() const {
	return craftingType == CraftingTool::CLOTHING;
}

bool DroidCraftingModuleDataComponent::isStructureFurniture() const {
	return craftingType == CraftingTool::STRUCTURE;
}

bool DroidCraftingModuleDataComponent::isShip() const {
	return craftingType == CraftingTool::SPACE;
}

bool DroidCraftingModuleDataComponent::validCraftingType(int type) {
	return craftingType == type;
}

void DroidCraftingModuleDataComponent::onCall() {
	SceneObject* craftedModule = getParent();
	Reference<DroidCraftingModuleTemplate*> moduleTemplate = cast<DroidCraftingModuleTemplate*>(craftedModule->getObjectTemplate());
	if (craftingStation == nullptr) {
		String stationTemplate = moduleTemplate->getCraftingStationTemplate();
		craftingStation = (craftedModule->getZoneServer()->createObject(stationTemplate.hashCode(), 0)).castTo<CraftingStation*>();
		craftingStation->setEffectiveness(craftingBonus);
	}
}

void DroidCraftingModuleDataComponent::onStore() {
	craftingStation = nullptr;
}

void DroidCraftingModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidCraftingModuleDataComponent* otherModule = cast<DroidCraftingModuleDataComponent*>(other);
	if( otherModule == nullptr ){
		return;
	}

	craftingBonus = otherModule->craftingBonus;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == nullptr){
		return;
	}
	droidComponent->addProperty("mechanism_quality", craftingBonus, 0, "exp_effectiveness");
}
