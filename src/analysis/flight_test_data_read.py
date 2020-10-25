import csv
import gmplot
from matplotlib import pyplot as plt
from numpy import array, concatenate, average
plt.rcParams['axes.grid'] = True

filename = "TESTLOG.txt"
plot_group = array([3, 3, 1, 1, 2, 2, 2])

f = open(filename, "r")
results = []
reader = csv.reader(f)  # change contents to floats
for row in reader:  # each row is a list
    results.append(row)
output = array(results)
n_parameters = len(output[1, :])
only_odd = [num for num in range(2, n_parameters) if num % 2 == 1]
jj = 0
if max(plot_group) > 1:
    fig, axes = plt.subplots(nrows=max(plot_group), ncols=1)
    axes[0].set_title(filename)
    axes[-1].set_xlabel(output[0, 0])
    for ii in only_odd:
        if plot_group[jj] > 0:
            axes[plot_group[jj] - 1].plot(output[:, 1].astype(float), output[:, ii].astype(float),
                                          label=output[1, ii - 1])
            axes[plot_group[jj] - 1].legend()
        jj = jj + 1
elif max(plot_group) == 1:
    plt.title(filename)
    plt.xlabel(output[0, 0])
    for ii in only_odd:
        if plot_group[jj] > 0:
            plt.plot(output[:, 1].astype(float), output[:, ii].astype(float),
                     label=output[1, ii - 1])
            plt.legend()
        jj = jj + 1
plt.show()

if sum(output[1, :] == ' longitude'):
    long_index = output[1, :] == ' longitude'
    long_index = [i for i, val in enumerate(long_index) if val]
    lat_index = output[1, :] == ' latitude'
    lat_index = [i for i, val in enumerate(lat_index) if val]
    api_key = ''  # (your API key here)
    lat = output[:, lat_index[0] + 1].astype(float)
    long = output[:, long_index[0] + 1].astype(float)
    g_map = gmplot.GoogleMapPlotter(average(lat), average(long), 14, apikey=api_key)
    coordinates = zip(*concatenate((lat.reshape((-1, 1)), long.reshape((-1, 1))), axis=1))
    g_map.plot(*coordinates, 'cornflowerblue', edge_width=2.5)
    g_map.draw('map.html')
