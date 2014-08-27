#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventBus.h"

namespace EventBusTestCase {
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
            Zep::EventBus bus;
            DummyObserver observer;
            auto subscription = bus.subscribe<Explosion>(observer);
            bus.emit<Explosion>();
            assertEqual(1, observer.counter);
            bus.emit<Explosion>();
            assertEqual(2, observer.counter);
            subscription.cancel();
            bus.emit<Explosion>();
            assertEqual(2, observer.counter);
        }
    };
    
    class TemplateEmissionTest : public Vincent::Test {
    public:
        TemplateEmissionTest() {
            name = "TemplateEmission";
        }
        void run() {
            Zep::EventBus bus;
            DummyObserver observer;
            auto subscription = bus.subscribe<Explosion>(observer);
            bus.emit<Explosion>();
            assertEqual(1, observer.counter);
            bus.emit<Collision>();
            assertEqual(1, observer.counter);
            subscription.cancel();
        }
    };
    
    class InstanceEmissionTest : public Vincent::Test {
    public:
        InstanceEmissionTest() {
            name = "InstanceEmissionTest";
        }
        void run() {
            Zep::EventBus bus;
            DummyObserver observer;
            auto subscription = bus.subscribe<Explosion>(observer);
            Explosion explosion;
            bus.emit(explosion);
            assertEqual(1, observer.counter);
            Collision collision;
            bus.emit(collision);
            assertEqual(1, observer.counter);
            subscription.cancel();
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventBus";
            add(new SubscriptionTest());
            add(new TemplateEmissionTest());
            add(new InstanceEmissionTest());
        }
    };
}
