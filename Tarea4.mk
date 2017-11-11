Resultados_hw4.pdf: *.png
	pdflatex Resultados_hw4.tex

*.png *.wav: datos.dat amplitudes.dat plots.py
	python plots.py

datos.dat:a.out
	./a.out

a.out: Ondas.c
	gcc Ondas.c -lm

clean:
	rm -f *.wav amplitudes.dat datos.dat datos2.dat a.out *.png *.pdf *.aux *.log
