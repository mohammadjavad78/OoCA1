module c1908 (N1,N4,N7,N2753,N2754,N2755);

input N1,N4,N7;

output N2753;

wire N190,N251;

not NOT1_1 (N190, N1);
nand NAND2_17 (N251, N190, N4);
and AND8_764 (N2753, N1, N4, N7);
endmodule