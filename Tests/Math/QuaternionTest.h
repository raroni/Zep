#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Math/Quaternion.h"
#include "Zep/Math/Vector3.h"

namespace QuaternionTestCase {
    class MultiplicationTest : public Vincent::Test {
    public:
        MultiplicationTest() {
            name = "Multiplication";
        }
        void run() {
            Zep::Quaternion operand1(3, Zep::Vector3(2, 4, 5));
            Zep::Quaternion operand2(2, Zep::Vector3(9, 6, 2));
            auto result = operand1 * operand2;
            assertEqual(-46, result.real);
            assertEqual(9, result.imaginaries[0]);
            assertEqual(67, result.imaginaries[1]);
            assertEqual(-8, result.imaginaries[2]);
        }
    };
    
    class DotTest : public Vincent::Test {
    public:
        DotTest() {
            name = "Dot";
        }
        void run() {
            Zep::Quaternion operand1(3, Zep::Vector3(2, 4, 5));
            Zep::Quaternion operand2(2, Zep::Vector3(9, 6, 2));
            auto result = Zep::Quaternion::dot(operand1, operand2);
            assertInRange(58, result, 0.01);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "Quaternion";
            add(new MultiplicationTest());
            add(new DotTest());
        }
    };
}
