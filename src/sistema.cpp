#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

//Criar função para saber se o usuário está logado;

bool compararUsuarios(vector<Usuario> usuarios)
{
  if (usuarios.size() == 0)
  {
    return false;
  }
  return true;
}

bool compararUsuariosLogados(map<int, std::pair<std::string, std::string>> usuariosLogados, int id)
{
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return false;
  }
  else
  {
    return true;
  }
}

string Sistema::retornarUsuarioPorID(int id)
{

  for (unsigned int i = 0; i < usuarios.size(); i++)
  {
    if (usuarios[i].id == id)
    {
      return usuarios[i].nome;
    }
  }
  return "";
}

/* COMANDOS */

//A1
string Sistema::quit()
{
  return "Saindo do Concordo";
}

string Sistema::create_user(const string email, const string senha, const string nome)
{
  if (usuarios.size() == 0)
  {
    Usuario newuser;
    newuser.email = email;
    newuser.senha = senha;
    newuser.nome = nome;
    newuser.id = indexIdUsuarios;
    indexIdUsuarios++;
    usuarios.push_back(newuser);
    return "Novo usuário criado";
  }
  else
  {
    for (unsigned int i = 0; i < usuarios.size(); i++)
    {
      if (email == usuarios[i].email)
        return "Usuário já existe!";
    }
    Usuario newuser;
    newuser.email = email;
    newuser.senha = senha;
    newuser.nome = nome;
    newuser.id = indexIdUsuarios;
    indexIdUsuarios++;
    usuarios.push_back(newuser);
    return "Novo usuário criado";
  }
}

string Sistema::login(const string email, const string senha)
{
  if (compararUsuarios(usuarios) == false)
  {
    return "Nenhum usuário criado";
  }
  else
  {
    for (unsigned int i = 0; i < usuarios.size(); i++)
    {
      if (email == usuarios[i].email && senha == usuarios[i].senha)
      {
        usuariosLogados.insert(make_pair(usuarios[i].id, make_pair("", "")));
        return "Logado como " + email;
      }
    }
    return "Login inválido";
  }
}

////////////////////////////////////// A2 //////////////////////////////////////

string Sistema::disconnect(int id)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    string email;
    for (unsigned int i = 0; i < usuarios.size(); i++)
    {
      if (id == usuarios[i].id)
      {
        email = usuarios[i].email;
      }
    }
    usuariosLogados.erase(usuariosLogados.find(id));
    return "Desconectando usuário " + email;
  }
}

string Sistema::create_server(int id, const string nome)
{
  Servidor novoServidor;

  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    if (servidores.size() == 0)
    {
      novoServidor.nome = nome;
      novoServidor.usuarioDonoId = id;
      servidores.push_back(novoServidor);
      return "Servidor criado";
    }
    else
    {
      for (unsigned int i = 0; i < servidores.size(); i++)
      {
        if (servidores[i].nome == nome)
        {
          return "Já existe um servidor com este nome";
        }
      }
      novoServidor.nome = nome;
      novoServidor.usuarioDonoId = id;
      servidores.push_back(novoServidor);
      return "Servidor criado";
    }
  }
}

string Sistema::set_server_desc(int id, const string nome, const string descricao)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == nome)
      {
        if (servidores[i].usuarioDonoId == id)
        {
          servidores[i].descricao = descricao;
          return "Descrição do servidor '" + nome + "' modificada!";
        }
        else
        {
          return "Usuário não é dono do servidor";
        }
      }
    }
    return "Servidor '" + nome + "' não existe";
  }
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == nome)
      {
        if (servidores[i].usuarioDonoId == id)
        {
          servidores[i].codigoConvite = codigo;
          if (codigo == "")
          {
            return "Código de convite do servidor '" + nome + "' removido";
          }
          else
          {
            return "Código de convite do servidor '" + nome + "' modificado";
          }
        }
        else
        {
          return "Usuário não é dono do servidor";
        }
      }
    }
    return "Servidor '" + nome + "' não existe";
  }
}

string Sistema::list_servers(int id)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    string lista;
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      cout << servidores[i].nome << endl;
    }
  }
  return "";
}

string Sistema::remove_server(int id, const string nome)
{
  //Usuário não está logado
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  //Usuário logado
  else
  {
    //Se não houver servidor criado
    if (servidores.size() == 0)
    {
      return "Nenhum servidor criado";
    }
    //Havendo servidores
    else
    {
      for (unsigned int i = 0; i < servidores.size(); i++)
      {
        //Se o servidor for o passado
        if (servidores[i].nome == nome)
        {
          //Se o dono do servidor é o id passado
          if (servidores[i].usuarioDonoId == id)
          {
            servidores.erase(servidores.begin() + i);
            for (unsigned int k = 0; k < usuariosLogados.size(); k++)
            {
              if (usuariosLogados[k].first == nome)
              {
                usuariosLogados[k].first = "";
                usuariosLogados[k].second = "";
              }
            }
            return "Servidor '" + nome + "' removido";
          }
          //Se o id não é do dono
          else
          {
            return "Usuário não é dono do servidor";
          }
        }
      }
      //Se não houver servidor com o nome passado
      return "Servidor '" + nome + "' não existe";
    }
  }
}

string Sistema::enter_server(int id, const string nome, const string codigo)
{
  //Se o usuário não está logado
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  //Se o usuário está logado
  else
  {
    //Se não há servidores
    if (servidores.size() == 0)
    {
      return "Nenhum servidor criado";
    }
    //Havendo servidores
    else
    {
      for (unsigned int i = 0; i < servidores.size(); i++)
      {
        //Servidor com o nome passado
        if (servidores[i].nome == nome)
        {
          //Descrição vazia
          if (servidores[i].descricao == "")
          {
            usuariosLogados[id].first = nome;
            servidores[i].participantesIDs.push_back(id);
            return "Entrou no servidor com sucesso";
          }
          //Descrição não vazia
          else
          {
            //Se o id é do dono do servidor
            if (servidores[i].usuarioDonoId == id)
            {
              servidores[i].participantesIDs.push_back(id);
              usuariosLogados[id].first = nome;
              return "Entrou no servidor com sucesso";
            }
            //Se não é o dono
            else
            {
              //Código de convite correto
              if (codigo == servidores[i].codigoConvite)
              {
                servidores[i].participantesIDs.push_back(id);
                usuariosLogados[id].first = nome;
                return "Entrou no servidor com sucesso";
              }
              //Código de convite incorreto
              else
              {
                return "Código de convite não existente";
              }
            }
          }
        }
      }
      //Se não houver servidor com o nome passado
      return "Servidor '" + nome + "' não existe";
    }
  }
}

string Sistema::leave_server(int id, const string nome)
{

  bool conectado = false;

  //Se o usuário não está logado
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  //Se o usuário está logado
  else
  {
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      //Verificação se o id está em algum servidor
      for (unsigned int l = 0; l < servidores[i].participantesIDs.size(); l++)
      {
        if (servidores[i].participantesIDs[l] == id)
        {
          conectado = true;
        }
      }

      //Servidor com o nome passado
      if (servidores[i].nome == nome)
      {
        for (unsigned int k = 0; k < servidores[i].participantesIDs.size(); k++)
        {
          //Se o id passado está conectado ao servidor
          if (servidores[i].participantesIDs[k] == id)
          {
            servidores[i].participantesIDs.erase(servidores[i].participantesIDs.begin() + k);
            usuariosLogados[id].first = "";
            usuariosLogados[id].second = "";
            return "Saindo do servidor '" + nome + "'";
          }
          //Se o id não está conectado ao servidor
          else
          {
            return "Você não está conectado ao servidor";
          }
        }
      }
      //Se não houver servidor com o nome passado
      else
      {
        return "Servidor '" + nome + "' não existe";
      }
    }
    //Caso não esteja conectado em nenhum servidor
    if (!conectado)
    {
      return "Você não em qualquer servidor";
    }
  }
}

string Sistema::list_participants(int id)
{
  string servidor;
  //Se o usuário não está logado
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  //Se o usuário está logado
  else
  {
    servidor = usuariosLogados[id].first;
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == servidor)
      {
        for (unsigned int k = 0; k < servidores[i].participantesIDs.size(); k++)
        {
          int id;
          id = servidores[i].participantesIDs[k];
          for (unsigned int l = 0; l < usuarios.size(); l++)
          {
            if (usuarios[l].id == id)
            {
              cout << usuarios[l].nome;
            }
          }
        }
      }
    }
    return "";
  }
}

////////////////////////////////////// B1 //////////////////////////////////////

string Sistema::list_channels(int id)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    string servidor;
    servidor = usuariosLogados[id].first;
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == servidor)
      {
        for (unsigned int k = 0; k < servidores[i].canaisTexto.size(); k++)
        {
          cout << servidores[i].canaisTexto[k].nome << endl;
        }
      }
    }
    return "";
  }
}

string Sistema::create_channel(int id, const string nome)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    string servidor;
    servidor = usuariosLogados[id].first;
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == servidor)
      {
        if (servidores[i].canaisTexto.size() == 0)
        {
          CanalTexto novoCanalTexto;
          novoCanalTexto.nome = nome;
          servidores[i].canaisTexto.push_back(novoCanalTexto);
          return "Canal de texto '" + nome + "' criado";
        }
        else
        {
          for (unsigned int k = 0; k < servidores[i].canaisTexto.size(); k++)
          {
            if (servidores[i].canaisTexto[k].nome == nome)
            {
              return "Já existe um canal de texto com esse nome";
            }
          }
          CanalTexto novoCanalTexto;
          novoCanalTexto.nome = nome;
          servidores[i].canaisTexto.push_back(novoCanalTexto);
          return "Canal de texto '" + nome + "' criado";
        }
      }
    }
  }
}

string Sistema::enter_channel(int id, const string nome)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    string servidor;
    servidor = usuariosLogados[id].first;
    for (unsigned int i = 0; i < servidores.size(); i++)
    {
      if (servidores[i].nome == servidor)
      {
        for (unsigned int k = 0; k < servidores[i].canaisTexto.size(); k++)
        {
          if (servidores[i].canaisTexto[k].nome == nome)
          {
            usuariosLogados[id].second = nome;
            return "Entrou no canal '" + nome + "'";
          }
        }
        return "Canal '" + nome + "' não existe";
      }
    }
  }
}

string Sistema::leave_channel(int id)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    usuariosLogados[id].second = "";
    return "Saindo do canal";
  }
}

////////////////////////////////////// B2 //////////////////////////////////////

string Sistema::send_message(int id, const string mensagem)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    if (usuariosLogados[id].first != "" && usuariosLogados[id].second != "")
    {

      for (unsigned int i = 0; i < servidores.size(); i++)
      {
        if (usuariosLogados[id].first == servidores[i].nome)
        {
          for (unsigned int k = 0; k < servidores[i].canaisTexto.size(); k++)
          {
            if (usuariosLogados[id].second == servidores[i].canaisTexto[k].nome)
            {
              Mensagem novaMensagem;
              novaMensagem.conteudo = mensagem;
              novaMensagem.enviadaPor = id;

              setlocale(LC_ALL, "Portuguese_Brazil");
              time_t data_hora_segundos;
              struct tm *timeinfo;
              time(&data_hora_segundos);
              timeinfo = localtime(&data_hora_segundos);
              char dataFormatada[80];
              strftime(dataFormatada, 80, "<%d/%m/%Y - %R>", timeinfo);
              string str(dataFormatada);
              novaMensagem.dataHora = str;

              servidores[i].canaisTexto[k].mensagens.push_back(novaMensagem);
              return "";
            }
          }
        }
      }
    }
  }
}

string Sistema::list_messages(int id)
{
  if (compararUsuariosLogados(usuariosLogados, id) == false)
  {
    return "Usuário não está conectado";
  }
  else
  {
    if (usuariosLogados[id].first != "" && usuariosLogados[id].second != "")
    {

      for (unsigned int i = 0; i < servidores.size(); i++)
      {
        if (usuariosLogados[id].first == servidores[i].nome)
        {
          for (unsigned int k = 0; k < servidores[i].canaisTexto.size(); k++)
          {
            if (usuariosLogados[id].second == servidores[i].canaisTexto[k].nome)
            {
              if (servidores[i].canaisTexto[k].mensagens.size() == 0)
              {
                return "Sem mensagens para exibir";
              }
              else
              {
                for (unsigned int l = 0; l < servidores[i].canaisTexto[k].mensagens.size(); l++)
                {
                  string usuario = retornarUsuarioPorID(servidores[i].canaisTexto[k].mensagens[l].enviadaPor);

                  cout << usuario << servidores[i].canaisTexto[k].mensagens[l].dataHora << ": " << servidores[i].canaisTexto[k].mensagens[l].conteudo << endl;
                }
                return "";
              }
            }
          }
        }
      }
    }
  }
  return "";
}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
