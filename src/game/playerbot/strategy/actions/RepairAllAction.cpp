#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RepairAllAction.h"


using namespace ai;

bool RepairAllAction::Execute(Event event)
{


    list<ObjectGuid> npcs = AI_VALUE(list<ObjectGuid>, "nearest npcs");
    for (list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
        Creature *unit = bot->GetNPCIfCanInteractWith(*i, UNIT_NPC_FLAG_REPAIR);
        if (!unit)
            continue;

        if(bot->hasUnitState(UNIT_STAT_DIED))
            bot->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH);

        float discountMod = bot->GetReputationPriceDiscount(unit);

        uint32 totalCost = bot->DurabilityRepairAll(true, discountMod, false);
        ostringstream out;
        out << "Repaired at " << unit->GetName() << ". Cost " << totalCost;
        ai->TellMaster(out);
        return true;
    }

    ai->TellMaster("Cannot find any npc to repair at");
    return false;
}