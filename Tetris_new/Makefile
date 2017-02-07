compilar: main_new.c funciones.c
	gcc -c funciones.c -lallegro -lallegro_main -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_dialog
	ar rv libfunciones.a funciones.o
	gcc -o main main_new.c -L. -lfunciones -lallegro -lallegro_main -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_dialog