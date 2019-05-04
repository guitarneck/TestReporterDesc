#include "TestReporterDesc.h"
#include "Colorized.hpp"

#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

#include "UnitTest++/TestDetails.h"

namespace UnitTest
{

  using namespace std;
  USE_COLORZ;
    
  #ifdef _WIN32
  #define TICK  "\u221a"
  #define CROSS "\u00d7"
  #else
  #define TICK  "\u2714"
  #define CROSS "\u2716"
  #endif
  
  inline string
  labelize(string const& text)
  {
    string sentence;
    string::const_iterator pos = text.begin();
    sentence.append(1, toupper(*pos++) );
    for ( ;pos != text.end(); ++pos)
    {
      if ( isupper(*pos) )
      {
        sentence.append(1, ' ').append(1, *pos);
      } else {
        sentence.append(1, *pos);
      }
    }
    return sentence;
  }

  inline
  string 
  formatMS ( float ms )
  {
    stringstream t;
    
    float hour = round(fmodf(ms / (1000 * 60 * 60), 24));
    float mins = round(fmodf(ms / (1000 * 60)     , 60));
    float secs = round(fmodf(ms /  1000           , 60));
    float mill = round(fmodf(ms                   , 1000));

    if ( hour >= 24.0f ) hour -= hour;
  
    if ( hour > 0 ) { t << hour << "h "; }
    if ( mins > 0 ) { t << mins << "m "; }
    if ( secs > 0 ) { t << secs << "s "; }
    if ( mill > 0 ) { t << '~' << mill << "ms "; }
    
    return t.str();
  }
  
  struct fill
  {
    string s;
    
    fill ( const char & c, int len )
    {
      while( len-- ) s.append( 1, c );
    }
    virtual ~fill () {}   

    int
    size ()
    {
      return (int) s.size();
    }
    
    friend std::ostream &
    operator << ( std::ostream & stream, const fill & f )
    {
      stream << f.s;
      return stream;
    }
  };

  auto pad  = fill(' ', 2);
  auto pad2 = fill(' ', 2 + pad.size());
  
  void TestReporterDesc::ReportFailure(TestDetails const& test, char const* failure)
  {
    __memoTestName = test.testName;
    string title( CROSS );
    title.append(1, ' ');
    title.append( labelize(test.testName) );
    cout << pad2 << setm(red) << title << endl;
    cout << pad  << ' '       << fill( '-', title.size() - 1 ) << endm() << endl;
    cout << pad2 << ' '       << setm(cyan) << failure << endl;
    cout << pad2 << ' '       << test.filename << " : " << test.lineNumber << endm();
    cout << endl << endl;
 }
  
  void TestReporterDesc::ReportTestStart(TestDetails const& test)
  {
    if ( __memoSuiteName != test.suiteName )
    {
      __memoSuiteName = test.suiteName;
      cout << endl;
      cout << pad << setm(underline) << labelize(test.suiteName) << endm();
      cout << endl << endl; 
    }
  }
  
  void TestReporterDesc::ReportTestFinish(TestDetails const& test, float)
  {  
    if ( __memoTestName != test.testName )
      cout << pad2 << setm(green) << TICK << endm() << ' ' << labelize(test.testName) << endl;
  }
  
  void TestReporterDesc::ReportSummary(int const totalTestCount, int const failedTestCount,
                                         int const failureCount, float secondsElapsed)
  {
    cout << endl;
    
    if ( failedTestCount > 0 )
    {
      cout << endl << pad << setm(red,bold) << "Failed tests:" << endm()
           << " There " << ((failedTestCount == 1 ) ? "was" : "were") << ' '
           << setm(red,bold) << failedTestCount << endm() << ' '
           << ((failedTestCount == 1) ? "failure" : "failures") << endl;
      cout << endl;
    }
    
    if ( totalTestCount == 0 )
    {
      cout << pad << setm(red) << CROSS << " No tests found" << endm();
    }
    else
    {
      int pass = totalTestCount - failedTestCount;
      cout << pad <<                "total    : " << totalTestCount << endl;
      cout << pad << setm(green) << "passing  : " << pass << endm() << endl;
      if ( failedTestCount > 0 )
      {
        cout << pad << setm(red) << "failing  : " << failedTestCount << endm() << endl;
      }
      cout << pad <<                "duration : " << formatMS(secondsElapsed * 1000) << endl;
    }
    
    cout << endl;
  }
  
}
