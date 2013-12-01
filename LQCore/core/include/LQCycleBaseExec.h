#ifndef LQCycleBaseExec_H
#define LQCycleBaseExec_H

// Local include(s):
#include "LQCycleBaseBase.h"
#include "SNUTreeFiller.h"

class LQCycleBaseExec :   public virtual LQCycleBaseBase , public SNUTreeFiller{

 public:
  /// Default constructor  
  LQCycleBaseExec();

  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  //   The following are the functions to be implemented in the derived    //
  //   classes.                                                            //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////

  /// Initialisation called at the beginning of a full cycle
  /**
   * Analysis-wide configurations, like the setup of some reconstruction
   * algorithm based on properties 
   */

  virtual void BeginCycle(TString filename)throw( LQError );

  /**
   * Called before the  event. Gets the weight from the configured job
   **/
  virtual void BeginEvent()throw( LQError );
  
  /// Function called for every event
  /**
   * This is the function where the main analysis should be done. By the
   * time it is called, all the input variables are filled with the
   * contents of the actual event.
   */
  virtual void ExecuteEvents() throw( LQError );

  /**  
   *  Called at end of cycle
   *
   **/
  virtual void EndCycle()throw( LQError );
  virtual void EndEvent()throw( LQError );
  
  /**
   *   Interates through the ntuple
   *
   **/
  virtual void SetUpEvent(Long64_t jevent, float ev_weight)throw( LQError );

  ClassDef(LQCycleBaseExec, 0 );
};

#endif
