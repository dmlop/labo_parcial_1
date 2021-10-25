
#ifndef ECLIENTE_H_
#define ECLIENTE_H_

typedef struct{
	int id;
	char nombreEmpresa[51];
	char cuit[15];
	char direccion[51];
	char localidad[51];
	int isEmpty;
}eCliente;

void ClienteInit(eCliente vector[], int tam);
void AgregarCliente(eCliente vector[],int tam,eCliente aux,int* id);
int CargarCliente(eCliente vector[],int tam,eCliente aux);
int BuscarEmptyCliente(eCliente vector[],int tam);
int BuscarClientePorId(eCliente vector[],int tam,int* auxId);
int ImprimirClientes(eCliente vector[],int tam);

//----------------------------------------
void ClientesTesteo(eCliente vector[],int *id,int* altas,int actividad);



#endif /* ECLIENTE_H_ */
