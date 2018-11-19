# Package information
LIBRARY = AnalyzerTools80X
OBJDIR  = $(OBJ)
DEPDIR  = $(OBJDIR)/dep
SRCDIR  = src
INCDIR  = include

# Overwrite the default rule defined in Makefile.common                                                                                                                      
# Include the generic compilation rules
include $(LQANALYZER_DIR)/bin/Make/Makefile.common
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/80X/Ntuplecore/include/
INCLUDES += -I$(LQANALYZER_DIR)/LQCore/80X/Selection/include/
INCLUDES += -I${ROCHDIR80X}

ifeq ($(isSLC),False)
	CXXFLAGS= -O2 -std=c++0x  -Wall -fPIC
	CXXFLAGS     += $(ROOTCFLAGS)
endif