#include "vincent/test_case.h"
#include "vincent/test.h"
#include <iostream>

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
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSignal";
            add(new ConnectDisconnectTest());
        }
    };
}
