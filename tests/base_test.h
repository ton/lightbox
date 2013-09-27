#ifndef BASE_TEST_H
#define BASE_TEST_H

#include <gtest/gtest.h>

#include <libgen.h>

#define TEST_DIRECTORY dirname(__FILE__)

#define BENCHMARK_TEST_FIXTURE(__TestFixtureClass__) \
    class __TestFixtureClass__: public BaseTest \
    { \
        public: \
            __TestFixtureClass__(): BaseTest(__FILE__) { } \
    }

class BaseTest: public ::testing::Test
{
    protected:
        BaseTest(const std::string &testPath):
            ::testing::Test(),
            testPath_(dirname(const_cast<char *>(testPath.c_str())))
        {
        }

        void SetUp()
        {
            ::testing::Test::SetUp();
        }

        std::string getInputFile(const std::string &fileName)
        {
            return testPath_ + "/input/" + fileName;
        }

    private:
        std::string testPath_;
};

#endif
