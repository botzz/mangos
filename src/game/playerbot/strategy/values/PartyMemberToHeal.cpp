#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PartyMemberToHeal.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

class IsTargetOfHealingSpell : public SpellEntryPredicate
{
public:
    virtual bool Check(SpellEntry const* spell) {
        for (int i=0; i<3; i++) {
            if (spell->Effect[i] == SPELL_EFFECT_HEAL ||
                spell->Effect[i] == SPELL_EFFECT_HEAL_MAX_HEALTH ||
                spell->Effect[i] == SPELL_EFFECT_HEAL_MECHANICAL || 
                spell->Effect[i] == SPELL_EFFECT_HEAL_PCT)
                return true;
        }
        return false;
    }

};

Unit* PartyMemberToHeal::Calculate()
{
    
    IsTargetOfHealingSpell predicate;

    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    MinValueCalculator calc(100);
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
        if (!Check(player) || !player->isAlive())
            continue;

        uint8 health = player->GetHealthPercent();
        if (health < sPlayerbotAIConfig.mediumHealth || !IsTargetOfSpellCast(player, predicate))
            calc.probe(health, player);

        Pet* pet = player->GetPet();
        if (pet && CanHealPet(pet)) 
        {
            health = pet->GetHealthPercent();
            if (health < sPlayerbotAIConfig.mediumHealth || !IsTargetOfSpellCast(player, predicate))
                calc.probe(health, player);
        }
    }
    return (Unit*)calc.param;
}

bool PartyMemberToHeal::CanHealPet(Pet* pet) 
{
    PetType type = pet->getPetType();
    return type != SUMMON_PET && type != MINI_PET;
}