#include "pch.h"
#include "aitest.h"

#include "EngineTestBase.h"
#include "../game/playerbot/strategy/druid/DruidAiObjectContext.h"

using namespace ai;

class GenericTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( GenericTestCase );
	CPPUNIT_TEST( flee );
	CPPUNIT_TEST( adds );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidAiObjectContext(ai), "bear", "flee", NULL);
    }

protected:
	void flee()
	{
	    list<Item*> items;
        set<list<Item*> >("inventory items", "drink", items);
	    set<list<Item*> >("inventory items", "food", items);

		lowHealth(1);
		lowMana(1);
		tick();

		assertActions(">S:flee");
	}

	void adds()
	{
	    engine->addStrategy("flee from adds");

	    list<ObjectGuid> adds;
	    adds.push_front(ObjectGuid(uint64(1)));
	    set<list<ObjectGuid> >("nearest adds", adds);

	    tick();

		assertActions(">S:runaway");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( GenericTestCase );