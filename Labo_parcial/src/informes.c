#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"
#include "ePedidos.h"
#include "eCliente.h"
#include "eLocalidad.h"
#include "eContador.h"
#include <string.h>
/// @brief imprime los datos de los clientes con pedidos
/// 		pendientes y la cantidad de pedidos pendientes
///
/// @param listP
/// @param tamP
/// @param listC
/// @param tamC
/// @return
int ImprimirClientesYPedidos(ePedidos listP[],int tamP,eCliente listC[],int tamC,eLocalidad listL[],int tamL){
	int retorno;
	int cPendiente;
	retorno=0;
	cPendiente=0;
	printf("==ID====NOMBRE===============CUIT===========DIRECCION=======LOCALIDAD====PEDIDOS==\n");
	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			for(int j=0;j<tamP;j++){
				if(listP[j].isEmpty==0&&listP[j].idC==listC[i].id&&listP[j].estado==0){
					cPendiente++;
				}
			}
			for(int k=0;k<tamL;k++){
				if(listC[i].idL==listL[k].id){
					printf("  %-2d  %-16s  %-16s  %-16s  %-15s  %-2d\n",listC[i].id,
					listC[i].nombreEmpresa,listC[i].cuit,
					listC[i].direccion,listL[k].localidad,cPendiente);
					cPendiente=0;
					retorno=1;
				}
			}

		}
	}
	printf("===================================================================================\n");

	return retorno;
}
/// @brief imprime el cuit y direccion del cliente y los kilos a procesar en cada pedido
///
/// @param listP
/// @param tamP
/// @param listC
/// @param tamC
/// @return
int ImprimirPedidosPendientes(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	retorno=0;
	printf("=====CUIT===========DIRECCION=============KILOS==\n");
	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			for(int j=0;j<tamP;j++){
				if(listC[i].id==listP[j].idC&&listP[j].estado==0){
					printf("%-15s   %-17s       %-5i\n",listC[i].cuit,listC[i].direccion,listP[j].kilos);
				}
			}
		}
	}


	return retorno;
}
/// @brief  imprime el cuit, direccion, del cliente y los
/// plasticos procesados de dicho cliente en cada pedido
///
/// @param listP
/// @param tamP
/// @param listC
/// @param tamC
/// @return
int ImprimirPedidosProcesados(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	retorno=0;
	printf("=====CUIT===========DIRECCION==========HDPE==LDPE====PP====DESECHOS===\n");
	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			for(int j=0;j<tamP;j++){
				if(listC[i].id==listP[j].idC&&listP[j].estado==1){
					printf(" %-15s %-17s     %-4i  %-4i   %-4i     %-4i\n",
							listC[i].cuit,listC[i].direccion,listP[j].HDPE,
							listP[j].LDPE,listP[j].PP,listP[j].desechos);
				}
			}
		}
	}
	return retorno;
}
/// @brief pide al usuario que ingrese una localidad y
/// luego muestra cuantos pedidos pendientes tiene esa dicha localidad
///
/// @param listC
/// @param tamC
/// @param listP
/// @param tamP
/// @return
int PedidosPendientesPorLocalidad(eCliente listC[],int tamC,ePedidos listP[],int tamP,eLocalidad listL[],int tamL){
	int retorno;
	char localidad[20];
	int contador;
	retorno=0;
	contador=0;

	if(GetCharLNPC(localidad, 20, "ingrese una Localidad: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n", 4)){
		for(int i=0;i<tamC;i++){
			for(int k=0;k<tamL;k++){
				if(listC[i].idL==listL[k].id&&strcmp(listL[k].localidad,localidad)==0){
					for(int j=0;j<tamP;j++){
						if(listC[i].id==listP[j].idC&&listP[j].estado==0){
							contador++;
							retorno=1;
					}
				}
			}
		}
	}
	if(contador!=0){
		printf("==========================================\n"
				"||Pedidos pendientes en %s: %d\n"
				"==========================================\n",localidad,contador);
	}
	return retorno;
}
/// @brief imprime los clientes y el promedio de plastico del
/// tipo PP que cada uno proceso en total
///
/// @param listP
/// @param tamP
/// @param listC
/// @param tamC
/// @return
int PromedioPP(ePedidos listP[],int tamP,eCliente listC[],int tamC){
	int retorno;
	int contador;
	int acumulador;
	float promedio;
	int bandera;
	retorno=0;
	bandera=0;
	contador=0;
	acumulador=0;

	for(int i=0;i<tamC;i++){
		if(listC[i].isEmpty==0){
			acumulador=0;
			contador=0;
			promedio=0;
			for(int j=0;j<tamP;j++){
				if(listC[i].id==listP[j].idC&&listP[j].estado==1){
					retorno=1;
					contador++;
					acumulador=acumulador+listP[j].PP;
					if(bandera==0){
						bandera=1;
						printf("==CLIENTE======PROMEDIO=PP==\n");
					}
				}
			}
			if(contador>0){
				promedio=(float)acumulador/contador;
			}

			if(promedio!=0){
				printf("%-15s  %-5.2f\n",listC[i].nombreEmpresa,promedio);
			}
		}
	}
	return retorno;
}
int ClienteMasPedidosPendientes(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam){
	int retorno;
	eContador cPedidos[100];
	for(int c=0;c<100;c++){
		cPedidos[c].id=-1;
	}

	for(int i=0;i<tamC;i++){
		for(int j=0;j<tamP;j++){
			if(vectorC[i].id==vectorP[j].idC&&vectorP[j].estado==0){
				cPedidos[i].contador++;
				cPedidos[i].id=vectorC[i].id;
			}
		}
	}
	for(int p=0;p<tamC;p++){
		for(int u=0;u<100;u++){
			if(vectorC[p].id==cPedidos[u].id){
				printf("%s -- %d",vectorC[p].nombreEmpresa,cPedidos[u].contador);
			}
		}
	}

	retorno=0;
	return retorno;
}
int ClienteMasPedidosCompletados(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam){
	int retorno;
	eContador cPedidos[100];
	for(int c=0;c<100;c++){
		cPedidos[c].id=-1;
	}

	for(int i=0;i<tamC;i++){
		for(int j=0;j<tamP;j++){
			if(vectorC[i].id==vectorP[j].idC&&vectorP[j].estado==0){
				cPedidos[i].contador++;
				cPedidos[i].id=vectorC[i].id;
			}
		}
	}
	for(int p=0;p<tamC;p++){
		for(int u=0;u<100;u++){
			if(vectorC[p].id==cPedidos[u].id){
				printf("%s -- %d",vectorC[p].nombreEmpresa,cPedidos[u].contador);
			}
		}
	}

	retorno=0;
	return retorno;
}
int ClienteMasPedidos(eCliente vectorC[],int tamC,ePedidos vectorP[],int tam){
	int retorno;
	eContador cPedidos[100];
	for(int c=0;c<100;c++){
		cPedidos[c].id=-1;
	}

	for(int i=0;i<tamC;i++){
		for(int j=0;j<tamP;j++){
			if(vectorC[i].id==vectorP[j].idC){
				cPedidos[i].contador++;
				cPedidos[i].id=vectorC[i].id;
			}
		}
	}
	for(int p=0;p<tamC;p++){
		for(int u=0;u<100;u++){
			if(vectorC[p].id==cPedidos[u].id){
				printf("%s -- %d",vectorC[p].nombreEmpresa,cPedidos[u].contador);
			}
		}
	}

	retorno=0;
	return retorno;
}
