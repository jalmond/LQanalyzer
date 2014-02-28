# $Id: CycleCreators.py 173 jalmond $
###########################################################################
# @Project: LQAnalyze - ROOT-based analysis framework for CMS             #
#                                                                         #
# @author J. Almond <jalmond@cern.ch> -  SNU                              #
#                                                                         #
###########################################################################

## @package CycleCreators
#    @short Functions for creating a new analysis cycle torso
#
# This package collects the functions used by LQanalyzer_create_cycle.py
# to create the torso of a new analysis cycle. Apart from using
# LQanalyzer_create_cycle.py, the functions can be used in an interactive
# python session by executing:
#
# <code>
#  >>> import CycleCreators
# </code>                                           

class CycleCreator:

    _headerFile = ""
    _sourceFile = ""
    
    def __init__( self ):
        self._headerFile = ""
        self._sourceFile = ""

    ## @short Template for cycle outside of a namespace
    #
    # This string is used by CreateHeader to create a header file that
    # holds a cycle which is not in a namespace.
    _header = """// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py  jalmond $
#ifndef %(class)-s_H
#define %(class)-s_H

#include \"AnalyzerCore.h\"

/**
*   @short Put short description of class here
*
*          Put a longer description over here...
*
*  @author Put your name here
* @version $Revision: 1 $
*/
class %(class)-s : public AnalyzerCore { 



public:
   /// Default constructor
   %(class)-s();
   /// Default destructor
   ~%(class)-s();

    /// Function called at the beginning of the cycle
    virtual void BeginCycle(TString filename) throw( LQError );
    /// Function called at the beginning of each event
    virtual void BeginEvent() throw( LQError );
    /// Function called for eac event
    virtual void ExecuteEvents()throw( LQError );
    /// Function called at the end of each event
    virtual void EndEvent()throw( LQError );
    /// Function called at the end of each cycle 
    virtual void EndCycle()throw( LQError );
    virtual void ClearOutputVectors()throw( LQError );

    void MakeHistograms();
    
private:
   //
   // Put all your private variables here
   //
   
   // Macro adding the functions for dictionary generation
   ClassDef( %(class)-s, 0 );
 
}; // class %(class)-s

#endif // %(class)-s_H

"""
    

    ## @short Function creating an analysis cycle header
    #
    # This function can be used to create the header file for a new analysis
    # cycle.
    #
    # @param cycleName Name of the analysis cycle. 
    # @param fileName  Optional parameter with the output header file name
    def CreateHeader( self, cycleName, fileName = "" ):

        # Construct the file name if it has not been specified:
        if fileName == "":
            fileName = cycleName + ".h"
            
        # Some printouts:
        print "CreateHeader:: Cycle name     = " + cycleName
        print "CreateHeader:: File name      = " + fileName
        self._headerFile = fileName
            
        # Create a backup of an already existing header file:
        import os.path
        if os.path.exists( fileName ):
            print "CreateHeader:: File \"" + fileName + "\" already exists"
            print "CreateHeader:: Moving \"" + fileName + "\" to \"" + \
                      fileName + ".backup\""
            import shutil
            shutil.move( fileName, fileName + ".backup" )

        # Write the header file:
        output = open( fileName, "w" )
        output.write( self._header % { 'class' : cycleName } )
                
        return

    ## @short Template for cycle outside of a namespace
    #
    # This string is used by CreateSource to create a source file that
    # holds a cycle which is not in a namespace.
    _source = """// $Id: CycleCreators.py 1 jalmond $
    
// Local include(s):
#include \"%(dir)-s/%(class)-s.h\"

ClassImp( %(class)-s );

/// core includes
#include \"EventBase.h\"

%(class)-s::%(class)-s()
: AnalyzerCore() {  

// To have the correct name in the log:
SetLogName(\" %(class)-s \" );

}

%(class)-s::~%(class)-s() {
}

void %(class)-s::BeginCycle) throw( LQError ){

}

void %(class)-s::BeginEvent()throw( LQError ){

}

void %(class)-s::ExecuteEvents()throw( LQError ){
}

void %(class)-s::EndCycle()throw( LQError ){

}


void %(class)-s::EndEvent()throw( LQError ){

}
void %(class)-s::MakeHistograms(){
//// Additional plots to make

maphist.clear();
AnalyzerCore::MakeHistograms();
Message("Made histograms", INFO);
/**
*  Remove//Overide this AnalyzerCore::MakeHistograms() to make new hists for your analysis
**/

}

void %(class)-s::ClearOutputVectors() throw(LQError) {

// This function is called before every execute event (NO need to call this yourself.

// Add any new output vector you create to this list.
// if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents an\
d will use excessive amoun of memory
//
// Reset all variables declared in Declare Variable
//
//out_muons.clear();

}




"""
    

    ## @short Function creating the analysis cycle source file
    #
    # This function creates the source file that works with the header created
    # by CreateHeader. It is important that CreateHeader is executed before
    # this function, as it depends on knowing where the header file is
    # physically. 
    #
    # @param cycleName Name of the analysis cycle. 
    # @param fileName  Optional parameter with the output source file name
    def CreateSource( self, cycleName, fileName = "" ):
        
         # Construct the file name if it has not been specified:
         if fileName == "":
             fileName = cycleName + ".cc"
             
         # Some printouts:
         print "CreateSource:: Cycle name     = " + cycleName
         print "CreateSource:: File name      = " + fileName
         self._sourceFile = fileName

    
         # The following is a tricky part. Here I evaluate how the source file
         # will be able to include the previously created header file.
         # Probably a Python guru could've done it in a shorter way, but
         # at least it works.
         import os.path
         hdir = os.path.dirname( self._headerFile )
         sdir = os.path.dirname( self._sourceFile )
         prefix = os.path.commonprefix( [ self._headerFile, self._sourceFile ] )
         
         hdir = hdir.replace( prefix, "" )
         sdir = sdir.replace( prefix, "" )
         
         nup = sdir.count( "/" );
         nup = nup + 1
         dir = ""
         for i in range( 0, nup ):
             dir = dir.join( [ "../", hdir ] )
    
         # Create a backup of an already existing header file:
         if os.path.exists( fileName ):
             print "CreateHeader:: File \"" + fileName + "\" already exists"
             print "CreateHeader:: Moving \"" + fileName + "\" to \"" + \
                   fileName + ".backup\""
             import shutil
             shutil.move( fileName, fileName + ".backup" )
             
         # Write the source file:
         output = open( fileName, "w" )
         output.write( self._source % { 'dir'   : dir,
                                        'class' : cycleName } )
         return
      
    
    ## @short Function adding link definitions for rootcint
    #
    # Each new analysis cycle has to declare itself in a so called "LinkDef
    # file". This makes sure that rootcint knows that a dictionary should
    # be generated for this C++ class.
    #
    # This function is also quite smart. If the file name specified does
    # not yet exist, it creates a fully functionaly LinkDef file. If the
    # file already exists, it just inserts one line declaring the new
    # cycle into this file.
    #
    # @param cycleName Name of the analysis cycle. Can contain the namespace name.
    # @param fileName  Optional parameter with the LinkDef file name
    def AddLinkDef( self, cycleName, fileName = "LinkDef.h" ):

        import os.path
        if os.path.exists( fileName ):
            print "AddLinkDef:: Extending already existing file \"" + fileName + "\""
            # Read in the already existing file:
            output = open( fileName, "r" )
            lines = output.readlines()
            output.close()
            
            # Find the "#endif" line:
            endif_line = ""
            import re
            for line in lines:
                if re.search( "#endif", line ):
                    endif_line = line
            if endif_line == "":
                print "AddLinkDef:: ERROR File \"" + file + "\" is not in the right format!"
                print "AddLinkDef:: ERROR Not adding link definitions!"
                return
            index = lines.index( endif_line )

            # Add the line defining the current analysis cycle:
            lines.insert( index, "#pragma link C++ class %s+;\n" % cycleName )
            lines.insert( index + 1, "\n" )

            # Overwrite the file with the new contents:
            output = open( fileName, "w" )
            for line in lines:
                output.write( line )
            output.close()

        else:
            # Create a new file and fill it with all the necessary lines:
            print "AddLinkDef:: Creating new file called \"" + fileName + "\""
            output = open( fileName, "w" )
            output.write( "// Dear emacs, this is -*- c++ -*-\n" )
            output.write( "// $Id: CycleCreators.py 1 2013-01-12 15:49:33Z jalmond $\n\n" )
            output.write( "#ifdef __CINT__\n\n" )
            output.write( "#pragma link off all globals;\n" )
            output.write( "#pragma link off all classes;\n" )
            output.write( "#pragma link off all functions;\n\n" )
            output.write( "#pragma link C++ nestedclass;\n\n" )
            output.write( "#pragma link C++ class %s+;\n\n" % cycleName )
            output.write( "#endif // __CINT__\n" )

        return

    ## @short Main analysis cycle creator function
    #
    # The users of this class should normally just use this function
    # to create a new analysis cycle.
    #
    # It only really needs to receive the name of the new cycle, it can guess
    # the name of the LinkDef file by itself if it has to. It calls all the
    # other functions of this class to create all the files for the new
    # cycle.
    #
    # @param cycleName Name of the analysis cycle. Can contain the namespace name.
    # @param linkdef Optional parameter with the name of the LinkDef file
    def CreateCycle( self, cycleName, linkdef = "" ):
        
        className = cycleName
        
        # Check if a directory called "include" exists in the current directory.
        # If it does, put the new header in that directory. Otherwise leave it up
        # to the CreateHeader function to put it where it wants.

        import os.path
        if os.path.exists( "./include" ):

            print "making header"
            self.CreateHeader( cycleName, "./include/" + className + ".h" )
            
            if linkdef == "":
                import glob
                filelist = glob.glob( "./include/*LinkDef.h" )
                if len( filelist ) == 0:
                    print "CreateCycle:: WARNING There is no LinkDef file under ./include"
                    print "CreateCycle:: WARNING Creating one with the name ./include/LinkDef."


                    linkdef = "./include/LinkDef.h"
                elif len( filelist ) == 1:
                    linkdef = filelist[ 0 ]

                else:
                    print "CreateCycle:: ERROR Multiple header files ending in LinkDef.h"
                    print "CreateCycle:: ERROR I don't know which one to use..."
                    return

            self.AddLinkDef( cycleName, linkdef )
        else:
            self.CreateHeader( cycleName )

            if linkdef == "":
                import glob
                filelist = glob.glob( "*LinkDef.h" )
                if len( filelist ) == 0:
                    print "CreateCycle:: Creating new LinkDef file: LinkDef.h"
                    linkdef = "LinkDef.h"

                elif len( filelist ) == 1:
                    linkdef = filelist[ 0 ]
                else:
                    print "CreateCycle:: ERROR Multiple header files ending in LinkDef.h"
                    print "CreateCycle:: ERROR I don't know which one to use..."
                    return
                self.AddLinkDef( cycleName, linkdef )

        if os.path.exists( "./src" ):
            self.CreateSource( cycleName, "./src/" + className + ".cc" )
        else:
            self.CreateSource( cycleName )

        return
