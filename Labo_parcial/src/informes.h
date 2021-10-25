
#ifndef INFORMES_H_
#define INFORMES_H_
#include "eCliente.h"
#include "ePedidos.h"

int ImprimirClientesYPedidos(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int ImprimirPedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int ImprimirPedidosProcesados(ePedidos listP[],int tamP,eCliente listC[],int tamC);
int PedidosPendientesPorLocalidad(eCliente listC[],int tamC,ePedidos listP[],int tamP);
int PromedioPP(ePedidos listP[],int tamP,eCliente listC[],int tamC);


#endif /* INFORMES_H_ */
