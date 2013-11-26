#ifndef SelectionFunctions_h
#define SelectionFunctions_h

#include <vector>

class TString;

static const double Mass_Z = 91.1876;
static const double Mass_W = 80.398;

class SelectionFunctions {

 public:
  
  //// constructors
  SelectionFunctions();
  ~SelectionFunctions();
  
  bool isGoodEvent(int nVertex, std::vector<bool> Vertex_Fake, std::vector<double> Vertex_Ndof, std::vector<double> Vertex_X,  std::vector<double> Vertex_Y, std::vector<double> Vertex_Z, bool *goodVerticies);
 
  
  bool TriggerSelector (std::vector<TString> triggernames, std::vector<std::string> inputtriggers, std::vector<bool> triggerdecision, std::vector<int> HLTPrescales, int &prescaler);
};

#endif

