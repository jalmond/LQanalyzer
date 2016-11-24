### Change tag name if not fresh terminal
current_tag=$CATTAG
source $1
# scripts/setup/SetBrachAndTag.sh
new_tag=$CATTAG
if [[ $current_tag != $new_tag ]];then
    echo     "@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    echo     "This is a new tag. You need to work from a new terminal"
    echo     "@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    echo     " This message will stop when you have setup CATANalyzer in a fresh terminal."
    make distclean
fi