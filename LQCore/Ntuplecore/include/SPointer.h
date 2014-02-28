#ifndef SPointer_H
#define SPointer_H

// ROOT include(s):                                                             
#include <TObject.h>

template< class T >
class SPointer : public TObject {

 public:
  /// Constructor taking ownership of the object                               
  SPointer( T* object );
  /// Destructor deleting the owned object                                     
  ~SPointer();

 private:
  /// Object owned by this pointer object                                      
  T* m_object;

}; // class SPointer                                                            

#ifndef __CINT__
#include "SPointer.icc"
#endif

#endif
