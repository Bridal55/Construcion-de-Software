#include "Manager.h"

using namespace std;

Manager::Manager()
{
    listSeats = new Seat[12];
}


string Manager::getName()
{
    return name;
}

void Manager::reserveNum(int n, Client c)
{
    if(listSeats[n-1]->reservation)
    {
        cout << "Este asiento ya esta reservado";
    }
    else
    {
        cout << "El administrador: "<< name<< "\n";
        cout << "Asiento reservado: "<< n << " de tipo: "<<listSeats[n-1]->t <<" para: " << c.getName()<< "\n";
        cout << "Costo: "<< listSeats[n-1]->cost;
        listSeats[n-1]-> reservation = true;
        listSeats[n-1]-> client =c;
    }
}

void Manager::reserveType(string t, Client c)
{
    for (int i = 0; i < 12; i++)
    {
       if (listSeats[i]->reservation != true)
       {
        if(listSeats[i]->type == t)
        {
        cout << "El administrador: "<< name<< "\n";
        cout << "Asiento de tipo: "<<listSeats[i]->type <<"fue reservado por el cliente: " << c.getName()<< "\n";
        cout << "Costo:" <<listSeats[i]->cost << "\n";
        listSeats[i]->reservation = true;
        listSeats[i]->client =c;
        }
       }
       else
       {
        cout << "No hay asientos disponibles "<< "\n";
       }
    
    
    }
     
}

void Manager::cancelReserve(int n)
{
    cout << "Se cancelo la reserva del asiento:"<< n <<"\n";
    listSeats[num-1]->reservation = false;
    listSeats[num-1]->client = Client();
}