#include "vincent/test_suite.h"
#include "vincent/text_presentation.h"
#include "Database/DatabaseTestCase.h"
#include "Database/AspectTypeRegistryTestCase.h"
#include "Database/EntityObserverTestCase.h"
#include "Database/AspectListTestCase.h"
#include "Events/EventSignalTestCase.h"
#include "Events/EventSubscriptionTestCase.h"
#include "Events/EventBusTestCase.h"
#include "Events/EventSubscriptionManagerTestCase.h"
#include "Math/QuaternionTest.h"

int main() {
    Vincent::TestSuiteResult result;
    Vincent::TestSuite suite;
    
    suite.add(new AspectListTestCase::Case());
    suite.add(new DatabaseTestCase::Case());
    suite.add(new AspectTypeRegistryTestCase::Case());
    suite.add(new EventSignalTestCase::Case());
    suite.add(new EventSubscriptionTestCase::Case());
    suite.add(new EventBusTestCase::Case());
    suite.add(new EventSubscriptionManagerTestCase::Case());
    suite.add(new EntityObserverTestCase::Case());
    suite.add(new QuaternionTestCase::Case());
    
    suite.run(result);
    Vincent::TextPresentation presentation(result);
    presentation.present();
}
