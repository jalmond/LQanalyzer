#ifndef LQErrorHandler_H
#define LQErrorHandler_H

// ROOT include(s):                                                                                                         
#include <TError.h>

/// Function printing log messages from ROOT                                                                                
extern void LQErrorHandler( int level, Bool_t abort, const char* location,
                           const char* message );

#endif 



