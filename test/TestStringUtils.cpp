#include "TestStringUtils.hpp"

#include "Logging.hpp"

#include "TestUtils.hpp"
#include "StringUtils.hpp"

void TestStringUtils::TestTrim() {
    LOG_INFO("TestStringUtils::TestTrim");

    std::string s1 = "  string ";
    std::string s1_expected = "string";
    AssertEquals(s1_expected, StringUtils::trim_copy(s1));

    std::string s2 = "dummy ";
    std::string s2_expected = "dummy";
    AssertEquals(s2_expected, StringUtils::trim_copy(s2));

    std::string s3 = "\t other ";
    std::string s3_expected = "other";
    AssertEquals(s3_expected, StringUtils::trim_copy(s3));
}

void TestStringUtils::TestSplit() {
    LOG_INFO("TestStringUtils::TestSplit");

    std::string s1 = "helloxworld";
    std::string delimiter1 = "x";
    std::vector<std::string> parts1 = StringUtils::split(s1, delimiter1);
    AssertEquals(2, (int) parts1.size());
    AssertEquals(std::string("hello"), parts1[0]);
    AssertEquals(std::string("world"), parts1[1]);

    std::string s2 = "let's \tparse  \tthis\t!";
    std::string delimiter2 = " \t";
    std::vector<std::string> parts2 = StringUtils::split(s2, delimiter2);
    AssertEquals(3, (int) parts2.size());
    AssertEquals(std::string("let's"), parts2[0]);
    AssertEquals(std::string("parse "), parts2[1]);
    AssertEquals(std::string("this\t!"), parts2[2]);
}
