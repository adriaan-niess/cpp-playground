import numpy as np
from numpy import genfromtxt
from numpy.core.fromnumeric import prod

for config in ['blocking', 'lockfree']:
    print("=== {} ===".format(config))

    producer_data = genfromtxt('results/{}_producer.csv'.format(config), delimiter=',')
    consumer_data = genfromtxt('results/{}_consumer.csv'.format(config), delimiter=',')
    latency = consumer_data[:,1] - producer_data[:,1]

    print("Min: {}ns".format(np.min(latency)))
    print("Max: {}ns".format(np.max(latency)))
    print("Median: {}ns".format(np.median(latency)))
    print("Mean: {}ns".format(np.mean(latency)))
