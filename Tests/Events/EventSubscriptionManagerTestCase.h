#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventBus.h"
#include "Zep/Events/EventSubscriptionManager.h"

namespace EventSubscriptionManagerTestCase {
    class Explosion : public Zep::Event { };
    class Collision : public Zep::Event { };
    
    struct DummyObserver {
        int counter = 0;
        void handle(const Explosion &event) {
            counter++;
        }
    };
    
    class SubscriptionTest : public Vincent::Test {
    public:
        SubscriptionTest() {
            name = "Subscription";
        }
        void run() {
            DummyObserver observer;
            Zep::EventBus eventBus;
            auto subscriptionManager = new Zep::EventSubscriptionManager<DummyObserver>(observer, eventBus);
            subscriptionManager->add<Explosion>();
            eventBus.emit<Explosion>();
            assertEqual(1, observer.counter);
            delete subscriptionManager;
            eventBus.emit<Explosion>();
            assertEqual(1, observer.counter);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSubscriptionManager";
            add(new SubscriptionTest());
        }
    };
}
