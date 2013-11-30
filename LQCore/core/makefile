# $Id: Makefile
###########################################################################                                                                                                    
# @Project: LQAnalyzer - ROOT-based analysis framework for Korea CMS      #                                                                                                    
#                                                                         #                                                                                                    
# @author John Almond       jalmond@cern.ch>           - SNU              #                                                                                                    
# Top level Makefile for compiling all the LQAnalyzer code                #                                                                                                    
#                                                                         #                                                                                                    
###########################################################################                                                                                                    


# Package information
LIBRARY = core
OBJDIR  = obj
DEPDIR  = $(OBJDIR)/dep
SRCDIR  = src
INCDIR  = include

coredefault: default $(LQANALYZER_BIN_PATH)/run_lqanalyzer   

# Include the generic compilation rules
include $(LQANALYZER_DIR)/Makefile.common

INCLUDES += -I$(LQANALYZER_DIR)/LQCore/SKTree/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCycle/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/Plotting/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/Selection/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/AnalysisCore/include/


$(LQANALYZER_BIN_PATH)/run_lqanalyzer: run_lqanalyzer.o $(SHLIBFILE)                                                                           
	@echo "Linking " $@                                                                                                                     
	@$(LD) $(LDFLAGS) $(OBJDIR)/run_lqanalyzer.o -L$(LQANALYZER_LIB_PATH) -lcore -lSNUTree -lHist -lAnalysisCore   \
                $(ROOTLIBS) -lPyROOT  -o $@                                                                                                    

run_lqanalyzer.o: app/run_lqanalyzer.cxx                                                                                                       
	@echo "Compiling $<"                                                                                                                    
	@mkdir -p $(OBJDIR)                                                                                                                     
	@$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(notdir $@) $(INCLUDES)