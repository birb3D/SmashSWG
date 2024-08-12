/*
 * WearablesDeltaVector.h
 *
 *  Created on: 09/04/2012
 *      Author: victor
 */

#ifndef WEARABLESDELTAVECTOR_H_
#define WEARABLESDELTAVECTOR_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "templates/tangible/ArmorObjectTemplate.h"

class WearablesDeltaVector : public DeltaVector<ManagedReference<TangibleObject*> > {
private:
	// note: duplicate of CombatManager::hitlocations.
	enum HitLocation : int {
		HIT_BODY = 0,
		HIT_HEAD = 1,
		HIT_RARM = 2,
		HIT_LARM = 3,
		HIT_RLEG = 4,
		HIT_LLEG = 5,
		HIT_NUM = 6,
	};

protected:
	VectorMap<uint8, Vector<ManagedReference<ArmorObject*> > > protectionArmorMap;

public:

	WearablesDeltaVector() : DeltaVector<ManagedReference<TangibleObject*> >() {
		protectionArmorMap.setAllowOverwriteInsertPlan();

		//addSerializableVariable("protectionArmorMap", &protectionArmorMap);
	}

	bool readObjectMember(ObjectInputStream* stream, const String& name) {
		if (name == "protectionArmorMap") {
			TypeInfo<VectorMap<uint8, Vector<ManagedReference<ArmorObject*> > >>::parseFromBinaryStream(&protectionArmorMap, stream);

			return true;
		}

		return DeltaVector<ManagedReference<TangibleObject*> >::readObjectMember(stream, name);
	}

	int writeObjectMembers(ObjectOutputStream* stream) {
		static String _name = "protectionArmorMap";
		int _offset;
		uint32 _totalSize;

		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<VectorMap<uint8, Vector<ManagedReference<ArmorObject*> > >>::toBinaryStream(&protectionArmorMap, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		return 1 + DeltaVector<ManagedReference<TangibleObject*> >::writeObjectMembers(stream);
	}

	friend void to_json(nlohmann::json& j, const WearablesDeltaVector& vec) {
		j["protectionArmorMap"] = vec.protectionArmorMap;

		const DeltaVector<ManagedReference<TangibleObject*> >& dv = vec;

		to_json(j, dv);
	}


	bool toBinaryStream(ObjectOutputStream* stream) override {
		int _currentOffset = stream->getOffset();
		stream->writeShort(0);
		int _varCount = writeObjectMembers(stream);
		stream->writeShort(_currentOffset, _varCount);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) override {
		uint16 _varCount = stream->readShort();

		for (int i = 0; i < _varCount; ++i) {
			String _name;
			_name.parseFromBinaryStream(stream);

			uint32 _varSize = stream->readInt();

			int _currentOffset = stream->getOffset();

			if(readObjectMember(stream, _name)) {
			}

			stream->setOffset(_currentOffset + _varSize);
		}

		return true;
	}

	void insertItemToMessage(ManagedReference<TangibleObject*>* item, BaseMessage* msg) const override {
		TangibleObject* object = item->get();

		String custString;
		object->getCustomizationString(custString);

		msg->insertAscii(custString);
		msg->insertInt(object->getContainmentType()); //Equipped
		msg->insertLong(object->getObjectID()); //object id
		msg->insertInt(object->getClientObjectCRC()); //CRC of the object
	}

	bool add(const ManagedReference<TangibleObject*>& element, DeltaMessage* message = nullptr, int updates = 1) override {
		if (element->isArmorObject()) {
			ManagedReference<ArmorObject*> armor = cast<ArmorObject*>(element.get());
			uint8 hitLocations = armor->getHitLocation();

			if (hitLocations & ArmorObjectTemplate::CHEST)
				addArmor(ArmorObjectTemplate::CHEST, armor);

			if (hitLocations & ArmorObjectTemplate::ARMS)
				addArmor(ArmorObjectTemplate::ARMS, armor);

			if (hitLocations & ArmorObjectTemplate::LEGS)
				addArmor(ArmorObjectTemplate::LEGS, armor);

			if (hitLocations & ArmorObjectTemplate::HEAD)
				addArmor(ArmorObjectTemplate::HEAD, armor);
		}

		return DeltaVector<ManagedReference<TangibleObject*> >::add(element, message, updates);
	}

	ManagedReference<TangibleObject*> remove(int index, DeltaMessage* message = nullptr, int updates = 1) override {
		ManagedReference<TangibleObject*> element = get(index);

		if (element->isArmorObject()) {
			ManagedReference<ArmorObject*> armor = cast<ArmorObject*>(element.get());
			uint8 hitLocations = armor->getHitLocation();

			if (hitLocations & ArmorObjectTemplate::CHEST)
				removeArmor(ArmorObjectTemplate::CHEST, armor);

			if (hitLocations & ArmorObjectTemplate::ARMS)
				removeArmor(ArmorObjectTemplate::ARMS, armor);

			if (hitLocations & ArmorObjectTemplate::LEGS)
				removeArmor(ArmorObjectTemplate::LEGS, armor);

			if (hitLocations & ArmorObjectTemplate::HEAD)
				removeArmor(ArmorObjectTemplate::HEAD, armor);
		}

		return DeltaVector<ManagedReference<TangibleObject*> >::remove(index, message, updates);
	}


	Vector<ManagedReference<ArmorObject*> > getArmorAtHitLocation(uint8 hl, uint8 species) const {

		// TODO: Migrate and remove this when the object versioning and migration system is in place

		// HIT_LOCATION has a circular dependency nightmare with CombatManager and CreatureObject
		switch(hl) {
		case 1: // HIT_BODY
			return protectionArmorMap.get((uint8)ArmorObjectTemplate::CHEST); // CHEST
		case 2: // HIT_LARM
		{
			Vector<ManagedReference<ArmorObject*> > armArmor = protectionArmorMap.get((uint8)ArmorObjectTemplate::ARMS); // ARMS
			Vector<ManagedReference<ArmorObject*> > armorAtLocation;

			if(armArmor.isEmpty())
				return armArmor;

			int armLoc = System::random(2);

			if(species == 4)
				armLoc = 0; // Wookies only have bracers
			else if(species == 2 && armLoc == 2)
				armLoc = System::random(1); // Trandos can't wear gloves

			for(int i=armArmor.size()-1; i>=0; i--) {
				ArmorObject *obj = armArmor.get(i);

				if(armLoc == 0 && obj->hasArrangementDescriptor("bracer_upper_l")) {
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
				else if(armLoc == 1 && obj->hasArrangementDescriptor("bicep_l")) {
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
				else if(armLoc == 2 && obj->hasArrangementDescriptor("gloves")){
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
			}
			return armorAtLocation;

			// Mini-Suit
			/*
			if(hl == 2) {
				for(int i=armArmor.size()-1; i>=0; i--) {
					ArmorObject *obj = armArmor.get(i);
					if(obj->hasArrangementDescriptor("bicep_l") || obj->hasArrangementDescriptor("bracer_upper_l") || obj->hasArrangementDescriptor("gloves"))
						armorAtLocation.add(obj);
				}
			} else {
				for(int i=armArmor.size()-1; i>=0; i--) {
					ArmorObject *obj = armArmor.get(i);

					if(obj->hasArrangementDescriptor("bicep_r") || obj->hasArrangementDescriptor("bracer_upper_r") || obj->hasArrangementDescriptor("gloves"))
						armorAtLocation.add(obj);
				}
			}

			if(armorAtLocation.isEmpty())
				return armArmor;
			else
				return armorAtLocation;*/
		}
		case 3: // HIT_RARM
		{
			Vector<ManagedReference<ArmorObject*> > armArmor = protectionArmorMap.get((uint8)ArmorObjectTemplate::ARMS); // ARMS
			Vector<ManagedReference<ArmorObject*> > armorAtLocation;

			if(armArmor.isEmpty())
				return armArmor;

			int armLoc = System::random(2);

			if(species == 4)
				armLoc = 0; // Wookies only have bracers
			else if(species == 2 && armLoc == 2)
				armLoc = System::random(1); // Trandos can't wear gloves

			for(int i=armArmor.size()-1; i>=0; i--) {
				ArmorObject *obj = armArmor.get(i);

				if(armLoc == 0 && obj->hasArrangementDescriptor("bracer_upper_r")) {
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
				else if(armLoc == 1 && obj->hasArrangementDescriptor("bicep_r")) {
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
				else if(armLoc == 2 && obj->hasArrangementDescriptor("gloves")){
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
			}
			return armorAtLocation;


			// Mini-Suit
			/*
			if(hl == 2) {
				for(int i=armArmor.size()-1; i>=0; i--) {
					ArmorObject *obj = armArmor.get(i);
					if(obj->hasArrangementDescriptor("bicep_l") || obj->hasArrangementDescriptor("bracer_upper_l") || obj->hasArrangementDescriptor("gloves"))
						armorAtLocation.add(obj);
				}
			} else {
				for(int i=armArmor.size()-1; i>=0; i--) {
					ArmorObject *obj = armArmor.get(i);

					if(obj->hasArrangementDescriptor("bicep_r") || obj->hasArrangementDescriptor("bracer_upper_r") || obj->hasArrangementDescriptor("gloves"))
						armorAtLocation.add(obj);
				}
			}

			if(armorAtLocation.isEmpty())
				return armArmor;
			else
				return armorAtLocation;*/
		}
		case 4: // HIT_LLEG
		case 5: // HIT_RLEG
		{
			Vector<ManagedReference<ArmorObject*> > legArmor = protectionArmorMap.get((uint8)ArmorObjectTemplate::LEGS); // LEGS
			Vector<ManagedReference<ArmorObject*> > armorAtLocation;

			if(legArmor.isEmpty())
				return legArmor;

			int legLoc = System::random(1);

			if(species == 4 || species == 2)
				legLoc = 1; // Trandos & Wookies don't have shoes


			for(int i=legArmor.size()-1; i>=0; i--) {
				ArmorObject *obj = legArmor.get(i);

				if(legLoc == 0 && obj->hasArrangementDescriptor("shoes")) {
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
				else if(legLoc == 1 && obj->hasArrangementDescriptor("pants1")){
					armorAtLocation.add(obj);
					return armorAtLocation;
				}
			}
			return armorAtLocation;

			// Mini Suit
			//return protectionArmorMap.get((uint8)ArmorObjectTemplate::LEGS); // LEGS
		}
		case 6: // HIT_HEAD
		{
			if(species == 4) return protectionArmorMap.get((uint8)ArmorObjectTemplate::CHEST); // Wookies dont have helmets. Take from chest

			return protectionArmorMap.get((uint8)ArmorObjectTemplate::HEAD); // HEAD
		}
		}

		return protectionArmorMap.get((uint8)ArmorObjectTemplate::NOLOCATION);
	}

	void addArmor(uint8 hitLocation, ManagedReference<ArmorObject*> armor) {
		Vector<ManagedReference<ArmorObject*> > armors = protectionArmorMap.get(hitLocation);
		armors.add(armor);

		protectionArmorMap.drop(hitLocation);
		protectionArmorMap.put(hitLocation, armors);
	}

	void removeArmor(uint8 hitLocation, ManagedReference<ArmorObject*> armor) {
		Vector<ManagedReference<ArmorObject*> > armors = protectionArmorMap.get(hitLocation);
		armors.removeElement(armor);

		protectionArmorMap.drop(hitLocation);
		protectionArmorMap.put(hitLocation, armors);
	}
};


#endif /* WEARABLESDELTAVECTOR_H_ */
