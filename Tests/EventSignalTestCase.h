#include <string>
#include "vincent/test_case.h"
#include "vincent/test.h"

namespace EventSignalTestCase {
    struct DummyFunction {
        int& counter;
        DummyFunction(int &counter) : counter(counter) { }
        void operator()(const Zep::Event &event) {
            counter++;
        }
    };
    
    class SubscribeUnsubscribeTest : public Vincent::Test {
    public:
        SubscribeUnsubscribeTest() {
            name = "SubscribeUnsubscribe";
        }
        void run() {
            Zep::EventSignal signal;
            int counter = 0;
            int subscriptionID = signal.subscribe(DummyFunction(counter));
            
            Zep::Event event;
            
            signal.emit(event);
            assertEqual(1, counter);
            
            signal.emit(event);
            assertEqual(2, counter);
            
            signal.unsubscribe(subscriptionID);
            signal.emit(event);
            assertEqual(2, counter);
        }
    };
    
    class SubscriptionIDReuseTest : public Vincent::Test {
    public:
        SubscriptionIDReuseTest() {
            name = "SubscriptionIDReuse";
        }
        void run() {
            Zep::EventSignal signal;
            int counter = 0;
            int subscriptionID1 = signal.subscribe(DummyFunction(counter));
            signal.unsubscribe(subscriptionID1);
            
            int subscriptionID2 = signal.subscribe(DummyFunction(counter));
            assertEqual(subscriptionID1, subscriptionID2);
        }
    };
    
    class OrderMaintenanceTest : public Vincent::Test {
    public:
        OrderMaintenanceTest() {
            name = "OrderMaintenance";
        }
        void run() {
            Zep::EventSignal signal;
            std::string log;
            int lambdaID = signal.subscribe([] (const Zep::Event&) { });
            signal.subscribe([&log] (const Zep::Event&) { log += "a"; });
            signal.unsubscribe(lambdaID);
            signal.subscribe([&log] (const Zep::Event&) { log += "b"; });
            
            Zep::Event event;
            signal.emit(event);
            
            assertEqual("ab", log);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSignal";
            add(new SubscribeUnsubscribeTest());
            add(new SubscriptionIDReuseTest());
            add(new OrderMaintenanceTest());
        }
    };
}
