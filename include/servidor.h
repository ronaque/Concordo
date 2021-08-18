#ifndef SERVIDOR_H
#define SERVIDOR_H

class Servidor
{
	/*
		TODO implementação dos atributos e métodos
	*/
public:
	int usuarioDonoId;
	std::string nome;
	std::string descricao;
	std::string codigoConvite;
	std::vector<CanalTexto> canaisTexto;
	std::vector<int> participantesIDs;
};

#endif
