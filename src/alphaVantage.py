import os
import sys
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from alpha_vantage.timeseries import TimeSeries

if (len(sys.argv) >= 3):
    passedSymbol = sys.argv[1]
    passedInterval = sys.argv[2]
else:
    sys.exit(1)

if (len(sys.argv) >= 4):
    passedFormat = sys.argv[3]
else:
    passedFormat = 'json'

os.environ["ALPHAVANTAGE_API_KEY"] = 'GRTMSJRG1AXL8822'

ts = TimeSeries(output_format=passedFormat)

data, meta_data = ts.get_intraday(symbol=passedSymbol, interval=passedInterval,
                                  outputsize='full')

print(data)
sys.exit(0)
#
# data['returns'] = np.log(data['4. close'] / data['4. close'].shift(1))
# print(data['returns'])

# cols = []
#
# for momentum in [15, 30, 60]:
#     col = 'position_%s' % momentum
#     data[col] = np.sign(data['returns'].rolling(momentum).mean())
#     cols.append(col)
#
# sns.set()
# strats = ['returns']
# for col in cols:
#     strat = 'strategy_%s' % col.split('_')[1]
#     data[strat] = data[col].shift(1) * data['returns']
#     strats.append(strat)
#
# data[strats].dropna().cumsum().apply(np.exp).plot()
# plt.show()

# Trigger

# Determine stoploss

# Determine Price Target

# Execute Trade


# create simulation to replay historic data
# test algorithms of buying and selling against this
