//#define _GLIBCXX_USE_CXX11_ABI 0

#include <UnitTest++/UnitTest++.h>

#include "reporters/desc/TestReporterDesc.h"

#define REPORTER_(ROOT,NAME) ROOT##NAME
#define REPORTER(NAME) REPORTER_(TestReporter,NAME)
#define REPORTER_N Desc

int
main (int, const char *[])
{
  using namespace UnitTest;

  REPORTER(REPORTER_N) reporter;
	
  TestRunner runner(reporter);
  return runner.RunTestsIf(Test::GetTestList(), NULL, True(), 0);
  /*
  return RunAllTests();
  */
}