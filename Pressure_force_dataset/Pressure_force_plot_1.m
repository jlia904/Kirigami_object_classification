figure;

working_dir = pwd;

curved_plate_40mm_dir = strcat(working_dir, '/Curved_plate/C_distance_40mm_cycle.csv');
curved_plate_40mm_data = readtable(curved_plate_40mm_dir);


scatter(curved_plate_40mm_data.weight_reading_1/1000*9.81, curved_plate_40mm_data.pressure_reading_1, 15, 'o', 'MarkerEdgeColor', '#D95319')
hold on


flat_plate_40mm_dir = strcat(working_dir, '/Flat_plate/F_distance_40mm_cycle.csv');
flat_plate_40mm_data = readtable(flat_plate_40mm_dir);

scatter(flat_plate_40mm_data.weight_reading_1/1000*9.81, flat_plate_40mm_data.pressure_reading_1, 15, 'o', 'MarkerEdgeColor', '#0072BD')
hold on

ylabel("Raw Pressure Reading")
xlabel("Force (N)")

xlim([0, 2.1])



x = 0:0.1:2.1;
curved_fit = -12.6*x.^3+42.27*x.^2+15.93.*x+0.8248;
flat_fit = -3.47*x.^3+20.3*x.^2+15.35.*x+0.6163;
plot(x,curved_fit, 'LineWidth', 2, 'Color', '#77AC30');
hold on
plot(x, flat_fit, 'LineWidth', 2, 'Color', '#EDB120')
lgd = legend('Curved Plate 40 mm', 'Flat Plate 40 mm', 'y=-12.6x^3+42.3x^2+15.9x+0.8', 'y=-3.5x^3+20.3x^2+15.4x+0.6');
lgd.FontSize = 11;