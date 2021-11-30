

clear all; clc; close all;

figure(1)
hold on

% Add the lines
% Create template for the drop zone
% line([x1 x2], [y1 y2], 'linewidth',2)
line([-0.5715,0.5715],[0,0],'linewidth',2)
line([-0.5715,-0.5715],[0,3.9624],'linewidth',2)
line([0.5715,0.5715],[0,3.9624],'linewidth',2)
line([0.5715,0.5715 + 0.6096],[3.9624,3.9624],'linewidth',2)
line([-0.5715,-0.5715 - 0.6096],[3.9624,3.9624],'linewidth',2)
line([-0.5715 - 0.6096,-0.5715 - 0.6096],[3.9624,3.9624 + 1.143],'linewidth',2)
line([0.5715 + 0.6096,0.5715 + 0.6096],[3.9624,3.9624 + 1.143],'linewidth',2)
line([-0.5715 - 0.6096,0.5715 + 0.6096],[3.9624 + 1.143,3.9624 + 1.143],'linewidth',2)

title('Course')
xlabel('Distance X (m)')
ylabel('Distance Y (m)')
grid on

