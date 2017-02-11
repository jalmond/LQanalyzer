# Package information
LIBRARY = Helpers
OBJDIR  = $(OBJ)
DEPDIR  = $(OBJDIR)/dep
SRCDIR  = src
INCDIR  = include

# Overwrite the default rule defined in Makefile.common                                                                                                                      
# Include the generic compilation rules
include $(LQANALYZER_DIR)/Makefile.common
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/Ntuplecore/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/Selection/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/SKTree/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/AnalysisCore/include/
INCLUDES += -I${ROCHDIR}
#INCLUDES += -I$(LQANALYZER_DIR)

ifeq ($(isSLC),False)
	CXXFLAGS= -O2 -std=c++0x  -Wall -fPIC
	CXXFLAGS     += $(ROOTCFLAGS)
endif