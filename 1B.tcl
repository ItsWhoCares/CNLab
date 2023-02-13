set ns [new Simulator]
set f [open out.tr w]
$ns trace-all $f
set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 2ms DropTail
$ns duplex-link $n1 $n2 1Mb 2ms DropTail
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n1 $n2 queuePos 0.5
$ns queue-limit $n0 $n1 10
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
set null0 [new Agent/Null]
$ns attach-agent $n2 $null0
set null1 [new Agent/Null]
$ns attach-agent $n1 $null1
$ns connect $udp0 $null0
$ns at 1.0 "$cbr0 start"
puts [$cbr0 set packetSize_]
puts [$cbr0 set interval_]
$ns at 3.0 "finish"
proc finish {} {
	global ns f nf
	$ns flush-trace
	close $f
	close $nf
	puts "running nam..."
	exec nam out.nam &
	exit 0
}
$ns run
