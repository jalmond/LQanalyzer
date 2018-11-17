#ifndef LQMsgType_H
#define LQMsgType_H

enum LQMsgType {
  VERBOSE = 1, /**< Type for the most detailed messages. Only for serious debugging. */
  DEBUG = 2,   /**< Type for debugging messages. A few messages per event allowed. */
  INFO = 3,    /**< Type for normal information messages. No messages in event processing! */
  WARNING = 4, /**< Type for smaller problems. (Analysis is not affected in general.) */
  ERROR = 5,   /**< Type for "real" problems. (Analysis results probably affected.) */
  FATAL = 6,   /**< Type for problems that should halt the execution. */
  ALWAYS = 7   /**< Type that should always be shown. (Not really used.) */
};


#endif // LQCore/core/LQMsgType_H




