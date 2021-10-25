
#ifndef INFORMES_H_
#define INFORMES_H_
#include "eCliente.h"
#include "ePedidos.h"

int ImprimirClientesYPedidos(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int ImprimirPedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int ImprimirPedidosProcesados(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int PedidosPendientesPorLocalidad(eCliente listC[],int tamC,ePedidos listP[],int tamP,eLocalidad listL[],int tamL);
int PromedioPP(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int ClienteMasPedidosPendientes(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam);
int ClienteMasPedidosCompletados(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam);
int ClienteMasPedidos(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam);





#endif /* INFORMES_H_ */
