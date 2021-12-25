import numpy as np
from numpy import genfromtxt
from numpy.core.fromnumeric import prod
import matplotlib.pyplot as plt

data = []
configs = ['blocking', 'lockfree']
for config in configs:
    print("=== {} ===".format(config))

    producer_data = genfromtxt('results/{}_producer.csv'.format(config), delimiter=',')
    consumer_data = genfromtxt('results/{}_consumer.csv'.format(config), delimiter=',')
    latency = (consumer_data[:,1] - producer_data[:,1]) / 1e3
    data.append(latency)

    print("Min: {}ns".format(np.min(latency)))
    print("Max: {}ns".format(np.max(latency)))
    print("Median: {}ns".format(np.median(latency)))
    print("Mean: {}ns".format(np.mean(latency)))

fig1, ax1 = plt.subplots()
ax1.set_title('Queuing latencies')
ax1.boxplot(data, labels=configs)
ax1.set_ylabel('Latency [us]')

plt.savefig('results/queuing_latencies.png')
#plt.show()
