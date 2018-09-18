import matplotlib.pylab as plt
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-xV", "--xVector", nargs='+', type=float, required=True, help="Vector with x coordinates")
ap.add_argument("-yV", "--yVector", nargs='+', type=float, required=True, help="Vector with y coordinates")
ap.add_argument("-x", "--xPoint", nargs='+', type=float, required=True, help="Point x coordinate")
ap.add_argument("-y", "--yPoint", nargs='+', type=float, required=True, help="Point y coordinate")
args = vars(ap.parse_args())

plt.axhline(0, color='k')
plt.axvline(0, color='k')
plt.plot(args["xVector"], args["yVector"], linewidth=3)
plt.plot(args["xPoint"], args["yPoint"], "ro")
plt.show() 