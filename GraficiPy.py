import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import imageio as gif
import os


numberOfFiles = input ("Numero dell'ultimo file txt generato dal programma: ")
fileNumber = int(numberOfFiles) + 1
numberOfPoints = input ("Numero di punti da cui e' composto l'intervallo spaziale: ")
pointsNumber = int(numberOfPoints)
for j in range(1, fileNumber):
  name = str(j).zfill(5)

  fileName = "iteration_" + name
  data = pd.read_csv("iteration_"+name+".txt", header = None)

  y = data

  x = np.linspace(0, 1, num = pointsNumber, endpoint = True, retstep = None, dtype = float)
  
  print(fileName)

  plt.plot(x,y)
  plt.title(fileName)
  plt.xlabel("Intervallo normalizzato")
  plt.ylabel("Densita' normalizzata")
  plt.xlim(0, 1)
  plt.ylim(-0.8, 1.4)
  plt.savefig("iteration_"+name+".png")
  plt.gca().cla()

png_dir = "/Users/Gabriele/Desktop/PROGRAMMI_TESI/"
images = []

for filename in os.listdir(png_dir):
  if filename.endswith(".png"):
    print(filename)
    file_path = os.path.join(png_dir, filename)
    images.append(gif.imread(filename))

kargs = {"duration" : 0.05}
gif.mimsave("ANDAMENTO.gif", images, "GIF", **kargs)