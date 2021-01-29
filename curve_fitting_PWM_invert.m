percent = [0
10
20
30
40
50
60
70
80
90
100]';

output = [0
0.5422
2.0422
3.5197
5.0657
6.552
8.096
9.5647
11.1302
12.417
12.417]';

x= 0:1:12;
p11 =       6.617;
p12 =       6.527;
linear =  p11.*x + p12;

 p1 =   -0.000383;
       p2 =     0.01606 ;
       p3 =      -0.259;
       p4 =        2.01;
       p5 =      -7.634;
       p6 =       19.21;
       p7 =      0.5095;
       
       poly6 = p1.*x.^6 + p2.*x.^5 + p3.*x.^4 + p4.*x.^3 + p5.*x.^2 + p6.*x + p7;
       
        plot (output,percent,'r-^','LineWidth',2)
       axis([0,12,0,100]);
       hold
       plot(x,linear,'g--','LineWidth',2)
       plot(x,poly6,'m-o','LineWidth',2)
       ylabel('PWM (%)')
       xlabel('Output Voltage (V)')
       grid on
legend('measure','Linear','Polynomial 6')