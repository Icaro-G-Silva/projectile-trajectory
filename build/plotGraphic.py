import pandas as pd
import matplotlib.pyplot as plt

windowTitle = 'Plot Projectile Trajectory'
plotDesign = 'fivethirtyeight'
plotTitle = 'Trajectory graphic'
plotLineTitle = 'Projectile Course'
plotXLabel = 'Distance (m)'
plotYLabel = 'Height (m)'
plotColor = '#444444'

alterPath = '../files/'

def getCSVData():
    return pd.read_csv(f'{alterPath}projectile.csv', delimiter=';')

def plot(x, y):
    plt.figure().canvas.manager.set_window_title(windowTitle)
    plt.style.use(plotDesign)
    plt.plot(x, y, color=plotColor, linestyle='--', linewidth=2, label=plotLineTitle)
    plt.title(plotTitle)
    plt.xlabel(plotXLabel)
    plt.ylabel(plotYLabel)
    plt.legend()
    plt.grid(False)
    plt.tight_layout()
    plt.savefig(f'{alterPath}projectileTrajectory.png')
    plt.show()

dataframe = getCSVData()

max_height = dataframe['height'].max()
max_height_time = dataframe['time'][dataframe['height'].idxmax()]
max_distance = dataframe['distance'].max()
max_distance_time = dataframe['time'][dataframe['distance'].idxmax()]

print(f'Maximum height reached: {max_height}m at {max_height_time}s\nMaximum distance reached: {max_distance}m at {max_distance_time}s\n')

plot(dataframe.distance, dataframe.height)
