This is a dual algorithm for finding the difference between two members of an array equaling another member and finding two members to equal the given number S

###running###
    to run this program you must invoke it in a specific way
        ./submission input.txt output.txt
    any other way will not result in a correct invocation.
    specifics on the input and output files are given in #input and #output respectively

##algorithms

#differences
    The differences algorithm only runs if there is no S in the input file. Otherwise, the sums algorithm will run
    The differences algorithm will take the new array created from the input file and sort it using merge sort
    The algorithm will then use a dual pointer/index array method to close in on the desired value
    The algorithm will then output to the output file given. See #output for more detail

#sums
    The sums algorithm only runs if there is a S character detected in the input file. Otherwise, the differences algorithm will run
    The sums algorithm will take the new array created from the input file and sort it using merge sort
    The algorithm will then use a dual pointer/index array method to find each pair of numbers whose sum equals S
    The algorithm will then output to the output file given. See #output for more detail

##this program only works with an input file and output file##

#input file
    the input file must be made in a specific way

    There must be one number on each line
        if there are multiple numbers in a line the program will not work
    The algorithm accounts for lines being commented out with the '/' character and empty lines with \n character
    The algorithm also accounts for lines beginning with NaN. With one exception
        THE CHARACTER S WILL CAUSE A SPECIAL PROCESS

    #The character 'S'
        if the program reads a line starting with the letter 'S' it will assume you want to conduct the 'sums' algorithm and read the next line for what S will equal.
        Please take note when creating your own input files

#output file
    For differences the output file will only display one key of the number whose two members' difference equals
        This can be changed by looking at the commented-out section and uncommenting it to display every instance of this
        This can further be changed to output in the style of "b - c = a" for a full analysis of which members are being used
    
    For sums the output file will display every combination of two numbers whose sums equal another member's value
        This can be changed by looking at the commented-out section and uncommenting it to display one instance of this
        This can further be changed to output in the style of "b + c = S" for a full analysis of which members are being used

Created by Evan Rich, 9/11/24 - last updated 9/13/24