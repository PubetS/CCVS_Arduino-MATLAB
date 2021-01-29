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

 p11 =      0.1382;
 p12 =     -0.4216;
 
 x= 0:5:100;
linear = p11*x + p12;

p1 =  -2.262e-11;
       p2 =  -4.086e-09;
       p3 =   1.856e-06;
       p4 =  -0.0001936;
       p5 =    0.008464;
       p6 =   -0.007243;
       p7 =   -0.009617;
       
       
       poly6 = p1.*x.^6 + p2.*x.^5 + p3.*x.^4 + p4.*x.^3 + p5.*x.^2 + p6.*x + p7;
       
       plot (percent,output,'r-^','LineWidth',2)
       axis([0,100,0,13]);
       hold
       plot(x,linear,'g-*','LineWidth',2)
       plot(x,poly6,'m-o','LineWidth',2)
       xlabel('PWM (%)')
       ylabel('Output Voltage (V)')
       grid on
legend('measure','Linear','Polynomial 6')