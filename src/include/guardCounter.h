#pragma once
#include "RE/Skyrim.h"
#include "ThreadSafeMap.h"

class guardCounter
{
public:
	static guardCounter* GetSingleton()
	{
		static guardCounter singleton;
		return  std::addressof(singleton);
	}

	/*Update executes once per frame. Decrement timers for actors in guard counter.*/
	void update();

	/*Register a block, reset timer.*/
	void registerBlock(RE::Actor* actor);

	/*Read settings from simpleIni.*/
	void readSettings();

	/*Load all game data.*/
	void loadData();
private:
	//timer for guard counter.
	float gc_Time = 1;
	
	// Map to track timers for each actor
	ThreadSafeMap<RE::FormID, float> gc_Timers;

	/*Only when having this spell would trigger guard counter.*/
	RE::SpellItem* gc_triggerSpell;
};