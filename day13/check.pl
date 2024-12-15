#!/usr/bin/env perl
#
# Day 13, Parts 1 and 2 in a single loop.  The problem is really a system
# of two equations with two unknowns and thus (relatively) easily calculated.
# The Part 1 approach with dynamic programming is an embarassing overkill and
# only goes to confirm that, if all you have is a hammer, everything looks
# like a nail.  One needs to think before jumping into programming!

use strict;
use warnings;

my ($Xa, $Xb, $Ya, $Yb);
use constant ADJ => 10000000000000;

           # Part 1   Part 2
my @sum = (  0,       0     );

while (<>) {
    if (/Button A: X\+(\d+), Y\+(\d+)/) {
        ($Xa, $Ya) = ($1, $2);
    } elsif (/Button B: X\+(\d+), Y\+(\d+)/) {
        ($Xb, $Yb) = ($1, $2);
    } elsif (/Prize: X=(\d+), Y=(\d+)/) {
        my ($X, $Y) = ($1, $2);
        my @problems = ([$X, $Y], [$X + ADJ, $Y + ADJ]);
        for (my $i = 0; $i < scalar(@problems); ++$i) {
            my ($X, $Y) = @{$problems[$i]};
            # my $bad_b = ($Y - $X * $Ya / $Xa)
            #                /
            #         ($Yb - $Xb * $Ya / $Xa)
            #         ;
            # Above is "bad" because it does not generate integer solutions.
            # Reducing number of divisions from 3 to 1 makes bogus fractional
            # parts disappear.
            #
            my $b = ($Y * $Xa - $X * $Ya)
                           /
                   ($Yb * $Xa - $Xb * $Ya)
                   ;
            my $a = ($X - $b * $Xb) / $Xa;
            if ($b == int($b) && $a == int($a)) {
                my $sol += $a * 3 + $b;
                $sum[$i] += $sol;
                # print "Part $i: Line $.: a=$a; b=$b; solution: $sol\n";
            } else {
                # print "Part $i: Line $.: no solution: $b\n";
            }
        }
    }
}

print "Part 1 Sum: $sum[0]\n";
print "Part 2 Sum: $sum[1]\n";
