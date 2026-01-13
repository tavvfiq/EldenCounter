#include "include/guardCounter.h"
#include "ActorUtils.h"
#include <SimpleIni.h>

void guardCounter::update() {
	static float* g_deltaTime = (float*)REL::RelocationID(523660, 410199).address();
	
	// Iterate through all tracked actors and update their timers
	gc_Timers.WithWriteLock([&](auto& gcTimersMap) {
		auto timersIt = gcTimersMap.begin();
		while (timersIt != gcTimersMap.end()) {
			RE::FormID formID = timersIt->first;
			float& timer = timersIt->second;

			auto actor = RE::TESForm::LookupByID<RE::Actor>(formID);
			// Check if actor is still valid
			if (!actor || actor->IsDead()) {
				timersIt = gcTimersMap.erase(timersIt);
				continue;
			}
			
			timer -= *g_deltaTime;
			if (timer <= 0) {
				actor->RemoveSpell(gc_triggerSpell);
				actor->SetGraphVariableBool("Val_GuardCounter", false);
				timersIt = gcTimersMap.erase(timersIt);
			} else {
				++timersIt;
			}
		}
	});
}

void guardCounter::registerBlock(RE::Actor* actor) {
	//DEBUG("registering block");
	if (actor && !actor->IsDead()) {
		actor->AddSpell(gc_triggerSpell);
		actor->SetGraphVariableBool("Val_GuardCounter", true);

		auto formIDOpt = ActorUtils::SafeGetFormID(actor);
        if (!formIDOpt.has_value()) {
			// add logging
            return;
        }
		
        RE::FormID formID = formIDOpt.value();
        // Get or create actor temporal data
        gc_Timers.Emplace(formID, gc_Time);
	}
	//RE::DebugNotification("guard counter start!");
}

void guardCounter::readSettings() {
	logger::info("Loading settings...");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\EldenCounter.ini"
	ini.LoadFile(SETTINGFILE_PATH);
	gc_Time = std::stof(ini.GetValue("General", "Time"));
	logger::info("Settings loaded.");
}

void guardCounter::loadData() {
	logger::info("Loading data...");
	gc_triggerSpell = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(0x801, "EldenCounter.esp");
	if (!gc_triggerSpell) {
		logger::error("Error: spell not found! Enable EldenCounter.esp");
		RE::DebugMessageBox("Error: spell not found! Enable EldenCounter.esp");
	}
}