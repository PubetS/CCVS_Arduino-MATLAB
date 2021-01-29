%a = arduino();
clear all
interv = 500;
passo = 1;
t=1;
x=0;
y=0;
y3=0;
y5=0;
y9=0;
z3=0.4;
z5=z3;
z9=z3;
% z=readVoltage(a,'A0');
figure
hold on
while(t<interv)
% b=readVoltage(a,'A0');
b=(rand(1)*0.02)+0.4; %(rand(number of random)* numbet_of_diferrent_up%dowm) + number_of_start 
x=[x,b];
%z=0.8546*z+0.1454*b; %fc = 0.5, SF = 0.05

z3=0.9813*z3+0.01869*b; %fc = 0.3, SF = 0.01
y3=[y3,z3];
z5=0.9691*z5+0.03093*b; %fc = 0.5, SF = 0.01
y5=[y5,z5];
z9=0.945*z9+0.05498*b; %fc = 0.9, SF = 0.01
y9=[y9,z9];

% z=0.9691*z+0.03093*b; %fc = 0.5, SF = 0.01
% y=[y,z];

plot(x,'r','LineWidth',1);
% plot(y,'b','LineWidth',1);
plot(y3,'b','LineWidth',1);
plot(y5,'g','LineWidth',1);
plot(y9,'y','LineWidth',1);
axis([0,interv,0.3,0.5]);
% grid
t=t+passo;
drawnow;
end
% legend('without LPF','With LPF')
% meanx = mean(x(100:interv));
% Iin_nofilX = meanx*1000
% meany = mean(y(100:interv));
% Iin_nofilY = meany*1000
% Iin1 = 835.74*meany+82.543
% Iin2 = 8743.4*meany^6-37353*meany^5+60434*meany^4-...
%     45769*meany^3+15894*meany^2-1090.7*meany+90.707