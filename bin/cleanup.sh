#!/bin/sh

### setup paths to be used in analysis code

function_remove(){
    cd $1
    echo "Cleaning up " $1     
    rm *~
    rm *.d
    rm *_cc*
    rm *_C*
    rm *.so
    cd -
}



if [[ $1 == --h* ]]
    then    
    echo "source cleanup.sh : remove all temp files only"
    echo "source cleanup.sh main : remove all dependency files and lib files in LQanalyzer"
    echo "source cleanup.sh tree : remove all dependency files and lib files in SNUTree"
    echo "source cleanup.sh all/-all/-a : remove all dependency files and lib files : "

    
else
    if [[ $1  == "all" ]] 
        then 
        
        function_remove $LQANALZER_DIR/src/
        function_remove $LQANALZER_DIR/include/	
	function_remove $LQANALZER_DIR/Selection/	
	function_remove $LQANALZER_DIR/scripts/	
	function_remove $LQANALZER_DIR/Plotting/	
	function_remove $LQANALZER_DIR/run/	
	function_remove $LQANALZER_DIR/SNUTree/src/
	function_remove $LQANALZER_DIR/SNUTree/include/
	
    else 
	if [[ $1  == "-all" ]] 
        then 
        
        function_remove $LQANALZER_DIR/src/
        function_remove $LQANALZER_DIR/include/	
	function_remove $LQANALZER_DIR/Selection/	
	function_remove $LQANALZER_DIR/scripts/	
	function_remove $LQANALZER_DIR/Plotting/	
	function_remove $LQANALZER_DIR/run/	
	function_remove $LQANALZER_DIR/SNUTree/src/
	function_remove $LQANALZER_DIR/SNUTree/include/	
	else 
	    if [[ $1  == "-a" ]] 
            then 
		
		function_remove $LQANALZER_DIR/src/
		function_remove $LQANALZER_DIR/include/	
		function_remove $LQANALZER_DIR/Selection/	
		function_remove $LQANALZER_DIR/scripts/	
		function_remove $LQANALZER_DIR/Plotting/	
		function_remove $LQANALZER_DIR/run/	
		function_remove $LQANALZER_DIR/SNUTree/src/
		function_remove $LQANALZER_DIR/SNUTree/include/	
	    else 
		
		if [[ $1  == "tree" ]]
		then
		    
		    function_remove $LQANALZER_DIR/SNUTree/src/
		    function_remove $LQANALZER_DIR/SNUTree/include/
		else
		    if [[ $1  == "-main" ]]
		    then
			function_remove $LQANALZER_DIR/src/
			function_remove $LQANALZER_DIR/include/
			function_remove $LQANALZER_DIR/Selection/
			function_remove $LQANALZER_DIR/scripts/
			function_remove $LQANALZER_DIR/run/
			function_remove $LQANALZER_DIR/Plotting/
			
		    else 
			cd $LQANALZER_DIR
			rm *~
			rm */*~
			rm */*/*~
			rm */*/*/*~		
			cd -
		    fi
		fi
	    fi
	fi	
    fi
fi

