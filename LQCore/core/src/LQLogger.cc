// STL include(s):                                                                                                          
#include <iomanip>
#include <iostream>

// ROOT include(s):                                                                                                         
#include "TObject.h"

// Local include(s):
#include "LQLogger.h"

using namespace std;

/// Hard-coded maximum length of the source names                                                                           
static const string::size_type MAXIMUM_SOURCE_NAME_LENGTH = 18;


LQLogger::LQLogger( const TObject* source )
  : m_objSource( source ), m_strSource( "" ), m_activeType( INFO ) {

  m_logWriter = LQLogWriter::Instance();

}


LQLogger::LQLogger( const string& source )
  : m_objSource( 0 ), m_strSource( source ), m_activeType( INFO ) {

  m_logWriter = LQLogWriter::Instance();

}

LQLogger::LQLogger( const LQLogger& parent )
  : std::basic_ios< LQLogger::char_type, LQLogger::traits_type >(),
    ostringstream() {

  *this = parent;

}

/**                                                                                                                         
 * The destructor is literally not doing anything...                                                                        
 */
LQLogger::~LQLogger() {

}


void LQLogger::SetSource( const TObject* source ) {

  m_objSource = source;
  m_strSource = "";
  return;

}

void LQLogger::SetSource( const std::string& source ) {

  m_objSource = 0;
  m_strSource = source;
  return;

}


LQLogger& LQLogger::operator= ( const LQLogger& parent ) {

  m_objSource = parent.m_objSource;
  m_strSource = parent.m_strSource;
  m_logWriter = LQLogWriter::Instance();

  return *this;

}

void LQLogger::Send( const LQMsgType type, const string& message ) const {

  if( type < m_logWriter->GetMinType() ) return;

  string::size_type previous_pos = 0, current_pos = 0;

  //                                                                                                                       
  // Make sure the source name is no longer than MAXIMUM_SOURCE_NAME_LENGTH:                                               
  //                                                                                                                       
  string source_name;
  if( m_objSource ) {
    source_name = m_objSource->GetName();
  } else {
    source_name = m_strSource;
  }
  if( source_name.size() > MAXIMUM_SOURCE_NAME_LENGTH ) {
    source_name = source_name.substr( 0, MAXIMUM_SOURCE_NAME_LENGTH - 3 );
    source_name += "...";
  }

  //                                                                                                                       
  // Slice the recieved message into lines:                                                                                
  //                                                                                                                       
  for( ; ; ) {

    current_pos = message.find( '\n', previous_pos );
    string line = message.substr( previous_pos, current_pos - previous_pos );

    ostringstream message_to_send;
    // I have to call the modifiers like this, otherwise g++ get's confused                                               
    // with the operators...                                                                                              
    message_to_send.setf( ios::adjustfield, ios::left );
    message_to_send.width( MAXIMUM_SOURCE_NAME_LENGTH );
    message_to_send << source_name << " : " << line;
    m_logWriter->Write( type, message_to_send.str() );

    if( current_pos == message.npos ) break;
    previous_pos = current_pos + 1;
  }

  return;

}


void LQLogger::Send() {

  //                                                                                                                       
  // Call the "other" send(...) function:                                                                                  
  //                                                                                                                       
  this->Send( m_activeType, this->str() );

  //                                                                                                                       
  // Reset the stream buffer:                                                                                              
  //                                                                                                                       
  this->str( "" );

  return;

}



LQLogger& LQLogger::endmsg( LQLogger& logger ) {

  logger.Send();
  return logger;

}


