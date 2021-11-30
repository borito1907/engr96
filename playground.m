%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                 
% ENGR 96 Mapping Code
% 30 November 2021
% Salih Boran Erol
%
% Draws the basic outline of the course.
% Also draws the drop zone when given the coordinates.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all; clc; close all;

figure(1)
hold on

% Add the lines
line([-0.5715,0.5715],[0,0],'linewidth',2)
line([-0.5715,-0.5715],[0,3.9624],'linewidth',2)
line([0.5715,0.5715],[0,3.9624],'linewidth',2)
line([0.5715,0.5715 + 0.6096],[3.9624,3.9624],'linewidth',2)
line([-0.5715,-0.5715 - 0.6096],[3.9624,3.9624],'linewidth',2)
line([-0.5715 - 0.6096,-0.5715 - 0.6096],[3.9624,3.9624 + 1.143],'linewidth',2)
line([0.5715 + 0.6096,0.5715 + 0.6096],[3.9624,3.9624 + 1.143],'linewidth',2)
line([-0.5715 - 0.6096,0.5715 + 0.6096],[3.9624 + 1.143,3.9624 + 1.143],'linewidth',2)

% Create the circle for the drop zone
circle(0,4.5,0.3048)

title('Course')
xlabel('Distance X (m)')
ylabel('Distance Y (m)')
grid on

function circle(x,y,r)
%x and y are the coordinates of the center of the circle
%r is the radius of the circle
%0.01 is the angle step, bigger values will draw the circle faster but
%you might notice imperfections (not very smooth)
ang=0:0.01:2*pi; 
xp=r*cos(ang);
yp=r*sin(ang);
plot(x+xp,y+yp);
end
