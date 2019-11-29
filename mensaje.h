#define TAM_MAX_DATA 4000 // 64000 - 12
#define VOTE_TAM_DATA 34
//Definicion de identificadores para operaciones permitidas:
#define suma 1
#define deposito 2

// Definicion del formato de mensaje
struct mensaje
{
	int messageType; //0= Solicitud, 1 = Respuesta
	unsigned int requestId; //Identificador del mensaje
	int operationId; //Identificador de la operación
	char arguments[TAM_MAX_DATA];
};

struct registro
{
	char celular[11];
	char CURP[19];
	char partido[4];
};
