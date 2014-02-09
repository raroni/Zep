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
    
    class ConnectDisconnectTest : public Vincent::Test {
    public:
        ConnectDisconnectTest() {
            name = "ConnectDisconnect";
        }
        void run() {
            Zep::EventSignal signal;
            int counter = 0;
            int connectionID = signal.connect(DummyFunction(counter));
            
            Zep::Event event;
            
            signal.emit(event);
            assertEqual(1, counter);
            
            signal.emit(event);
            assertEqual(2, counter);
            
            signal.disconnect(connectionID);
            signal.emit(event);
            assertEqual(2, counter);
        }
    };
    
    class ConnectionIDReuseTest : public Vincent::Test {
    public:
        ConnectionIDReuseTest() {
            name = "ConnectionIDReuse";
        }
        void run() {
            Zep::EventSignal signal;
            int counter = 0;
            int connectionID1 = signal.connect(DummyFunction(counter));
            signal.disconnect(connectionID1);
            
            int connectionID2 = signal.connect(DummyFunction(counter));
            assertEqual(connectionID1, connectionID2);
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
            int lambdaID = signal.connect([] (const Zep::Event&) { });
            int aID = signal.connect([&log] (const Zep::Event&) { log += "a"; });
            signal.disconnect(lambdaID);
            int bID = signal.connect([&log] (const Zep::Event&) { log += "b"; });
            
            Zep::Event event;
            signal.emit(event);
            
            assertEqual("ab", log);
            
            signal.disconnect(aID);
            signal.disconnect(bID);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSignal";
            add(new ConnectDisconnectTest());
            add(new ConnectionIDReuseTest());
            add(new OrderMaintenanceTest());
        }
    };
}
