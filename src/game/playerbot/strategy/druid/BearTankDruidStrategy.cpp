#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

class BearTankDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    BearTankDruidStrategyActionNodeFactory()
    {
        creators["melee"] = &melee;
        creators["feral charge - bear"] = &feral_charge_bear;
        creators["swipe (bear)"] = &swipe_bear;
        creators["faerie fire (feral)"] = &faerie_fire_feral;
        creators["bear form"] = &bear_form;
        creators["dire bear form"] = &dire_bear_form;
        creators["mangle (bear)"] = &mangle_bear;
        creators["maul"] = &maul;
        creators["bash"] = &bash;
        creators["swipe"] = &swipe;
        creators["lacerate"] = &lacerate;
        creators["demoralizing roar"] = &demoralizing_roar;
    }
private:
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("feral charge - bear"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* feral_charge_bear(PlayerbotAI* ai)
    {
        return new ActionNode ("feral charge - bear",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* swipe_bear(PlayerbotAI* ai)
    {
        return new ActionNode ("swipe (bear)",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* faerie_fire_feral(PlayerbotAI* ai)
    {
        return new ActionNode ("faerie fire (feral)",
            /*P*/ NextAction::array(0, new NextAction("feral charge - bear"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* bear_form(PlayerbotAI* ai)
    {
        return new ActionNode ("bear form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* dire_bear_form(PlayerbotAI* ai)
    {
        return new ActionNode ("dire bear form",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("bear form"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* mangle_bear(PlayerbotAI* ai)
    {
        return new ActionNode ("mangle (bear)",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("maul"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* maul(PlayerbotAI* ai)
    {
        return new ActionNode ("maul",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* bash(PlayerbotAI* ai)
    {
        return new ActionNode ("bash",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* swipe(PlayerbotAI* ai)
    {
        return new ActionNode ("swipe",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lacerate(PlayerbotAI* ai)
    {
        return new ActionNode ("lacerate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mangle (bear)"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* growl(PlayerbotAI* ai)
    {
        return new ActionNode ("growl",
            /*P*/ NextAction::array(0, new NextAction("reach spell"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* demoralizing_roar(PlayerbotAI* ai)
    {
        return new ActionNode ("demoralizing roar",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

BearTankDruidStrategy::BearTankDruidStrategy(PlayerbotAI* ai) : FeralDruidStrategy(ai)
{
    actionNodeFactories.Add(new BearTankDruidStrategyActionNodeFactory());
}

NextAction** BearTankDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 11.0f), new NextAction("lacerate", 10.0f), NULL);
}

void BearTankDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    FeralDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bear form",
        NextAction::array(0, new NextAction("dire bear form", 29.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", 31.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("growl", 29.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("demoralizing roar", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("swipe (bear)", 29.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "bash",
        NextAction::array(0, new NextAction("bash", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", 27.0f), NULL)));
}