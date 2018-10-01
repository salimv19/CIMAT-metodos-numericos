import matplotlib.pylab as plt
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-x", "--xVector", nargs='+', type=float, required=True, help="Vector with x coordinates")
ap.add_argument("-y", "--yVector", nargs='+', type=float, required=True, help="Vector with y coordinates")
ap.add_argument("-t", "--plotTrue", type=int, required=True, help="Flag for true points plot")
ap.add_argument("-xT", "--xTrueVector", nargs='+', type=float, help="Vector with x coordinates")
ap.add_argument("-yT", "--yTrueVector", nargs='+', type=float, help="Vector with y coordinates")
args = vars(ap.parse_args())

#plt.axhline(0, color='k')
#plt.axvline(0, color='k')
if (args["plotTrue"]):
	plt.plot(args["xTrueVector"], args["yTrueVector"])
plt.plot(args["xVector"], args["yVector"])
plt.show() 