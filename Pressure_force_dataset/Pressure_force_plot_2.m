figure;

working_dir = pwd;
curved_plate_20mm_dir = strcat(working_dir, '\Curved_plate\C_distance_20mm_combined.csv');
curved_plate_20mm_data = readtable(curved_plate_20mm_dir);
curved_plate_30mm_dir = strcat(working_dir, '\Curved_plate\C_distance_30mm_combined.csv');
curved_plate_30mm_data = readtable(curved_plate_30mm_dir);
curved_plate_40mm_dir = strcat(working_dir, '\Curved_plate\C_distance_40mm_combined.csv');
curved_plate_40mm_data = readtable(curved_plate_40mm_dir);
curved_plate_50mm_dir = strcat(working_dir, '\Curved_plate\C_distance_50mm_combined.csv');
curved_plate_50mm_data = readtable(curved_plate_50mm_dir);

scatter(curved_plate_20mm_data.pressure_reading_1, curved_plate_20mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#77AC30')
hold on
scatter(curved_plate_30mm_data.pressure_reading_1, curved_plate_30mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#EDB120')
hold on
scatter(curved_plate_40mm_data.pressure_reading_1, curved_plate_40mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#D95319')
hold on
scatter(curved_plate_50mm_data.pressure_reading_1, curved_plate_50mm_data.weight_reading_1/1000*9.81, 15, 'o', 'MarkerEdgeColor', '#0072BD')

flat_plate_20mm_dir = strcat(working_dir, '\Flat_plate\F_distance_20mm_combined.csv');
flat_plate_20mm_data = readtable(flat_plate_20mm_dir);
flat_plate_30mm_dir = strcat(working_dir, '\Flat_plate\F_distance_30mm_combined.csv');
flat_plate_30mm_data = readtable(flat_plate_30mm_dir);
flat_plate_40mm_dir = strcat(working_dir, '\Flat_plate\F_distance_40mm_combined.csv');
flat_plate_40mm_data = readtable(flat_plate_40mm_dir);
flat_plate_50mm_dir = strcat(working_dir, '\Flat_plate\F_distance_50mm_combined.csv');
flat_plate_50mm_data = readtable(flat_plate_50mm_dir);

scatter(flat_plate_20mm_data.pressure_reading_1, flat_plate_20mm_data.weight_reading_1/1000*9.81, 15, '^', 'MarkerEdgeColor', '#77AC30')
hold on
scatter(flat_plate_30mm_data.pressure_reading_1, flat_plate_30mm_data.weight_reading_1/1000*9.81, 15, '^', 'MarkerEdgeColor', '#EDB120')
hold on
scatter(flat_plate_40mm_data.pressure_reading_1, flat_plate_40mm_data.weight_reading_1/1000*9.81, 15, '^', 'MarkerEdgeColor', '#D95319')
hold on
scatter(flat_plate_50mm_data.pressure_reading_1, flat_plate_50mm_data.weight_reading_1/1000*9.81, 15, '^', 'MarkerEdgeColor', '#0072BD')
hold on

xlabel("Raw Pressure Reading")
ylabel("Force (N)")
lgd = legend('Curved Plate 20 mm', 'Curved Plate 30 mm', 'Curved Plate 40 mm', 'Curved Plate 50 mm', 'Flat Plate 20 mm', 'Flat Plate 30 mm', 'Flat Plate 40 mm', 'Flat Plate 50 mm');
lgd.FontSize = 10;