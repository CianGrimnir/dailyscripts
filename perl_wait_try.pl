use strict;
use warnings;
use POSIX ":sys_wait_h";

# spawn multiple process concurrently, 
# if one of them get killed, notify user which process got killed.

sub spawn(@) {
	my $pid=fork();
	die "fork: $!" if not defined $pid;
	if ($pid == 0){
		exec @_ or die "exec: $!";
	}
	return $pid;
}
#my %pid_hash;
my $p1=spawn '/bin/bash ~/while.sh 2';			# fork process
my $p2=spawn '/bin/bash ~/while.sh 3';
my $p3=spawn '/bin/bash ~/while.sh 4';
#$pid_hash{first}=$p1;
#$pid_hash{second}=$p2;
#$pid_hash{third}=$p3;
my  %pid_hash=('first',$p1,'second',$p2,'third',$p3); 	# p1,p2,p3 hold pid of each forked process

print "spawn PIDs $p1 and $p2 $p3\n";

while((my $child = waitpid(-1,0)) > 0) {
	my $code= $? >> 8;
	my $status = $? & 0xff;
	my @ keys = grep { $pid_hash{$_} eq $child } keys %pid_hash;
#	printf "child %d finished with exit code %d (status/sig %d)\n)", $child, $code, $status;
#	system("/usr/bin/notify-send 'child $child finished with exit code $code status: $status'")
	system("/usr/bin/notify-send 'process @keys finished with exit code $code status: $status'")
}
