#ifndef __UnitTestCpp_TestReporterDesc__
#define __UnitTestCpp_TestReporterDesc__

#include "UnitTest++/TestReporter.h"
#include <string>

namespace UnitTest
{

  class TestReporterDesc : public TestReporter
  {

    private:
      virtual void ReportTestStart(TestDetails const& test);
      virtual void ReportFailure(TestDetails const& test, char const* failure);

      virtual void ReportTestFinish(TestDetails const& test, float secondsElapsed);
      virtual void ReportSummary(int totalTestCount, int failedTestCount, 
                                 int failureCount  , float secondsElapsed);

    std::string __memoTestName;
    std::string __memoSuiteName;
  };

}

#endif