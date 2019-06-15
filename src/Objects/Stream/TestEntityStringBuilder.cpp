#include "TestEntityStringBuilder.hpp"

#include "EntityStringBuilder.hpp"

#include <src/Test/TestUtils.hpp>

void TestEntityStringBuilder::testFactoryString() {
    EntityStringBuilder esb1(569, "SOME_TYPE", 1);
    esb1.setArg2(5000)
            .setArg3((Id) 568)
            .setArg4((short) -100)
            .setArg5(2);
    assertEquals<std::string>("569 SOME_TYPE 1 5000 568 -100 2", esb1.build());

    EntityStringBuilder esb2(617, "OTHER_TYPE", 6);
    esb2.setArg2(500)
            .setArg3((unsigned short) 1)
            .setArg4((unsigned int) 100000);
    assertEquals<std::string>("617 OTHER_TYPE 6 500 1 100000 0", esb2.build());
}
