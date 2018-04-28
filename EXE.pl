#print "$ARGV[0] \n";
system("g++", "-std=c++11", "-o", "Exe", "C++_files/main.cpp", "C++_files/Scanner.cpp", "C++_files/Error.cpp");
system("./Exe $ARGV[0]");

#Checks If there were errors, won't run if there are any
#my $filename = 'C++_files/Error_Free.txt';
#$compile_c = 0;
#if (open(my $fh, '<:encoding(UTF-8)', $filename)) {
#  while (my $row = <$fh>) {
#    chomp $row;  
    #if ($row eq "Yes"){
    #	$compile_c = 1;
    #}
#  }
#}

#if ($compile_c eq 1){
	#system("gcc CodeGen_files/CodeGenReg.c -std=c99");
	#system("./a.out");
#} else {
	#print "* Could Not Compile C Code Due To Errors *\n";		
#}