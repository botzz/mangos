#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "DpsPaladinStrategy.h"

using namespace ai;

class DpsPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsPaladinStrategyActionNodeFactory()
    {
        creators["seal of command"] = &seal_of_command;
        creators["blessing of might"] = &blessing_of_might;
        creators["crusader strike"] = &crusader_strike;
    }

private:
    static ActionNode* seal_of_command(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of command",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of wisdom"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* blessing_of_might(PlayerbotAI* ai)
    {
        return new ActionNode ("blessing of might",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blessing of kings"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* crusader_strike(PlayerbotAI* ai)
    {
        return new ActionNode ("crusader strike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
};

DpsPaladinStrategy::DpsPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
    actionNodeFactories.Add(new DpsPaladinStrategyActionNodeFactory());
}

NextAction** DpsPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("crusader strike", 10.0f), NULL);
}

void DpsPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("divine shield", 50.0f), new NextAction("holy light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of wisdom",
        NextAction::array(0, new NextAction("judgement of wisdom", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("blessing of might", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe",
		NextAction::array(0, new NextAction("divine storm", 27.0f), new NextAction("consecration", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"art of war",
		NextAction::array(0, new NextAction("exorcism", 27.0f), NULL)));
}