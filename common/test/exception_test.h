#include "common/itf/exception.h"

#include "tests/base_test.h"

#include <gtest/gtest.h>

using namespace lb;

BENCHMARK_TEST_FIXTURE(ExceptionTest);

enum class TestExceptionCode
{
    NO_ARGUMENTS = 990001,
    ONE_ARGUMENT,
    MULTIPLE_ORDERED_ARGUMENTS,
    MULTIPLE_UNORDERED_ARGUMENTS,
    INVALID_ARGUMENT,
};

std::ostream &operator <<(std::ostream &out, TestExceptionCode code)
{
    switch (code)
    {
        case TestExceptionCode::NO_ARGUMENTS:
            out << "This is an exception message without arguments";
            break;
        case TestExceptionCode::ONE_ARGUMENT:
            out << "This exception message has one argument: '%1%'";
            break;
        case TestExceptionCode::MULTIPLE_ORDERED_ARGUMENTS:
            out << "This exception message has two arguments, 1st: '%1%', 2nd: '%2%'";
            break;
        case TestExceptionCode::MULTIPLE_UNORDERED_ARGUMENTS:
            out << "This exception message has two arguments, 2nd: '%2%', 1st: '%1%'";
            break;
        case TestExceptionCode::INVALID_ARGUMENT:
            out << "This exception message has no arguments, but contains '%' signs, and '%3 %', and an argument placeholder '%1001%'";
            break;
    }

    return out;
}

/// Tests generating an exception message without any arguments.
TEST_F(ExceptionTest, TestExceptionWithNoArguments)
{
    EXPECT_STREQ("Error 990001: This is an exception message without arguments.", Exception(TestExceptionCode::NO_ARGUMENTS).what());

    // Test that an exception with no placeholders but with exception arguments
    // does not cause any issues.
    Exception e = Exception(TestExceptionCode::NO_ARGUMENTS) % 10 % "test";
    EXPECT_STREQ("Error 990001: This is an exception message without arguments.", e.what());
}

/// Tests generating an exception message with one argument.
TEST_F(ExceptionTest, TestExceptionWithOneArgument)
{
    Exception e = Exception(TestExceptionCode::ONE_ARGUMENT) % 10 % "test";
    EXPECT_STREQ("Error 990002: This exception message has one argument: '10'.", e.what());
}

/// Tests generating an exception message with multiple ordered arguments.
TEST_F(ExceptionTest, TestExceptionWithMultipleOrderedArguments)
{
    Exception e = Exception(TestExceptionCode::MULTIPLE_ORDERED_ARGUMENTS) % "test" % 3.1415;
    EXPECT_STREQ("Error 990003: This exception message has two arguments, 1st: 'test', 2nd: '3.1415'.", e.what());
}

/// Tests generating an exception message with multiple unordered arguments.
TEST_F(ExceptionTest, TestExceptionWithMultipleUnorderedArguments)
{
    Exception e = Exception(TestExceptionCode::MULTIPLE_UNORDERED_ARGUMENTS) % "first argument" % "second argument";
    EXPECT_STREQ("Error 990004: This exception message has two arguments, 2nd: 'second argument', 1st: 'first argument'.", e.what());
}

/// Tests generating an exception message with an invalid argument placeholder.
TEST_F(ExceptionTest, TestExceptionWithInvalidArgument)
{
    Exception e = Exception(TestExceptionCode::INVALID_ARGUMENT) % "1st argument";
    EXPECT_STREQ("Error 990005: This exception message has no arguments, but contains '%' signs, and '%3 %', and an argument placeholder '1st argument'.", e.what());
}
