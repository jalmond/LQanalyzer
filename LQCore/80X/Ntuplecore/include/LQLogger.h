#ifndef LQLogger_H
#define LQLogger_H

// STL include(s):
#include <string>
#include <sstream>

// Local include(s):
#include "LQMsgType.h"
#include "LQLogWriter.h"

// Forward declaration(s):
class TObject;
class LQLogWriter;

class LQLogger : public std::ostringstream {
  
 public:
  /// Constructor with pointer to the parent object
  LQLogger( const TObject* source );
  /// Constructor with a name of the parent object
  LQLogger( const std::string& source );
  /// Copy constructor
  LQLogger( const LQLogger& parent );
  /// Default destructor
  virtual ~LQLogger();

  void SetSource( const TObject* source );
  void SetSource( const std::string& source );

  /// Copy operator
  LQLogger& operator= ( const LQLogger& parent );

  /// Stream modifier to send a message
  static LQLogger& endmsg( LQLogger& logger );

  /// Operator accepting LQLogger stream modifiers
  LQLogger& operator<< ( LQLogger& ( *_f )( LQLogger& ) );
  /// Operator accepting std::ostream stream modifiers
  LQLogger& operator<< ( std::ostream& ( *_f )( std::ostream& ) );
  /// Operator accepting std::ios stream modifiers
  LQLogger& operator<< ( std::ios& ( *_f )( std::ios& ) );

  /// Operator accepting message type setting
  LQLogger& operator<< ( LQMsgType type );

  /// Operator accepting basically any kind of argument
  /**
   * LQLogger was designed to give all the features that std::ostream
   * objects usually provide. This operator handles all kinds of
   * arguments and passes it on to the std::ostringstream base class.
   */
  template < class T > LQLogger& operator<< ( T arg ) {
    if( m_activeType >= m_logWriter->GetMinType() ) {
      ( * ( std::ostringstream* ) this ) << arg;
    }
    return *this;
  }

  /// Old style message sender function
  void Send( LQMsgType type, const std::string& message ) const;

 private:
  void Send();

  const TObject* m_objSource;
  std::string    m_strSource;


  LQLogWriter*    m_logWriter;
  LQMsgType       m_activeType;

}; // class LQLogger

//////////////////////////////////////////////////////////////////////
//                                                                  //
//   To speed up the code a bit, the following operators are        //
//   declared 'inline'.                                             //
//                                                                  //
//////////////////////////////////////////////////////////////////////

/**
 * This operator handles all stream modifiers that have been written
 * to work on LQLogger objects specifically. Right now there is basically
 * only the LQLogger::endmsg stream modifier that is such.
 */
inline LQLogger& LQLogger::operator<< ( LQLogger& ( *_f )( LQLogger& ) ) {

  return ( _f )( *this );
}

/**
 * This operator handles all stream modifiers that have been written
 * to work on std::ostream objects. Most of the message formatting
 * modifiers are such.
 */
inline LQLogger& LQLogger::operator<< ( std::ostream& ( *_f )( std::ostream& ) ) {

  if( m_activeType >= m_logWriter->GetMinType() ) {
    ( _f )( *this );
  }
  return *this;
}


/**
 * This operator handles all stream modifiers that have been written
 * to work on std::ios objects. I have to admit I don't remember exactly
 * which operators these are, but some formatting operations need this.
 */

inline LQLogger& LQLogger::operator<< ( std::ios& ( *_f )( std::ios& ) ) {

  if( m_activeType >= m_logWriter->GetMinType() ) {
    ( _f )( *this );
  }
  return *this;
}

/**
 * Messages have a type, defined by the LQMsgType enumeration. This operator
 * allows the user to write intuitive message lines in the code like this:
 *
 * <code>
 *   logger << INFO << "This is an info message" << LQLogger::endmsg;
 * </code>
 */
inline LQLogger& LQLogger::operator<< ( LQMsgType type ) {

  m_activeType = type;
  return *this;
}

// This is a GCC extension for getting the name of the current function.
#if defined( __GNUC__ )
#   define LQLOGGER_FNAME __PRETTY_FUNCTION__
#else
#   define LQLOGGER_FNAME ""
#endif

/// Common prefix for the non-usual messages
/**
 * The idea is that a regular user usually only wants to see DEBUG, INFO
 * and some WARNING messages. So those should be reasonably short. On the other
 * hand serious warnings (ERROR, FATAL) or VERBOSE messages should be as precise
 * as possible.
 *
 * So I stole the idea from Athena (what a surprise...) to have a few macros which
 * produce messages with a common formatting. This macro provides the prefix for
 * all the messages.
 */
#define LQLOGGER_REPORT_PREFIX \
   __FILE__ << ":" << __LINE__ << " (" << LQLOGGER_FNAME << "): "

/// Convenience macro for reporting VERBOSE messages in the code
/**
 * This macro is very similar to the REPORT_MESSAGE macros of Athena. It prints
 * a nicely formatted output that specifies both the exact function name where
 * the message was printed, and also the filename:line combination. It can be used
 * like a regular function inside cycles:
 *
 * <code>
 *   REPORT_VERBOSE( "This is a verbose message with a number: " << number );
 * </code>
 */
#define REPORT_VERBOSE( MESSAGE ) \
  m_logger << VERBOSE << LQLOGGER_REPORT_PREFIX << MESSAGE << LQLogger::endmsg

/// Convenience macro for reporting ERROR messages in the code
/**
 * This macro is very similar to the REPORT_MESSAGE macros of Athena. It prints
 * a nicely formatted output that specifies both the exact function name where
 * the message was printed, and also the filename:line combination. It can be used
 * like a regular function inside cycles:
 *
 * <code>
 *   REPORT_ERROR( "A serious error message" );
 * </code>
 */
#define REPORT_ERROR( MESSAGE ) \
   m_logger << ERROR << LQLOGGER_REPORT_PREFIX << MESSAGE << LQLogger::endmsg

/// Convenience macro for reporting FATAL messages in the code

/**
* This macro is very similar to the REPORT_MESSAGE macros of Athena. It prints
* a nicely formatted output that specifies both the exact function name where
* the message was printed, and also the filename:line combination. It can be used
* like a regular function inside cycles:
*
* <code>
*   REPORT_FATAL( "A very serious error message" );
* </code>
*/
#define REPORT_FATAL( MESSAGE ) \
  m_logger << FATAL << LQLOGGER_REPORT_PREFIX << MESSAGE << LQLogger::endmsg

#endif // LQLogger_H
