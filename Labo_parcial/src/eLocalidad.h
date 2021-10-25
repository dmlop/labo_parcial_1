

#ifndef ELOCALIDAD_H_
#define ELOCALIDAD_H_

typedef struct{
	int id;
	int isEmpty;
	char localidad[51];
}eLocalidad;
void LocalidadInit(eLocalidad vector[],int tam);


#endif /* ELOCALIDAD_H_ */
