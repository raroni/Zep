#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventManager.h"
#include "Zep/Events/EventSubscriptionManager.h"

namespace EventSubscriptionManagerTestCase {
    class Explosion : public Zep::Event { };
    class Collision : public Zep::Event { };
    
    struct DummyObserver {
        int counter = 0;
        void receive(const Explosion &event) {
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
            Zep::EventManager eventManager;
            auto subscriptionManager = new Zep::EventSubscriptionManager<DummyObserver>();
            subscriptionManager->initialize(observer, eventManager);
            subscriptionManager->add<Explosion>();
            eventManager.emit<Explosion>();
            assertEqual(1, observer.counter);
            delete subscriptionManager;
            eventManager.emit<Explosion>();
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
