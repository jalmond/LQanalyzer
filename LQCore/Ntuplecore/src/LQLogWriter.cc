// System include(s):                                                                                                       
extern "C" {
#   include <unistd.h>
}

// STL include(s):                                                                                                          
#include <iostream>

// Local include(s):                                                                                                        
#include "LQLogWriter.h"

LQLogWriter* LQLogWriter::m_instance = 0;

/**                                                                                                                         
 * This function implements the singleton design pattern for the                                                            
 * class. Since the constructor of the class is "protected", the                                                            
 * user can not create it manually. He/she has to access a (single)                                                         
 * instance of the object with this function.                                                                               
 */
LQLogWriter* LQLogWriter::Instance() {

  if( ! m_instance ) {
    m_instance = new LQLogWriter();
  }

  return m_instance;
}
/**                                                                                                                         
 * This is also one of the "don't do anything" destructors.                                                                 
 */
LQLogWriter::~LQLogWriter() {

}

/**                                                                                                                         
 * This function is the heavy-lifter of the class. It writes the received                                                   
 * message to the console. The function assumes that the message has no                                                     
 * line breaks and that it has been formatted by LQLogger.                                                                   
 *                                                                                                                          
 * @param type The message type                                                                                             
 * @param line A single line of message to be displayed.                                                                    
 */
void LQLogWriter::Write( LQMsgType type, const std::string& line ) const {

  if( type < m_minType ) return;
  std::map< LQMsgType, std::string >::const_iterator stype;
  if( ( stype = m_typeMap.find( type ) ) == m_typeMap.end() ) return;

  // Print the output in colours only if it's printed to the console. If it's                                              
  // redirected to a logfile, then produce simple black on while output.                                                   
  if( isatty( STDOUT_FILENO ) ) {
    std::cout << m_colorMap.find( type )->second << " (" << stype->second << ")  "
	      << line << "\033[0m" << std::endl;
  } else {
    std::cout << " (" << stype->second << ")  " << line << std::endl;
  }

  return;
}



/**                                                                                                                         
 * This function sets the minimum message type that should still be                                                         
 * displayed. All messages having a higher priority will be displayed                                                       
 * as well of course.                                                                                                       
 *                                                                                                                          
 * @param type The value of the minimum type                                                                                
 * @see LQLogWriter::GetMinType                                                                                              
 */
void LQLogWriter::SetMinType( LQMsgType type ) {

  m_minType = type;
  return;
}


/**                                                                                                                         
 * Not much to say here.                                                                                                    
 *                                                                                                                          
 * @see LQLogWriter::SetMinType                                                                                              
 */
LQMsgType LQLogWriter::GetMinType() const {

  return m_minType;
}

/**                                                                                                                         
 * The constructor takes care of filling the two std::map-s that are                                                        
 * used for generating the nice colured output.                                                                             
 */
LQLogWriter::LQLogWriter()
  : m_minType( INFO ) {

  m_typeMap[ VERBOSE ] = "VERBOSE";
  m_typeMap[ DEBUG ]   = " DEBUG ";
  m_typeMap[ INFO ]    = " INFO  ";
  m_typeMap[ WARNING ] = "WARNING";
  m_typeMap[ ERROR ]   = " ERROR ";
  m_typeMap[ FATAL ]   = " FATAL ";
  m_typeMap[ ALWAYS ]  = "ALWAYS ";

  m_colorMap[ VERBOSE ] = "\033[1;34m";
  m_colorMap[ DEBUG ]   = "\033[34m";
  m_colorMap[ INFO ]    = "\033[32m";
  m_colorMap[ WARNING ] = "\033[35m";
  m_colorMap[ ERROR ]   = "\033[31m";
  m_colorMap[ FATAL ]   = "\033[1;31;40m";
  m_colorMap[ ALWAYS ]  = ""; // Used to be: "\033[30m";        
}
