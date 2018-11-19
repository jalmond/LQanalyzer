#ifndef LQLogWriter_H
#define LQLogWriter_H


// STL include(s):
#include <string>
#include <map>

// Local include(s):
#include "LQMsgType.h"


/**
 *   @short Message writing class
 *
 *          Singleton class for actually writing the formatted
 *          messages to the console.
 *
 *          Right now it only writes messages to the terminal, but
 *          one possibility would be to write messages to a file
 *          for batch running later on. (Just an idea...)
 *
 *     @see LQLogger
 * @version $Revision: 1 $
 */

class LQLogWriter {

 public:
  /// Function for accessing the single object
  static LQLogWriter* Instance();
  /// Default destructor
  ~LQLogWriter();

  /// Function writing a message to the output
  void Write( LQMsgType type, const std::string& line ) const;

  /// Set the message type above which messages are printed
  void SetMinType( LQMsgType type );
  /// Get the message type above which messages are printed
  LQMsgType GetMinType() const;

 protected:
  /// Protected default constructor
  LQLogWriter();

 private:
  static LQLogWriter* m_instance;

  std::map< LQMsgType, std::string > m_typeMap;
  std::map< LQMsgType, std::string > m_colorMap;
  LQMsgType                          m_minType;

}; // class LQLogWriter

#endif //LQLogWriter_H
