import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile

init_cuerda1 = np.genfromtxt("cond_ini_cuerda.dat")
datos_cuerdas = np.genfromtxt("datos.dat") #este archivo contiene todos los datos de los tiempos en columnas
amplitudes = np.genfromtxt("amplitudes.dat")
init_tambor = np.genfromtxt("cond_ini_tambor.dat", delimiter=" ")
phi_ini1 = init_cuerda1[:,1]
phi_ini2 = np.zeros(129)
toctavos1 = datos_cuerdas[:,0]
toctavos2 = datos_cuerdas[:,1]
tcuartos1 = datos_cuerdas[:,2]
tcuartos2 = datos_cuerdas[:,3]
tmedios1 = datos_cuerdas[:,4]
tmedios2 = datos_cuerdas[:,5]
x = np.linspace(0, 0.64, 129)

plt.figure()
plt.title("Solución de $\phi$ para cuerda con extremos fijos")
plt.xlabel("$x$")
plt.ylabel("$\phi(x,t)$")
plt.plot(x, phi_ini1, label="$t=0$")
plt.plot(x, toctavos1, label="$t=T/8$")
plt.plot(x, tcuartos1, label="$t=T/4$")
plt.plot(x, tmedios1, label="$t=T/2$")
plt.legend()
plt.savefig("plots_guitarrafija.pdf")

scipy.io.wavfile.write("sonido.wav", 100000, amplitudes)
plt.figure()
plt.title("Solución de $\phi$ para cuerda con perturbación en un extremo")
plt.xlabel("$x$")
plt.ylabel("$\phi(x,t)$")
plt.plot(x, phi_ini2, label="$t=0$")
plt.plot(x, toctavos2, label="$t=T/8$")
plt.plot(x, tcuartos2, label="$t=T/4$")
plt.plot(x, tmedios2, label="$t=T/2$")
plt.legend(loc=2)
plt.savefig("plots_cuerdasuelta.pdf")
