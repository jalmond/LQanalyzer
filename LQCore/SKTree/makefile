 # $Id: Makefile 120 2013-11-26 16:42:57Z jalmond $
 ###########################################################################
 # @Project: SFrame - ROOT-based analysis framework for ATLAS              #
 # @Package: User                                                          #
 #                                                                         #
 # @author John       <John.Almond@cern.ch>                - SNU           #
 #                                                                         #
 # Makefile compiling the SNUTree    library.                              #
 #                                                                         #
 ###########################################################################
# Package information
LIBRARY = SNUTree
OBJDIR  = obj
DEPDIR  = $(OBJDIR)/dep
SRCDIR  = src
INCDIR  = include


# Override default target so we can install the rootmap file
SNUTreedefault: default rootmap SNUTreeUnit

# Include the generic compilation rules
include $(LQANALYZER_DIR)/Makefile.common

SNUTreeUnit: SNUTreeUnit.o $(SHLIBFILE)
	@echo "Linking " $@
	@$(LD) $(LDFLAGS) -O2 $(OBJDIR)/SNUTreeUnit.o -L$(LQANALYZER_LIB_PATH) \
                $(ROOTLIBS) -lSNUTree -o $@

SNUTreeUnit.o: SNUTreeUnit.cxx include/KParticle.h
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -O2 -c $< -o $(OBJDIR)/$(notdir $@) $(INCLUDES)

#install the rootmap file
rootmap: $(LQANALYZER_DIR)/SNUTree/util/SNUTree.rootmap
	@echo "Installing rootmap " $<
	(cp $< $(LQANALYZER_LIB_PATH)/.)



