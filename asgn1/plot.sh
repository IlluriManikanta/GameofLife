#!/bin/bash

#Makes dat files clean and compiles Monte_carlo using make
make clean && make monte_carlo

#Files created

#Tmp files for graph1
>/tmp/graph1_out.dat
>/tmp/blue.dat
>/tmp/red.dat

#Tmp files for graph2
>/tmp/graph2_out1.dat
>/tmp/graph2_out2.dat
>/tmp/graph2_out3.dat
>/tmp/graph2_out4.dat
>/tmp/lightblue.dat
>/tmp/blue2.dat
>/tmp/gold.dat
>/tmp/yellow.dat


#Graph 1 (Figure 2)

#Running monte carlo for 1000 iterations and putting output data into tmp file
./monte_carlo -n 1000 >> /tmp/graph1_out.dat 

#Using awk to read colum 5 to see if circle is 0 or 1, if ) will put x and y values into red.dat if 1 will put x y values into blue.dat
awk '{if($5 == 0){print $3" "$4}}' /tmp/graph1_out.dat >> /tmp/red.dat
awk '{if($5 == 1){print $3" "$4}}' /tmp/graph1_out.dat >> /tmp/blue.dat

#Gnuplot commands to set graph format
gnuplot <<END
	set terminal pdf
	set output "graph1.pdf"
	set title "Graph1"
	set xlabel "x"
	set ylabel "y"
	set xrange [0:1]
	set xtics 0.2
	set yrange [0:1]
	set ytics 0.2
	set size square 1,1
	set zeroaxis
	set key off


	plot "/tmp/blue.dat" with dots lt rgb "blue", "/tmp/red.dat" with dots lt rgb "red", [0:1] sqrt(1-x**2) lt rgb "black" 
	
END
#Plots graph with color
echo "Done Plotting Graph 1!"



#Graph 2 (Figure 3)

#Running monte carlo for random seed iterations and putting output data into tmp file
./monte_carlo -n 16384 -r "$RANDOM" >/tmp/graph2_out1.dat 
#Using awk file to compare pi value with estimated pi value, data will be sent to tmp file 
awk '{print $1" "(3.1415926535897932 - $2)}' /tmp/graph2_out1.dat | tail +2 >>/tmp/lightblue.dat 

#Running monte carlo for random seed iterations and putting output data into tmp file
./monte_carlo -n 16384 -r "$RANDOM" >/tmp/graph2_out2.dat
#Using awk file to compare pi value with estimated pi value, data will be sent to tmp file 
awk '{print $1" "(3.1415926535897932 - $2)}' /tmp/graph2_out2.dat | tail +2 >>/tmp/blue2.dat 

#Running monte carlo for random seed iterations and putting output data into tmp file
./monte_carlo -n 16384 -r "$RANDOM" >/tmp/graph2_out3.dat
#Using awk file to compare pi value with estimated pi value, data will be sent to tmp file 
awk '{print $1" "(3.1415926535897932 - $2)}' /tmp/graph2_out3.dat | tail +2 >>/tmp/gold.dat 

#Running monte carlo for random seed iterations and putting output data into tmp file
./monte_carlo -n 16384 -r "$RANDOM" >/tmp/graph2_out4.dat
#Using awk file to compare pi value with estimated pi value, data will be sent to tmp file 
awk '{print $1" "(3.1415926535897932 - $2)}' /tmp/graph2_out4.dat | tail +2 >>/tmp/yellow.dat 

#Gnuplot commands to set graph format
gnuplot <<END
    set terminal pdf 
    set output "graph2.pdf"
    set xlabel "PI & ~PI"
    set xrange [1:16384]
    set ylabel "Error"	
    set yrange [-1:1]
    set ytics 0.5
    set grid
    set zeroaxis
    set logscale x 4
    set key off
    
    plot "/tmp/lightblue.dat" with lines lt rgb "blue", "/tmp/blue2.dat" with lines lt rgb "green", "/tmp/gold.dat" with lines lt rgb "yellow", "/tmp/yellow.dat" with lines lt rgb "orange"
    
END
#Plots graph with color
echo "Done Plotting Graph 2!"


