// STL include(s):                                                                                                          
#include <map>
#include <cstdlib>

// ROOT include(s):                                                                                                         
#include <TSystem.h>
#include <TError.h>

// Local include(s):  
#include "LQErrorHandler.h"
#include "LQLogger.h"

/// Local map to translate between ROOT and LQAnalysis message levels                                                           
static std::map< int, LQMsgType > msgLevelMap;

/**                                                                                                                         
 * This function is the "LQAnalysis version" of DefaultErrorHandler defined in the                                              
 * TError.h header. By calling                                                                                              
 *                                                                                                                          
 * <code>                                                                                                                   
 * SetErrorHandler( LQErrorHandler )                                                                                         
 * </code>                                                                                                                  
 *                                                                                                                          
 * somewhere at the beginning of the application, we can channel all ROOT messages                                          
 * through our own message logging facility.                                                                                
 *                                                                                                                          
 * @param level ROOT message level                                                                                          
 * @param abort Flag telling that the process should abort execution                                                        
 * @param location The source of the message                                                                                
 * @param message The message itself                                                                                        
 */


void LQErrorHandler( int level, Bool_t abort, const char* location,
                    const char* message ) {

  // Veto some message locations:                                                                                          
  TString tlocation( location );
  if( tlocation.Contains( "NotifyMemory" ) ) {
    return;
  }
  // Create a local logger object:                                                                                         
  LQLogger logger( location );

  // Initialise the helper map the first time the function is called:                                                      
  if( ! msgLevelMap.size() ) {
    msgLevelMap[ kInfo ]     = INFO;
    msgLevelMap[ kWarning ]  = WARNING;
    msgLevelMap[ kError ]    = ERROR;
    msgLevelMap[ kBreak ]    = ERROR;
    msgLevelMap[ kSysError ] = ERROR;
    msgLevelMap[ kFatal ]    = FATAL;
  }


  // Print the message:                                                                                                    
  logger << msgLevelMap[ level ] << message << LQLogger::endmsg;

  // Abort the process if necessary:                                                                                       
  if( abort ) {
    logger << ERROR << "Aborting..." << LQLogger::endmsg;
    if( gSystem ) {
      gSystem->StackTrace();
      gSystem->Abort();
    } else {
      ::abort();
    }
  }

  return;

}
/**                                                                                                                         
 * The following code makes sure that <code>SetErrorHandler(LQErrorHandler)</code>                                           
 * is called when loading the LQAnalysisCore library. This way all ROOT messages get                                            
 * printed using LQLogger on the PROOF workers from the moment the LQAnalysis libraries                                          
 * are loaded. (This is one of the first things that the workers do...)                                                     
 *                                                                                                                          
 * I "stole" the idea for this kind of code from RooFit actually...                                                         
 */
Int_t SetLQErrorHandler() {

  // Set up LQAnalysis's error handler:                                                                                        
  SetErrorHandler( LQErrorHandler );

  // Report this feat:                                                                                                     
  LQLogger logger( "SetLQErrorHandler" );

  logger << DEBUG << "Redirected ROOT messages to LQAnalys's logger" << LQLogger::endmsg;

  return 0;

}


// Call the function:                                                                                                       
static Int_t dummy = SetLQErrorHandler();
