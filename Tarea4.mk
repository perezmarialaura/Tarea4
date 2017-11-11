Resultados_hw4.pdf: plots_guitarrafija.pdf plots_cuerdasuelta.pdf
	pdflatex Resultados_hw4.tex

plots_guitarrafija.pdf plots_cuerdasuelta.pdf sonido.wav: datos.dat
	python plots.py

datos.dat:compila
	./a.out > amplitudes.dat

compila: Ondas.c
	gcc Ondas.c -lm

clean:
	rm -f sonido.wav amplitudes.dat datos.dat a.out plots_guitarrafija.pdf plots_cuerdasuelta.pdf Resultados_hw4.pdf Resultados_hw4.aux Resultados_hw4.log
