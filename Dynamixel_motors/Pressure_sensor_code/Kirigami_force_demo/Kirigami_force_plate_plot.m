clear
clc

line_1 = animatedline('Color',[0, 0.4470, 0.7410], 'LineWidth', 1.5);
line_2 = animatedline('Color',[0.8500, 0.3250, 0.0980], 'LineWidth', 1.5);
% set(gca, 'XLim',[40 220], 'YLim',[0 210])
axis([40 220 0 210])
xlabel("Raw Pressure Reading");
ylabel("Force Exertion (g)");
title("Force vs Pressure Plot");


T = readtable('Kirigami_force_demo.xlsm','Sheet','45mm_calibration_359_video','Format','auto');

for j = 1:length(T.Average_raw_pressure_reading)

    addpoints(line_1, T.Average_raw_pressure_reading(j), T.Force_g(j))
    
    F(j) = getframe(gcf);
    pause(0.05)

    % update screen
    drawnow

end

pause(0.5);

force_exertion = 40:3:220;
predicted_force_exertion = -0.003155.*force_exertion.^2+1.937.*force_exertion-75.03;

for k = 1:length(force_exertion)

    addpoints(line_2, force_exertion(k), predicted_force_exertion(k))
    F(j+k) = getframe(gcf);
    % update screen
    drawnow

end

video = VideoWriter('calibration_plot.mp4');
open(video);
writeVideo(video, F);
close(video);



% force_exertion = 40:1:220;
% predicted_force_exertion = -0.003155.*force_exertion.^2+1.937.*force_exertion-75.03;
% plot(force_exertion, predicted_force_exertion,LineWidth=1);



% plot(T.Average_raw_pressure_reading,T.Force_N, LineWidth=1)
% hold on;
% 
% disp("predicted_force_exertion = -0.003155*force_exertion^2+1.937*force_exertion-75.03")
% 
% force_exertion = 40:1:220;
% predicted_force_exertion = -0.003155.*force_exertion.^2+1.937.*force_exertion-75.03;
% plot(force_exertion, predicted_force_exertion,LineWidth=1);



