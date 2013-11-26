#ifndef LQError_H
#define LQError_H

// STD include(s):                                                                                                          
#include <exception>
#include <sstream>

class LQError : public std::exception,
                public std::ostringstream {
             
 public:
  /// Severity enumeration                                                                                                 
  /**                                                                                                                      
   * The exception can request an action from the framework. This                                                          
   * can be one of the actions described by the enumeration values.                                                        
   */
  
  enum Severity {
    SkipEvent = 1,     /**< The current event should be skipped from being written */
    SkipFile = 2,      /**< Processing of the current file should stop */
    SkipInputData = 3, /**< Processing of the current input data type should stop */
    SkipCycle = 4,     /**< Running of the current cycle should stop */
    StopExecution = 5  /**< SFrame should stop completely */
  };
  
  /// Constructor specifying only a severity                                                                               
  LQError( Severity severity = SkipEvent ) throw();
  /// Constructor with description and severity                                                                            
  LQError( const char* description, Severity severity = SkipEvent ) throw();
  /// Copy constructor                                                                                                     
  LQError( const LQError& parent ) throw();
  
  /// Destructor                                                                                                           
  virtual ~LQError() throw();
  
  /// Set the description of the exception                                                                                 
  void SetDescription( const char* description ) throw();
  /// Set the severity of the exception                                                                                    
  void SetSeverity( Severity severity ) throw();
  
  /// Get the description of the exception                                                                                 
  virtual const char* what()    const throw();
  /// Get the severity of the exception                                                                                    
  virtual Severity    request() const throw();

  /// Function to get the std::ostream functionality                                                                       
  /**                                                                                                                      
   * A little template magic is needed to provide all the << operator                                                      
   * functionalities of std::ostream to LQError. This function takes                                                        
   * care of that. So in principle you should be able to use an LQError                                                     
   * object as any other kind of std::ostream object.                                                                      
   */
  template < class T > LQError& operator<< ( T arg ) {
    ( * ( std::ostringstream* ) this ) << arg;
    return *this;
  }

  private:
  /// The severity of the exception                                                                                        
  /**                                                                                                                      
   * This member variable describes what the framework should do when                                                      
   * it cathces this exception.                                                                                            
   */
  Severity m_severity;

}; // class LQError
#endif
