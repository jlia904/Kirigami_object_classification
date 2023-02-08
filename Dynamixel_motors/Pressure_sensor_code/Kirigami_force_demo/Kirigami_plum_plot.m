clear
clc

line_1 = animatedline('Color',[0, 0.4470, 0.7410], 'LineWidth', 1.5);
axis([0 161 0 160]);
xlabel("Raw Pressure Reading");
ylabel("Force Exertion (g)");
title("Force vs Pressure Plot");


T = readtable('Kirigami_force_demo.xlsm','Sheet','plum_401_video','Format','auto');

predicted_force_exertion = -0.003155.*T.Average_raw_pressure_reading.^2+1.937.*T.Average_raw_pressure_reading-75.03;


for j = 1:length(predicted_force_exertion)

    addpoints(line_1, j, predicted_force_exertion(j))
    
    F(j) = getframe(gcf);
    pause(0.6)

    % update screen
    drawnow

end


video = VideoWriter('plum_plot.mp4');
open(video);
writeVideo(video, F);
close(video);



% force_exertion = 40:1:220;
% predicted_force_exertion = -0.003155.*force_exertion.^2+1.937.*force_exertion-75.03;
% plot(force_exertion, predicted_force_exertion,LineWidth=1);

% predicted_force_exertion = -0.003155.*T.Average_raw_pressure_reading.^2+1.937.*T.Average_raw_pressure_reading-75.03
% 
% plot(1:1:length(T.Average_raw_pressure_reading),T.Average_raw_pressure_reading, LineWidth=1)
% hold on;
% plot(1:1:length(T.Average_raw_pressure_reading),predicted_force_exertion, LineWidth=1)
% % 
% disp("predicted_force_exertion = -0.003155*force_exertion^2+1.937*force_exertion-75.03")
% 
% force_exertion = 40:1:220;
% predicted_force_exertion = -0.003155.*force_exertion.^2+1.937.*force_exertion-75.03;
% plot(force_exertion, predicted_force_exertion,LineWidth=1);



