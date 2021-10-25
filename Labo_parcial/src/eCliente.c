#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eCliente.h"
#include "eLocalidad.h"
#include "biblioteca.h"
/// @brief inicializa toda el vector con isEmpty=1
///
/// @param vector- vector de cliente a iniciar
/// @param tam - tamaño del vector
void ClienteInit(eCliente vector[],int tam){
	int i;
	for(i=0;i<tam;i++){
		vector[i].isEmpty=1;
	}
	printf("==========PROGRAMA=INICIADO===========\n");
}
/// @brief Pide datos y agrega un cliente a la lista
///
/// @param vector - vector de clientes
/// @param tam - tamaño del vector de clientes
/// @param aux - auxiliar que guardara los datos ingresados por el usuario de forma momentanea
/// @param id - puntero del contador de id que se le asignara al nuevo cliente.
void AgregarCliente(eCliente vector[],int tam,eCliente auxC,int* id,eLocalidad vectorL[],int tamL,eLocalidad auxL,int* idL){
	int cPasos;
	cPasos=1;
	do{
		switch(cPasos){
		case 1://NOMBRE EMPRESA
			if(GetCharNombre(auxC.nombreEmpresa, 51, "Ingrese el Nombre de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4)){
				cPasos++;
			}
			else{
				cPasos=-1;

			}
			break;
		case 2://CUIT
			if(GetCharCuit(auxC.cuit, 51, "Ingrese su CUIT: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 4)){
				cPasos++;
			}
			else{
				cPasos=-1;
			}
			break;
		case 3://DIRECCION
			if(GetCharLNPC(auxC.direccion, 51, "Ingrese la Direccion: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 4)){
				cPasos++;
			}
			else{
				cPasos=-1;
			}
			break;
		case 4://LOCALIDAD
			if(GetCharLNPC(auxL.localidad, 51, "Ingrese la Localidad: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 4)){
				cPasos++;
			}
			else{
				cPasos=-1;
			}
			break;
		case 5://VUELVE
			cPasos=5;
			break;
		}


	}while(cPasos!=5&&cPasos!=-1);
	auxC.id=*id;
	auxC.isEmpty=0;

	for(int i=0;i<tamL;i++){
		if(vectorL[i].isEmpty==0&&strcmp(auxL.localidad,vectorL[i].localidad)==0){
			auxC.idL=vectorL[i].id;
			break;
		}
		else{
			if(vectorL[i].isEmpty==1){
				vectorL[i].id=*idL;
				vectorL[i].isEmpty=0;
				strncpy(vectorL[i].localidad,auxL.localidad,51);
				auxC.idL=vectorL[i].id;
				*idL=*idL+1;
			}
		}
	}

	if(CargarCliente(vector,tam,auxC)==-1||cPasos==-1){
		printf("===NO=SE=PUDO=CARGAR=CLIENTE===\n");
	}
	else{
		printf("=====CLIENTE=CARGADO=ID=%d=====",*id);
		*id=*id+1;
	}

}
/// @brief  buscara un lugar libre en la lista y copiara los datos guardados en la variable eCliente auxiliar
///   		a la lista de cliente en la posicion disponible.
///
/// @param vector - vector de clientes
/// @param tam - tamaño del vector de clientes
/// @param aux - variable eCliente auxiliar que contiene la informacion del nuevo cliente
/// @return devuelve 0 si hay algun problema. y 1 si sale todo bien.
int CargarCliente(eCliente vector[],int tam,eCliente aux){

	int posicion;

	posicion=BuscarEmptyCliente(vector,tam);
	if(posicion!=-1){
		vector[posicion].id=aux.id;
		strncpy(vector[posicion].nombreEmpresa,aux.nombreEmpresa,sizeof(vector[posicion].nombreEmpresa));
		strncpy(vector[posicion].cuit,aux.cuit,sizeof(vector[posicion].cuit));
		strncpy(vector[posicion].direccion,aux.direccion,sizeof(vector[posicion].direccion));
		vector[posicion].idL=aux.idL;
		vector[posicion].isEmpty=0;
	}
	return posicion;
}
/// @brief Busca en un vector eCliente un lugar disponible para cargar un nuevo cliente.
///
/// @param vector - vector eCliente
/// @param tam - tamaño del vector eCliente
/// @return - devuelve 0 si hay algun problema. y 1 si sale todo bien.
int BuscarEmptyCliente(eCliente vector[],int tam){
	int retorno;
	retorno=-1;
	for(int i=0;i<tam;i++){
		if(vector[i].isEmpty==1){
			retorno=i;
			break;
		}
	}
	return retorno;
}
/// @brief  Pide al usuario un id de un cliente activo, busca en el vector eCliente
/// 		un cliente con el mismo id y devuelve el id y la posicion del cliente
/// @param vector - vector eCliente
/// @param tam - tamaño del vector
/// @param auxId - puntero auxiliar del id ingresado por el usuario si es que se encontro un cliente con ese id
/// @return - devuelve -1 si no encontro ningun cliente con ese id y si encontro un cliente con la id ingresada
/// 		devuelve la posicion del cliente en el vector.
int BuscarClientePorId(eCliente vector[],int tam,int* auxId){
	int retorno;
	int id;
	retorno=-1;
	GetIntR(&id, "Ingrese el ID del cliente: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4);

	for(int i=0;i<tam;i++){
		if(vector[i].id==id&&vector[i].isEmpty==0){
			retorno=i;
			*auxId=vector[i].id;
			break;
		}
	}
	return retorno;
}
/// @brief imprime una lista de clientes, mostrando su id y su nombre
///
/// @param vector - vector eCliente
/// @param tam - tamaño del vector
/// @return devuelve 0 si hay algun problema y 1 si no.
int ImprimirClientes(eCliente vector[],int tam){
	int retorno;
	retorno=0;
	printf("=====LISTA=DE=CLIENTES====\n");
	for(int i=0;i<tam;i++){
		if(vector[i].isEmpty==0){
			printf("%d -- %s\n",vector[i].id,vector[i].nombreEmpresa);
			retorno=1;
		}
	}
	return retorno;
}
//-----------------HARD CODE TEST-------------------
void ClientesTesteo(eCliente vector[],int *id,int* altas,int actividad){

	if(actividad==1){
		printf("=====CLIENTES=DE=TESTEO=CARGADOS=====\n");
		vector[0].id=*id;
		vector[0].isEmpty=0;
		strncpy(vector[0].nombreEmpresa,"Marolio",51);
		strncpy(vector[0].cuit,"12-34940336-8",15);
		strncpy(vector[0].direccion,"Cantinfla 220",51);
		vector[0].idL=1;
		*id=*id+1;
		*altas=*altas+1;

		vector[1].id=*id;
		vector[1].isEmpty=0;
		strncpy(vector[1].nombreEmpresa,"HellsMans",51);
		strncpy(vector[1].cuit,"12-34231336-8",15);
		strncpy(vector[1].direccion,"cervantes 1220",51);
		vector[1].idL=1;
		*id=*id+1;
		*altas=*altas+1;

		vector[2].id=*id;
		vector[2].isEmpty=0;
		strncpy(vector[2].nombreEmpresa,"Danica",51);
		strncpy(vector[2].cuit,"12-33240336-8",15);
		strncpy(vector[2].direccion,"Lafayette 720",51);
		vector[2].idL=2;
		*id=*id+1;
		*altas=*altas+1;

		vector[3].id=*id;
		vector[3].isEmpty=0;
		strncpy(vector[3].nombreEmpresa,"CocaCola",51);
		strncpy(vector[3].cuit,"12-34979826-8",15);
		strncpy(vector[3].direccion,"Lagos 1997",51);
		vector[3].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[4].id=*id;
		vector[4].isEmpty=0;
		strncpy(vector[4].nombreEmpresa,"Pepsi",51);
		strncpy(vector[4].cuit,"12-11140336-8",15);
		strncpy(vector[4].direccion,"Burruchaga 220",51);
		vector[4].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[5].id=*id;
		vector[5].isEmpty=0;
		strncpy(vector[5].nombreEmpresa,"Manaos",51);
		strncpy(vector[5].cuit,"12-10940336-8",15);
		strncpy(vector[5].direccion,"La Carra 220",51);
		vector[5].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[6].id=*id;
		vector[6].isEmpty=0;
		strncpy(vector[6].nombreEmpresa,"Felizia",51);
		strncpy(vector[6].cuit,"12-34232136-8",15);
		strncpy(vector[6].direccion,"Italia 20",51);
		vector[6].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[7].id=*id;
		vector[7].isEmpty=0;
		strncpy(vector[7].nombreEmpresa,"La Compostela",51);
		strncpy(vector[7].cuit,"22-76543336-8",15);
		strncpy(vector[7].direccion,"La Trota 1098",51);
		vector[7].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[8].id=*id;
		vector[8].isEmpty=0;
		strncpy(vector[8].nombreEmpresa,"Cunninton",51);
		strncpy(vector[8].cuit,"12-34978954-1",15);
		strncpy(vector[8].direccion,"Puerredon 501",51);
		vector[8].idL=3;
		*id=*id+1;
		*altas=*altas+1;

		vector[9].id=*id;
		vector[9].isEmpty=0;
		strncpy(vector[9].nombreEmpresa,"Paladini",51);
		strncpy(vector[9].cuit,"12-34999886-8",15);
		strncpy(vector[9].direccion,"San Martin 1235",51);
		vector[9].idL=4;
		*id=*id+1;
		*altas=*altas+1;

		vector[10].id=*id;
		vector[10].isEmpty=0;
		strncpy(vector[10].nombreEmpresa,"Calchaqui",51);
		strncpy(vector[10].cuit,"14-34440336-8",15);
		strncpy(vector[10].direccion,"Sarmiento 9281",51);
		vector[10].idL=5;
		*id=*id+1;

		*altas=*altas+1;

		vector[11].id=*id;
		vector[11].isEmpty=0;
		strncpy(vector[11].nombreEmpresa,"Vienisima",51);
		strncpy(vector[11].cuit,"12-34123336-8",15);
		strncpy(vector[11].direccion,"Rotta 9478",51);
		vector[11].idL=5;
		*id=*id+1;
		*altas=*altas+1;
	}
}

