/*DANIEL MANRESA 34940336
1) Alta de cliente: Se da de alta un cliente con nombre de la empresa, cuit dirección y
localidad. Se
generará un ID único para este cliente que se imprimirá por pantalla si el alta es correcta.
2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá cambiar la dirección
y la localidad.
3) Baja de cliente: Se ingresa el ID del cliente. Luego se preguntará si se quiere confirmar
la eliminación.
4) Crear pedido de recolección: Se imprimirán los clientes por pantalla y se pedirá
que se ingrese el ID de un cliente existente y la cantidad de kilos totales que se
recolectarán del cliente. Se generará un ID para el pedido y el mismo quedará en
estado “Pendiente” hasta que se obtengan los residuos del cliente y se trasladen
a la empresa.
5) Procesar residuos: Se elegirá esta opción cuando los residuos que volvieron a
la empresa se hayan procesado y separado en los diferentes tipos de plástico que
la empresa puede reciclar. Se imprimirán los pedidos por pantalla y se pedirá
seleccionar el ID de uno de ellos. Luego deberán ingresarse la cantidad de kilos
de plástico de cada uno de los 3 tipos que la empresa puede procesar que se
obtuvieron de los kilos totales que se recolectaron. Por último, se marcará
al pedido como “Completado”.
6) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus datos junto
con la cantidad de “pedidos de recolección” que posee en estado “Pendiente”.
7) Imprimir Pedidos pendientes: Se imprimirá una lista de los pedidos que se
encuentren en estado “Pendiente” con la información: Cuit del cliente, dirección
del cliente, cantidad de kilos a recolectar.
8) Imprimir Pedidos procesados: Se imprimirá una lista de los pedidos que se
encuentren en estado “Completado” con la información: Cuit del cliente, dirección
del cliente, cantidad de kilos reciclados de cada tipo de plástico.
9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para dicha
localidad.
10) Cantidad de kilos de polipropileno reciclado promedio por cliente.
(kilos totales / cantidad de clientes)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "biblioteca.h"
#include "eCliente.h"
#include "ePedidos.h"
#include "informes.h"
#include "eLocalidad.h"
#include "menu.h"

int main(void) {
	setbuf(stdout,NULL);
	int opcionMenu;
	int opcionMenuModificacion;
	int opcionMenuInformes;
	int idCliente;
	int idPedido;
	int idLocalidad;
	int auxPos;
	int auxId;
	int altas;
	char sOrN[3];
	eCliente listCliente[100];
	eCliente auxCliente;
	ePedidos listPedidos[1000];
	ePedidos auxPedido;
	eLocalidad listLocalidad[100];
	eLocalidad auxLocalidad;
	idCliente=1;
	idPedido=1;
	idLocalidad=1;
	altas=0;
	ClienteInit(listCliente,100);
	PedidosInit(listPedidos,1000);
	LocalidadInit(listLocalidad,100);

	ClientesTesteo(listCliente,&idCliente,&altas,1);
	PedidosTesteo(listPedidos,&idPedido,1);

	do{
		Menu(&opcionMenu);

		switch(opcionMenu){
		case 1://ALTA CLIENTE
			system("cls");
			if(altas!=100){
				AgregarCliente(listCliente,100,auxCliente,&idCliente,listLocalidad,100,auxLocalidad,&idLocalidad);
				altas++;
			}
			else{
				printf("============PROGRAMA=LLENO============\n");
			}
			break;
		case 2://MODIFICAR DATOS
			system("cls");
			auxPos=BuscarClientePorId(listCliente,100,&auxId);
			if(auxPos!=-1){
				MenuModificacion(&opcionMenuModificacion);
				switch(opcionMenuModificacion){
				case 1:

					if(GetCharLNPC(auxCliente.direccion, 51, "Ingrese la Nueva Direccion de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4)){
						strncpy(listCliente[auxPos].direccion,auxCliente.direccion,sizeof(listCliente[auxPos].direccion));
					}
					else{
						printf("\nERROR CODE 1\n");
					}
					break;
				case 2:
					if(GetCharLNPC(auxLocalidad.localidad, 51, "Ingrese la Nueva Localidad de la Empresa: ","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n",4)){
						for(int i=0;i<100;i++){
							if(listLocalidad[i].isEmpty==0&&strcmp(auxLocalidad.localidad,listLocalidad[i].localidad)){
								listCliente[auxPos].idL=listLocalidad[i].id;
								break;
							}
							else{
								if(listLocalidad[i].isEmpty==1){
									listLocalidad[i].id=idLocalidad;
									listLocalidad[i].isEmpty=0;
									strncpy(listLocalidad[i].localidad,auxLocalidad.localidad,51);
									listCliente[auxPos].idL=listLocalidad[i].id;
									idLocalidad++;
								}
							}
						}
					}
					else{
						printf("\nERROR CODE 1\n");
					}
					break;
				}
			}
			else{
				printf("===NO=EXISTE=EL=CLIENTE===\n");
			}
			break;
		case 3://BAJA DE CLIENTE
			system("cls");
			if(altas==0||idCliente==0){
				printf("==NO=HAY=CLIENTES=DISPONIBLES==\n");
				break;
			}
			auxPos=BuscarClientePorId(listCliente,100,&auxId);
			if(auxPos!=-1){
				do{
					printf("Cliente ==== %s\n", listCliente[auxPos].nombreEmpresa);
					if(GetCharSorN(sOrN,"¿Esta seguro de dar de baja este cliente? <s/n>","ERROR DATO INVALIDO! VUELVA A INTENTARLO!\n")){
						if(sOrN[0]=='S'){
							listCliente[auxPos].isEmpty=1;
							altas--;
							printf("=========BAJA=COMPLETADA=========\n");

						}
						else{
							printf("=========BAJA=CANCELADA=========\n");
							break;
						}
					}
				}while(sOrN[0]!='S'&&sOrN[0]!='N');
			}
			break;
		case 4://CREAR PEDIDO DE RECOLECCION
			system("cls");
			if(altas==0||idCliente==0){
				printf("==NO=HAY=CLIENTES=DISPONIBLES==\n");
				break;
			}
			if(ImprimirClientes(listCliente, 100)){
				auxPos=BuscarClientePorId(listCliente,100,&auxId);
				if(auxPos!=-1){
					AgregarPedido(listPedidos, 1000,auxPedido, &idPedido, auxId);
				}

			}
			break;
		case 5://PROCESAR RESIDUOS
			system("cls");
			if(altas==0||idPedido==0){
				printf("==NO=HAY=PEDIDOS=DISPONIBLES==\n");
				break;
			}
			if(ImprimirPedidos(listPedidos,1000)){
				auxPos=BuscarPedidoPorId(listPedidos,1000,&auxId);
				if(listPedidos[auxPos].estado==1){
					printf("Ese pedido ya esta Procesado");
					auxPos=-2;
				}

				if(auxPos>=0){
					if(ProcesarPedido(&listPedidos[auxPos])){
						printf("====PEDIDO=PROCESADO====\n");
					}
				}
			}
			break;
		case 6://MENU INFORMES
			system("cls");
			if(altas==0||idPedido==0){
				printf("==NO=HAY=PEDIDOS=DISPONIBLES==\n");
				break;
			}
			do{
				MenuInformes(&opcionMenuInformes);
				switch(opcionMenuInformes){
				case 1://IMPRIMIR CLIENTES Y SUS PEDIDOS
					system("cls");
					if(ImprimirClientesYPedidos(listPedidos, 1000, listCliente, 100)){
					}
					else{

					}
					break;
				case 2://IMPRIMIR PEDIDOS PENDIENTES
					system("cls");
					if(ImprimirPedidosPendientes(listPedidos, 1000, listCliente, 100)){
					}
					else{

					}
					break;
				case 3://IMPRIMIR PEDIDOS PROCESADOS
					system("cls");
					if(ImprimirPedidosProcesados(listPedidos, 1000, listCliente, 100)){
					}
					else{

					}
					break;
				case 4://IMPRIMIR PEDIDOS PENDIENTES POR LOCALIDAD
					system("cls");
					if(PedidosPendientesPorLocalidad(listCliente, 100,listPedidos, 1000,listLocalidad,100)==0){
						printf("=NO=HAY=PEDIDOS=PENDIENTES=\n");
					}
					break;
				case 5://IMPRIMIR PROMEDIO DE POLIPROPILENO RECICLADO
					system("cls");
					if(PromedioPP(listPedidos, 1000,listCliente, 100)==0){
						printf("=NO=HAY=PEDIDOS=PROCESADOS=\n");
					}
					break;
				case 6://ClienteMasPedidosPendientes
					system("cls");
					if(ClienteMasPedidosPendientes(listCliente, 100,listPedidos, 1000)==0){
						printf("=NO=HAY=PEDIDOS=PROCESADOS=\n");
					}
					break;
				case 7://ClienteMasPedidosCompletados
					system("cls");
					if(ClienteMasPedidosCompletados(listCliente, 100,listPedidos, 1000)==0){
						printf("=NO=HAY=PEDIDOS=PROCESADOS=\n");
					}
					break;
				case 8://ClienteMasPedidos
					if(ClienteMasPedidos(listCliente, 100,listPedidos, 1000)==0){
						printf("=NO=HAY=PEDIDOS=PROCESADOS=\n");
					}
					break;
				case 9:
					break;
				case 10:
					break;
			}
			}while(opcionMenuInformes!=9);
			break;
		case 7://FIN PROGRAMA
			system("cls");
			Firma();
			break;
		}
	}while(opcionMenu!=7);
	return EXIT_SUCCESS;
}
