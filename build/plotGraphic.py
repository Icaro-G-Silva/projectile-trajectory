import pandas as pd
import matplotlib.pyplot as plt

windowTitle = 'Plot Shoot Trajectory'
plotDesign = 'fivethirtyeight'
plotTitle = 'Shoot graphic'
plotLineTitle = 'Projectile Course'
plotXLabel = 'Distance (m)'
plotYLabel = 'Height (m)'
plotColor = '#444444'

alterPath = '../files/'

def getCSVData():
    return pd.read_csv(f'{alterPath}projectile.csv', index_col=0, delimiter=';')

def plot(x, y):
    plt.figure().canvas.set_window_title(windowTitle)
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
plot(dataframe.distance, dataframe.height)
