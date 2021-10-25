

#ifndef EPEDIDOS_H_
#define EPEDIDOS_H_
#include "eCliente.h"
#include "eLocalidad.h"

typedef struct{
	int id;
	int idC;
	int estado;
	int isEmpty;
	int kilos;
	int HDPE;
	int LDPE;
	int PP;
	int desechos;
}ePedidos;

void PedidosInit(ePedidos vector[],int tam);
void AgregarPedido(ePedidos vector[],int tam,ePedidos aux,int* id, int auxId);
int CargarPedido(ePedidos vector[],int tam,ePedidos aux);
int BuscarEmptyPedidos(ePedidos vector[],int tam);
int ImprimirPedidos(ePedidos vector[],int tam);
int BuscarPedidoPorId(ePedidos vector[],int tam,int* auxId);
int ProcesarPedido(ePedidos* pedido);

//-------------------
void PedidosTesteo(ePedidos vector[],int *id,int actividad);


#endif /* EPEDIDOS_H_ */
