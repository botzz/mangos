#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GrindTargetValue.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

Unit* GrindTargetValue::Calculate()
{
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    Unit* target = NULL;
    uint32 assistCount = 0;
    while (!target && assistCount < group->GetMembersCount())
    {
        target = FindTargetForGrinding(assistCount++);
    }

    return target;
}


Unit* GrindTargetValue::FindTargetForGrinding(int assistCount)
{
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;


    list<ObjectGuid> targets = *context->GetValue<list<ObjectGuid> >("possible targets");

    if(targets.empty())
        return NULL;

    float distance = 0;
    Unit* result = NULL;
    for(list<ObjectGuid>::iterator tIter = targets.begin(); tIter != targets.end(); tIter++)
    {
        Unit* unit = ai->GetUnit(*tIter);
        if (!unit)
            continue;

        if (abs(bot->GetPositionZ() - unit->GetPositionZ()) > sPlayerbotAIConfig.spellDistance)
            continue;

        if (GetTargetingPlayerCount(unit) > assistCount)
            continue;

        if (master->GetDistance(unit) >= sPlayerbotAIConfig.grindDistance)
            continue;

        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = sObjectMgr.GetPlayer(itr->guid);
            if( !member || !member->isAlive())
                continue;

            float d = member->GetDistance(unit);
            if (!result || d < distance)
            {
                distance = d;
                result = unit;
            }
        }
    }

    return result;
}


int GrindTargetValue::GetTargetingPlayerCount( Unit* unit )
{
    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    int count = 0;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *member = sObjectMgr.GetPlayer(itr->guid);
        if( !member || !member->isAlive() || member == bot)
            continue;

        PlayerbotAI* ai = member->GetPlayerbotAI();
        if ((ai && *ai->GetAiObjectContext()->GetValue<Unit*>("current target") == unit) ||
            (!ai && member->GetSelectionGuid() == unit->GetObjectGuid()))
            count++;
    }

    return count;
}
