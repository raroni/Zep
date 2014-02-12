#include "vincent/test_suite.h"
#include "vincent/text_presentation.h"
#include "DatabaseTestCase.h"
#include "ComponentTypeRegistryTestCase.h"
#include "EntityObserverProcessorTestCase.h"
#include "Events/EventSignalTestCase.h"
#include "Events/EventSubscriptionTestCase.h"
#include "Events/EventManagerTestCase.h"

int main() {
    Vincent::TestSuiteResult result;
    Vincent::TestSuite suite;
    
    suite.add(new DatabaseTestCase::Case());
    suite.add(new ComponentTypeRegistryTestCase::Case());
    suite.add(new EntityObserverProcessorTestCase::Case());
    suite.add(new EventSignalTestCase::Case());
    suite.add(new EventSubscriptionTestCase::Case());
    suite.add(new EventManagerTestCase::Case());
    
    suite.run(result);
    Vincent::TextPresentation presentation(result);
    presentation.present();
}
