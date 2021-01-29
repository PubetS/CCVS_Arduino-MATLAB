%a = arduino();
interv = 200;
passo = 1;
t=1;
x=0;
y3=0;
y5=0;
y9=0;
% z=readVoltage(a,'A0');

while(t<interv)
b=readVoltage(a,'A0');
x=[x,b];

z3=0.9813*z3+0.01869*b; %fc = 0.3, SF = 0.01
y3=[y3,z3];
z5=0.9691*z5+0.03093*b; %fc = 0.5, SF = 0.01
y5=[y5,z5];
z9=0.945*z9+0.05498*b; %fc = 0.9, SF = 0.01
y9=[y9,z9];

t=t+passo;

end
meanx = mean(x(10:interv));
Iin_nofilX = meanx*1000
meany = mean(y(10:interv));
Iin_nofilY = meany*1000
Iin1 = 835.74*meany+82.543
Iin2 = 8743.4*meany^6-37353*meany^5+60434*meany^4-...
    45769*meany^3+15894*meany^2-1090.7*meany+90.707

 xvalue = 3;
 Voc = xvalue * Iin2
 Voc2 = 0.1959*(Voc/1000) - 0.0002
 if Voc2 >= 1 
     Voc2 = 1; 
 end
 
 writePWMDutyCycle(a,'D3',Voc2);

%cure fitting from MATLAB cftool
% l = -567.2;
% m =  -22.44;
% n =  2280;
% linearFit = l*(sin(meany-pi))+m*((meany-10)^2)+n*(1)
% 
%      p1 =8743 ; p2 = -3.735e+04;p3 =6.043e+04; p4 =-4.577e+04; p5 =   1.589e+04 ;
%      p6 = -1091; p7 =90.71 ;
%      
% Poly6 = p1*meany^6 + p2*meany^5 + p3*meany^4 + p4*meany^3 + p5*meany^2 +...
%     p6*meany + p7
% 
%  p11 = 2.857e+05;
%  p21 =  -1.845e+06;
%  p31 =   5.005e+06;
%  p41 =  -7.401e+06;
%  p51 =   6.471e+06;
%  p61 =  -3.396e+06;
%  p71 =   1.038e+06;
%  p81 =  -1.715e+05;
%  p91 =   1.441e+04;
%  p101 =      -350.7;
% poly9 = p11*meany^9 + p21*meany^8 + p31*meany^7 + p41*meany^6 + ...
%     p51*meany^5 + p61*meany^4 + p71*meany^3 + p81*meany^2 + p91*meany + p101