import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.mlab import bivariate_normal


#GRÁFICAS DE LAS CUERDAS
init_cuerda1 = np.genfromtxt("cond_ini_cuerda.dat")
datos_cuerdas = np.genfromtxt("datos.dat") #este archivo contiene todos los datos de los tiempos en columnas
amplitudes = np.genfromtxt("amplitudes.dat")
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
plt.savefig("plots_guitarrafija.png")

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
plt.savefig("plots_cuerdasuelta.png")


#GRÁFICAS DEL TAMBOR
x0 = y0 = np.linspace(0, 0.5, 101)
init_tambor = np.genfromtxt("cond_ini_tambor.dat", delimiter=" ")
ladox, ladoy = np.meshgrid(x0, y0)

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot_surface(ladox, ladoy, init_tambor, color='violet', linewidth=0)
ax.set_xlabel('Lado X (m)')
ax.set_ylabel('Lado Y (m)')
ax.set_zlabel('Amplitud (m)')
ax.tick_params(labelsize=7)
plt.title("Condición inicial del tambor")
plt.savefig("Tambor_init.png")

datos_tambor = np.genfromtxt("datos2.dat")
z_toctavos = np.reshape(datos_tambor[:, 0], (101,101))
z_tcuartos = np.reshape(datos_tambor[:, 1], (101,101))
z_tmedios = np.reshape(datos_tambor[:, 2], (101,101))

fig2 = plt.figure()
ax2 = fig2.gca(projection='3d')
ax2.plot_surface(ladox, ladoy, z_toctavos, color='violet', linewidth=0)
ax2.set_xlabel('Lado X (m)')
ax2.set_ylabel('Lado Y (m)')
ax2.set_zlabel('Amplitud (m)')
ax2.tick_params(labelsize=7)
plt.title("Estado del tambor en $T/8$")
plt.savefig("Tambor_toctavos.png")

fig3 = plt.figure()
ax3 = fig3.gca(projection='3d')
ax3.plot_surface(ladox, ladoy, z_tcuartos, color='violet', linewidth=0)
ax3.set_xlabel('Lado X (m)')
ax3.set_ylabel('Lado Y (m)')
ax3.set_zlabel('Amplitud (m)')
ax3.tick_params(labelsize=7)
plt.title("Estado del tambor en $T/4$")
plt.savefig("Tambor_tcuartos.png")

fig4 = plt.figure()
ax4 = fig4.gca(projection='3d')
ax4.plot_surface(ladox, ladoy, z_tmedios, color='violet',linewidth=0)
ax4.set_xlabel('Lado X (m)')
ax4.set_ylabel('Lado Y (m)')
ax4.set_zlabel('Amplitud (m)')
ax4.tick_params(labelsize=7)
plt.title("Estado del tambor en $T/2$")
plt.savefig("Tambor_tmedios.png")
