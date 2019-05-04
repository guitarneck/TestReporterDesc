#ifndef __Colorized__hpp__
#define __Colorized__hpp__
  
#include <string>
#include <iostream>
#include <list>
  
namespace colorized
{
  
  typedef enum : int
  {
    // Style  
     bold          = 1
    ,underline    = 4
    ,blink        = 5
    ,reverse      = 7
    
    ,normal        = 22
    
    ,off          = 20
    // 21 Doubly underline or Bold off...  
    ,boldOff      = 22 // Normal color or intensity
    ,underlineOff = 24
    ,blinkOff     = 25
    ,reverseOff   = 27
    
    // Colors
    ,black        = 30
    ,red
    ,green
    ,yellow
    ,blue
    ,magenta
    ,cyan
    ,white
  
    ,fgBlack      = 30,
    ,fgRed
    ,fgGreen
    ,fgYellow
    ,fgBlue
    ,fgMagenta
    ,fgCyan
    ,fgWhite
  
    // Background
    ,bg            = 10 // bg + black
    
    ,bgBlack      = 40
    ,bgRed
    ,bgGreen
    ,bgYellow
    ,bgBlue
    ,bgMagenta
    ,bgCyan
    ,bgWhite
    
    ,bright       = 60 // black + bright
    
    ,bfgBlack      = 90
    ,bfgRed
    ,bfgGreen
    ,bfgYellow
    ,bfgBlue
    ,bfgMagenta
    ,bfgCyan
    ,bfgWhite
  
    ,bbright      = 70
    
    ,bbgBlack      = 100
    ,bbgRed
    ,bbgGreen
    ,bbgYellow
    ,bbgBlue
    ,bbgMagenta
    ,bbgCyan
    ,bbgWhite
  
    ,end          = 0
  
  } Color;
  
  class setm
  {
    
    std::list<Color> __colors;
  
    void append( Color c ) { __colors.push_back( c ); }
  
    template<typename T>
    void 
    __setm (T t)
    {
      append( t ); 
    }
    
    template<typename T, typename... Args>
    void
    __setm (T t, Args... args)
    {
      append( t );
      __setm( args... );
    }
  
    template<typename T>
    const std::string
    __tom ( T begin, T end ) const
    {
      std::string tom("\033[");
      tom += std::to_string(*begin);
      begin++;
      for(;begin != end;++begin)
      {
            tom += ";";
        tom += std::to_string(*begin);
      }
      return tom + "m";
    }
    
    public:
    
      template <typename T>
      setm (T t) 
      {
        __colors.clear();
        __setm( t ); 
      }
    
      template<typename T, typename... Args>
      setm (T t, Args... args)
      {
        __colors.clear();
        __setm( t );
        __setm( args... );
      }
    
      virtual ~setm () {}
  
      friend std::ostream &
      operator << ( std::ostream & stream, setm * s )
      {
        stream << s->__tom(s->__colors.begin(), s->__colors.end());
        return stream;
      }
  
      friend std::ostream &
      operator << ( std::ostream & stream, const setm & s )
      {
        stream << s.__tom(s.__colors.cbegin(), s.__colors.cend());
        return stream;
      }
  
  };
  
  class endm : public setm
  {
    public:
      endm() : setm(end) {}
      virtual ~endm() {}
  };
  
}
  
#define USE_COLORZ using namespace colorized
  
#endif