figure;

working_dir = pwd;

curved_plate_40mm_dir = strcat(working_dir, '/Curved_plate/C_distance_40mm_cycle.csv');
curved_plate_40mm_data = readtable(curved_plate_40mm_dir);


scatter(curved_plate_40mm_data.pressure_reading_1, curved_plate_40mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#D95319')
hold on


flat_plate_40mm_dir = strcat(working_dir, '/Flat_plate/F_distance_40mm_cycle.csv');
flat_plate_40mm_data = readtable(flat_plate_40mm_dir);



scatter(flat_plate_40mm_data.pressure_reading_1, flat_plate_40mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#0072BD')
hold on

xlabel("Raw Pressure Reading")
ylabel("Force (N)")
lgd = legend('Curved Plate 40 mm', 'Flat Plate 40 mm');
ylim([0, 2.1])

lgd.FontSize = 11;