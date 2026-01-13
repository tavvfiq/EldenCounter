#pragma once

#include "RE/Skyrim.h"
#include <optional>

namespace ActorUtils {
        // Check if actor is valid and accessible
        inline bool IsValid(RE::Actor* a_actor)
        {
            if (!a_actor) {
                return false;
            }
            try {
                return !a_actor->IsDead() && a_actor->IsInCombat();
            } catch (...) {
                return false;
            }
        }

        // Safe GetFormID - returns optional to handle failures
        inline std::optional<RE::FormID> SafeGetFormID(RE::Actor* a_actor)
        {
            if (!a_actor) {
                return std::nullopt;
            }
            try {
                return a_actor->GetFormID();
            } catch (...) {
                return std::nullopt;
            }
        }
}