import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from alpha_vantage.timeseries import TimeSeries
# from alpha_vantage.sectorperformance import SectorPerformances
# import matplotlib.pyplot as plt

os.environ["ALPHAVANTAGE_API_KEY"] = 'GRTMSJRG1AXL8822'

ts = TimeSeries(output_format='pandas')

data, meta_data = ts.get_intraday(symbol='TSLA', interval='1min',
                                  outputsize='compact')

print(data)

data['returns'] = np.log(data['4. close'] / data['4. close'].shift(1))
print(data['returns'])

cols = []

for momentum in [15, 30, 60]:
    col = 'position_%s' % momentum
    data[col] = np.sign(data['returns'].rolling(momentum).mean())
    cols.append(col)

sns.set()
strats = ['returns']
for col in cols:
    strat = 'strategy_%s' % col.split('_')[1]
    data[strat] = data[col].shift(1) * data['returns']
    strats.append(strat)

data[strats].dropna().cumsum().apply(np.exp).plot()
plt.show()
# Trigger

# Determine stoploss

# Determine Price Target

# Execute Trade


# create simulation to replay historic data
# test algorithms of buying and selling against this
