#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eCliente.h"
#include "eLocalidad.h"
#include "biblioteca.h"


void LocalidadInit(eLocalidad vector[],int tam){
	int i;
	for(i=0;i<tam;i++){
		vector[i].isEmpty=1;
	}
	printf("==========LOCALIDAD=INICIADO===========\n");
}
