Resultados_hw4.pdf: *.png
	pdflatex Resultados_hw4.tex

*.png *.wav: datos.dat amplitudes.dat plots.py
	python plots.py

datos.dat:a.out
	./a.out > amplitudes.dat

a.out: Ondas.c
	gcc Ondas.c -lm

clean:
	rm -f *.wav *.dat a.out *.png *.pdf *.aux *.log
