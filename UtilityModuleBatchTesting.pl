#!/usr/local/bin/perl
#
# testing Utility module in batch
#


$filename = $ARGV[0];
$timeLogFilename=$ARGV[1];
open(FILE1,"$filename");
open(FILE2,">>$timeLogFilename");
@lines=<FILE1>;
close(FILE1);

foreach $line(@lines) {
	
	$cmd1 = "./convert -blaPDB $line";
	$cmd2 = "./convert -blaNR $line";
	$cmd3 = "./convert -hhr $line";
	$cmd4 = "./convert -hhrNR $line";
	$cmd5 = "./convert -cnfSearch $line";

	$start_run = time();
	print $cmd1."\n";
	system($cmd1);
	print $cmd2."\n";
	system($cmd2);
	print $cmd3."\n";
	system($cmd3);
	print $cmd4."\n";
	system($cmd4);
	print $cmd5."\n";
	system($cmd5);
	$end_run = time();
	$run_time = $end_run - $start_run;
	print FILE2 "$line running time: $run_time \n";
}
close(FILE2);


